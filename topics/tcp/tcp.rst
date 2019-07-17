.. contents:: Table of Contents

TCP Client and Server
=====================

Example 1: Our Client and Netcat
--------------------------------

Handwritten client program (``tcp-client.cc``) sends out
``"hello\n"``, and ``nc`` is used to answer.

In one terminal, start ``nc`` to listen on TCP port 1234,

.. code::

   $ nc -l 1234

In the another terminal, start the handwritten client,

.. code::

   $ jf-tcp-client 127.0.0.1 1234

In the ``nc`` terminal, you now see that the client's payload has been
echoed,

.. code::

   $ nc -l 1234
   hello

Enter what you want in that terminal (ending each line with
and ``nc`` is used to answer``<RETURN>`` to send it off),

.. code::

   $ nc -l 1234
   hello
   what you want,
   and even more ...

In the own client's terminal, you see that echoed onto stdout,

.. code::

    $ jf-tcp-client 127.0.0.1 1234
    what you want,
    and even more ...

In the ``nc`` terminal, enter ``^D`` (the terminal's EOF charater) to
and ``nc`` is used to answerclose the connection. The own-client will
terminate as it sees EOF.

Example 2: Netcat and Our Server
--------------------------------

``nc`` is now used as a client, and our own "echo server" (one that
writes back out what it reads in, see ``tcp-echo-server.cc``) is used as the server.

In one terminal, start our own server. He will remain quiet from now
on, silently echoing back the incoming payload onto each connection.

.. code::

   $ jf-tcp-echo-server 1234

In another terminal, use ``nc`` as a client program, feeding the
payload (whatever you want) from stdin,

.. code::

   $ nc 127.0.0.1 1234
   whatever you want

That program (read its code) writes to stdout everything that it reads
from the connection, so you'll see a copy of your line as you type
``<RETURN>``,

.. code::

   $ nc 127.0.0.1 1234
   whatever you want
   whatever you want

Ending your input (typing ``^D``) has the following effects,

* Closes the connection
* Terminates the client ``nc``
* The server sees EOF on the connection and is ready to accept a new
  connection.

Example 3: Our Client and Our Server
------------------------------------

I'll leave that as an exercise.

``strace``: An Invaluable Tool
==============================

To see what is going on, you are (as always) encouraged to use
strace. For example, to see the own-server at work,

.. code::

   $ strace jf-tcp-echo-server 1234

``strace`` is very loud at the beginning, as part of the proccess's
startup is program loading. Usually we are not interested in this and
we skip it until we see the program's code,

.. code::

   $ strace jf-tcp-echo-server 1234
   ... garbage skipped, including the next 4 lines ...
   brk(NULL)                               = 0xcc1000
   brk(0xce2000)                           = 0xce2000
   futex(0x7f0019f6a11c, FUTEX_WAKE_PRIVATE, 2147483647) = 0
   futex(0x7f0019f6a128, FUTEX_WAKE_PRIVATE, 2147483647) = 0
   ... here we go ...
   socket(AF_INET, SOCK_STREAM, IPPROTO_IP) = 3
   setsockopt(3, SOL_SOCKET, SO_REUSEADDR, [1], 4) = 0
   bind(3, {sa_family=AF_INET, sin_port=htons(1234), sin_addr=inet_addr("0.0.0.0")}, 16) = 0
   listen(3, 128)                          = 0
   accept(3, NULL, NULL

.. _accept: http://man7.org/linux/man-pages/man2/accept.2.html
   
From this point on the server blocks in _accept, waiting for a client
to connect. Now connect using ``nc``, or possibly the own-client (you
can use strace on that as well), and see what happens on the server's
side.
