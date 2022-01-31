from algorithms.maths import factorial

def handler(event, context):
    input = 100000
    result = factorial(input)
    print(result)
