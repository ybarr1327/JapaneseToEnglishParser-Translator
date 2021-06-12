Each Branch is the different parts of the project, part A part B part C
Part A - Scanner
Part B - Parser
Part C - Translator

Each sucessive part includes the previous step, for example part c includes parts a and b

Purpose of the project: This project was meant to simulate the process of what it would be like to write different parts of a compiler.

Using a limited subset of Japanese words, we were able to follow some steps which included scanning the text and turning the characters into tokens, 
parsing these tokens to check for correct syntax of the words, and finally converting the parsed tokens to English meaning. By doing this project we 
basically learned about the many steps that a complier would take to convert raw c++ code and turn it into the assembly language for the cpu to run.

Part C Run Example

In partCtest1: 
watashi wa rika desu . 
watashi wa sensei desu . 
rika wa gohan o tabE masu . 
watashi wa tesuto o seito ni agE mashita . 
shikashi seito wa yorokobI masendeshita . 
dakara watashi wa kanashii deshita . 
soshite rika wa toire ni ikI mashita . 
rika wa nakI mashita . 
eofm

Output on command line:
 ./group9project.out
Enter the input file name: partCtest1
Processing <story>
Processing <s>
Scanner called using word: watashi
Processing <noun>
Matched PRONOUN
Scanner called using word: wa
Matched SUBJECT
Processing <after_subject>
Scanner called using word: rika
Processing <noun>
Matched WORD1
Processing <after_noun>
Scanner called using word: desu
Processing <be>
Matched IS
Scanner called using word: .
Matched PERIOD
Scanner called using word: watashi
Processing <s>
Processing <noun>
Matched PRONOUN
Scanner called using word: wa
Matched SUBJECT
Processing <after_subject>
Scanner called using word: sensei
Processing <noun>
Matched WORD1
Processing <after_noun>
Scanner called using word: desu
Processing <be>
Matched IS
Scanner called using word: .
Matched PERIOD
Scanner called using word: rika
Processing <s>
Processing <noun>
Matched WORD1
Scanner called using word: wa
Matched SUBJECT
Processing <after_subject>
Scanner called using word: gohan
Processing <noun>
Matched WORD1
Processing <after_noun>
Scanner called using word: o
Matched OBJECT
Processing <after_object>
Scanner called using word: tabE
Processing <verb>
Matched WORD2
Processing <tense>
Scanner called using word: masu
Matched VERB
Scanner called using word: .
Matched PERIOD
Scanner called using word: watashi
Processing <s>
Processing <noun>
Matched PRONOUN
Scanner called using word: wa
Matched SUBJECT
Processing <after_subject>
Scanner called using word: tesuto
Processing <noun>
Matched WORD1
Processing <after_noun>
Scanner called using word: o
Matched OBJECT
Processing <after_object>
Scanner called using word: seito
Processing <noun>
Matched WORD1
Scanner called using word: ni
Matched DESTINATION
Processing <verb>
Scanner called using word: agE
Matched WORD2
Processing <tense>
Scanner called using word: mashita
Matched VERBPAST
Scanner called using word: .
Matched PERIOD
Scanner called using word: shikashi
Processing <s>
Matched CONNECTOR
Processing <noun>
Scanner called using word: seito
Matched WORD1
Scanner called using word: wa
Matched SUBJECT
Processing <after_subject>
Scanner called using word: yorokobI
Processing <verb>
Matched WORD2
Processing <tense>
Scanner called using word: masendeshita
Matched VERBPASTNEG
Scanner called using word: .
Matched PERIOD
Scanner called using word: dakara
Processing <s>
Matched CONNECTOR
Processing <noun>
Scanner called using word: watashi
Matched PRONOUN
Scanner called using word: wa
Matched SUBJECT
Processing <after_subject>
Scanner called using word: kanashii
Processing <noun>
Matched WORD1
Processing <after_noun>
Scanner called using word: deshita
Processing <be>
Matched WAS
Scanner called using word: .
Matched PERIOD
Scanner called using word: soshite
Processing <s>
Matched CONNECTOR
Processing <noun>
Scanner called using word: rika
Matched WORD1
Scanner called using word: wa
Matched SUBJECT
Processing <after_subject>
Scanner called using word: toire
Processing <noun>
Matched WORD1
Processing <after_noun>
Scanner called using word: ni
Matched DESTINATION
Processing <verb>
Scanner called using word: ikI
Matched WORD2
Processing <tense>
Scanner called using word: mashita
Matched VERBPAST
Scanner called using word: .
Matched PERIOD
Scanner called using word: rika
Processing <s>
Processing <noun>
Matched WORD1
Scanner called using word: wa
Matched SUBJECT
Processing <after_subject>
Scanner called using word: nakI
Processing <verb>
Matched WORD2
Processing <tense>
Scanner called using word: mashita
Matched VERBPAST
Scanner called using word: .
Matched PERIOD
Scanner called using word: eofm
Sucessfully parsed <story>.


Output in translated.txt:

ACTOR: I/me
DESCRIPTION: rika
TENSE: IS
ACTOR: I/me
DESCRIPTION: teacher
TENSE: IS
ACTOR: rika
OBJECT: meal
ACTION: eat
TENSE: VERB
ACTOR: I/me
OBJECT: test
TO: student
ACTION: give
TENSE: VERBPAST
CONNECTOR: However
ACTOR: student
ACTION: enjoy
TENSE: VERBPASTNEG
CONNECTOR: Therefore
ACTOR: I/me
DESCRIPTION: sad
TENSE: WAS
CONNECTOR: Then
ACTOR: rika
TO: restroom
ACTION: go
TENSE: VERBPAST
ACTOR: rika
ACTION: cry
TENSE: VERBPAST
© 2021 GitHub, Inc.
