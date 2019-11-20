import datetime

class Switch:
    def __init__(self, name, interfaces, uptime):
        assert isinstance(uptime, datetime.timedelta)

        self.name = name
        self.interfaces = interfaces
        self.uptime = uptime
