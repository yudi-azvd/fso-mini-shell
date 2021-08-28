#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

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

int main() {
  int ps_status;
  pid_t process;
  char command[MAX_COMMAND_SIZE];
  char command_name[MAX_COMMAND_SIZE];
  char command_args[MAX_COMMAND_ARGS_SIZE];

  time_t child_process_timer, child_elapsed_time,
    parent_process_timer, parent_elapsed_time;
  
  timer_start(&parent_process_timer);
  while (scanf("%s", command) != EOF) {
    strcpy(command_name, command); // deveria copiar apenas o nome do binário
    scanf("%s", command_args);
    // printf("[%s] [%s]\n", command, command_args);

    timer_start(&child_process_timer);
    process = fork();

    if (process > 0) {
      wait(&ps_status);
      child_elapsed_time = timer_get_elapsed_time(&child_process_timer);
      printf("> Demorou %ld segundos, retornou %d\n", 
        child_elapsed_time, WEXITSTATUS(ps_status));
    }
    else if (process == 0) {
      int there_was_error = execl(command, command_name, command_args, (char*) NULL);
      if (there_was_error) {
        printf("> Erro: %s\n", strerror(errno));
        exit(1);
      }
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