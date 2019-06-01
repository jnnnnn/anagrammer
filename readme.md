# Simple Anagram Programs

These programs will return anagrams for words typed in to stdin.

The simplest one is python; it is designed to use many of the most common features of python while still being very simple to explain (or rewrite).

Once the python one is understood, the subject becomes the differences between python and C++.

Finally, we rewrite it for a third time in plain C, introducing raw memory allocation, string handling, and implementing our own hash table.

From a pedagogical viewpoint it may actually be better to use C to introduce C++, as C++ is really only sugar over many of the C concepts.

The wordlist, `enable1.txt`, comes recommended by https://norvig.com/spell-correct.html .

## Algorithm

I picked anagrams because it is one of the simplest algorithms I know of while still having a bit of meat to it. It is something that people can't easily do in their head while still only being a few lines of code.

The algorithm is:

1. sort the letters of each word in the wordlist: `search` becomes `acehrs`.
2. Create a lookup table from sorted word to real word. The `search` entry might be `'acehrs' -> ['arches', 'chaser', 'search']`
3. For each anagram word, look it up in the lookup table (sorting it first as well) and return the related words. So if we typed `resach`, it would look up `acehrs` and find all three words again.

## Languages

| Language | Commands to build/run              |
| -------- | ---------------------------------- |
| Python   | `cd python; python server.py`      |
| C++      | `cd c++; clang++ main.cpp; ./main` |
