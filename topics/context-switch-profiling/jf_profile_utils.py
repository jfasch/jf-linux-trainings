import os
import os.path
import pprint


MULTITHREADED_PROGRAM = 'jf-profile-timer-multithreaded'
SINGLETHREADED_PROGRAM = 'jf-profile-timer-singlethreaded'
NUM_EXPIRIES = 10000
#NUM_EXPIRIES = 1000
INTERVAL_MS = 1
NUM_PARALLEL_TIMERS = (10, 20, 30, 40, 50, 60, 70, 80, 90, 100)

MULTITHREADED_STATS_FILE = 'multithreaded-all.stats'
SINGLETHREADED_STATS_FILE = 'singlethreaded-all.stats'

PERF_EVENTS = (
    'context-switches',
    'L1-dcache-load-misses',
    'L1-icache-load-misses',
    'dTLB-load-misses',
    'iTLB-load-misses',    
    )

def read_singlethreaded_stats(directory):
    with open(os.path.join(directory, SINGLETHREADED_STATS_FILE)) as f:
        return eval(f.read())

def read_multithreaded_stats(directory):
    with open(os.path.join(directory, MULTITHREADED_STATS_FILE)) as f:
        return eval(f.read())

def write_singlethreaded_stats(directory, stats):
    if not os.path.isdir(directory):
        os.mkdir(directory)
    with open(os.path.join(directory, SINGLETHREADED_STATS_FILE), 'w') as f:
        pprint.pprint(stats, stream=f)

def write_multithreaded_stats(directory, stats):
    if not os.path.isdir(directory):
        os.mkdir(directory)
    with open(os.path.join(directory, MULTITHREADED_STATS_FILE), 'w') as f:
        pprint.pprint(stats, stream=f)
