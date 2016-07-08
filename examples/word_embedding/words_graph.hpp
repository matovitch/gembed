#ifndef __WORDS_GRAPH_H__
#define __WORDS_GRAPH_H__

#include "words_occurences.hpp"
#include "graph.hpp"
#include "node.hpp"

#include <unordered_set>

template <typename W,
          typename D>
struct WordGraph
{
    WordGraph(const WordsOccurences& wordOccurences,
              const unsigned kernelSize) :
        _wordOccurences(wordOccurences),
        _kernelSize(kernelSize)
    {
        for (const auto& wo : _wordOccurences())
        {
            _wordToNodes[wo] = _wordGraph.createNode(wo.first);
        }
    }

    void modifyEdge(const Word iWord,
                    const Word jWord,
                    const unsigned j)
    {
        if (!_wordGraph.hasEdge(_wordToNodes[iWord],
                                _wordToNodes[jWord]))
        {
            _wordGraph.addEdge(_wordToNodes[iWord],
                               _wordToNodes[jWord], W(0));
        }

        const auto jFit = _wordOccurences().find(jWord);

        const T jWordOcc = T(jFit->second)
        const T jWordFrq = jWordOcc / T(_wordOccurences._totalCount);

        constrexpr auto subtractor = [] (T lhs, T rhs) { return lhs - rhs; };

        _wordGraph.transformEdge(_wordToNodes[iWord],
                                 _wordToNodes[jWord],
                                 subtractor,
                                 _distance(j) * std::log(jWordFreq) / jWordOcc);
    }

    void addText(const std::vector<uint32_t>& text)
    {
        const auto wOEnd = _wordOccurences().end();
        const unsigned wOTotalCount = _wordOccurences._totalCount;

        for (int i = _kernelSize; i < text.size() - _kernelSize; i++)
        {
            const Word iWord = text[i];

            const auto iFit = _wordOccurences.find(iWord);

            if (iFit != wOEnd)
            {
                for (int j = -kernelSize; j <= kernelSize; j++)
                {
                    const Word jWord = text[i + j];

                    const auto jFit = _wordOccurences().find(jWord);

                    if (j != 0 && jFit != wOEnd)
                    {
                        modifyEdge(iWord,
                                   jWord,j);
                    }
                }
            }
        }
    }

    void normalize()
    {
        for (const auto& node : _wordGraph._nodes)
        {
            const auto fit = _wordOccurences().find(node->_point);

            const T divisor = fit->second;

            for (const auto& neighbour: _nodes->_neighbourhood)
            {
                constrexpr auto divider = [] (T lhs, T rhs) { return lhs / rhs; };

                _wordGraph.transformEdge(_wordGraph.toId(node.get()),
                                         _wordGraph.toId(neighbour.first),
                                         divider,
                                         divisor);
            }
        }
    }

    std::unordered_map<Word, std::size_t>   _wordToNodes;
    Graph<Word, W, WordHasher>              _wordGraph;
    const WordsOccurences&                  _wordOccurences;
    const unsigned                          _kernelSize;
    D                                       _distance;
};

#endif // __WORDS_GRAPH_H__
