from os import listdir
from os.path import isfile, join
import matplotlib.pyplot as plt
import pandas as pd
from operator import itemgetter
import json

def load_profiles():
  # Memory
  with open('./data/mem_json/merge_sort.txt', 'r') as f:
    merge_mem = json.load(f)

  with open('./data/mem_json/quick_sort.txt', 'r') as f:
    quick_mem = json.load(f)

  with open('./data/mem_json/cholesky.txt', 'r') as f:
    cholesky_mem = json.load(f)

  with open('./data/mem_json/multiply.txt', 'r') as f:
    multiply_mem = json.load(f)

  with open('./data/mem_json/factorial.txt', 'r') as f:
    factorial_mem = json.load(f)

  # CPU
  with open('./data/cpu_json/merge_sort.txt', 'r') as f:
    merge_cpu = json.load(f)

  with open('./data/cpu_json/quick_sort.txt', 'r') as f:
    quick_cpu = json.load(f)

  with open('./data/cpu_json/cholesky.txt', 'r') as f:
    cholesky_cpu = json.load(f)

  with open('./data/cpu_json/multiply.txt', 'r') as f:
    multiply_cpu = json.load(f)

  with open('./data/cpu_json/factorial.txt', 'r') as f:
    factorial_cpu = json.load(f)

  return merge_mem, quick_mem, cholesky_mem, multiply_mem, factorial_mem, merge_cpu, quick_cpu, cholesky_cpu, multiply_cpu, factorial_cpu

merge_mem, quick_mem, cholesky_mem, multiply_mem, factorial_mem, merge_cpu, quick_cpu, cholesky_cpu, multiply_cpu, factorial_cpu = load_profiles()

def search(memory_list, cpu_list, input):
  if input > 2000000:
    mem = 150
    cpu = 350
  else:
    for record in memory_list:
      if input <= 20000:
        keys = list(record.keys())
        mem = float(keys[0])
        break
      else:
        for key, value in record.items():
          for i in value:
            if input in range(i, i+10000):
              mem = float(key)
              break
            else:
              continue
        
    for record in cpu_list:
      if input <= 20000:
        keys = list(record.keys())
        cpu = float(keys[0])
        break
      else:
        for key, value in record.items():
          for i in value:
            if input in range(i, i+10000):
              cpu = float(key)
              break
            else:
              continue
  return mem, cpu

def search_cholesky(memory_list, cpu_list, input):
  mem_exists = False
  cpu_exists = False
  for record in memory_list:
    for key, value in record.items():
      for i in value:
        if input == i:
          mem = float(key)
          mem_exists = True
          break
        else:
          continue
        
    for record in cpu_list:
      for key, value in record.items():
        for i in value:
          if input == i:
            cpu = float(key)
            cpu_exists = True
            break
          else:
            continue

    if not mem_exists and not cpu_exists:
      mem = 150
      cpu = 350
  return mem, cpu


def search_multiply(memory_list, cpu_list, input_1, input_2):
  mem_exists = False
  cpu_exists = False
  for record in memory_list:
    for key, value in record.items():
      for i in value:
        i = i.split('_')
        if input_1 == i[0] and input_2 == i[1]:
          mem = float(key)
          mem_exists = True
          break
        else:
          continue
        
    for record in cpu_list:
      for key, value in record.items():
        for i in value:
          i = i.split('_')
          if input_1 == i[0] and input_2 == i[1]:
            cpu = float(key)
            cpu_exists = True
            break
          else:
            continue

    if not mem_exists and not cpu_exists:
      mem = 150
      cpu = 350
  return mem, cpu

def determine_resources(func, input_1, input_2=None):
  if func == 'merge_sort':
    mem, cpu = search(merge_mem, merge_cpu, input_1)
  elif func == 'quick_sort':
    mem, cpu = search(quick_mem, quick_cpu, input_1)
  elif func == 'cholesky':
    mem, cpu = search_cholesky(cholesky_mem, cholesky_cpu, input_1)
  elif func == 'multiply':
    mem, cpu = search_multiply(multiply_mem, multiply_cpu, input_1, input_2)
  elif func == 'factorial':
    mem, cpu = search(factorial_mem, factorial_cpu, input_1)
  else:
    mem = 150
    cpu = 350
  
  return mem, cpu

determine_resources('multiply', '432x89', '232x432')