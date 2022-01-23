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
//https://github.com/hlandau/acme.t/issues/1 --> have to install a package to recognize library
#include <sys/capability.h>
#include "global.h"
using namespace std;

int TRY(int status, const char *msg) {
 if(status == -1) {  
    perror(msg); 
    exit(EXIT_FAILURE);
 }
 return status;
}

void write_rule(const char* path, const char* value) {
  int fp = open(path, O_WRONLY | O_APPEND );
  write(fp, value, strlen(value));
  close(fp);
} 

#define CGROUP_FOLDER "/sys/fs/cgroup/pids/" 
//https://doc.dataiku.com/dss/latest/operations/cgroups.html
#define MEM_FOLDER "/sys/fs/cgroup/memory/"
#define CPU_FOLDER "/sys/fs/cgroup/cpu/"
#define DEVICES "/sys/fs/cgroup/devices/"
#define concat(a,b) (a"" b)
void limitProcessCreation(std::string my_path) {
  std::string cgroup = CGROUP_FOLDER + my_path + "/";
  std::string memory = MEM_FOLDER + my_path + "/";
  std::string cpu = CPU_FOLDER + my_path + "/";
  //std::string devices = DEVICES + my_path + "/";

  mkdir(cgroup.c_str(), S_IRUSR | S_IWUSR);  // Read & Write
  //mkdir(devices.c_str(), S_IRUSR | S_IWUSR);  // Read & Write
  //mkdir(memory.c_str(), S_IRUSR | S_IWUSR);  // Read & Write
  //mkdir(cpu.c_str(), S_IRUSR | S_IWUSR);  // Read & Write
  const char* pid  = std::to_string(getpid()).c_str();

  std::string pids_max = cgroup + "pids.max";
  std::string notify_on_release = cgroup + "notify_on_release";
  std::string cgroup_procs = cgroup + "cgroup.procs";
  //std::string cgroup_devices = devices + "devices.allow";
  //std::cout << cgroup_devices;

  write_rule(pids_max.c_str(), "8"); 
  write_rule(notify_on_release.c_str(), "1"); 
  write_rule(cgroup_procs.c_str(), pid);
  //write_rule(cgroup_devices.c_str(), "c 1:8 r");

  //write_rule(concat(memory.c_str(), "memory.limit_in_bytes"), "20M");

  // https://drill.apache.org/docs/configuring-cgroups-to-control-cpu-usage/
  //write_rule(concat(cpu.c_str(), "cpu.cfs_period_us"), "1000000"); // the length of a period (in microseconds)
  //write_rule(concat(cpu.c_str(), "cpu.cfs_quota_us"), "1000000"); //the total available run-time within a period (in microseconds)
}

char* stack_memory() {  
  const int stackSize = 65536;
  auto *stack = new (std::nothrow) char[stackSize];

  if (stack == nullptr) { 
    printf("Cannot allocate memory \n");
    exit(EXIT_FAILURE);
  }  

  return stack+stackSize;  //move the pointer to the end of the array because the stack grows backward. 
}

void setHostName(std::string hostname) {
  sethostname(hostname.c_str(), hostname.size());
}

void setup_variables() {
  clearenv();
  setenv("TERM", "xterm-256color", 0);
  //setenv("PATH", "/bin/:/sbin/:usr/bin:/usr/sbin", 0);
  setenv("PATH", "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin", 0);
  //setenv("PATH", "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", 0);
  //setenv("PATH", "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin", 0);
}

template <typename... P> 
int run(P... params) {
  char *args[] = {(char *)params..., (char *)0};
  
  execvp(args[0], args);

  perror("execvp"); 
  return 0; 
  
}

// void networkSettings() {
//   //https://www.toptal.com/linux/separation-anxiety-isolating-your-system-with-linux-namespaces
//   // calling unshare() from inside the init process lets you create a new namespace after a new process has been spawned
//   unshare(CLONE_NEWNET);
// }

void setup_root(const char* folder){
  chroot(folder);
  chdir("/");
}

//https://www.toptal.com/linux/separation-anxiety-isolating-your-system-with-linux-namespaces
static void print_nodename() {
  struct utsname utsname;
  uname(&utsname);
  printf("%s\n", utsname.nodename);
}


template <typename Function>
void clone_process(Function&& function, int flags){
 auto pid = TRY( clone(function, stack_memory(), flags, 0), "clone" );

 wait(nullptr); 
} 

#define lambda(fn_body) [](void *args) ->int { fn_body; };
 
int jail(void *args) {
  std::string name;
  printf("Please give a name for your container: ");
  std::cin >> name;

  //networkSettings();
  unshare(CLONE_NEWNS);
  limitProcessCreation(name);

  printf("child pid: %d\n", getpid());
  setHostName(name);
  setup_variables();

  setup_root("./root");

  mount("proc", "/proc", "proc", 0, 0); 
  mount("sys", "/sys", "sysfs", 0, 0);
  //mount("dev", "/dev/shm", "tmpfs", 0, 0);

  printf("New UTS namespace nodename: ");
  print_nodename();
  
  auto runnable = lambda(run("/bin/bash"));
  //auto runnable = lambda(run("/bin/sh"));

  clone_process(runnable, SIGCHLD);

  umount("/proc");
  umount("/sys");
  //umount("/dev/shm");

  return EXIT_SUCCESS;
}


int main(int argc, char** argv) {
  int parent_pid = getpid();

  printf("parent pid: %d\n", parent_pid);
  printf("Original UTS namespace nodename: ");
  print_nodename();

  //clone_process(jail, CLONE_NEWPID | CLONE_NEWNET | CLONE_NEWUTS | CLONE_NEWNS | SIGCHLD);
  clone_process(jail, CLONE_NEWPID | CLONE_NEWUTS |  CLONE_NEWNS | SIGCHLD);

  return EXIT_SUCCESS;
}
