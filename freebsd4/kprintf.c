#include <sys/types.h>
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/module.h>
#include <sys/sysent.h>
#include <sys/kernel.h>
#include <sys/systm.h>

struct kprintf_args {
	char *buf;
};

static int kprintf_syscall(struct proc *p, struct kprintf_args *uap)
{
	if (uap != NULL)
		printf("%s", uap->buf);
	return 0;
}

static struct sysent kprintf_sysent = {
	2,
	kprintf_syscall	/* sy_call */
};

static int
kprintf_load(struct module *module, int cmd, void *arg)
{
    switch (cmd) {
    case MOD_LOAD:
        printf("kprintf syscall module loaded at offset %d\n", offset);
        break;
    case MOD_UNLOAD:
        printf("kprintf syscall module unloaded\n");
        break;
    default:
        return EOPNOTSUPP;
    }
    return 0;
}


static int offset = NO_SYSCALL;

SYSCALL_MODULE(kprintf, &offset, &kprintf_sysent, kprintf_load, NULL); 

