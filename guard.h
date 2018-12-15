/*************************************************************************
	> File Name: guard.h
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 五  8/ 3 11:05:21 2018
 ************************************************************************/

#ifndef _GUARD_H
#define _GUARD_H

#include "register.h"

#define True 1
#define False 0
#define MAXLEN 300

typedef struct Guard {
    char *name;
    int (*open)();
    void (*attack)();
} Guard;

int open_eye(char*);
void attack();

int getLine(char sentence[], int maxsent) {
    int length = 0;
    char ch;
    while ((ch = getchar()) == '\n' || ch == ' ');
    do {
        sentence[length++] = ch;
        ch = getchar();
    } while (ch != '\n' && length < maxsent);
    sentence[length] = '\0';
    return length;    
}

Guard*guard_init(char*name) {
    Guard*new_guard = (Guard*)malloc(sizeof(Guard));
    new_guard->name = name;
    new_guard->open = &open_eye;
    new_guard->attack = &attack;
    return new_guard;
}

//实现在文件中提取关键字对应的值
char *get_con_val(char *path, const char* key) {
    char *value = (char *)malloc(sizeof(char) * MAXLEN);
    strcpy(value, "root");
    return value;
}

//检查激活文件
int check_key(char *key_path) {
    char *key = get_con_val(key_path, "key.dxt");
    if (strcmp(key, "root") == 0) return 1;
    return 0;
}

int understand (char *say) {
    return 0;
}

//身份审核
int open_eye(char*name) {
    printf("My name is %s!\n", name);
    char 
    if (check_key(key_path)) return 1;
    return 0;
}

void attack() {
    printf("attack is runing~\n");
    exit(1);
}

#endif
