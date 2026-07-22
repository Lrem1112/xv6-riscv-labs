#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"

#define DATASIZE (9*4096)

int
main(int argc, char *argv[])
{
  // Your code here.
  char *buf = sbrk(DATASIZE);
  int n = 0;
  for (; n < DATASIZE; ++n, ++buf) {
    if (*buf == 'T') {
      if (strcmp("This may help.", buf) == 0) {
        printf("%s\n", buf + 16);
        exit(0);
      }
    }
  }
  exit(1);
}
