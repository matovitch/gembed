#ifndef __NODE_H__
#define __NODE_H__

#include <unordered_map>
#include <cstddef>
#include <utility>

template <typename H>
struct NodePtrHasher
{
    template <typename T>
    std::size_t operator()(const T& n) const
    {
        return H()(n->_point);
    }
};

struct NodePtrEqual
{
    template <typename T>
    bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs->_point == rhs->_point;
    }
};

template <typename P,
          typename W, 
          typename H>
struct Node
{
    typedef std::unordered_map<const Node<P, W, H>*, 
                               W,
                               NodePtrHasher<H>,
                               NodePtrEqual> Neighbourhood;

    Node() = delete;

    template <typename... Args>
    Node(Args&&... args) : _point(args...) {}

    void addNeighbour(const Node<P, W, H>* nodePtr, const W weight)
    {
        _neighbourhood.insert(std::pair<const Node<P, W, H>*, W>(nodePtr, weight));
    }

    void removeNeighbour(const Node<P, W, H>* nodePtr)
    {
        _neighbourhood.erase(nodePtr);
    }

    void updateNeighbour(const Node<P, W, H>* nodePtr, const W weight)
    {
        _neighbourhood.at(nodePtr) = weight;
    }

    template <typename F, typename... Args>
    void transformNeighbour(const Node<P, W, H>* nodePtr, const F& functor, Args&&... args)
    {
        auto& weight = _neighbourhood.at(nodePtr);
        weight = functor(weight, args...);
    }

    const Neighbourhood& neighbourhood() const { return _neighbourhood; }

    const P _point;

    Neighbourhood _neighbourhood;
};

#endif // __NODE_H__