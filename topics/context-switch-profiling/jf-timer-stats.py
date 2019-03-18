#!/usr/bin/python3

import jf_profile_utils

import subprocess
import tempfile
import pprint
import sys
import re
import io


sys_stderr = sys.stderr
sys_exit = sys.exit

DIRECTORY = sys.argv[1]

rex = re.compile('^real\s+(.*)$')

_rex_cputime_user = re.compile(r'^user\s+(.*)$')
_rex_cputime_sys = re.compile(r'^sys\s+(.*)$')

def create_sample(program, num_timers):
    stats = {}

    with open(DIRECTORY+'/perf.stat', 'w+') as perf_file:
        # set up command to gather late timers, CPU time information,
        # and perf counter stats.
        if True:
            # the command to be statted. it sets up timers, and prints
            # information about those onto stdout.
            command = [program, str(num_timers), str(jf_profile_utils.NUM_EXPIRIES), str(jf_profile_utils.INTERVAL_MS)]
        if True:
            # `time -p ...` writes to stderr.
            command = ['time', '-p'] + command
        if True:
            command = ['perf', 'stat', 
                       '--output', str(perf_file.name),
                       '--field-separator', ';',
                       '--event', ','.join(jf_profile_utils.PERF_EVENTS)
            ] + command

        try:
            ret = subprocess.run(
                command,
                # we expect text (not binary) on stdout and stderr
                text=True,
                capture_output=True,
                check=True)
        except subprocess.CalledProcessError as e:
            print('Failed to run '+str(e.cmd), file=sys_stderr)
            print('  exit code: '+str(e.returncode), file=sys_stderr)
            print('  stderr: '+str(e.stderr), file=sys_stderr)
            sys_exit(1)

        # stdout: timer stats
        if True:
            timer_stats = eval(ret.stdout)
    
            # sanity check
            assert type(timer_stats) is dict
            assert 'total_late' in timer_stats
            assert 'max_late'in timer_stats

            stats['timer.total_late'] = timer_stats['total_late']
            stats['timer.max_late'] = timer_stats['max_late']

        # stderr: rusage
        if True:
            for line in io.StringIO(ret.stderr):
                user = _rex_cputime_user.search(line)
                sys = _rex_cputime_sys.search(line)
                if user:
                    stats['rusage.user'] = float(user[1])
                if sys:
                    stats['rusage.sys'] = float(sys[1])

        # perf_file: perf, in "CSV"
        if True:
            for line in perf_file:
                if line.isspace() or line.startswith('#'): continue
                cols = line.split(';')
                eventname = cols[2]
                if eventname.endswith(':u'):
                    eventname = eventname[:-2]
                value = int(cols[0])
                stats['perf.'+eventname] = value

    return stats

multithreaded_stats = []
singlethreaded_stats = []

for ntimers in jf_profile_utils.NUM_PARALLEL_TIMERS:
    multithreaded_stats.append(
        (
            ntimers,
            create_sample(
                program=jf_profile_utils.MULTITHREADED_PROGRAM,
                num_timers=ntimers)
        )
    )
    singlethreaded_stats.append(
        (
            ntimers,
            create_sample(
                program=jf_profile_utils.SINGLETHREADED_PROGRAM,
                num_timers=ntimers)
        )
    )

jf_profile_utils.write_singlethreaded_stats(directory=DIRECTORY, stats=singlethreaded_stats)
jf_profile_utils.write_multithreaded_stats(directory=DIRECTORY, stats=multithreaded_stats)
