from random import randint
import os
from State.Marge import Marge
import sys

class Homer:
    def __init__(self, ia):
        self.ia = ia
        self.stones = [("linemate", 9), ("deraumere", 8), ("sibur", 10), ("mendiane", 5), ("phiras", 6), ("thystame", 1)]
        self.to_hatch = 5 - self.ia.communication.connect_nbr
        self.processes = []
        self.has_forked = False
        self.has_hatched = False
        self.stones_dropped = False
        self.nb_incantation = 0

    def __del__(self):
        for process in self.processes:
            if process != 0:
                os.waitpid(process, 0)

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

    def check_stones(self):
        for stone in self.stones:
            if self.ia.inventory[stone[0]] >= stone[1]:
                self.stones.remove(stone)

    def incantation(self):
        if self.ia.communication.nb_marge.get() == 5 and self.nb_incantation != 8 and self.stones_dropped:
            self.ia.communication.messages_to_send.append("Incantation\n")
            self.nb_incantation += 1
            return 1
        self.ia.communication.messages_to_send.append("Broadcast " + self.ia.team_name + "_QUOICOUBEH\n")
        for stone in self.ia.inventory:
            if self.ia.inventory[stone] != 0 and stone != "food":
                self.ia.communication.messages_to_send.append("Set " + stone +"\n")
                return 2
        self.stones_dropped = True
        return 1

    def action(self):
        if not self.has_forked and self.to_hatch != 0:
            for _ in range(self.to_hatch):
                self.ia.communication.messages_to_send.append("Fork\n")
            self.has_forked = True
            print("CACAPAGNANGEANHOICQOUBER", self.to_hatch, self.ia.communication.connect_nbr, file=sys.stderr)
            return self.to_hatch # + 1
        elif not self.has_hatched:
            process = os.fork()
            self.processes.append(process)
            self.has_hatched = True
            if process == 0:
                from ai import AI
                print("CACAPAGNANNGEAJNFN:", self.ia.communication.server_address[0], self.ia.communication.server_address[1], self.ia.team_name, file=sys.stderr)
                ia = AI(self.ia.communication.server_address[0], self.ia.communication.server_address[1], self.ia.team_name, Marge)
                ia.run()
                sys.exit(0)
        self.check_stones()
        if not self.stones:
            return self.incantation()
        else:
            if self.ia.inventory["food"] < 50:
                action_list = self.find_ressources("food")
                if action_list:
                    for action in action_list:
                        self.ia.communication.messages_to_send.append(action)
                    return len(action_list)
                else:
                    self.random_move()
                    return 1
            else:
                if len(self.stones) != 0:
                    action_list = self.find_ressources(self.stones[randint(0, len(self.stones) - 1)][0])
                    if action_list:
                        for action in action_list:
                            self.ia.communication.messages_to_send.append(action)
                        return len(action_list)
                    else:
                        self.random_move()
                        return 1
            return 0
