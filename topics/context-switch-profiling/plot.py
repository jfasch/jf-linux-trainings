#!/usr/bin/python3

# https://matplotlib.org/gallery/api/agg_oo_sgskip.html

import jf_profile_utils

from matplotlib.figure import Figure
from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas

import sys


DIRECTORY = sys.argv[1]

def plot_timers(mt_stats, st_stats, directory):
    figure = Figure()
    FigureCanvas(figure)
    ax = figure.add_subplot(1, 1, 1)

    ax.set_title('late timers')
    ax.grid(True)
    ax.set_xlabel('#parallel timers')
    ax.set_ylabel('#late')

    num_timers = [stat[0] for stat in mt_stats]
    assert len([stat[0] for stat in st_stats]) == len(num_timers), 'disagreement between mt and st stats'

    singlethreaded_late = [s[1]['timer.total_late'] for s in singlethreaded_stats]
    multithreaded_late = [s[1]['timer.total_late'] for s in multithreaded_stats]

    ax.plot(num_timers, singlethreaded_late, label='singlethreaded')
    ax.plot(num_timers, multithreaded_late, label='multithreaded')

    figure.legend()
    figure.savefig(directory+'/timer')

def plot_rusage(mt_stats, st_stats, directory):
    figure = Figure()
    FigureCanvas(figure)
    ax = figure.add_subplot(1, 1, 1)

    ax.set_title('%user/system')
    ax.grid(True)
    ax.set_xlabel('#parallel timers')
    ax.set_ylabel('%')

    num_timers = [stat[0] for stat in mt_stats]
    assert len([stat[0] for stat in st_stats]) == len(num_timers), 'disagreement between mt and st stats'

    singlethreaded_user = [s[1]['rusage.user'] for s in singlethreaded_stats]
    singlethreaded_sys = [s[1]['rusage.sys'] for s in singlethreaded_stats]
    multithreaded_user = [s[1]['rusage.user'] for s in multithreaded_stats]
    multithreaded_sys = [s[1]['rusage.sys'] for s in multithreaded_stats]

    ax.plot(num_timers, singlethreaded_user, label='singlethreaded(user)')
    ax.plot(num_timers, singlethreaded_sys, label='singlethreaded(sys)')
    ax.plot(num_timers, multithreaded_user, label='multithreaded(user)')
    ax.plot(num_timers, multithreaded_sys, label='multithreaded(sys)')

    figure.legend()
    figure.savefig(directory+'/rusage')

def plot_perf(mt_stats, st_stats, directory):
    figure = Figure()
    FigureCanvas(figure)
    ax = figure.add_subplot(1, 1, 1)

    ax.set_title('#perf events')
    ax.grid(True)
    ax.set_xlabel('#parallel timers')
    ax.set_ylabel('#')

    num_timers = [stat[0] for stat in mt_stats]
    assert len([stat[0] for stat in st_stats]) == len(num_timers), 'disagreement between mt and st stats'

    for ev in jf_profile_utils.PERF_EVENTS:
        singlethreaded = [s[1]['perf.{ev}'.format(ev=ev)] for s in singlethreaded_stats]
        multithreaded = [s[1]['perf.{ev}'.format(ev=ev)] for s in multithreaded_stats]

        ax.plot(num_timers, singlethreaded, label='singlethreaded({ev})'.format(ev=ev))
        ax.plot(num_timers, multithreaded, label='multithreaded({ev})'.format(ev=ev))

    figure.legend()
    figure.savefig(directory+'/perf')

singlethreaded_stats = jf_profile_utils.read_singlethreaded_stats(DIRECTORY)
multithreaded_stats = jf_profile_utils.read_multithreaded_stats(DIRECTORY)

plot_timers(mt_stats=multithreaded_stats, st_stats=singlethreaded_stats, directory=DIRECTORY)
plot_rusage(mt_stats=multithreaded_stats, st_stats=singlethreaded_stats, directory=DIRECTORY)
plot_perf(mt_stats=multithreaded_stats, st_stats=singlethreaded_stats, directory=DIRECTORY)
