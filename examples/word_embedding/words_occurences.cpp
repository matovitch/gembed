#include "words_occurences.hpp"

#include "occurence_word.hpp"
#include "word.hpp"

#include <algorithm>
#include <utility>
#include <vector>

void WordsOccurences::countWords(const std::vector<Word>& text)
{
    for (const auto& word: text)
    {
        auto fit = _wordsToOccurences.find(word);

        if (fit != _data.end())
        {
            fit->second++;
            _totalCount++;
        }
        else
        {
            _wordsToOccurences[word] = 1;
            _totalCount++;
        }
    }
}

void keepMostFrequentWords(unsigned toKeep)
{
    std::vector<OccurencesWord> occurenceWords;

    for (const auto& wo : _wordsToOccurences)
    {
        occurenceWords.push(OccurencesWord(wo.second, wo.first));
    }

    std::partial_sort(occurenceWords.begin(),
                      occurenceWords.begin() + toKeep,
                      occurenceWords.end());

    occurenceWords.resize(toKeep);

    _wordsToOccurences.clear();

    for (const auto& ow : occurenceWords)
    {
        _wordsToOccurences.insert(std::make_pair<Word, unsigned>(ow._word, ow._occurences));
    }
}

const std::unordered_map<Word, unsigned>& operator() const
{
    return _wordsToOccurences;
}