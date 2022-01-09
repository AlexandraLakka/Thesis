from algorithms.matrix import cholesky_matrix_decomposition
from prometheus_client import start_http_server
import numpy as np
import random
from sys import getsizeof
import time

if __name__ == "__main__":
    start_http_server(8000)
    start_time = time.time()

    #A = [lst[:] for lst in [random.sample(range(80), 6)]*6]
    matrixSize = 1050
    A = np.random.rand(matrixSize, matrixSize)
    B = np.dot(A, A.transpose())
    print(B)

    V = cholesky_matrix_decomposition.cholesky_decomposition(B)

    print(V)

    print("---Size of input matrix: %s bytes---" % (getsizeof(B)))
    print("--- Execution time: %s seconds ---" % (round(time.time() - start_time, 2)))
