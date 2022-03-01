import socket
import threading

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print("Socket successfully created")

port = 7878
s.bind(('192.168.8.172', port))
print("socket bound to %s" % (port))

s.listen(5)
print("server is listening on port:",port)

Client_counter =0
Client_info =[]

def thread_clients(c,addr):
        global Client_counter
        global Client_info
        while True:
            sentence = c.recv(1024).decode()
            if sentence == 'CLOSE SOCKET':
                Client_counter -= 1
                print("connection with client with address:", addr, "has been terminated !")
                print('current number of clients= ', Client_counter)
                Client_info.remove(addr)
                print("current client's info", Client_info)
                break
            else:
                Capital_Sentence = sentence.upper()
                c.send(Capital_Sentence.encode())
                print(Capital_Sentence)
        c.close()

while True:
    c, addr = s.accept()
    Client_counter += 1
    print('current number of clients =', Client_counter)
    Client_info.append(addr)
    print("client's info" , Client_info)
    thread = threading.Thread(target=thread_clients, args=(c,addr))
    thread.start()

