from algorithms.sort import quick_sort
import random

def handler(event, context):
    my_list = [random.randrange(1, 2000000, 1) for i in range(100000)]
    my_list = quick_sort(my_list)
    print(my_list)

