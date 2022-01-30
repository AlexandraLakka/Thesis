from algorithms.matrix import cholesky_matrix_decomposition
from prometheus_client import start_http_server
import numpy as np
import random
from sys import getsizeof
import time

def main():
    start_http_server(8000)
    start_time = time.time()

    #A = [random.sample(range(-20000, 20000), 3000) for _ in range(3000)]
    matrixSize1 = 580
    matrixSize2 = 580
    A = np.random.rand(matrixSize1, matrixSize2)
    B = np.dot(A, A.transpose())
    print(B)

    V = cholesky_matrix_decomposition.cholesky_decomposition(B)

    print(V)

    print("---Size of input matrix: %s bytes---" % (getsizeof(B)))
    print("--- Execution time: %s seconds ---" % (round(time.time() - start_time, 2)))

if __name__ == "__main__":
    main()
