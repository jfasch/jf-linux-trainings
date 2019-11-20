#!/usr/bin/python

class Switch:
    'hier geschieht ein wunder'

    def __init__(self, name, interfaces):
        'hier geschieht das erste wunder'
        


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
    print(sw.name)
