project('jf-linux-trainings', 'cpp')

thread_dep = dependency('threads')
cc = meson.get_compiler('cpp')
librt = cc.find_library('rt') # POSIX message queues are there, at
                              # least

subdir('lib')
subdir('unittests')
subdir('topics')
subdir('trainings')
