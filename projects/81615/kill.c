#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include<err.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>

#include "signals.h"

#define SIGNAL_COUNT 15

int default_signal = SIGTERM;

// I was debating on creating a file mapping
// signal_num:signal_name and loading it on startup
// but this does the job well enough. 
// Plus there is probably a smarter way, but this does the job for now.
void init_signals(struct signal signals[SIGNAL_COUNT]) {
  signals[0].signal_num = SIGABRT;
  signals[0].signal_name = "SIGABRT";

  signals[1].signal_num = SIGALRM;
  signals[1].signal_name = "SIGALRM";
  
  signals[2].signal_num = SIGBUS;
  signals[2].signal_name = "SIGBUS";
  
  signals[3].signal_num = SIGCHLD;
  signals[3].signal_name = "SIGCHLD";

  signals[4].signal_num = SIGILL;
  signals[4].signal_name = "SIGILL";

  signals[5].signal_num = SIGKILL;
  signals[5].signal_name = "SIGKILL";
  
  signals[6].signal_num = SIGPIPE;
  signals[6].signal_name = "SIGPIPE";

  signals[7].signal_num = SIGQUIT;
  signals[7].signal_name = "SIGQUIT";

  signals[8].signal_num = SIGSEGV;
  signals[8].signal_name = "SIGSEGV";
  
  signals[9].signal_num = SIGSTOP;
  signals[9].signal_name = "SIGSTOP";

  signals[9].signal_num = SIGTERM;
  signals[9].signal_name = "SIGTERM";

  signals[10].signal_num = SIGTSTP;
  signals[10].signal_name = "SIGTSTP";

  signals[11].signal_num = SIGTTIN;
  signals[11].signal_name = "SIGTTIN";

  signals[12].signal_num = SIGTTOU;
  signals[12].signal_name = "SIGTTOU";

  signals[13].signal_num = SIGUSR1;
  signals[13].signal_name = "SIGUSR1";

  signals[14].signal_num = SIGUSR2;
  signals[14].signal_name = "SIGUSR2";
}

void invalid_usage_exit() {
    errx(1, "Usage: kill [-SIGNAL | -s SIGNAL] PID, [...PID]");
    exit(EXIT_FAILURE);
}

void invalid_pid_exit(char * pid) {
  errx(2, "PIDs should be valid numbers, you provided: %s", pid);
  exit(2);
}

void invalid_signal_exit(char * signal) {
  errx(3, "PIDs should be valid numbers, you provided: %s", signal);
  exit(3);
}

bool is_number_valid(char * str) {
  while(*str) {
    if(*str < '0' || *str > '9') {
      return false;
    }
    str++;
  }


  return true;
}

// We just loop and check if the desired signal name is within the array of supported signals
// if we find it, we return the first one, otherwise we return -1 indicating that we couldn't find it.
// We also check without the SIG part, because it is prepended to each signal.
int get_signal_from_name(char * name, struct signal signals[SIGNAL_COUNT]) {
  for(int i = 0; i < SIGNAL_COUNT; ++i) {
    if(strcmp(name, signals[i].signal_name) == 0) {
      return i;
    }
    if(strcmp(name, signals[i].signal_name + 3) == 0) {
      return i;
    }
  }
  return -1;
}

int main(int argc, char**argv) {
  if(argc == 1) {
    invalid_usage_exit();
  }
  
  struct signal signals[SIGNAL_COUNT];

  init_signals(signals);

  int sig_num = default_signal;
  int pid_start_index = 1;
  // This means a parameter has been set
  if (argv[1][0] == '-') {
    // We are not giving the signal directly, but rather with the -s parameter.
    if(argv[1][1] == 's') {
      // We need at least kill -s signal pid
      if(argc < 4) {
        invalid_usage_exit();
      }
      if(is_number_valid(argv[2])) {
        sig_num = atoi(argv[2]);
        pid_start_index = 3;
      } else {
        // Parse SIG<NAME>
        int signal_index = get_signal_from_name(argv[2], signals);
        if(signal_index == -1) {
          invalid_signal_exit(argv[2]);
        } else {
          sig_num = signals[signal_index].signal_num;
          pid_start_index = 3;
        }
      }
    } else {
      // Here it should be a number, need to verify.
      if(is_number_valid(argv[1] + 1)) {
        sig_num = atoi(argv[1] + 1);
        pid_start_index = 2;
      } else {
        
        // Parse SIG<NAME>
        int signal_index = get_signal_from_name(argv[1] + 1, signals);
        if(signal_index == -1) {
          invalid_signal_exit(argv[1] + 1);
        } else {
          sig_num = signals[signal_index].signal_num;
          pid_start_index = 2;
        }
      }
    }
  }
  

  // Check command correctness before actually killing processes
  for(int i = pid_start_index; i < argc; i++) {
    if (!is_number_valid(argv[i])) {
      invalid_pid_exit(argv[i]);
    }
  }

  for(int i = pid_start_index; i < argc; i++) {
      int pid = atoi(argv[i]);
      if(kill(pid, sig_num) == -1) {
        perror(argv[i]);
      }
  }

  exit(EXIT_SUCCESS);
}
