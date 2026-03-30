import socket
from Tools.SafeList import SafeList
from Tools.SafeVar import SafeVar
from State.Marge import Marge
import sys
import os
import threading

COMMANDS = ["Forward", "Right", "Left", "Look", "Inventory", "Broadcast", "Connect_nbr", "Fork", "Eject", "Take", "Set", "Incantation"]

class Communication:
    def __init__(self, server_address, team_name):
        self.server_address = server_address
        self.sent_messages = SafeList([])
        self.messages_to_send = SafeList([])
        self.responses = SafeList([])
        self.has_received_messsage_from_homer = SafeVar(False)
        self.nb_marge = SafeVar(0)
        self.message_pos = SafeVar(-1)
        self.temp_message_pos = SafeVar(-1)
        self.sem_has_recvd_brdcst = threading.Semaphore(0)
        self.team_name = SafeVar(team_name)
        self.is_dead_received = SafeVar(False)
        self.process = 0
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.s.connect(server_address)
        data = ""
        while len(data) == 0 or data[-1] != '\n':
            data += self.s.recv(1024).decode('utf-8')
        self.s.sendall((team_name + "\n").encode('utf-8'))
        data = ""
        while len(data) == 0 or data[-1] != '\n':
            data += self.s.recv(1024).decode('utf-8')
        if "ko" in data.lower():
            print("Error: an error occured while connecting to the server.\n(hint: the team name is probably not valid)", file=sys.stderr)
            sys.exit(84)
        print("FIRST_RECEVegnazuoghoiIED:", data)
        self.connect_nbr = int(data.split("\n")[0])
        self.map_size = (int(data.split("\n")[1].split(" ")[0]), int(data.split("\n")[1].split(" ")[1]))
        if self.connect_nbr != 0:
            self.process = os.fork()
            if self.process == 0:
                from ai import AI
                ia = AI(server_address[0], server_address[1], team_name, Marge)
                ia.run()
                sys.exit(0)
    
    def __del__(self):
        # for process in self.processes:
        #     process.wait()
        if self.process != 0:
            os.waitpid(self.process, 0)
        self.s.close()

    def send_messages(self):
        print("SENDING:", self.messages_to_send.get())
        while len(self.messages_to_send) > 0:
            if self.is_dead_received.get():
                return
            message_to_send = self.messages_to_send.pop(0)
            self.s.sendall(message_to_send.encode('utf-8'))
            print("SENT:", message_to_send)
            self.sent_messages.append(message_to_send.split(" ")[0])

    def receive_broadcasted_messages(self, sem_brdcst_msg, sem_brdcst_msg2):
        while True:
            sem_brdcst_msg.acquire()
            sem_brdcst_msg2.acquire()
            self.message_pos.set(self.temp_message_pos.get())
            self.sem_has_recvd_brdcst.release()

    def receive_messages(self, semaphore, n, sem_brdcst_msg):
        while True:
            data = ""
            while len(data) == 0 or data[-1] != '\n':
                print("WAITING:", data)
                data += self.s.recv(1024).decode('utf-8')
                if len(data) == 0:
                    self.is_dead_received.set(True)
                    for _ in range(n.get()):
                        semaphore.release()
                    return
            print("RECEIVED:", data)
            datas = data.split('\n')
            datas.pop()
            for data in datas:
                if "dead" in data:
                    self.is_dead_received.set(True)
                    for _ in range(n.get()):
                        semaphore.release()
                    return
                elif "message" in data:
                    self.message_pos.set(-1)
                    data = data.split(", ")
                    data[0] = data[0].split(" ")[1]
                    # self.responses.append(("Message", data[0], data[1]))
                    if self.team_name.get() in data[1].split('_')[0] and "QUOICOUBEH" in data[1].split('_')[1]:
                        self.has_received_messsage_from_homer.set(True)
                    if self.team_name.get() in data[1].split('_')[0] and "DONUTS" in data[1].split('_')[1]:
                        self.nb_marge.set(self.nb_marge.get() + 1)
                    self.temp_message_pos.set(int(data[0]))
                    sem_brdcst_msg.release()
                # TODO: vérifier les cas particulier type eject, broadcast etc
                elif "eject" in data:
                    pass
                elif "Current level" in data:
                    pass
                elif "Elevation underway" in data:
                    for elem in self.sent_messages.get():
                        if "Incantation" in elem:
                            self.sent_messages.remove(elem)
                            semaphore.release()
                            break
                else:
                    print("SEND SEMAPHORE")
                    msg_type = self.sent_messages.pop(0)
                    self.responses.append((msg_type, data))
                    # print("MSG_RECEIVED:", msg_type, data, file=sys.stderr)
                    semaphore.release()
