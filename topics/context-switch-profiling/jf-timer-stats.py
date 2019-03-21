#!/usr/bin/python3

import jf_profile_utils
from jf_stats import Stats

import subprocess
import tempfile
import pprint
import sys
import os
import re
import io


sys_stderr = sys.stderr
sys_exit = sys.exit

_rex_cputime_user = re.compile(r'^user\s+(.*)$')
_rex_cputime_sys = re.compile(r'^sys\s+(.*)$')

def make_command(program, num_timers, num_expiries, interval_ms):
    return [program, str(num_timers), str(num_expiries), str(interval_ms)]

def run(command):
    try:
        ret = subprocess.run(
            command,
            text=True,
            capture_output=True,
            check=True)
        return ret.stdout, ret.stderr
    except subprocess.CalledProcessError as e:
        print('Failed to run '+str(e.cmd), file=sys_stderr)
        print('  exit code: '+str(e.returncode), file=sys_stderr)
        print('  stderr: '+str(e.stderr), file=sys_stderr)
        sys_exit(1)

def perf_samples(directory, program, num_timers):
    with open(directory+'/perf.stat', 'w+') as perf_file:
        cout, cerr = run(
            ['perf', 'stat', 
             '--output', str(perf_file.name),
             '--field-separator', ';',
             '--event', ','.join(jf_profile_utils.PERF_EVENTS)
            ] + \
            make_command(
                program=program,
                num_timers=num_timers,
                num_expiries=jf_profile_utils.NUM_EXPIRIES,
                interval_ms=jf_profile_utils.INTERVAL_MS)
        )

        # perf_file: perf, in "CSV"
        if True:
            for line in perf_file:
                if line.isspace() or line.startswith('#'): continue
                cols = line.split(';')
                eventname = cols[2]
                if eventname.endswith(':u'):
                    eventname = eventname[:-2]
                value = int(cols[0])
                yield 'perf.'+eventname, value

def rusage_timer_samples(program, num_timers):
    cout, cerr = run(
        ['time', '-p'] + \
        make_command(
            program=program,
            num_timers=num_timers,
            num_expiries=jf_profile_utils.NUM_EXPIRIES,
            interval_ms=jf_profile_utils.INTERVAL_MS))

    # stdout: timer stats
    if True:
        timer_stats = eval(cout)
    
        # sanity check
        assert type(timer_stats) is dict
        assert 'total_late' in timer_stats
        assert 'max_late'in timer_stats

        yield 'timer.total_late', timer_stats['total_late']
        yield 'timer.max_late', timer_stats['max_late']

    # stderr: rusage
    if True:
        for line in io.StringIO(cerr):
            user = _rex_cputime_user.search(line)
            sys = _rex_cputime_sys.search(line)
            if user:
                yield 'rusage.user', float(user[1])
            if sys:
                yield 'rusage.sys', float(sys[1])


def main():
    directory = sys.argv[1]

    if not os.path.isdir(directory):
        os.mkdir(directory)

    stats = Stats()

    for ntimers in jf_profile_utils.NUM_PARALLEL_TIMERS:
        for k, v in perf_samples(
                directory=directory,
                program=jf_profile_utils.MULTITHREADED_PROGRAM,
                num_timers=ntimers):
            stats.add_sample(which=Stats.MT, num_timers=ntimers, key=k, value=v)
        for k, v in perf_samples(
                directory=directory,
                program=jf_profile_utils.SINGLETHREADED_PROGRAM,
                num_timers=ntimers):
            stats.add_sample(which=Stats.ST, num_timers=ntimers, key=k, value=v)

        for k, v in rusage_timer_samples(
                program=jf_profile_utils.MULTITHREADED_PROGRAM,
                num_timers=ntimers):
            stats.add_sample(which=Stats.MT, num_timers=ntimers, key=k, value=v)
        for k, v in rusage_timer_samples(
                program=jf_profile_utils.SINGLETHREADED_PROGRAM,
                num_timers=ntimers):
            stats.add_sample(which=Stats.ST, num_timers=ntimers, key=k, value=v)

    with open(directory + '/stats', 'w') as f:
        stats.write(f)


if __name__ == "__main__":
    main()
