boost_test = dependency('boost', modules: ['unit_test_framework'])

testbin = executable(
    'jf-test',
    ['jf-test.cc', 
     'eventloop-suite.cc',
     'work-queue-suite.cc',
     'posix-message-queue-suite.cc',
     'graceful-eventloop-termination-suite.cc',
     'tcp4-suite.cc',
     'shared-event-queue-suite.cc',
    ],
    include_directories: common_includedir,
    link_with: [jf_lib],
    dependencies: [boost_test, thread_dep]
)

test('test', testbin)
