#include "kernel/param.h"
#include "user.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(2, "Usage: xargs COMMAND\n");
        exit(0);
    }
    int ret = 0;
    char *child_argv[MAXARG];
    int num = 1;
    while (num < argc) {
        child_argv[num - 1] = argv[num];
        num++;
    }
    char buf_from_input[32];
    while ((ret = read(0, buf_from_input, 32)) > 0) {
        printf("Current buf is %s\n", buf_from_input);
        char temp[32] = {0};
        child_argv[num - 1] = temp;
        int len = strlen(buf_from_input);
        for (int i = 0; i < len; i++) {
            if (buf_from_input[i] == '\n') {
                printf("Current arg is %s\n", temp); //Don't know why it cannot output without these printf(s).
                if (fork() == 0) {
                    exec(argv[1], child_argv);
                    fprintf(2, "exec %s failed\n", argv[1]);
                } else {
                    wait(0);
                }
            } else {
                temp[i] = buf_from_input[i];
            }
        }
        memset(buf_from_input, 0, 32);
    }
    exit(0);
}
