#include "../kernel/types.h"
#include "user.h"

int main(int argc, char *argv[]) {
    int p[2] = {0};
    pipe(p);
    int pid = fork();
    char byte = 127;
    if (pid > 0) {
        write(p[1], &byte, sizeof byte);
        read(p[0], &byte, 1);
        printf("%d: received pong\n", getpid());
		//sleep(5);
    } else {
        read(p[0], &byte, 1);
        printf("%d: received ping\n", getpid());
        byte = 5;
        write(p[1], &byte, sizeof byte);
    }
    exit(0);
}
