#!/usr/bin/python

from michi import parse_switch
from error import SwitchZeugError, MichisError

import argparse

parser = argparse.ArgumentParser()
parser.add_argument('adminstatus', help='admin status file blah')
parser.add_argument('descr', help='descr file blah')
parser.add_argument('lastchange', help='last change file blah')
parser.add_argument('operstatus', help='oper status file blah')
parser.add_argument('snmpenginetime', help='SNMP engine file blah')



try:
    switch = parse_switch(name='hansi',
                          adminstatus_fname = 'data/ifAdminStatus.txt',
                          descr_fname = 'data/ifDescr.txt',
                          lastchange_fname = 'data/ifLastChange.txt',
                          operstatus_fname = 'data/ifOperStatus.txt',
                          snmpenginetime_fname = 'data/snmpEngineTime.txt',
    )
    print(switch)
except MichisError as e:
    print('hmm. suboptimal. im switchzeug is was faul, der michi wars: ', e)
except SwitchZeugError as e:
    print('hmm. suboptimal. im switchzeug is was faul: ', e)
# all other exceptions pass unhandled
