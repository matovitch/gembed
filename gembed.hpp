#ifndef __GEMBED_H__
#define __GEMBED_H__

#include "euclidian_vector.hpp"
#include "graph.hpp"
#include "node.hpp"

#include <unordered_map>
#include <utility>
#include <random>
#include <cmath>

template <typename P,
          typename W,
          typename H,
          typename R,
          typename T, 
          unsigned N>
struct Gembed
{

    Gembed(std::random_device::result_type seed) : 
        _normalDistrib(0.0, 1.0)
    {
        _urgn.seed(seed);
    }

    void initDilatation()
    {
        _scale = 0.0;

        unsigned weight = 0;

        for (const auto& e : _embedding)
        {
            for (const auto& n: e.first->neighbourhood())
            {
                _scale += distance(_embedding.at(n.first), e.second) / n.second;
                weight++;
            }
        }

        _scale /= weight;
    }

    EuclidianVector<T, N> randomPoint()
    {
        EuclidianVector<T, N> rp;

        for (unsigned i = 0; i < N; i++)
        {
            rp._coordinates[i] = _normalDistrib(_urgn);
        }

        return rp;
    }

    void init(const Graph<P, W, H>& graph)
    {
        _embedding.clear();

        for (const auto& n: graph._nodes)
        {
            _embedding.insert(
                std::pair<const Node<P, W, H>*, 
                          EuclidianVector<T, N>>
                    (&*n, randomPoint()));
        }

        initDilatation();
    }

    void normalize()
    {
        const unsigned size = _embedding.size();
        EuclidianVector<T, N> mean;

        mean.setAsOrigin();

        for (const auto& e : _embedding)
        {
            mean += e.second;
        }

        mean /= size;

        T deviation = 0;

        for (const auto& e : _embedding)
        {
            deviation += distance(mean, e.second);
        }

        deviation /= size;

        deviation = std::sqrt(deviation);

        for (auto& e : _embedding)
        {
            e.second -= mean;
            e.second /= deviation;
        }
    }

    void update(const Graph<P, W, H>& graph,
                const T learn,
                const T blow)
    {
        std::unordered_map<const Node<P, W, H>*, 
                           EuclidianVector<T, N>> embedding;

        unsigned weight = 0;
        T newScale = 0.0;

        for (const auto& e : _embedding)
        {
            EuclidianVector<T, N> speed;
            speed.setAsOrigin();

            for (const auto& n: e.first->neighbourhood())
            {
                const T dilatation = distance(_embedding.at(n.first), e.second) /
                                     n.second;

                newScale += dilatation;
                weight++;

                speed +=  (std::log(dilatation / _scale) + blow) * 
                          (_embedding.at(n.first) - e.second);
            }

            embedding.insert(
                std::pair<const Node<P, W, H>*, 
                          EuclidianVector<T, N>>
                    (e.first, e.second + learn * speed));
        }

        _scale = newScale / weight;

        _embedding = embedding;

        normalize();
    }

    void operator() (const Graph<P, W, H>& graph,
                     const unsigned steps,
                     const T learn,
                     const T blow)
    {
        init(graph);

        for (unsigned i = steps; i > 0; i--)
        {
            update(graph, learn, i * blow / T(steps));
        }

        for (unsigned i = 0; i < steps; i++)
        {
            update(graph, learn, 0.0);
        }
    }

    T _scale;

    std::unordered_map<const Node<P, W, H>*, 
                       EuclidianVector<T, N>> _embedding;

    std::normal_distribution<T> _normalDistrib;

    R _urgn;

};

#endif  // __GEMBED_H__
