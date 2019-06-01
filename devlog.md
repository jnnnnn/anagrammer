# Devlog: simple anagram server in Python

https://codeburst.io/this-is-how-easy-it-is-to-create-a-rest-api-8a25122ab1f3

python - flask REST API? nah I want to focus on the actual algorithm.

## 2019-05-26

If not a REST API then how will I talk to it? Read wordlist from a command-line-parameter-file and read stdin for words to anagram. Good.

Implemented python code. 12 lines, no imports.

The letters with the most anagrams in English according to the enable1 wordlist:

[('aeprs', 12), ('aelrst', 11), ('aelst', 10), ('aeinrst', 9), ('aceprs', 9), ('einrst', 9), ('aelpst', 9), ('aelrs', 8), ('aeprss', 8), ('aest', 8), ('acerst', 8), ('aeginrs', 8), ('eenrst', 8), ('aelps', 8), ('eiprs', 8), ('abest', 7), ('acers', 7), ('agilns', 7), ('aemns', 7), ('aeginrst', 7), ('abders', 7), ('aers', 7), ('adeirst', 7), ('ailr', 7), ('adeilr', 7), ('ailrs', 7), ('aemrst', 7), ('aerrst', 7), ('aeirstt', 7), ('aenps', 7), ('acenrt', 7), ('acenrst', 7), ('acert', 7), ('cerstu', 7), ('deist', 7), ('adeprs', 7), ('aeilnst', 7), ('eimst', 7), ('eeimprs', 7), ('einoss', 7), ('eiprsst', 7), ('eerst', 7), ('eorsstu', 7), ('aelrsv', 7), ('aelsv', 7), ('aelpt', 7), ('eimrst', 7), ('enorst', 7), ('aepst', 7), ('inopst', 7), ('eoprst', 7), ('aersw', 7)]

## 2019-06-01

Implemented c++ version. pretty short in the end; I avoided using lots of abstractions. This means there are a few more memory copies than necessary, and also that many C++ concepts aren't used (function calls, classes and class instantiation with new/delete, pointers, references, shared pointers, virtual methods that can be overridden, RAII). Because all that was missed, maybe this isn't such a good problem to demonstrate C++.

Implementing C version. Started writing my own hash table. When I got up to the hash function, went googling for one. There's a lot about hash tables online.

http://man7.org/linux/man-pages/man3/hsearch.3.html

> The three functions hcreate_r(), hsearch_r(), hdestroy_r() are reentrant versions that allow a program to use more than one hash search table at the same time.

However, the table does not dynamically resize; you need to specify a size for it when creating it.
I guess adding dynamic resizing is just an extra level of abstraction?

Or, in the interest of keeping things simple, we just initialize big enough? I kind of wanted to show the actual hash function because a big part of c is bit manipulation.

Thinking about it more, I think it is better to code my own function. Explaining `hsearch` etc. will be additional complexity on top of malloc etc.

Would also have been good to demonstrate the perils of threading in c++ (mostly just double-checked locking) but that's probably not beginner material.

Ugh, had to set vscode to clang intellisense mode before all the inline stuff worked (otherwise lots of import errors and nothing else).

I've fixed about forty errors in my c code. Still getting a segfault when running it. Sad face. I need to debug it. Fix all the warnings. Wow there are a lot, why doesn't vscode show all this shit? Functions that aren't specifying a return value? Come on.

When attempting to debug with `lldb`, I get `step in failed (Could not create return address breakpoint.`.

Follow https://www.40tude.fr/blog/compile-cpp-code-with-vscode-clang/ with a new temporary project. OK, can debug a c hello world. switch it to the actual code I wrote.

Still got an obscure bug somewhere. `arches`, `chaser` and `search` all return `search` only. It is like the old values got lost during a rehash or add.

Some other values work fine though.

I wrote a little dump function to print out the hash table. I noticed that sometimes the table was supposed to have two buckets after rehashing but it actually only had one -- the rehash was overwriting buckets, because it wasn't respecting the open addressing thing -- it just put the new bucket in at the calculated hash without checking if there was already a bucket there.

With that fixed, the whole program works correctly. Ugh. It took me several hours to get all that code right..

Also ran clang-tidy and fixed most of the warnings. I'm mystified by the following warning:

    c\hash.c:91:26: note: The result of the '' expression is undefined
    size_t i = hash(key) % table->size;
                         ^

Everything here is a `size_t`. Why is it not ok to use modulus in this case?
