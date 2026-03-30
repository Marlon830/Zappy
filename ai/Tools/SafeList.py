import threading

class SafeList:
    def __init__(self, l):
        self.l = l
        self.lock = threading.Lock()
        
    def append(self, value):
        self.lock.acquire()
        self.l.append(value)
        self.lock.release()
    
    def pop(self, index=-1):
        self.lock.acquire()
        value = self.l.pop(index)
        self.lock.release()
        return value

    def length(self):
        self.lock.acquire()
        length = len(self.l)
        self.lock.release()
        return length
    
    def get(self):
        self.lock.acquire()
        l = self.l.copy()
        self.lock.release()
        return l
    
    def clear(self):
        self.lock.acquire()
        self.l.clear()
        self.lock.release()
    
    def remove(self, value):
        self.lock.acquire()
        self.l.remove(value)
        self.lock.release()
    
    def __len__(self):
        self.lock.acquire()
        length = len(self.l)
        self.lock.release()
        return length