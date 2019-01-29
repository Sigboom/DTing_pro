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
#define MAXLEN 200
#define MAXNAME 30

typedef struct Env {
    char *key[MAXLEN];
    char *value[MAXLEN];
    int max, cnt;
    char *(*getval) (char *);
    int (*get_val_num) (char *);
    void (*setval)(char *, const char *);
    void (*show_env)();
} Env;

Env env;

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

int get_env_num(char *key) {
    if (env.cnt == 0) return -1;
    int min = 0, max = env.cnt, mid;
    mid = (min + max) >> 1;
    while (min <= max) {
        if (strcmp(env.key[mid], key) == 0) return mid;
        if (strcmp(env.key[mid], key) > 0) max = mid - 1;
        else min = mid + 1;
        mid = (min + max) >> 1;
    }
    return -1; 
}

char *get_env(char *key) {
    if (env.cnt == 0) return NULL;
    int min = 0, max = env.cnt, mid;
    mid = (min + max) >> 1;
    while (min <= max) {
        if (strcmp(env.key[mid], key) == 0) return env.value[mid];
        if (strcmp(env.key[mid], key) > 0) max = mid - 1;
        else min = mid + 1;
        mid = (min + max) >> 1;
    }
    return NULL; 
}

void set_env(char *key, const char *val) {
    if (env.max <= env.cnt) {
        printf("init_env overflow!\n");
        return ;
    }
    int i;
    if((i = get_env_num(key) != -1)) {
        strcpy(env.value[i], val);
        return ;
    }
    env.key[env.cnt] = (char *)malloc(sizeof(char) * MAXNAME);
    env.value[env.cnt] = (char *)malloc(sizeof(char) * MAXLEN);
    for (i = env.cnt; i; --i) {
        if (strcmp(env.key[i], key) > 0) break;
        strcpy(env.key[i], env.key[i - 1]);
        strcpy(env.value[i], env.value[i - 1]);
    }
    strcpy(env.key[i], key);
    strcpy(env.value[i], val);
    env.cnt++;
    return ;
}

void show_env() {
    for (int i = 0; i < env.cnt; ++i) {
        printf("%s : %s\n", env.key[i], env.value[i]);
    }
    return ;
}

int init_env() {
    env.max = MAXLEN;
    env.cnt = 0;
    env.setval = set_env;
    env.getval = get_env;
    env.get_val_num = get_env_num;
    env.show_env = show_env;
    char temp[MAXLEN];
    FILE *fp = fopen("DXT.conf", "r");
    while ((fscanf(fp, "%s", temp) != EOF)) {
        char *key = strtok(temp, "=");
        char *val = strtok(NULL, "=");
        env.setval(key, val);
    }
    env.show_env();
    printf("env init successfully!\n");
    fclose(fp);
    return 1;
}

#endif
