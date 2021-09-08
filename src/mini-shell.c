#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <fcntl.h>


#define MAX_COMMAND_SIZE 256
#define MAX_COMMAND_ARGS_SIZE 256

typedef struct timeval timeval_t;

void timer_start(timeval_t* timer) {
  gettimeofday(timer, NULL);
}

double timer_get_elapsed_time_seconds(timeval_t old) {
  timeval_t now, elapsed;
  gettimeofday(&now, NULL);
  elapsed.tv_sec = now.tv_sec - old.tv_sec;
  elapsed.tv_usec = now.tv_usec - old.tv_usec;
  double seconds = elapsed.tv_sec + elapsed.tv_usec/1000000.0;
  return seconds;
}

int main() {
  int ps_status;
  pid_t process;
  char command[MAX_COMMAND_SIZE];
  char command_name[MAX_COMMAND_SIZE];
  char command_args[MAX_COMMAND_ARGS_SIZE];

  timeval_t child_timer, parent_timer;
  double seconds_elapsed;
  
  timer_start(&parent_timer);
  while (scanf("%s", command) != EOF) {
    scanf("%s", command_args);

    timer_start(&child_timer);
    process = fork();

    if (process > 0) {
      wait(&ps_status);
      seconds_elapsed = timer_get_elapsed_time_seconds(child_timer);
      printf("> Demorou %.1lf segundos, retornou %d\n", 
        seconds_elapsed, WEXITSTATUS(ps_status));
      fflush(stdout);
    }
    else if (process == 0) {
      int there_was_error = execl(command, command, command_args, (char*) NULL);
      if (there_was_error) {
        printf("> Erro: %s\n", strerror(errno));
        fflush(stdout);
        _exit(errno);
      }
    }
    else {
      printf("> Não foi possível criar um processo.\n");
      fflush(stdout);
      _exit(errno);
    }
  }

  seconds_elapsed = timer_get_elapsed_time_seconds(parent_timer);
  printf(">> O tempo total foi de %.1lf segundos\n", seconds_elapsed);
  fflush(stdout);
  
  return 0;
}