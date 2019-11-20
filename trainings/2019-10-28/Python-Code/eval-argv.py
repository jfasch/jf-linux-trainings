#!/usr/bin/python3

# question: how can I take an argument from the commandline (say,
# sys.argv[1]) and interpret that as a list?

# answer: eval (https://docs.python.org/3/library/functions.html#eval)

# call like ('$' is the shell prompt, the quotes are necessary to
# prevent the shell from splitting the arguments at the spaces)

#   $ ./eval-argv.py '[1, 2, 3, 4]'


import sys

input_list_string = sys.argv[1]
input_list = eval(input_list_string)
print(input_list)
