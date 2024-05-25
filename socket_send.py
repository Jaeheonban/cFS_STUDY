import socket

packet1 = bytearray(b'\x18\x82\xc0\x00\x00\x01\x00\x00') # SAMPLE_APP_NOOP_CC
packet2 = bytearray(b'\x18\x82\xc0\x00\x00\x01\x00\x02') # SAMPLE_APP_HELLO_CC
packet3 = bytearray(b'\x18\x87\xc0\x00\x00\x01\x00\x00') # change file name
packet4 = bytearray(b'\x18\x9A\xc0\x00\x00\x01\x00\x00') # HK_NOOP_CC

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

sock.sendto(packet2, ('172.21.150.226', 1234))