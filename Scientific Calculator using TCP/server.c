#importing necessary libraries
from socket import *

#setting up the welcoming port of the TCP server

welcoming_port=50001

#AF_INET for IPV4 and SOCK_STREAM for TCP
serverSocket=socket(AF_INET,SOCK_STREAM)
serverSocket.bind(("",welcoming_port))

#I will be using ANS global variable to store the answer of the previous Calculation
ANS=0

#I will be using a flag to denote whether calculation has been performed atleast once 
#since then only ANS variable will make sense as if user enters ANS for the first time in calculation then 
# we should return error

is_ANS_calculated=False

def isNumeric(num):
    digits="0123456789"
    count_neg_sign=0
    count_dots=0
    if num[0]=='-':
        count_neg_sign=1
    if num[-1]=='.':
        return False
    #if the number starts with a negative sign
    if count_neg_sign==1:
        for letter in num[1:]:
            if letter in digits:
                continue
            elif letter=='.':
                count_dots+=1
                if count_dots>1:
                    return False
            else:
                return False
    else:
        for letter in num:
            if letter in digits:
                continue
            elif letter=='.':
                count_dots+=1
                if count_dots>1:
                    return False
            else:
                return False
    return True

#the operands list will contain all the oprands 
def add(operands):
    global ANS
    global is_ANS_calculated
    temp_sum=0
    for operand in operands:
        if operand=="ANS":
            temp_sum+=ANS
        elif operand!="ANS" and not isNumeric(operand):
            return "INV ARGS"
        else:
            temp_sum+=float(operand)
    ANS=temp_sum
    is_ANS_calculated=True
    return ANS

#the operands list will contain all the oprands 
def sub(operands,usePrevANS=False):
    global ANS
    global is_ANS_calculated
    operand=operands[0]
    temp_diff=0
    if operand=="ANS":
        temp_diff=ANS
    elif operand!="ANS" and not isNumeric(operand):
        return "INV_ARGS"
    else:
        temp_diff=float(operands[0])
    i=1
    for operand in operands[1:]:
        if operand=="ANS":
            temp_sum-=ANS
        elif operand!="ANS" and not isNumeric(operand):
            return "INV ARGS"
        else:
            temp_diff-=float(operand)
    ANS=temp_diff
    is_ANS_calculated=True
    return ANS

#the operands list will contain all the oprands 
def mul(operands,usePrevANS=False):
    global ANS
    global is_ANS_calculated
    operand=operands[0]
    temp_mul=1
    if operand=="ANS":
        temp_mul=ANS
    elif operand!="ANS" and not isNumeric(operand):
        return "INV_ARGS"
    else:
        temp_mul=float(operands[0])
    i=1
    for operand in operands[1:]:
        if operand.upper()=="ANS":
            temp_mul*=ANS
        elif operand.upper()!="ANS" and not isNumeric(operand):
            return "INV ARGS"
        else:
            temp_mul*=float(operand)
    ANS=temp_mul
    is_ANS_calculated=True
    return ANS

def div(operands):
    global ANS
    global is_ANS_calculated
    temp_ans=1
    num=operands[0]
    den=operands[1]
    
    if num=="ANS":
        num=ANS
    elif num!="ANS" and not isNumeric(num):
        return "INV_ARGS"
    
    if den=="ANS":
        den=ANS
    elif den!="ANS" and not isNumeric(den):
        return "INV_ARGS"
    
    if float(den)==0:
        return "DZERO"
    else:
        ANS=float(num)/float(den)
        is_ANS_calculated=True
        return ANS
    
def power(operands,usePrevANS=False):
    global ANS
    global is_ANS_calculated
    temp_ans=1
    num1=operands[0]
    num2=operands[1]
    
    if num1=="ANS":
        num1=ANS
    elif num1!="ANS" and not isNumeric(num1):
        return "INV_ARGS"
    
    if num2=="ANS":
        num2=ANS
    elif num2!="ANS" and not isNumeric(num2):
        return "INV_ARGS"
    
    ANS=pow(float(num1),float(num2))
    is_ANS_calculated=True
    return ANS

def preProcess(command):
    operations=["ADD","SUB","MUL","DIV","POW"]
    arguments=command.split(" ")
    operation=arguments[0] #what operation to perform now
    if operation not in operations:
        return "INV CMD"
    else:
        #if the operation is add , sub or mul
        if operation in operations[:3]:
            if arguments[1]!="-n":
                return "INV ARGS"
            elif not isNumeric(arguments[2]):
                return "INV CMD"
            elif int(arguments[2])!=len(arguments)-3 or int(arguments[2])==1:
                return "INSUF ARGS"
            else:
                return calculate(operation,arguments[3:])
        #if the operator is div or power then it will only have 2 args
        elif operation in operations[3:] and len(arguments)==3:
            return calculate(operation,arguments[1:])
        else:
            return "INSUF ARGS"

def calculate(operation,operands):
    global ANS
    global is_ANS_calculated
    if "ANS" in operands and not is_ANS_calculated:
        return "ANS NOT YET CALCULATED , BUT USED"
    else:
        if operation=="ADD":
            return add(operands)
        elif operation=="SUB":
            return sub(operands)
        elif operation=="MUL":
            return mul(operands)
        elif operation=="DIV":
            return div(operands)
        else:
            return power(operands)

serverSocket.listen(10) 
print("Server is Ready !!")

while True:
#     print("Listening....")
    connection , address = serverSocket.accept()
    print("Client Detail : "+str(address))
    command=(connection.recv(10000))
    command=command.decode("utf-8")
    print(command)
    msg_to_send=bytes(str(preProcess(command)),"utf-8")
    connection.send(msg_to_send)
    connection.close()
