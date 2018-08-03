/*************************************************************************
	> File Name: register.h
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 五  8/ 3 13:39:06 2018
 ************************************************************************/

#ifndef _REGISTER_H
#define _REGISTER_H

typedef struct Register {
    char *name;
    void (*open)();
    int (*getInfo)();
} Register;

void Ropen();
int getInfo();

Register* register_init(char* name) {
    Register* Xabi = (Register*)malloc(sizeof(Register));
    Xabi->name = name;
    Xabi->open = &Ropen;
    Xabi->getInfo = &getInfo;
    return Xabi;
}

void Ropen() {
    printf("register Ropen is running~~\n");
    return ;
}
int getInfo() {
    printf("register getInfo is running~~\n");
    return 1;
}
#endif
