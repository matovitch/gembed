#include "gembed.hpp"
#include "graph.hpp"

#include <iostream>
#include <cstddef>
#include <random>


struct Point
{
    Point(const char value) : _value(value) {}

    const char _value;
};

struct PointHasher
{
    std::size_t operator() (const Point& point) const
    {
        return point._value;
    }
};

bool operator== (const Point& lhs, const Point& rhs)
{
    return lhs._value == rhs._value;
}

constexpr unsigned EMBEDDING_DIM = 2;

int main()
{
    Graph<Point, float, PointHasher> g;

    auto a = g.createNode('A');
    auto b = g.createNode('B');
    auto c = g.createNode('C');
    auto d = g.createNode('D');

    g.addEdge(a, b, 1.0);
    g.addEdge(b, a, 1.0);
    g.addEdge(a, c, 1.0);
    g.addEdge(c, a, 1.0);
    g.addEdge(c, b, 1.0);
    g.addEdge(b, c, 1.0);
    g.addEdge(a, d, 1.0);
    g.addEdge(d, a, 1.0);

    Gembed<Point, float, PointHasher,
           std::default_random_engine,
           float,
           EMBEDDING_DIM> gembed((std::random_device())());

    const unsigned steps = 10;
    const float    learn =  0.2;
    const float    blow  =  3.0;

    gembed(g, steps, learn, blow);

    for (const auto& e: gembed._embedding)
    {
        for (const auto& f: gembed._embedding)
        {
            const char ec = e.first->_point._value;
            const char fc = f.first->_point._value;

            if (ec < fc)
            {
                std::cout << ec << "-" << fc << ": " << distance(e.second, f.second) << std::endl;
            }
        }        
    }

    return 0;
}
