/*Write a C program which creates a child process to run linux/ unix command or any
user defined program. The parent process set the signal handler for death of child
signal and Alarm signal. If a child process does not complete its execution in 5
second then parent process kills child process.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void child_signal_handler(int signo) {
    if (signo == SIGCHLD) {
        printf("Parent: Received SIGCHLD - Child process terminated.\n");
    }
}

void alarm_handler(int signo) {
    if (signo == SIGALRM) {
        printf("Parent: Child process did not complete within 5 seconds. Killing...\n");
        exit(EXIT_SUCCESS);
    }
}

int main() {
    pid_t child_pid;

    // Set up signal handlers
    signal(SIGCHLD, child_signal_handler);
    signal(SIGALRM, alarm_handler);

    // Create a child process
    if ((child_pid = fork()) == -1) {
        perror("Error creating child process");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process

        // Sleep for 10 seconds to simulate a long-running task
        sleep(10);

        // Child process exits
        printf("Child: Process completed.\n");
        exit(EXIT_SUCCESS);
    } else {
        // Parent process

        // Set an alarm for 5 seconds
        alarm(5);

        // Wait for the child process to terminate
        wait(NULL);

        // Cancel the alarm if the child process terminates before the alarm
        alarm(0);

        printf("Parent: Parent process exiting.\n");
    }

    return 0;
}
