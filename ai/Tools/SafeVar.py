import threading

class SafeVar:
    def __init__(self, value):
        self.value = value
        self.lock = threading.Lock()
    
    def set(self, value):
        self.lock.acquire()
        self.value = value
        self.lock.release()
    
    def get(self):
        self.lock.acquire()
        value = self.value
        self.lock.release()
        return value