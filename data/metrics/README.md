# Metrics collection

For the collection of the data, the [Prometheus Python client](https://github.com/prometheus/client_python) was utilized. 

The `metrics.sh` script listens on the port Prometheus exports its metrics and writes them in files to then later be appropriately handled by the `read_metrics.py`.

The script writes Prometheus' results every 2 seconds, to avoid as much as possible affecting the execution time of our [programs](./scripts).

The `read_metrics.py` script reads from the files `metrics.sh` creates and writes, for every run of the function, one record in an Excel.

The Excel that was created ([Dataset-VM1.xlsx](./data/metrics/Dataset-VM1.xlsx)) includes the following columns:

| Feature | Explanation |
|   ----  |    ----     |
| VM_RAM(MB) | The RAM allocated to the VM the experiments were run on in MB |
| Input_function | The function that was tested |
| Num_of_Input | The number of arguments the input function receives | 
| Type_of_Input | The data type of the input of the function|
| Input 1 | The value of the first input |
| Input 2 | The value of the second input (could be None) |
| Size of input (bytes) | The size of the input in bytes |
| Type_of_output | The data type of the output of the function |
| Number_of_files | The number of files created by `metrics.sh` |
| Max_Virtual_Memory (MB) | The maximum Virtual Memory from the collected files |
| Min_Virtual_Memory (MB) | The minimum Virtual Memory from the collected files |
| Avg_Virtual_Memory (MB) | The average Virtual Memory from the collected files |
| Max_Resident_Memory (MB) | The maximum Resident Memory from the collected files |
| Min_Resident_Memory (MB) | The minimum Resident Memory from the collected files |
| Avg_Resident_Memory (MB) | The average Resident Memory from the collected files |
| Max_CPU_time (sec) | The maximum CPU from the collected files |
| Min_CPU_time (sec) | The minimum CPU from the collected files |
| Avg_CPU_time (sec) | The average CPU from the collected files |
| Total_Exec_Time (sec) | The total execution time of the program |
