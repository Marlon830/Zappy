class Dumb:
    def __init__(self, ia):
        self.ia = ia

    def action(self):
        self.ia.communication.messages_to_send.append("Forward\n")
        self.ia.communication.messages_to_send.append("Left\n")
        return 2
