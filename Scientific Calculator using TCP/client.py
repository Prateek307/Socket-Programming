#importing required libraries

import sys 
from socket import *

#setting up initial server configurations

'''I am using my Local PVT IP address , so that all computers running client code connected to my Wi-Fi router can
communicate
'''

# servername="10.1.19.220"
servername="192.168.29.249"
localhost="127.0.0.1" #if we want to use local host as server IP address
serverport=50001


error_msg={
            "INV ARGS":"Invalid arguments",
            "INSUF ARGS":"Insufficient arguments",
            "DZERO":"Divide by zero",
            "INV CMD":"Invalid command",
    "ANS NOT YET CALCULATED , BUT USED":"ANS NOT YET CALCULATED , BUT USED"
}

#creating a loop so that we can constantly take input from user , and when user presses exit we must exit

while True:
    #creating the client socket , AF_INET is for IPV4 use and SOCK_STREAM is for TCP 
    clientSocket=socket(AF_INET,SOCK_STREAM)
    clientSocket.connect((servername,serverport))
    command=""
    command=input("Client : ")
    if command.lower()=="quit":
        clientSocket.close()
        break
    args=command.split()
    encoded_cmd=bytes(command,"utf-8")
    
    #send the command
    clientSocket.sendall(encoded_cmd)
    msg=clientSocket.recv(10000) #a buffer of 10,000 characters
    msg=msg.decode("utf-8")
    
    print("Server : ",msg)
    print("Client : ",end="")
    #Now we will be checking if the msg received is an error message 
    if msg in error_msg.keys():
        print(error_msg[msg])
    else:
        print("Result of operation is : ",msg)
    print("\n")
