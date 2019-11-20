import datetime

class Switch:
    def __init__(self, name, interfaces, uptime):
        assert isinstance(uptime, datetime.timedelta)

        self.name = name
        self.interfaces = interfaces
        self.uptime = uptime

    def __str__(self):
        ifstrs = '\n'.join([' '*8 + str(i) + ',' for i in self.interfaces])
        swlines = [
            'Switch(',
            f'    name="{self.name}",',
            '    interfaces=[',
            f'{ifstrs}]',
            f'    uptime={self.uptime})'
        ]
        return '\n'.join(swlines)
