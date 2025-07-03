#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <getopt.h>

#define DEFAULT_SYSCALL_NUM 550

int main(int argc, char *argv[])
{
    int syscall_num = DEFAULT_SYSCALL_NUM;
    int opt;

    while ((opt = getopt(argc, argv, "d:")) != -1) {
        switch (opt) {
        case 'd':
            syscall_num = atoi(optarg);
            break;
        default:
            fprintf(stderr, "usage: %s [-d syscall_num] message...\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "usage: %s [-d syscall_num] message...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = optind; i < argc; i++) {
        syscall(syscall_num, argv[i]);
        if (i + 1 == argc)
            syscall(syscall_num, "\n");
        else
            syscall(syscall_num, " ");
    }

    return 0;
}

