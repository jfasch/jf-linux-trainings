Signals
=======

(start out with manual compiler invocation)

* barebones naive program (`010-signal-basics.cc`)

  * `pause()` in main
  * output `getpid()` for convenience
  * default actions

    * `kill TERM` -> terminated
    * `kill SEGV` -> core (discuss)
    * show exit status `!= 0`

  * `echo core > /proc/sys/kernel/core_pattern`
  * "core" conflicts
  * `core.%p`

* handler (`020-signal-handler.cc`)
  
  * handler

    * cerr in signal handler context -> NO!

  * install as `SIGTERM`

    * still only `pause()`, in linear flow, no loop
    * terminates -> why? show fallthrough, cout after pause
    * discuss `errno`, `EINTR`, and error handling in general
    * loop around pause
    * install as `SIGINT` (-> no second terminal necessary)

  * termination

    * `bool quit` -> NO! `sig_atomic_t`
    * `while (!quit) ... pause ...`

  * fix crap

    * cout in signal handler context
    * `sig_atomic_t quit`
    * error handling. fail when trying to comprehend bloody `signal()`
      return value -> use `sigaction` from here on
    * `sigaction`

* alarm (`030-signal-termination-alarm.cc`)

  * add `alarm()` periodic handler (i.e. re-arm in signal handler)
  * see how `pause()` is still interrupted

* multithreading

  * original multi-pipe-consumer (`040-mt-pipe.cc`). read n pipes and
    write to stdout, in n threads
  * add alarm handling to that (`050-mt-pipe-alarm.cc`). **be puzzled
    why system calls are not interrupted in pipe thtreads.** write a
    standalone single-threaded program and see systemn call
    interrupted (`051-st-pipe-alarm.cc`). discuss.

    * `man open` says `EINTR` on pipe
    * `man alarm` says delivered to calling *process*

    so wtf?
