* profile-timer-singlethreaded.cc: use epoll
* EventLoop

  * epoll: use sorted vector to eliminate cache misses
  * remove num_{in,out} from interface
