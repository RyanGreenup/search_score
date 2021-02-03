#!/usr/bin/env python
import hashlib
import sys
import time
import re
# import os
import numpy as np
from scipy.spatial import distance

ARRAY_SIZE = 3*10**6
doc_vec  = np.zeros(ARRAY_SIZE)+(1e-20)
term_vec = np.zeros(ARRAY_SIZE)+(1e-20)


N = 10**6
def norm1alize(vec):
    vec += 1e-12 # HACK Slightly faster to inc, also -12 seems to
                 #      perform the best timewise
    vec *= 1/sum(vec)
    return vec

def norm1alize_slower(vec):
    vec_sum = sum(vec)  # Slightly slower
    for i in range(len(vec)):
        if vec[i] != 0:
            vec[i] *= (1/vec_sum)




def hash_it(string):
    return int(hashlib.sha1(string.encode('utf-8')).hexdigest(), 16) % (ARRAY_SIZE)


def create_vec_stdin(vec):
    # Open the File
    # Create Empty Words list
    words = []
    # Loop over every line, extract word, lower case and create a list
    for line in sys.stdin:
            #####
            # Cleaning
            #####
            # Strip White Space
            line = line.strip()
            # Strip periods and commas
            # Regex to Identify not-words
            # pattern = re.compile(r'[\W_]+')  # Nah what if my search term contains commas
            # Replace things that are not words with whitespace
            # line = pattern.sub(' ', line)
            left  = ""
            right = ""
            for char in line:
                left = right
                right = char
                combination = left+right
                print(combination)
                # 4*^150C_4 < 10^8, 100 MB memory though, jee
                combination_int = hash_it(combination)
                print(combination_int)
                vec[combination_int] += 1
    
            # #####
            # # Splitting
            # #####
            # # Split out some words and make them lower case
            # new_words = line.split()
            # new_words_lower = [word.lower() for word in new_words]
            # # Create a combined list of words
            # words = new_words_lower + words
    return vec


def create_vec_string(vec, search_string):
    left  = ""
    right = ""
    for char in search_string:
        left = right
        right = char
        combination = left+right
        combination_int = hash_it(combination)
        print(combination)
        print(combination_int)
        vec[combination_int] += 1
    return vec

def similarity(u, v):
    u = norm1alize(u)  # This doesn't copy them, whic is good, save memory
    v = norm1alize(v)
    return 1-distance.cosine(u, v)

distance.cosine(np.array([1.0, 1, 1]), np.array([20.0, 20, 10]))
distance.cosine(np.array([1.0, 1, 1]), np.array([2, 2, 1]))

create_vec_stdin(doc_vec)
create_vec_string(term_vec, sys.argv[1])
print(sum(doc_vec))
print(sum(term_vec))
print(distance.cosine(doc_vec, term_vec))
