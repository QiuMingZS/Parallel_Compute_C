import multiprocessing as mp

def job1(q):
    print('Job1: I am coming...')
    result = 0
    # here, you cannot return any value, so we changed to use queue 
    for i in range(100):
        result += i 
    q.put(result)

def job2(q):
    print('Job2: I am coming...')
    result = 0
    # here, you cannot return any value, so we changed to use queue 
    for i in range(100):
        result -= i
    q.put(result)




if __name__ == '__main__':
    q = mp.Queue()
    p1 = mp.Process(target=job1, args=(q,))
    p2 = mp.Process(target=job2, args=(q,))
    p1.start()
    p2.start()
    p1.join()
    p2.join()

    result1 = q.get()
    result2 = q.get()
    print('result1: %d' % result1)
    print('result2: %d' % result2)
    print('final result: %d' % (result1 + result2))




