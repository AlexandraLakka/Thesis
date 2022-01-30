from algorithms.maths import factorial
#from prometheus_client import start_http_server
import time
from sys import getsizeof

if __name__ == "__main__":
    #start_http_server(8000)
    start_time = time.time()

    input = 525000
    result = factorial(input)
    print(result)

    print("---Input: %s ---" % (input))
    print("---Size of input: %s bytes---" % (getsizeof(input)))
    print("--- Execution time: %s seconds ---" % (round(time.time() - start_time, 2)))
