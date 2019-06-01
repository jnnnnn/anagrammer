wordlist = '../enable1.txt'

sortedletters = dict()

for line in open(wordlist, 'r').read().splitlines():
    key = ''.join(sorted(line.lower()))
    if key not in sortedletters:
        sortedletters[key] = list()
    sortedletters[key].append(line)

while True:
    letters = input("Enter some letters: ")
    key = ''.join(sorted(letters.lower()))
    print("Anagrams:", sortedletters.get(key))
