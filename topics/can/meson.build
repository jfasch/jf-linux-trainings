executable(
    'jf-can-send-hello',
    ['can-send-hello.cc'],
    include_directories: common_includedir,
    link_with: [jf_lib],
    install: true,
)

executable(
    'jf-can-recv-one',
    ['can-recv-one.cc'],
    include_directories: common_includedir,
    link_with: [jf_lib],
    dependencies: [thread_dep],
    install: true,
)

executable(
    'jf-can-recv-many',
    ['can-recv-many.cc'],
    include_directories: common_includedir,
    link_with: [jf_lib],
    dependencies: [thread_dep],
    install: true,
)

executable(
    'jf-can-echo-many',
    ['can-echo-many.cc'],
    include_directories: common_includedir,
    link_with: [jf_lib],
    dependencies: [thread_dep],
    install: true,
)

