Socket CAN
==========

Demo Programs
-------------

Given a CAN interface (see below), one can use the following programs
to play with it.

* ``jf-can-send-hello``. Sends one frame with ID 42 and the payload
  "hello" (a C string).
* ``jf-can-recv-one``. Receives one frame, prints its payload to
  standard output, and terminates.
* ``jf-can-echo-many``. Sits and receives frames, echoing them back on
  the same interface.

Interfaces
----------

Use networking tools like ``ip`` to show interface parameters.

.. code::

   # ip link show
   ... lists all interfaces ...
   # ip link show can0
   3: can0: <NOARP,ECHO> mtu 16 qdisc noop state DOWN mode DEFAULT qlen 10
       link/can 

Get inline help.

.. code::

   # ip link set can0 type can help

Set interface parameters, and enable the interface.

.. code::

   # ip link set can0 bitrate 500000
   # ip link set can0 bitrate 500000 listen-only on
   # ip link set can0 up
  
