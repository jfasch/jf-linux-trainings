#!/usr/bin/python

from switch import Switch
from interface import Interface

import sqlite3 as db
import datetime


filename = '/tmp/switch-zeug.sqlite3'
connection = db.connect(filename)
cursor = connection.cursor()

def insert_switches(switches, cursor):
    for switch in switches:
        cursor.execute('INSERT INTO switches(name, uptime) values(?,?)', (switch.name, switch.uptime.total_seconds()))
        switchid = cursor.lastrowid
        for iface in switch.interfaces:
            cursor.execute('INSERT INTO interfaces(switch_id, name, number, adminstatus, operstatus, lastchange)'
                           ' values(?,?,?,?,?,?)',
                           (switchid, iface.name, iface.number,
                            iface.adminstatus, iface.operstatus, iface.last_change))


sw01 = Switch(
    'sw01',
    interfaces=[
        Interface(name='if1', number=1,
                  adminstatus=Interface.UP, operstatus=Interface.DOWN, 
                  last_change=datetime.datetime(year=2019, month=11, day=20, hour=13, minute=17, second=33)),
        Interface(name='if2', number=2, adminstatus=Interface.UP, operstatus=Interface.DOWN, 
                  last_change=datetime.datetime(year=2019, month=11, day=20, hour=13, minute=17, second=33)),
    ],
    uptime=datetime.timedelta(seconds=1))

sw02 = Switch(
    'sw02',
    interfaces=[
        Interface(name='if1', number=1,
                  adminstatus=Interface.UP, operstatus=Interface.DOWN, 
                  last_change=datetime.datetime(year=2019, month=11, day=20, hour=13, minute=17, second=33)),
        Interface(name='if2', number=2, adminstatus=Interface.UP, operstatus=Interface.DOWN, 
                  last_change=datetime.datetime(year=2019, month=11, day=20, hour=13, minute=17, second=33)),
        Interface(name='if3', number=2, adminstatus=Interface.UP, operstatus=Interface.DOWN, 
                  last_change=datetime.datetime(year=2019, month=11, day=20, hour=13, minute=17, second=33)),
    ],
    uptime=datetime.timedelta(seconds=1))

insert_switches((sw01, sw02), cursor)
connection.commit()
