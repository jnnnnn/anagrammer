#include <iostream>
#include <fstream>
#include <string>

#include "anagramlookup.h"

int
main()
{
    AnagramLookup* anagramLookup = new AnagramLookup();
    // auto*
    // shared_ptr<AnagramLookup>(new AnagramLookup())
    // make_shared<AnagramLookup>()
    // make_unique<AnagramLookup>()

    std::ifstream infile("../enable1.txt");

    std::string word;
    while (infile >> word)
    {
        anagramLookup->add(word);
    }

    while (true)
    {
        std::string letters;
        std::cout << "Enter some letters: ";
        std::cin >> letters;
        std::string key = letters;
        std::cout << "Anagrams: ";
        auto matching_words = anagramLookup->lookup(key);
        for (auto word : matching_words)
        {
            std::cout << word << " ";
        }
        std::cout << std::endl;
    }

    delete anagramLookup;

    return 0;
}

// not demonstrated: class/new/delete, shared_ptr, virtual, RAII