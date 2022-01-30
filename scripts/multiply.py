from algorithms.matrix import multiply
from prometheus_client import start_http_server
from sys import getsizeof
import time
import random

def main():
    start_http_server(8000)
    start_time = time.time()
    A = [random.sample(range(2000), 940) for _ in range(254)]
    B = [random.sample(range(2000), 679) for _ in range(940)]

    C = multiply.multiply(A, B)
    print(C)

    print("--- Size of A: %s bytes ---" % (getsizeof(A)))
    print("--- Size of B: %s bytes ---" % (getsizeof(B)))
    input = getsizeof(A) + getsizeof(B)
    print("--- Size of input: %s bytes" % (input))
    print("--- Execution time: %s seconds ---" % (round(time.time() - start_time, 2)))

if __name__ == "__main__":
    main()
