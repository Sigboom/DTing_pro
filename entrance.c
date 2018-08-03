/*************************************************************************
	> File Name: entrance.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 日  7/15 09:43:49 2018
 ************************************************************************/

#include "foundation.h"
#include "guard.h"

void signboard();
void portal();

int main() {
    signboard();
    Guard *daniel = guard_init("daniel");
    if (daniel->open(daniel->name)) {
        portal();
    } else {
        daniel->attack();  
    }
    free(daniel);
    return 0;
}

void signboard() {
    printf("Welcome to DXTing~~\n");
    return ;
}

void portal() {
    printf("portal is runing~\n");
    return ;
}
