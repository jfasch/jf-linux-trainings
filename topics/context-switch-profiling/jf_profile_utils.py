import os
import os.path
import pprint


MULTITHREADED_PROGRAM = 'jf-profile-timer-multithreaded'
SINGLETHREADED_PROGRAM = 'jf-profile-timer-singlethreaded'
NUM_EXPIRIES = 10000
#NUM_EXPIRIES = 100
INTERVAL_MS = 1
NUM_PARALLEL_TIMERS = (10, 20, 30, 50, 70, 100, 150)

MULTITHREADED_STATS_FILE = 'multithreaded-all.stats'
SINGLETHREADED_STATS_FILE = 'singlethreaded-all.stats'

PERF_EVENTS = (
    'context-switches',
    'L1-dcache-load-misses',
    'L1-icache-load-misses',
    'dTLB-load-misses',
    'iTLB-load-misses',    
    )
