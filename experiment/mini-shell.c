#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

#define MAX_COMMAND_SIZE 50
#define MAX_COMMAND_ARGS_SIZE 50

void timer_start(time_t* timer) {
  time(timer);
}

time_t timer_get_elapsed_time(time_t* timer) {
  time_t now;
  time(&now);
  return now - *timer;
}

time_t child_process_timer;

void start_child_timer(int signal){
  timer_start(&child_process_timer);
}

int main() {
  signal(SIGUSR1, start_child_timer);

  int ps_status;
  pid_t process;
  char command[MAX_COMMAND_SIZE];
  char command_args[MAX_COMMAND_ARGS_SIZE];

  time_t child_elapsed_time,
    parent_process_timer, parent_elapsed_time;
  
  timer_start(&parent_process_timer);
  while (scanf("%s", command) != EOF) {
    scanf("%s", command_args);

    process = fork();

    if (process > 0) {
      wait(&ps_status);
      child_elapsed_time = timer_get_elapsed_time(&child_process_timer);
      printf("> Demorou %ld segundos, retornou %d\n", 
        child_elapsed_time, WEXITSTATUS(ps_status));
    }
    else if (process == 0) {
      kill(getppid(), SIGUSR1);
      int there_was_error = execl(command, command, command_args, NULL);
      if (there_was_error) {
        printf("> Erro: %s\n", strerror(errno));
        exit(1);
      }
      exit(0);
    }
    else {
      printf("> Não foi possível criar um processo.\n");
      exit(1);
    }
  }

  parent_elapsed_time = timer_get_elapsed_time(&parent_process_timer);
  printf(">> O tempo total foi de %ld segundos\n", parent_elapsed_time);
  
  return 0;
}