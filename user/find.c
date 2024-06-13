#include "kernel/fcntl.h"
#include "kernel/fs.h"
#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"

void find(const char *path, const char *file) {
    char buf[128], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if ((fd = open(path, O_RDONLY)) < 0) {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }
    if (fstat(fd, &st) < 0) {
        fprintf(2, "find: cannot stat at line:18 %s\n", path);
        close(fd);
        return;
    }

    const char *pp = path;

    switch (st.type) {
    case T_DEVICE:
    case T_FILE:
        while (*pp++ != '/') {
        }
        if (strcmp(pp, file) == 0)
            printf("%s\n", path);
        break;
    case T_DIR:
        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
            printf("find: path too long\n");
            break;
        }
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
        while (read(fd, &de, sizeof(de)) == sizeof(de)) {
            if (de.inum == 0)
                continue;
            // printf("De.name is:%s\n", de.name);
            // continue;
            if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) {
                //printf("Jump over:%s\n", de.name);
                continue;
            }
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            if (stat(buf, &st) < 0) {
                printf("find: cannot stat at line:51 %s\n", buf);
                continue;
            }
            if (st.type == 1) {
                //printf("Searching next dir:%s\n", de.name);
                find(buf, file);
            } else if (st.type == 2) {
                //printf("Matching file:%s\n", de.name);
                if (strcmp(de.name, file) == 0)
                    printf("%s\n", buf);
            }
            // printf("%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
        }
        break;
    }
    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(2, "Usage: [path] [name]\n");
        exit(0);
    }
    find(argv[1], argv[2]);
    return 0;
}
