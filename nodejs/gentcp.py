#!/usr/bin/python
import socket
port = 8124
ip = "127.0.0.1"
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
s.connect((ip,port));
s.send("helllooooo");
