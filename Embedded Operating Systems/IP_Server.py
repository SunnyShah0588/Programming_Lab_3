import sys
import socket 
import os

host=''
port=5540
sc_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # Create a socket object

'''s = socket.socket (socket_family, socket_type, protocol=0)
Here is the description of the parameters −

socket_family: This is either AF_UNIX or AF_INET, as explained earlier.AF_INET is an address family that is used to designate the type of addresses that your socket can communicate with (in this case, Internet Protocol v4 addresses). 

socket_type: This is either SOCK_STREAM or SOCK_DGRAM.

protocol: This is usually left out, defaulting to 0.

The family of protocols that is used as the transport mechanism. These values are constants such as AF_INET, PF_INET, PF_UNIX, PF_X25, and so on.
type    The type of communications between the two endpoints, typically SOCK_STREAM for connection-oriented protocols and SOCK_DGRAM for connectionless protocols.'''

sc_server.bind((host,port))
sc_server.listen(10)
print "Server in listening mode " 

bFileFound = 0

while True:
    con,addr = sc_server.accept()
    print addr
    filename = con.recv(1024)

    for file in os.listdir(os.getcwd()):
        if file == filename:
            bFileFound = 1
            break
        
    if bFileFound == 0:
        print filename+"  THIS FILE IS NOT PRESENT ON SERVER"
        
    else:
        print filename+"  File Found"
   
        ClientFile = open(os.getcwd()+"/"+filename,"r")
        sRead = ClientFile.read(1024)
        while sRead:
            con.send(sRead)
            sRead = ClientFile.read(1024)
        print "FILE SEND TO CLIENT AS PER REQUEST"       
    break

con.close()
sc_server.close()
