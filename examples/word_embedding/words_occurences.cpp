#include "words_occurences.hpp"

#include "most_frequent_words.hpp"
#include "word.hpp"


WordsOccurences::WordsOccurences(const MostFrequentWords& mostFrequentWords) :
    _totalCount(0)
{
    for (const auto& fw : mostFrequentWords._data)
    {
        const unsigned occurences = fw._occurences;

        _wordsToOccurences[fw._word] = occurences;
        _totalCount += occurences;
    }
}

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