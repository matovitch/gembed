#ifndef __WORDS_OCCURENCES_H__
#define __WORDS_OCCURENCES_H__

#include <unordered_map>

#include "word.hpp"

struct MostFrequentWords;


struct WordsOccurences
{

    WordsOccurences(const MostFrequentWords& mostFrequentWords);

    void countWords(const std::vector<Word>& text);

    unsigned _totalCount;

    std::unordered_map<Word, unsigned> _wordsToOccurences;
};

#endif // end __WORDS_OCCURENCES_H__