#!/usr/bin/env python

import sys
import re
# import os
# import numpy as np

# Searching ################################################


def create_words():
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
        pattern = re.compile(r'[\W_]+')
        # Replace things that are not words with whitespace
        line = pattern.sub(' ', line)

        #####
        # Splitting
        #####
        # Split out some words and make them lower case
        new_words = line.split()
        new_words_lower = [word.lower() for word in new_words]
        # Create a combined list of words
        words = new_words_lower + words
    return words


print(create_words())
