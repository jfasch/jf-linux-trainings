import pprint


class Stats:
    MT, ST = 'mt', 'st'

    def __init__(self):
        self.stats = {}

    def add_sample(self, which, num_timers, key, value):
        num_timers_entry = self.stats.setdefault(num_timers, {})
        which_entry = num_timers_entry.setdefault(which, {})
        assert key not in which_entry
        which_entry[key] = value

    def iter_sorted(self):
        for num_timers in sorted(self.stats.keys()):
            yield num_timers, self.stats[num_timers]['mt'], self.stats[num_timers]['st']

    def write(self, f):
        pprint.pprint(self.stats, stream=f)

    @classmethod
    def read(cls, f):
        obj = cls()
        obj.stats = eval(f.read())
        return obj
