from random import randint
import sys

class Marge:
    def __init__(self, ia):
        self.ia = ia
        self.with_homer = False

    def find_ressources(self, to_find):
        action_list = []
        line_nb = 1
        middle = 0
        n = 0
        index = 0
        if to_find in self.ia.view[0]:
            for _ in range(self.ia.view[0].count(to_find)):
                action_list.append("Take " + to_find + "\n")
        for tile in self.ia.view[1:]:
            if n == 1 + 2 * line_nb:
                line_nb += 1
                middle = index + line_nb
                n = 0
            n += 1
            if to_find in tile:
                for _ in range(line_nb):
                    action_list.append("Forward\n")
                if index < middle:
                    action_list.append("Left\n")
                elif index > middle:
                    action_list.append("Right\n")
                return action_list
            index += 1
        return action_list


    def random_move(self):
        self.ia.communication.messages_to_send.append(["Forward\n", "Left\n", "Right\n"][randint(0, 2)])

    def follow_homer(self):
        try:
            act_msg_pos = self.ia.communication.message_pos.get()
            print("MESSAGE_POS:", act_msg_pos, file=sys.stderr)
            if act_msg_pos == -1:
                return 0
            if act_msg_pos == 0 and not self.with_homer:
                self.ia.communication.messages_to_send.append("Broadcast " + self.ia.team_name + "_DONUTS\n")
                self.with_homer = True
                return 1
            if act_msg_pos == 0:
                return 0
            print("LIST OF MOVEMENTS: ", self.ia.movements[act_msg_pos], file=sys.stderr)
            for movement in self.ia.movements[act_msg_pos]:
                self.ia.communication.messages_to_send.append(movement)
            self.ia.communication.message_pos.set(-1)
            return len(self.ia.communication.messages_to_send)
        except:
            print("ERROR: Cannot convert to int:", self.ia.communication.message_pos.get(), file=sys.stderr)
            return 0

    def action(self):
        if self.ia.communication.has_received_messsage_from_homer.get():
            self.ia.communication.sem_has_recvd_brdcst.acquire()
            return self.follow_homer()
        if self.ia.inventory["food"] < 50:
            action_list = self.find_ressources("food")
            if action_list:
                for action in action_list:
                    self.ia.communication.messages_to_send.append(action)
                return len(action_list)
            else:
                self.random_move()
                return 1
        return 0