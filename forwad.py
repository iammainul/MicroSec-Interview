import socket,asyncore

class forwarder(asyncore.dispatcher):
    def __init__(self, ip, port, remoteip,remoteport,backlog=5):
        asyncore.dispatcher.__init__(self)
        self.remoteip=remoteip
        self.remoteport=remoteport
        self.create_socket(socket.AF_INET,socket.SOCK_STREAM)
        self.set_reuse_addr()
        self.bind((ip,port))
        self.listen(backlog)

    def handle_accept(self):
        conn, addr = self.accept()
        # print '--- Connect --- '
        sender(receiver(conn),self.remoteip,self.remoteport)

class receiver(asyncore.dispatcher):
    def __init__(self,conn):
        asyncore.dispatcher.__init__(self,conn)
        self.from_remote_bfr=''
        self.to_remote_bfr=''
        self.sender=None

    def handle_connect(self):
        pass

    def handle_read(self):
        read = self.recv(4096)
        self.from_remote_bfr += read

    def writable(self):
        return (len(self.to_remote_bfr) > 0)

    def handle_write(self):
        sent = self.send(self.to_remote_bfr)
        self.to_remote_bfr = self.to_remote_bfr[sent:]

    def handle_close(self):
        self.close()
        if self.sender:
            self.sender.close()

class sender(asyncore.dispatcher):
    def __init__(self, receiver, remoteaddr,remoteport):
        asyncore.dispatcher.__init__(self)
        self.receiver=receiver
        receiver.sender=self
        self.create_socket(socket.AF_INET, socket.SOCK_STREAM)
        self.connect((remoteaddr, remoteport))

    def handle_connect(self):
        pass

    def handle_read(self):
        read = self.recv(4096)
        self.receiver.to_remote_bfr += read

    def writable(self):
        return (len(self.receiver.from_remote_bfr) > 0)

    def handle_write(self):
        sent = self.send(self.receiver.from_remote_bfr)
        self.receiver.from_remote_bfr = self.receiver.from_remote_bfr[sent:]

    def handle_close(self):
        self.close()
        self.receiver.close()

if __name__ == '__main__':
    forwarder('127.0.0.1',3111,'127.0.0.1',2999)
    forwarder('127.0.0.1',2999,'127.0.0.1',3111)
    asyncore.loop()
