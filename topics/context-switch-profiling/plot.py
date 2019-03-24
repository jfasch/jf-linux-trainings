#!/usr/bin/python3

import jf_profile_utils
from jf_figure import Figure
from jf_stats import Stats

import sys


def plot_timers(mt_stats, st_stats, directory):
    assert [s[0] for s in mt_stats] == [s[0] for s in st_stats], 'disagreement between mt and st stats'

    figure = Figure()
    FigureCanvas(figure)
    figure.suptitle('Late timers depending on number of parallel 1ms timers')

    x_axis_timers = [s[0] for s in mt_stats]
    y_axis_mt = [s[1]['timer.total_late'] for s in mt_stats]
    y_axis_st = [s[1]['timer.total_late'] for s in st_stats]
    y_max = max(y_axis_mt + y_axis_st)

    ax_mt = figure.add_subplot(1, 2, 1) # nrows, ncols, index
    ax_mt.set_title('Multithreaded')
    ax_mt.grid(True)
    ax_mt.set_xlabel('#timers')
    ax_mt.set_ylabel('#late')
    ax_mt.set_ylim(top=y_max)
    ax_mt.plot(x_axis_timers, y_axis_mt)

    ax_st = figure.add_subplot(1, 2, 2) # nrows, ncols, index
    ax_st.set_title('Singlethreaded')
    ax_st.grid(True)
    ax_st.set_xlabel('#timers')
    ax_st.set_ylabel('#late')
    ax_st.set_ylim(top=y_max)
    ax_st.plot(x_axis_timers, y_axis_st)

    # figure.legend()
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

    singlethreaded_user = [s[1]['rusage.user'] for s in st_stats]
    singlethreaded_sys = [s[1]['rusage.sys'] for s in st_stats]
    multithreaded_user = [s[1]['rusage.user'] for s in mt_stats]
    multithreaded_sys = [s[1]['rusage.sys'] for s in mt_stats]

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
        singlethreaded = [s[1]['perf.{ev}'.format(ev=ev)] for s in st_stats]
        multithreaded = [s[1]['perf.{ev}'.format(ev=ev)] for s in mt_stats]

        ax.plot(num_timers, singlethreaded, label='singlethreaded({ev})'.format(ev=ev))
        ax.plot(num_timers, multithreaded, label='multithreaded({ev})'.format(ev=ev))

    figure.legend()
    figure.savefig(directory+'/perf')

def main():
    directory = sys.argv[1]

    with open(directory + '/stats') as f:
        stats = Stats.read(f)

    with open(directory + '/late-timers.png', 'wb') as f:
        Figure(stats=stats, title='Late timers', 
               keys=('timer.total_late',), 
               ylabel='#late timers').write_png(f)

    with open(directory + '/cpu.png', 'wb') as f:
        Figure(stats=stats, title='CPU usage', 
               keys=('rusage.user', 'rusage.sys'), 
               ylabel='seconds').write_png(f)

    with open(directory + '/perf.png', 'wb') as f:
        Figure(stats=stats, title='Performance counters',
               # keys=('perf.L1-dcache-load-misses',
               #       'perf.L1-icache-load-misses',
               #       'perf.context-switches',
               #       'perf.dTLB-load-misses',
               #       'perf.iTLB-load-misses'),
               keys=('perf.LLC-load-misses',),
               # keys=('perf.L1-dcache-load-misses',
               #       'perf.L1-icache-load-misses',
               #       'perf.dTLB-load-misses',
               #       'perf.iTLB-load-misses'),
               ylabel='num').write_png(f)


if __name__ == "__main__":
    main()
