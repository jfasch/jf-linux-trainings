#!/usr/bin/python

from michi import parse_switch
from error import SwitchZeugError, MichisError

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
