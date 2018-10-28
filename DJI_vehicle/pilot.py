#!/usr/bin/python
# -*- coding: UTF-8 -*-

import socket

port=8000
host='localhost'
s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

s.sendto(b'Hello World!',(host,port))


