#!/usr/bin/python

class Switch:
    def __init__(self, name, interfaces):
        self.name = name
        self.interfaces = interfaces

meine_interfaces = [
    
]

mein_switch = Switch('sw01', interfaces=meine_interfaces)

alle_switches = [
    mein_switch,
    Switch('sw05', interfaces=[]),
    Switch('sw07', interfaces=[]),
    Switch('sw42', interfaces=[]),
    Switch('sw28', interfaces=[]),
]

for sw in alle_switches:
    print('name:', sw.name, ', interfaces:', sw.interfaces)
