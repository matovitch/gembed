#ifndef __WORDS_GRAPH_H__
#define __WORDS_GRAPH_H__

#include "words_occurences.hpp"
#include "graph.hpp"

template <typename T,
          typename W>
struct WordGraph
{

    WordGraph(const WordsOccurences& wordOccurences,
              const unsigned kernelSize) :
        _wordOccurences(wordOccurences),
        _kernelSize(kernelSize)
    {
        for (const auto& wo : _wordOccurences)
        {
            _graph.createNode(wo.first);
        }
    }

    void modifyEdge(const Word iWord,
                    const Word jWord,
                    const T iWordFreq,
                    const T jWordFreq)
    {

    }

    void addText(const std::vector<uint32_t>& text)
    {
        const auto wOEnd = _wordOccurences.end();
        const unsigned wOTotalCount = _wordOccurences._totalCount;

        for (unsigned i = _kernelSize; i < text.size() - _kernelSize; i++)
        {
            const Word iWord = text[i];

            const auto iFit = _wordOccurences.find(iWord);

            if (iFit != wOEnd)
            {
                const T iWordFreq = iFit->second / T(wOTotalCount);

                for (unsigned j = -kernelSize; j <= kernelSize; j++)
                {
                    const Word jWord = text[i + j];

                    const auto jFit = _wordOccurences.find(jWord);

                    if (j != 0 && jFit != wOEnd)
                    {
                        const T jWordFreq = jFit->second / T(wOTotalCount);

                        modifyEdge(iWord,
                                   jWord,
                                   iWordFreq, 
                                   jWordFreq);
                    }
                }
            }
        }
    }

    Graph<Word, T, WordHasher>  _graph;
    const WordsOccurences&      _wordOccurences;
    const unsigned              _kernelSize;
    W                           _weighter;
    
};

#endif // __WORDS_GRAPH_H__