import multiprocessing as mp

def job(x):
    return x * x

def multiproc():
    pool = mp.Pool()
    result = pool.map(job, range(10))
    print(result)
    result = pool.apply_async(job, (2, ))
    print(result.get())
    multi_result = [pool.apply_async(job, (i, )) for i in range(10)]
    print([result.get() for result in multi_result])

if __name__ == '__main__':
    multiproc()
