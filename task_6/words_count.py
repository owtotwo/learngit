#!/usr/bin/env python
#-*- coding:utf-8 -*-

import sys, os, re
from string import split, strip

script, filename = sys.argv

try:
    file_in = open(filename, "rt")
except IOError:
    print "Can not open the file '" + filename + "'.(maybe not exist)"
    sys.exit(1)

article = file_in.read()

article = article.decode("ascii", "ignore").encode("ascii")

words = article.split()

for i in range(len(words)):
    words[i] = re.sub("[^a-zA-Z\-\']+", " ", words[i])
    words[i].split('\'')

words_str = " ".join(words)
words = words_str.split(' ')

words = map(lambda x: x.strip('\'-'), words)

words = filter(lambda x: x, words)

word_setA = set(words)

word_setB = set(map(lambda x: x.lower(), word_setA))


word_setC = word_setA & word_setB

word_setC |= set([i for i in word_setA if not i.lower() in word_setC])
        

word_listC = list(word_setC)

lower_words = map(str.lower, words)

words_count = map(lower_words.count, map(str.lower, word_listC))
word_tuple = tuple([[words_count[i], word_listC[i]] for i in range(len(words_count))])

word_list = sorted(word_tuple, reverse=True)

print "  %(word)-20s %(count)-6s" % {'word': 'words', 'count': 'count'}

word_list.sort(key=lambda x: (-x[0], str.lower(x[1])))

for word in word_list:
    print "  %(word)-20s %(count)-6d" % {'word': word[1], 'count': word[0]}
