#include <sys/types.h>
#include <sys/param.h>
#include <sys/module.h>
#include <sys/sysent.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/syscallsubr.h>
#include <sys/proc.h>
#include <sys/uio.h>
#include <sys/unistd.h>

#ifndef AUE_NULL
#define AUE_NULL 0
#endif

struct kprintf_args {
    char *buf;
};

static int
kprintf_syscall(struct thread *td, void *args)
{
    struct kprintf_args *uap = (struct kprintf_args *)args;

    if (uap != NULL) {
        char kbuf[256] = {0};
        if (copyinstr(uap->buf, kbuf, sizeof(kbuf), NULL) == 0) {
            printf("%s", kbuf);
        }
    }

    return 0;
}

static struct sysent kprintf_sysent = {
    .sy_narg = sizeof(struct kprintf_args) / sizeof(register_t),
    .sy_call = kprintf_syscall
};

static int offset = NO_SYSCALL;

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

SYSCALL_MODULE(kprintf, &offset, &kprintf_sysent, kprintf_load, NULL);

