#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/module.h>

struct kprintf_args {
	char *buf;
};

int main(int argc, char *argv[])
{
	int s, i;
	struct module_stat stat;
	struct kprintf_args uag;

	if (argc < 2){
		fprintf(stderr, "usage: %s Hello World\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	stat.version = sizeof(stat);
	if ((modstat(modfind("kprintf"),  &stat)) < 0){
		perror("modstat");
		exit(EXIT_FAILURE);
	}

	s = stat.data.intval;

	if (s < 0){
		fprintf(stderr, "%s: no such systemcalls\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	for (i = 1; i < argc; i++){
		uag.buf = argv[i];
		syscall(s, uag);
		if (i + 1 == argc)
			syscall(s, "\n");
		else
			syscall(s, " ");
	}
	exit(EXIT_SUCCESS);
}
