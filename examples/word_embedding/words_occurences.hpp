#ifndef __WORDS_OCCURENCES_H__
#define __WORDS_OCCURENCES_H__

#include <unordered_map>

#include "word.hpp"

struct MostFrequentWords;


struct WordsOccurences
{

    void countWords(const std::vector<Word>& text);

    void keepMostFrequentWords(unsigned toKeep);

    const std::unordered_map<Word, unsigned>& operator() () const;

    unsigned _totalCount;

    std::unordered_map<Word, unsigned> _wordsToOccurences;
};

#endif // end __WORDS_OCCURENCES_H__