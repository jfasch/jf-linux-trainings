boost_test = dependency('boost', modules: ['unit_test_framework'])

testbin = executable(
    'jf-test',
    ['jf-test.cc', 
     'eventloop-suite.cc'],
    include_directories: common_includedir,
    link_with: [jf_eventloop_lib, jf_fd_lib],
    dependencies: boost_test,
)

test('test', testbin)
