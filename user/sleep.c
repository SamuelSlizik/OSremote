#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc > 2 || argc < 2) {
    printf("usage: sleep seconds\n");
  }

  printf("sleeping...\n");
  sleep(atoi(argv[1]));

  exit(0);
}
