import threading
from queue import Queue
import copy
import time

def job(l, q):
    result = sum(l)
    q.put(result)

def multithreading(l):
    q = Queue()
    threads = []
    for i in range(4):
        t = threading.Thread(target=job, args=(copy.copy(l), q), name='T%i' % i)
        t.start()
        threads.append(t)
    [t.join() for t in threads]
    total = 0
    for _ in range (4):
        total += q.get()
        print(total)

def normal(l):
    total = sum(l)
    print(total)

if __name__ == '__main__':
    l = list(range(100000))
    t0 = time.time()
    normal(l*4)
    t1 = time.time()
    print('normal: ', t1 - t0)
    t2 = time.time()
    multithreading(l)
    t3 = time.time()
    print('multithreading: ', t3 - t2)
