_headers = [
    'eventloop.h',
    'eventloop-epoll.h',
    'eventloop-select.h',
]

_sources = [    
    'eventloop-epoll.cc',
    'eventloop-select.cc',
]

jf_eventloop_lib = library(
    'jf-eventloop',
    _sources,
    _headers,
    include_directories: common_includedir,
    link_with: [jf_fd_lib],
    install: true)
