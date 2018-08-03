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

int open(char*);
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
    new_guard->open = &open;
    new_guard->attack = &attack;
    return new_guard;
}

int is_check (FILE *fp) {
    return 1;
}

int understand (char *say) {
    return 0;
}

int open(char*name) {
    printf("My name is %s!\n", name);
    FILE*key;
    int license = 0;
    char say[MAXLEN];
    if ((key = fopen("key.dxt", "r+")) == NULL) {
        license = -1;
    }
    while (True) {
        if (license == -1) {
            FILE*NY = fopen("come.say", "r");
            if (NY != NULL) {
                int i = 0;
                while (fscanf(NY, "%s", say) != EOF) {
                    if (i == 0) {
                        printf("%s >> ", name);
                    } else {
                        printf("\t");
                    }
                    printf("%s\n", say);
                }
                while (getLine(say, MAXLEN)) {
                    if(understand(say)) {
                        Register *Xabi = register_init("Xabi");
                        Xabi->open();
                        if (Xabi->getInfo()) {
                            return 1;
                        } else {
                            return 0;
                        }
                    } else {
                        printf("%s >> ", name);
                        printf("pardon?\n");
                    }
                }
            } else {
                printf("%s >> ", name);
                printf("What Should I say when you firsh come here?\n");
                NY = fopen("come.say", "w");
                scanf("%s", say);
                fprintf(NY, "%s", say);
                fclose(NY);
            }
        } else {
            printf("reading license~~\n");
            if (is_check(key)) {
                return 1;
            }
        }
    }
    return 0;
}

void attack() {
    printf("attack is runing~\n");
    return ;
}

#endif
