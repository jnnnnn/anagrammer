#include <unordered_map>
#include <string>
#include <algorithm>
#include <vector>

#define INITIAL_SIZE 17

class AnagramLookup
{
public:
    void add(const std::string &word)
    {
        std::string key = word;
        std::sort(key.begin(), key.end());
        sortedletters[key].push_back(word);
    }
    const auto &lookup(std::string &key)
    {
        std::sort(key.begin(), key.end());
        return sortedletters[key];
    }

private:
    std::unordered_map<std::string, std::vector<std::string>> sortedletters;
};
