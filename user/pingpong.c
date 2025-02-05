#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pipeP[2];
  int pipeC[2];
  int pid;
  char buffer[2];

  if (pipe(pipeP) == -1 || pipe(pipeC) == -1) {
    printf("Pipe error\n");
    exit(1);
  }

  pid = fork();

  if (pid == -1) {
    printf("Fork error\n");
    exit(1);
  }

  if (pid > 0) { // Parent
    pid = getpid();
    close(pipeP[0]);
    close(pipeC[1]);

    write(pipeP[1], "x", 2);
    close(pipeP[1]);

    sleep(2);

    read(pipeC[0], buffer, 2);
    if (buffer[0] == 'y') {
        printf("%d: recieved pong\n", pid);
    }
    close(pipeC[0]);
  } else { // Child
    pid = getpid();
    close(pipeP[1]);
    close(pipeC[0]);

    sleep(1);

    pid = getpid();

    read(pipeP[0], buffer, 2);
    if (buffer[0] == 'x') {
        printf("%d: recieved ping\n", pid);
    }
    close(pipeP[0]);

    write(pipeC[1], "y", 2);
    close(pipeC[1]);
  }

  exit(0);
}
