def __getsize(msg):
    return ord(msg[:1])

def __getmsg(msg):
    return msg[1:__getsize(msg)]

def send(socket, data, flags=None):
    size = chr(len(data))
    socket.send(size + data)

def recv(socket, buffersize, flags=None):
    tmp = socket.recv(buffersize)
    size = __getsize(tmp)
    data = __getmsg(tmp)
    while len(data) < size:
        data += socket.recv(buffersize)
    return data
