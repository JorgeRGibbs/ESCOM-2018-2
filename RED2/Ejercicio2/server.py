#!/usr/bin/env python
"USAGE: %s <server> <word> <port>"
from socket import *    # import *, but we'll avoid name conflict
from sys import argv
if len(argv) != 2:
print __doc__ % argv[0]
else:
sock = socket(AF_INET, SOCK_DGRAM)
sock.bind(('',int(argv[1])))
while 1:    # Run until cancelled
message, client = sock.recvfrom(256) # <=256 byte datagram
print "Client connected:", client
sock.sendto(message, client)