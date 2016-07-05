#include "occurences_word.hpp"

#include "word.hpp"

OccurencesWord::OccurencesWord(const unsigned occurences, 
                               const Word word) :
    _occurences(occurences), 
    _word(word)
{}

bool operator< (const OccurencesWord& lhs,
                const OccurencesWord& rhs)
{
    return lhs._occurences < rhs._occurences;
}