#!/usr/bin/python
# -*- coding: UTF-8 -*-

import socket

port = 8000
host = 'localhost'
socket_obj = -1

'''
cmd is down below

"Takeoff",                
"Landing",
"MoveUp, 
"MoveDown, 
"MoveForward, 
"MoveBack, 
"MoveLeft, 
"MoveRight, 
"TurnLeft, 
"TurnRight, 
'''
def ExecuteCmd(cmd,x = 0):
    print(cmd+" " + str(x))
    global socket_obj
    if socket_obj == -1:
        socket_obj = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    socket_obj.sendto(bytes((cmd+" "+ str(x)),encoding = "utf8"),(host,port))
    return

if __name__ == "__main__":

    ExecuteCmd("MoveUp",2)