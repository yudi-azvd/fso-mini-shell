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

#define MAX_COMMAND_PATH_SIZE 256
#define MAX_COMMAND_ARGS_SIZE 256

struct timeval child_process_timer;

typedef struct command
{
    char path[MAX_COMMAND_PATH_SIZE];
    char args[MAX_COMMAND_ARGS_SIZE];
}command_t;


void timer_start(struct timeval *timer)
{
    gettimeofday(timer, 0);
}

double timer_get_elapsed_time(struct timeval *timer)
{
    struct timeval now;

    timer_start(&now);

    long seconds = now.tv_sec - timer->tv_sec;
    long microseconds = now.tv_usec - timer->tv_usec;
    return seconds + microseconds * 1e-6;
}

void start_child_timer(int signal)
{
    timer_start(&child_process_timer);
}

void manage_child(command_t *command)
{
    kill(getppid(), SIGUSR1);
    
    int there_was_error = execl(command->path, command->path, command->args, NULL);
    
    if (there_was_error)
    {
        printf("> Erro: %s\n", strerror(errno));
        fflush(stdout);
        exit(errno);
    }
}

void manage_parent()
{
    int ps_status;
    double child_elapsed_time;

    wait(&ps_status);
    child_elapsed_time = timer_get_elapsed_time(&child_process_timer);
    printf("> Demorou %.1f segundos, retornou %d\n", child_elapsed_time, WEXITSTATUS(ps_status));
    fflush(stdout);
}

int main()
{
    signal(SIGUSR1, start_child_timer);

    pid_t process;
    command_t command;

    struct timeval parent_process_timer;
    double parent_elapsed_time;

    timer_start(&parent_process_timer);

    while (scanf("%s %s", command.path, command.args) != EOF)
    {
        process = fork();

        if (process > 0)
            manage_parent();
        else if (process == 0)
            manage_child(&command);
        else
        {
            printf("> Não foi possível criar um processo.\n");
            fflush(stdout);
            exit(1);
        }
    }

    parent_elapsed_time = timer_get_elapsed_time(&parent_process_timer);
    printf(">> O tempo total foi de %.1f segundos\n", parent_elapsed_time);
    fflush(stdout);

    return 0;
}