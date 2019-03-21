import matplotlib.figure
from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas


class Figure:
    def __init__(self, stats, title, keys, ylabel):
        self.__figure = matplotlib.figure.Figure()
        FigureCanvas(self.__figure)
        self.__figure.suptitle(title)

        x_axis_timers = []
        y_axis_mt = dict((k, []) for k in keys)
        y_axis_st = dict((k, []) for k in keys)

        y_max = 0

        for num_timers, mt, st in stats.iter_sorted():
            x_axis_timers.append(num_timers)
            for k in keys:
                y = mt[k]
                y_max = max(y_max, y)
                y_axis_mt[k].append(y)

                y = st[k]
                y_max = max(y_max, y)
                y_axis_st[k].append(y)


        ax_mt = self.__figure.add_subplot(1, 2, 1) # nrows, ncols, index
        ax_mt.set_title('Multithreaded')
        ax_mt.grid(True)
        ax_mt.set_xlabel('#timers')
        ax_mt.set_ylabel(ylabel)
        ax_mt.set_ylim(top=y_max)
        for k in keys:
            print(x_axis_timers, y_axis_mt[k])
            ax_mt.plot(x_axis_timers, y_axis_mt[k], label=k)

        ax_st = self.__figure.add_subplot(1, 2, 2) # nrows, ncols, index
        ax_st.set_title('Singlethreaded')
        ax_st.grid(True)
        ax_st.set_xlabel('#timers')
        ax_st.set_ylabel(ylabel)
        ax_st.set_ylim(top=y_max)
        for k in keys:
            ax_st.plot(x_axis_timers, y_axis_st[k], label=k)

        self.__figure.legend()

    def write_png(self, f):
        self.__figure.savefig(f, format='png')
