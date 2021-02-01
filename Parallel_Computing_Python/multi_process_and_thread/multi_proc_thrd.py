import multiprocessing as mp
import threading as thd
import time

def job(q):
    result = 0
    # here, you cannot return any value, so we changed to use queue 
    for i in range(100000):
        result += i + i**2 + i**3
    q.put(result)

def multiproc():
    q = mp.Queue()
    p1 = mp.Process(target=job, args=(q,))
    p2 = mp.Process(target=job, args=(q,))
    p1.start()
    p2.start()
    p1.join()
    p2.join()

    result1 = q.get()
    result2 = q.get()
    print('multicore: %d' % (result1 + result2))


def multithread():
    q = mp.Queue()
    th1 = thd.Thread(target=job, args=(q, ))
    th2 = thd.Thread(target=job, args=(q, ))
    th1.start()
    th2.start()
    th1.join()
    th2.join()
    result1 = q.get()
    result2 = q.get()
    print('multithread: %d' % (result1 + result2))

def normal():
    result = 0
    for _ in range(2):
        for i in range(100000):
            result += i + i**2 + i**3
    print('Normal: %d' % result)

if __name__ == '__main__':
    start_time = time.time()
    normal()
    time_1 = time.time()
    print('Normal time: ', (time_1 - start_time))
    time_2 = time.time()
    multithread()
    time_3 = time.time()
    print('Multithread time: ', (time_3 - time_2))
    time_4 = time.time()
    multiproc()
    time_5 = time.time()
    print('Multiprocess time: ', (time_5 - time_4))

