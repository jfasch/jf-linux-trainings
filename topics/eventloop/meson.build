executable(
    'jf-eventloop-two-timers',
    ['eventloop-two-timers.cc'],
    include_directories: common_includedir,
    link_with: [jf_lib],
    install: true,
)

executable(
    'jf-eventloop-ros-and-a-timer',
    ['eventloop-ros-and-a-timer.cc'],
    include_directories: common_includedir,
    link_with: [jf_lib],
    dependencies: [thread_dep],
    install: true,
)

