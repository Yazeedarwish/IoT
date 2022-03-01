import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print("Socket successfully created")

port = 7879
s.connect(('192.168.100.12', port))

while True:
    message = input('enter your message:')
    if message == 'CLOSE SOCKET':
        s.send(message.encode())
        print('the socket is closed! \n bye')
        break
    else:
        s.send(message.encode())
        print('capitalized message:', s.recv(1024).decode())
s.close()
