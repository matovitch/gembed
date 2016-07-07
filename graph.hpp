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
    static Node<P, W, H>* toNode(const std::size_t id)
    {
        return reinterpret_cast<Node<P, W, H>*>(id);
    }

    static std::size_t toId(const Node<P, W, H>* const node)
    {
        return reinterpret_cast<std::size_t>(node);
    }

    Graph() {}

    template <typename... Args>
    std::size_t createNode(Args&&... args)
    {
        std::unique_ptr<Node<P, W, H>> n(std::make_unique<Node<P, W, H>>(args...));

        const Node<P, W, H>* const node = &*n;

        _nodes.insert(std::move(n));
        
        return toId(node);
    }

    void destroyNode(const std::size_t id)
    {
        _nodes.erase(toNode(id));
    }

    void removeEdge(const std::size_t lhs,
                    const std::size_t rhs)
    {
        toNode(lhs)->removeNeighbour(toNode(rhs));
    }

    void addEdge(const std::size_t lhs,
                 const std::size_t rhs,
                 const W weight)
    {
        toNode(lhs)->addNeighbour(toNode(rhs), weight);
    }

    bool hasEdge(const std::size_t lhs,
                 const std::size_t rhs) const
    {
        return toNode(lhs)->hasNeighbour(toNode(rhs));
    }

    void updateEdge(const std::size_t lhs,
                    const std::size_t rhs,
                    const W weight)
    {
        toNode(lhs)->updateNeighbour(toNode(rhs), weight);
    }

    template <typename F, typename... Args>
    void transformEdge(const std::size_t lhs,
                       const std::size_t rhs,
                       const F& functor,
                       Args&&... args)
    {
        toNode(lhs)->transformNeighbour(toNode(rhs), functor, args...);
    }

    std::unordered_set<std::unique_ptr<Node<P, W, H>>,
                       NodePtrHasher             <H>,
                       NodePtrEqual>                   _nodes;
};

#endif // __GRAPH_H__
