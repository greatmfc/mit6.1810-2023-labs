#include "../kernel/types.h"
#include "user.h"

void process_action(int fd_from_left) {
    int byte = 2;
    read(fd_from_left, &byte, sizeof byte);
    printf("prime %d\n", byte);
    if (byte == 31) {
        return;
    }
    int p[2] = {0};
    int ret = pipe(p);
    if (ret == -1) {
        printf("Fail to create pipe in process:%d.\nCurrent byte is:%d.\n",
               getpid(), byte);
    }
    int initial_num = byte;
    while (read(fd_from_left, &byte, sizeof byte) > 0) {
        if (byte % initial_num != 0) { // Not a mutiple
            write(p[1], &byte, sizeof byte);
        }
    }
    close(p[1]);
    int pid = fork();
    if (pid == 0) { // Child
        process_action(p[0]);
    }
    return;
}

int main() {
    int p[2] = {0, 0};
    pipe(p);
    int byte = 2;
    write(p[1], &byte, sizeof byte);
    byte++;
    do {
        if (byte % 2 != 0) {
            write(p[1], &byte, sizeof byte);
        }
    } while (byte++ <= 35);
    close(p[1]);
    int pid = fork();
    if (pid == 0) { // Child
        process_action(p[0]);
    } else {
        sleep(10);
    }
    return 0;
}
