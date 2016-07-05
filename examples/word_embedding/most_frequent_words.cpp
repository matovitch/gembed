#include "most_frequent_words.hpp"

#include "words_occurences.hpp"

#include <algorithm>


MostFrequentWords::MostFrequentWords(const WordsOccurences& wordsOccurences,
                                     const unsigned toKeep)
{
    for (const auto& wo : wordsOccurences._data)
    {
        _data.push(OccurencesWord(wo.second, wo.first));
    }

    std::sort(_data.begin(), _data.end());

    _data.resize(toKeep);
}
