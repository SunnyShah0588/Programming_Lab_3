import sys
import socket 

sc_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sc_client.connect(("192.168.7.2",5540))

filename = raw_input("ENTER THE NAME OF THE FILE YOU WANT FROM SERVER : ")

while True:
    sc_client.send(filename)
    sData = sc_client.recv(1024)
    download = open(filename,"wb")
    while sData:
        download.write(sData)
        sData = sc_client.recv(1024)
    
    break
sc_client.close()
