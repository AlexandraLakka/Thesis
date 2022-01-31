# Instructions

To run tha handler.cpp file execute the following:

``` bash
g++ handler.cpp

sudo ./a.out {container_name} {container_pid}
```

To find the pid of the container execute:

```bash
ps aux | grep ./container
```

**Future work**:
Intergrate allocator.py and handler.cpp, with the help of the [CPython Interpreter](#https://docs.python.org/3/extending/embedding.html)
