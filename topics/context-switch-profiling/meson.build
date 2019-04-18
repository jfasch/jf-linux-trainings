executable(
    'jf-profile-timer-singlethreaded',
    ['profile-timer-singlethreaded.cc', '_timer.cc'],
    ['_timer.h'],
    include_directories: common_includedir,
    link_with: [jf_lib],
    install: true,
)

executable(
    'jf-profile-timer-multithreaded',
    ['profile-timer-multithreaded.cc', '_timer.cc'],
    ['_timer.h'],
    include_directories: common_includedir,
    link_with: [jf_lib],
    dependencies: [thread_dep],
    install: true,
)
