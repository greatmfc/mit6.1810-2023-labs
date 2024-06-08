#include "../kernel/types.h"
#include "user.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(2, "Need additional argument!\n");
		exit(1);
    }
    int time = atoi(argv[1]);
	sleep(time);
	exit(0);
}
