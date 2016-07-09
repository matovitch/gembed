#include "words_graph.hpp"
#include "gembed.hpp"

#include <iostream>
#include <fstream>
#include <random>


typedef Scalar float;

typedef Gembed<Word, Scalar, WordHaher,
           std::default_random_engine,
           Scalar,
           EMBED_DIM> GembedType;

constrexpr unsigned EMBED_DIM = 256;

constrexpr unsigned KEEP_WORDS = 20000;

void fillWordsOccurence(WordsOccurences& wordsOccurences)
{
    const std::string filename = "./data/wiki.bin";
    const unsigned blockSize = 4096;

    std::ifstream ifs(filename);

    std::vector<Word> words;

    words.resize(blockSize);

    Word* pWords = &*(words.begin());

    while (ifs)
    {
        ifs.read(pWords, blockSize * sizeof(Word));

        if (ifs)
        {
            wordsOccurences.addWords(words);
        }
    }
}

void writeGembed(const GembedType& gembed)
{
    const std::string filename = "./data/embed.bin";
}

int main()
{
    WordsOccurences wordsOccurences;

    fillWordsOccurence(wordsOccurences);

    wordsOccurences.keepWords(KEEP_WORDS);

    WordsGraph wordsGraph(wordsOccurences);

    GembedType gembed((std::random_device())());

    const unsigned steps = 10000;
    const float    learn = 0.03;
    const float    blow  = 1.1;

    gembed(wordsGraph, steps, learn, blow);

    writeGembed(gembed);

    return 0;
}