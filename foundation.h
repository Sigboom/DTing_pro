/*************************************************************************
	> File Name: foundation.h
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 日  7/15 09:46:18 2018
 ************************************************************************/

#ifndef _FOUNDATION_H
#define _FOUNDATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAXID 10000
#define MAXNAME 20

typedef struct Memory {
    int askTimes;
    char *order;
    int orderTimes;
} Memory;

typedef struct Waiter {
    int id:8;
    char *name;
    Memory memory;
    int (*wait)();
    void (*getOrder)();
    void (*doOrder)();
} Waiter;

extern void waiterInit(Waiter*);

#endif
