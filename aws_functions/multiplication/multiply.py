from algorithms.matrix import multiply
import random

def handler(event, context):
    A = [random.sample(range(2000), 450) for _ in range(450)]
    B = [random.sample(range(2000), 450) for _ in range(450)]

    C = multiply.multiply(A, B)
    print(C)


