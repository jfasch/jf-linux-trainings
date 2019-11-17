#!/usr/bin/python

import dat
import sys

filename = sys.argv[1]
matrix = dat.load_dat(filename)

stringified_string = matrix.__str__()

print(stringified_string)

