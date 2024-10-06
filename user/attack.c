#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"
#include "stdbool.h"

int
main(int argc, char *argv[])
{
  char* start = sbrk(PGSIZE * 32);
  const char* phrase = "very very secret pw is: ";
  int len = strlen(phrase);
  bool flag = true;
  char buffer[9];
  buffer[7] = '\0';
  int count;

  for (int i = 0; i < (PGSIZE * 32) / sizeof(char); i++) {
    flag = true;
    for (int j = 0; j < len; j++) {
      if (phrase[j] != start[i + j]) {
	flag = false;
        break;
      }
    }
    if (flag == true) {
      count = 0;
      for (int j = i + len; j < (PGSIZE * 32) / sizeof(char); j++) {
        if (count > 6) {
          break;
        }
        buffer[8] = start[j];
        if (buffer[8] > 31 && buffer[8] < 127) {
          buffer[0 + count] = buffer[8];
          count += 1;
        }
      }
      for (int j = 0; j < 7; j++) {
        if ((buffer[j] < 46 || buffer[j] > 47) && (buffer[j] < 97 || buffer[j] > 102)) {
          flag = false;
          break;
        }
      }
      if (flag == true) {
        write(2, buffer, 8);
      }
    }
  }

  // your code here.  you should write the secret to fd 2 using write
  // (e.g., write(2, secret, 8)

  exit(1);
}
