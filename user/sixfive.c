#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"

char buf[1024];

static void process_file(char *path) {
  int fd;

  if ((fd = open(path, O_RDONLY)) < 0) {
    printf("sixfive: cannot open %s\n", path);
    exit(1);
  }

  int n;
  char c;
  char *p = buf;

  memset(buf, 0, sizeof(buf));
  while (read(fd, &c, 1) > 0) {
    if (strchr("0123456789", c)) {
      *(p++) = c;
      continue;
    } else if (strchr(" -\r\t\n./,", c)) {
      if (p != buf) {
        n = atoi(buf);
        if ((n % 5 == 0) || (n % 6 == 0))
          printf("%d\n", n);
      }
      p = buf;
      memset(buf, 0, sizeof(buf));
    } else {
      while (read(fd, &c, 1) > 0 && !(strchr(" -\r\t\n./,", c)))
        ;
      p = buf;
      memset(buf, 0, sizeof(buf));
    }
  }

  n = atoi(buf);
  if (p != buf && ((n % 5 == 0) || (n % 6 == 0)))
    printf("%d\n", n);

  close(fd);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(2, "Usage: sixfive [file ...]\n");
    exit(1);
  }

  for (int i = 1; i < argc; i++) {
    process_file(argv[i]);
  }

  exit(0);
}