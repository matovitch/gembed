#ifndef __MOST_FREQUENT_WORDS_H__
#define __MOST_FREQUENT_WORDS_H__

#include "occurences_word.hpp"

#include <vector>

struct WordsOccurences;


struct MostFrequentWords
{

    MostFrequentWords(const WordsOccurences& wordsOccurences,
                      const unsigned toKeep);

    std::vector<OccurencesWord> _data;
};

#endif // __MOST_FREQUENT_WORDS_H__