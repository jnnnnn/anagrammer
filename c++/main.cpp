#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <algorithm>

int main()
{
    std::unordered_map<std::string, std::vector<std::string>> sortedletters;

    std::ifstream infile("../enable1.txt");

    std::string word;
    while (infile >> word)
    {
        std::string key = word;
        std::sort(key.begin(), key.end());
        sortedletters[key].push_back(word);
    }

    while (true)
    {
        std::string letters;
        std::cout << "Enter some letters: ";
        std::cin >> letters;
        std::string key = letters;
        std::sort(key.begin(), key.end());
        std::cout << "Anagrams: ";
        auto matching_words = sortedletters[key];
        for (auto word : matching_words)
        {
            std::cout << word << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}

// not demonstrated: class/new/delete, shared_ptr, virtual, RAII