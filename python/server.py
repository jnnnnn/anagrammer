wordlist = '../enable1.txt'

sortedletters = dict() # key -> words, e.g. "aet" -> ["ate", "eat", "tea"]

for line in open(wordlist, 'r'):
    word = line.strip()
    key = ''.join(sorted(word.lower()))
    if key not in sortedletters:
        sortedletters[key] = list()
    sortedletters[key].append(word)

while True:
    letters = input("Enter some letters: ")
    key = ''.join(sorted(letters.lower()))
    words = sortedletters.get(key)
    print("Anagrams:", ' '.join(words) if words else "None")
