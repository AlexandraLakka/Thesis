#include <iostream>
#include <sched.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <fstream>
#include <string> 
#include <iostream>
#include <sys/utsname.h>
#include <signal.h>
#include <cstdlib>
#include <sstream>
using namespace std;

#define CGROUP_FOLDER "/sys/fs/cgroup/pids/" 
#define MEM_FOLDER "/sys/fs/cgroup/memory/"
#define CPU_FOLDER "/sys/fs/cgroup/cpu/"

void write_rule(const char* path, const char* value) {
  int fp = open(path, O_WRONLY | O_APPEND );
  write(fp, value, strlen(value));
  close(fp);
} 

void write_cgroups(std::string my_container){
  std::string memory = MEM_FOLDER + my_container + "/";
  std::string cpu = CPU_FOLDER + my_container + "/";

  mkdir(memory.c_str(), S_IRUSR | S_IWUSR);  // Read & Write
  mkdir(cpu.c_str(), S_IRUSR | S_IWUSR);  // Read & Write

  std::string memory_limit_in_bytes = memory + "memory.limit_in_bytes";
  printf("%s\n", memory_limit_in_bytes.c_str());
  std::string cpu_cfs_period_us = cpu + "cpu.cfs_period_us";
  std::string cpu_cfs_quota_us = cpu + "cpu.cfs_quota_us";

  write_rule(memory_limit_in_bytes.c_str(), "20M");

  // https://drill.apache.org/docs/configuring-cgroups-to-control-cpu-usage/
  write_rule(cpu_cfs_period_us.c_str(), "1000000"); // the length of a period (in microseconds)
  write_rule(cpu_cfs_quota_us.c_str(), "1000000"); //the total available run-time within a period (in microseconds)

  printf("Your container's memory and CPU have been altered\n");
}


bool setResources(std::string my_container, std::string pid) {
  std::string cgroup = CGROUP_FOLDER + my_container + "/";
  std::string cgroup_procs = cgroup + "cgroup.procs";
  
  std::string line;
  std::ifstream input(cgroup_procs);

  bool pid_exists = false;

  for(std::string line; getline( input, line );) {
    if (line.compare(pid) == 0) {
      pid_exists = true;
      write_cgroups(my_container);
      break;
    }
  }

  return pid_exists;
}

int main(int argc, char** argv) {
  if (argv[1] != NULL && argv[2] != NULL){
    pid_t pid;
    bool success = false;
    std::string my_container = argv[1];
    int int_pid = atoi(argv[2]);
     
    pid = (pid_t)int_pid;

    printf("PID: %d\n", pid);

    if (0 == kill(pid, 0)){
      success = setResources(my_container, argv[2]);
      if (success) {
        return EXIT_SUCCESS;
      } else {
        printf("The allocation could not happen\n");
      }
      
    } else { 
      printf("Process is not running\n");
      return EXIT_FAILURE;
    }
  } else {
      printf("Enter the name of your container and its PID\n");
      return EXIT_FAILURE;
  }
	
}
