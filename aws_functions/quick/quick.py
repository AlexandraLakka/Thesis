from algorithms.sort import merge_sort,quick_sort
#from prometheus_client import start_http_server
import random
import time
from sys import getsizeof

if __name__ == "__main__":
    #start_http_server(8000)
    start_time = time.time()

    my_list = [random.randrange(1, 2000000, 1) for i in range(2000000)]
    #my_list = merge_sort(my_list)
    my_list = quick_sort(my_list)
    print(my_list)

    print("--- Size of input: %s" % (getsizeof(my_list)))
    print("--- Execution time: %s seconds ---" % (round(time.time() - start_time, 2)))
