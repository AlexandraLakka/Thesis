from algorithms.matrix import multiply
from prometheus_client import start_http_server
from sys import getsizeof
import time
import random

if __name__ == "__main__":
    start_http_server(8000)
    start_time = time.time()
    A = [lst[:] for lst in [random.sample(range(2000), 450)]*450]
    B = [lst[:] for lst in [random.sample(range(2000), 450)]*450]

    C = multiply.multiply(A, B)
    print(C)

    print("--- Size of A: %s bytes ---" % (getsizeof(A)))
    print("--- Size of B: %s bytes ---" % (getsizeof(B)))
    input = getsizeof(A) + getsizeof(B)
    print("--- Size of input: %s bytes" % (input))
    print("--- Execution time: %s seconds ---" % (round(time.time() - start_time, 2)))
