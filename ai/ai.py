import threading
import time
from communication import Communication
from Tools.SafeVar import SafeVar
import sys
from State.Homer import Homer

class AI:
    def __init__(self, host, port, name, bot_state):
        self.team_name = name
        self.communication = Communication((host, int(port)), name)
        self.alive = True
        self.state = bot_state(self)
        self.inventory = {"food": 10, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
        self.view = [[] for i in range(82)]
        self.movements = {1: ["Forward\n"], 2: ["Forward\n", "Left\n", "Forward\n"], 3: ["Left\n", "Forward\n"], 4: ["Left\n", "Forward\n", "Left\n", "Forward\n"],
                        5: ["Left\n", "Left\n", "Forward\n"], 6: ["Right\n", "Forward\n", "Right\n", "Forward\n"], 7: ["Right\n", "Forward\n"], 8: ["Forward\n", "Right\n", "Forward\n"]}

    def response_analyse(self):
        for response in self.communication.responses.get():
            print("RESPONSE:", response)
            if "Inventory" in response[0]:
                tab = response[1][:-1]
                inventory = tab.strip('][').split(', ')
                for item in inventory:
                    try:
                        item = item.split(" ")
                        item = [x for x in item if x]
                        self.inventory[item[0]] = int(item[1])
                    except:
                        print("BEFORE CRASH:", file=sys.stderr)
                        print("IL Y A UN PROBLEME DANS LA REPONSE:", response, file=sys.stderr)
                        print(self.inventory, file=sys.stderr)
                        print(item, file=sys.stderr)
                        print(item[0], file=sys.stderr)
                        print(item[1], file=sys.stderr)
                        print("FIN", file=sys.stderr)
                        break
            if "Look" in response[0]:
                print("RESPONSE[1]:", response[1], file=sys.stderr)
                view = response[1].strip().strip('][').split(',')
                print("VIEW:", view, file=sys.stderr)
                for i in range(len(view)):
                    item = view[i].split(" ")
                    item = [x for x in item if x]
                    print("ITEM:", item, "I:", i, file=sys.stderr)
                    self.view[i] = item
        self.communication.responses.clear()

    def run(self):
        n = SafeVar(0)
        semaphore = threading.Semaphore(0)
        sem_brdcst_msg = threading.Semaphore(0)
        sem_brdcst_msg2 = threading.Semaphore(0)
        t = threading.Thread(target=self.communication.receive_messages, args=(semaphore, n, sem_brdcst_msg,))
        t2 = threading.Thread(target=self.communication.receive_broadcasted_messages, args=(sem_brdcst_msg, sem_brdcst_msg2,))
        t.start()
        t2.start()
        while True:
            print("NUM OF SEMAPHORE TO WAIT:", n.get())
            for _ in range(n.get()):
                # if isinstance(self.state, Homer):
                #     print("HERE2-1", file=sys.stderr)
                semaphore.acquire()
            self.communication.message_pos.set(-1)
            sem_brdcst_msg2.release()
            # self.message_pos = self.communication.message_pos.get()
                # if isinstance(self.state, Homer):
                #     print("HERE2-2", file=sys.stderr)
            print("HERE3")

            if self.communication.is_dead_received.get() == True:
                print("Player is DEAD")
                break

            self.response_analyse()
            nb_actions = self.state.action()
            while nb_actions > 8:
                nb_actions -= 1
                self.communication.messages_to_send.pop()
            n.set(nb_actions)
            self.communication.messages_to_send.append("Inventory\n")
            self.communication.messages_to_send.append("Look\n")
            n.set(n.get() + 2)
            self.communication.send_messages()
            print("HERE4")

        t.join()
        t2.join()

    def change_state(self, state):
        self.communication.messages_to_send.clear()
        self.state = state
