#ifndef __OCCURENCES_WORD_H__
#define __OCCURENCES_WORD_H__

#include "word.hpp"

struct OccurencesWord
{
    OccurencesWord(const unsigned occurences, 
                   const Word word);

    unsigned _occurences;
    Word _word;
};

#endif // __OCCURENCES_WORD_H__