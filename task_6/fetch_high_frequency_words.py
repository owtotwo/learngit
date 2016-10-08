#!/usr/bin/env python
#-*- coding: utf-8 -*-

''' Extract the high-frequency words from the results. '''
__author__ = "sysu_AT"


def get_result_texts_from_files(result_files):
    result_texts = []
    for filename in result_files:
        try:
            with open(filename, "rt") as f:
                result_texts.append(f.read())
        except IOError as err:
            exit(str(err))
    return result_texts

def parse_result_texts_to_dict(result_texts):
    import re
    results = {}
    for text in result_texts:
        for line in text.split('\n'):
            tmp = re.search(r"\b(?P<word>\S+)\b\s+(?P<count>\d+)", line)
            if not tmp: continue # ignore the title
            word, count = tmp.group('word', 'count')
            count = int(count)
            if word not in results:
                results[word] = [count, 1] # the first time show up in result
            else:
                results[word][0] += count
                results[word][1] += 1
    return results

def fetch_high_freq_words_to_list(results):
    ''' throw the words only show up one time. '''
    return list(filter(lambda (w, (c, t)): t > 1, results.items()))

def sort_freq_words_list(freq_words_list):
    ''' sort by times, count then letter. '''
    return sorted(freq_words_list, key=lambda (w, (c, t)): (-t, -c, w.lower()))

def print_freq_words(freq_words_list):
    for (word, (count, times)) in freq_words_list:
        print "{word:20} {count:5} {times:5}".format(word=word, count=count, times=times)

def main():
    from sys import argv, exit
    script, result_files = argv[0], argv[1:]
    if len(result_files) < 2:
        exit("Usage: python script.py result1 result2 [result3 ...]")
    result_texts = get_result_texts_from_files(result_files)
    results = parse_result_texts_to_dict(result_texts)
    freq_words_list = fetch_high_freq_words_to_list(results)
    ordered_freq_words_list = sort_freq_words_list(freq_words_list)
    print_freq_words(ordered_freq_words_list)


if __name__ == "__main__":
    main()
