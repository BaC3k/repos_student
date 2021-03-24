import time
start_time = time.perf_counter()
N=range(1000)
arr=[]
for i in N:
    arr.append(i)
print(" %f seconds \n"  %(time.perf_counter() - start_time))
