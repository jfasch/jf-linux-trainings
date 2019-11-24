#!/usr/bin/python

import sqlite3 as db


filename = '/tmp/switch-zeug.sqlite3'
connection = db.connect(filename)
cursor = connection.cursor()


cursor.execute('''
CREATE TABLE switches (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT UNIQUE,
    uptime INTEGER);
''')

cursor.execute('''
CREATE TABLE interfaces (
    internal_id INTEGER PRIMARY KEY AUTOINCREMENT,
    switch_id INTEGER,
    name TEXT,
    number TEXT,
    adminstatus INTEGER,
    operstatus INTEGER,
    lastchange INTEGER,
    FOREIGN KEY(switch_id) REFERENCES switches(id));
''')

cursor.execute('''
CREATE UNIQUE INDEX if2switch ON interfaces(switch_id, name);
''')

cursor.execute('PRAGMA foreign_keys = ON;')

connection.commit()
