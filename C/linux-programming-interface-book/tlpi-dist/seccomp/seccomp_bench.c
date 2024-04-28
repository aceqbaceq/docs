/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2022.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Supplementary program for Chapter Z */

/* seccomp_bench.c

   A program to do some rough benchmarking for seccomp filtering.

   This program is run with the following command-line:

        seccomp_bench <num-loops> [<instr> <instr-cnt> [num-filters]]

   The program loops calling getppid() 'num-loops' times after optionally
   installing seccomp filter(s).

   If just one command-line argument is supplied, then no BPF filter
   installed; this can be used to establish the baseline cost of the
   getppid() calls.

   If additional arguments are supplied, then a seccomp filter is installed
   before the getppid() loop is executed. The 'instr' argument determines
   what kind of instructions are placed in the filter, and can be
   'a' (BPF_ADD), 'l' (BPF_LD), or 'j' (BPF_JEQ). A filter is constructed
   that contains 'instr-cnt' instances of the specified instruction, plus
   a BPF_RET instruction to terminate the filter.

   By default, one copy of the filter is installed into the kernel, but the
   optional 'num-filters' argument can be used to specify that multiple
   filter instances should be installed.

   To test with the in-kernel JIT compiler enabled:

        $ sudo sh -c "echo 1 > /proc/sys/net/core/bpf_jit_enable"

   (In more recent Linux distributions, the JIT compiler is enabled by
   default.)
*/
#define _GNU_SOURCE
#include <sys/syscall.h>
#include <linux/filter.h>
#include <linux/seccomp.h>
#include <sys/prctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)

static int
seccomp(unsigned int operation, unsigned int flags, void *arg)
{
    return syscall(__NR_seccomp, operation, flags, arg);
    // Or: return prctl(PR_SET_SECCOMP, operation, arg);
}

static void
install_filter(char *instr, int icnt)
{
    struct sock_filter load = BPF_STMT(BPF_LD | BPF_W | BPF_ABS, 0);
    struct sock_filter jump = BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0, 0, 0);
    struct sock_filter add = BPF_STMT(BPF_ALU | BPF_ADD | BPF_K, 1);
    struct sock_filter ret = BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ALLOW);
    struct sock_filter instruction;
    struct sock_filter *filter;

    filter = calloc(icnt + 1, sizeof(struct sock_filter));

    /* Create a filter containing 'icnt' instructions of the kind specified
       in 'instr' */

    if (instr[0] == 'a')
        instruction = add;
    else if (instr[0] == 'j')
        instruction = jump;
    else if (instr[0] == 'l')
        instruction = load;
    else {
        fprintf(stderr, "Bad instruction value: %s\n", instr);
        exit(EXIT_FAILURE);
    }

    for (int j = 0; j < icnt; j++)
        filter[j] = instruction;

    /* Add a return instruction to terminate the filter */

    filter[icnt] = ret;

    /* Install the BPF filter */

    struct sock_fprog prog = {
        .len = icnt + 1,
        .filter = filter,
    };

    if (seccomp(SECCOMP_SET_MODE_FILTER, 0, &prog) == -1)
        errExit("seccomp");
}

int
main(int argc, char *argv[])
{
    if (argc != 2 && argc < 4) {
        fprintf(stderr, "Usage: %s <num-loops> [<add|jump|load> "
                "<instr-cnt> [num-filters]]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc >= 4) {
        int nfilters = (argc > 4) ? atoi(argv[4]) : 1;
        int icnt = atoi(argv[3]);

        printf("Applying BPF filter\n");

        if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0))
            errExit("prctl");

        for (int j = 0; j < nfilters; j++)
            install_filter(argv[2], icnt);
    }

    int nloops = atoi(argv[1]);

    for (int j = 0; j < nloops; j++)
        getppid();

    exit(EXIT_SUCCESS);
}
