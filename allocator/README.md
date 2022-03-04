# Instructions

To run tha handler.cpp file execute the following:

``` bash
g++ handler.cpp

sudo ./a.out {container_name} {container_pid}
```

To find the pid of the container, execute:

```bash
ps aux | grep ./container
```

`allocator.py` can be run as a stanalone program. Only configure the inputs of the `determine_resources` function. 

**Future work**:
Intergrate allocator.py and handler.cpp, with the help of the [CPython Interpreter](https://docs.python.org/3/extending/embedding.html)

# Allocator Registry
The regitry created for the allocator to search when deciding on the reources can be found in the following links:

[Memory Registry](https://drive.google.com/drive/folders/1_7l9iXlwKDnFfCPnpu-t7O1DX0PSapt4?usp=sharing)

[CPU Registry](https://drive.google.com/drive/folders/1o5A0yIJWEwcWI9rAjq51ne3fkwOjWO_Q?usp=sharing)
