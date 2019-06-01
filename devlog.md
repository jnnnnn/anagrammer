# Devlog: simple anagram server in Python

https://codeburst.io/this-is-how-easy-it-is-to-create-a-rest-api-8a25122ab1f3

python - flask REST API? nah I want to focus on the actual algorithm.

## 2019-05-26

If not a REST API then how will I talk to it? Read wordlist from a command-line-parameter-file and read stdin for words to anagram. Good.

Implemented python code. 12 lines, no imports.

The letters with the most anagrams in English according to the enable1 wordlist:

[('aeprs', 12), ('aelrst', 11), ('aelst', 10), ('aeinrst', 9), ('aceprs', 9), ('einrst', 9), ('aelpst', 9), ('aelrs', 8), ('aeprss', 8), ('aest', 8), ('acerst', 8), ('aeginrs', 8), ('eenrst', 8), ('aelps', 8), ('eiprs', 8), ('abest', 7), ('acers', 7), ('agilns', 7), ('aemns', 7), ('aeginrst', 7), ('abders', 7), ('aers', 7), ('adeirst', 7), ('ailr', 7), ('adeilr', 7), ('ailrs', 7), ('aemrst', 7), ('aerrst', 7), ('aeirstt', 7), ('aenps', 7), ('acenrt', 7), ('acenrst', 7), ('acert', 7), ('cerstu', 7), ('deist', 7), ('adeprs', 7), ('aeilnst', 7), ('eimst', 7), ('eeimprs', 7), ('einoss', 7), ('eiprsst', 7), ('eerst', 7), ('eorsstu', 7), ('aelrsv', 7), ('aelsv', 7), ('aelpt', 7), ('eimrst', 7), ('enorst', 7), ('aepst', 7), ('inopst', 7), ('eoprst', 7), ('aersw', 7)]
