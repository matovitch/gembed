#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "node.hpp"

#include <unordered_set>
#include <cstddef>
#include <memory>
#include <utility>

template <typename P,
          typename W,
          typename H>
struct Graph
{
    Graph() {}

    template <typename... Args>
    std::shared_ptr<Node<P, W, H>> createNode(Args&&... args)
    {
        std::shared_ptr<Node<P, W, H>> n(std::make_shared<Node<P, W, H>>(args...));

        _nodes.insert(n);
        
        return n;
    }

    void destroyNode(const std::shared_ptr<Node<P, W, H>>& n)
    {
        _nodes.erase(n);
    }

    void removeEdge(const std::shared_ptr<Node<P, W, H>>& lhs,
                    const std::shared_ptr<Node<P, W, H>>& rhs)
    {
        lhs->removeNeighbour(&*rhs);
    }

    void addEdge(const std::shared_ptr<Node<P, W, H>>& lhs,
                 const std::shared_ptr<Node<P, W, H>>& rhs,
                 const W weight)
    {
        lhs->addNeighbour(&*rhs, weight);
    }

    void updateEdge(const std::shared_ptr<Node<P, W, H>>& lhs,
                    const std::shared_ptr<Node<P, W, H>>& rhs,
                    const W weight)
    {
        lhs->updateNeighbour(&*rhs, weight);
    }

    template <typename F, typename... Args>
    void transformEdge(const std::shared_ptr<Node<P, W, H>>& lhs,
                       const std::shared_ptr<Node<P, W, H>>& rhs,
                       const F& functor,
                       Args&&... args)
    {
        lhs->transformNeighbour(&*rhs, functor, args...);
    }

    std::unordered_set<std::shared_ptr<Node<P, W, H>>,
                       NodePtrHasher             <H>> _nodes;
};

#endif // __GRAPH_H__
