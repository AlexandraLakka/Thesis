from algorithms.matrix import cholesky_matrix_decomposition
import numpy as np
import random

def handler(event, context):

    #A = [random.sample(range(-20000, 20000), 1050) for _ in range(1050)]
    matrixSize1 = 450
    matrixSize2 = 450
    A = np.random.rand(matrixSize1, matrixSize2)
    B = np.dot(A, A.transpose())
    print(B)

    V = cholesky_matrix_decomposition.cholesky_decomposition(B)

    print(V)
