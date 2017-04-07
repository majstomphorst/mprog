class Queue(object):
    def __init__(self):
        self.lijst = []
        
    def add(self, item):
        self.lijst.append(item)
        
    def pop(self):
        self.lijst.pop(0)
    
    def print_queue(self):
        print(self.lijst)
        
    def clean(self):
        del self.lijst[:]

lijst = Queue()
lijst.add(1)
lijst.add("hoi")
lijst.add(4)
lijst.print_queue()
lijst.pop()
lijst.print_queue()
lijst.add("wij zijn de baas")
lijst.print_queue()
lijst.clean()
lijst.print_queue()