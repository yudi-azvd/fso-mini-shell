#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <signal.h>

#define MAX_COMMAND_SIZE 256
#define MAX_COMMAND_ARGS_SIZE 256

struct timeval child_process_timer;

void timer_start(struct timeval *timer) {
  gettimeofday(timer, 0);
}

double timer_get_elapsed_time(struct timeval * timer) {
  struct timeval now;
  struct timeval elapsed;
  
  timer_start(&now);

  long seconds = now.tv_sec - timer->tv_sec;
  long microseconds = now.tv_usec - timer->tv_usec;
  return seconds + microseconds*1e-6;
}

void start_child_timer(int signal){
  timer_start(&child_process_timer);
}

int main() {
  signal(SIGUSR1, start_child_timer);

  int ps_status;
  pid_t process;
  char command[MAX_COMMAND_SIZE];
  char command_args[MAX_COMMAND_ARGS_SIZE];

  struct timeval parent_process_timer;
  double child_elapsed_time, parent_elapsed_time;

  timer_start(&parent_process_timer);
  while (scanf("%s", command) != EOF) {
    scanf("%s", command_args);

    process = fork();

    if (process > 0) {
      wait(&ps_status);
      child_elapsed_time = timer_get_elapsed_time(&child_process_timer);
      printf("> Demorou %.1f segundos, retornou %d\n", 
        child_elapsed_time, WEXITSTATUS(ps_status));
    }
    else if (process == 0) {
      kill(getppid(), SIGUSR1);
      int there_was_error = execl(command, command, command_args, NULL);
      if (there_was_error) {
        printf("> Erro: %s\n", strerror(errno));
        exit(errno);
      }
    }
    else {
      printf("> Não foi possível criar um processo.\n");
      exit(1);
    }
  }

  parent_elapsed_time = timer_get_elapsed_time(&parent_process_timer);
  printf(">> O tempo total foi de %.1f segundos\n", parent_elapsed_time);
  
  return 0;
}