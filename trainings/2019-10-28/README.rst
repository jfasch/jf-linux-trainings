.. contents:: Table of Contents

Exercises
=========

* **Slide 51, "Exercises: Basics"**

  Write a program that takes a single digit as commandline parameter.
  Print the English word for that digit.

  `Exercises/digit.py <Exercises/digit.py>`

* **Slide 58, "Exercises: While Loop"**

  Write a program that takes an integer commandline parameter and
  checks whether that number is prime!

  `Exercises/prime.py <Exercises/prime.py>`__

* **Slide 94, "Exercises: Lists, Loops, Functions"**

  Write a function uniq() that takes a sequence as input. It returns a
  list with duplicate elements removed, and where the contained
  elements appear in the same order that is present in the input
  sequence. The input sequence remains unmodified.

  `Exercises/uniq.py <Exercises/uniq.py>`__

* **Slide 121, "Exercises: Strings"**

  Write a program that receives any number of arguments and prints
  them out right justified at column 20.

  `Exercises/20.py <Exercises/20.py>`__

Miscellaneous
=============

* Famous **Generator** introduction: *producing* an infinite sequence
  (Fibonacci, what else)

  `Misc/fibo-generator-yield.py <Misc/fibo-generator-yield.py>`__

* During the ``uniq`` exercise, people tend to want to pass a Python
  list from the commandline, naively. 

  Enter ``eval()``, as seen in `Misc/eval-argv.py
  <Misc/eval-argv.py>`__

* Operator Overloading. `See the docs for more
  <https://docs.python.org/3/reference/datamodel.html#special-method-names>`__.

  `Misc/operator-overloading.py <Misc/operator-overloading.py>`__

* Getters and Setters. `See the docs for more
  <https://docs.python.org/3/library/functions.html#property>`__.

  `Misc/getter-setter.py <Misc/getter-setter.py>`__

* More on listcomprehension and generator expressions.

  `Misc/listcomprehension-generatorexpression.py <Misc/listcomprehension-generatorexpression.py>`__

* More on local and global scope, and global variables.

  `Misc/scope.py <Misc/scope.py>`__

* Closures: between local and global.

  `Misc/scope-closure.py <Misc/scope-closure.py>`__

Project
=======

We had two days left, in addition to the usual three days which are
sufficient to learn the basics. A group project was launched, with the
somewhat real-life topic "talking to switches and doing all kinds of
stuff with that information".

This gave us the opportunity to discover a couple of areas more
closely.

* Object oriented programming (a switch has interfaces, and both have
  properties)
* Storing all that in databases
* Exception handling
* Commandline interfaces
* Unit testing

See `SwitchZeug/README.rst <SwitchZeug/README.rst>`__
