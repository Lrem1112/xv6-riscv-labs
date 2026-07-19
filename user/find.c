#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"
#include "kernel/stat.h"
#include "user/user.h"

int fnamecmp(char *path, char *f) {
  char *p;
  for (p = path + strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;
  return strcmp(p, f);
}

void find(char *path, char *f) {
  int fd;
  char buf[512], *p;
  struct dirent de;
  struct stat st;

  if ((fd = open(path, O_RDONLY)) < 0) {
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }

  if (fstat(fd, &st) < 0) {
    fprintf(2, "find: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch (st.type) {
  case T_DEVICE:
    break;
  case T_FILE:
    if (!fnamecmp(path, f))
      printf("%s\n", path);
    break;
  case T_DIR:
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
      if (de.inum == 0)
        continue;
      if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
        continue;
      memmove(p, de.name, sizeof(de.name));
      p[sizeof(de.name)] = 0;
      find(buf, f);
    }
    break;
  }
  close(fd);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: find <dir> <filename>\n");
    exit(0);
  }

  find(argv[1], argv[2]);
  exit(0);
}