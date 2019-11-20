#!/usr/bin/python

from michi import parse_switch


switch = parse_switch(name='hansi',
                      adminstatus_fname = 'data/ifAdminStatus.txt',
                      descr_fname = 'data/ifDescr.txt',
                      lastchange_fname = 'data/ifLastChange.txt',
                      operstatus_fname = 'data/ifOperStatus.txt',
                      snmpenginetime_fname = 'data/snmpEngineTime.txt',
)


print(switch)
