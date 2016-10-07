#!/usr/bin/env python
#-*- coding:utf-8 -*-

''' A Vocabuary Statistics Script for some Articles in English(ASCII). '''

__author__ = "sysu_AT"


from sys import argv, exit
import codecs
import re # one of the backbone in this script
from collections import Counter # the other one

# get filename
try:
    script, filename = argv
except ValueError as err:
    exit("Usage: script <file>")


# get the content in file
content = ""
try:
    with codecs.open(filename, "rt", encoding='ascii', errors="ignore") as f:
        content = f.read()
except IOError as err:
    exit("File '" + filename + "' not found")


# cut the content by regex and count the words
words = re.findall(r"[a-zA-Z]+['_/]?[a-zA-Z]+", content)
words = filter(lambda x: x.islower() or x.lower() not in words, words)
words_count = Counter(words).items()


# sort it, the most counts is on the top, while 
#    on lexicographical order when they have the same counts.
words_count.sort(cmp=
    lambda (w1, c1), (w2, c2): 
        (1 if c1 < c2 else -1) if c1 != c2 else 
            (1 if w1.lower() > w2.lower() else -1))


# pretty print
output_format = " {word:<20}{count:>5}"
print output_format.format(word='Word', count='Count')
print ""
for i, j in words_count:
    print output_format.format(word=i, count=j)

