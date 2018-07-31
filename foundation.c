/*************************************************************************
	> File Name: foundation.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 一  7/23 13:43:48 2018
 ************************************************************************/

#include "foundation.h"

void waiterInit(Waiter*);
int waiting();
void getOrder();
char*getName();
void run();

void waiterInit(Waiter* waiter) {
    if (waiter == NULL) {
        waiter = (Waiter*)malloc(sizeof(Waiter));
    }
    srand(time(0));
    waiter->id = rand() % MAXID;
    waiter->name = getName();
    waiter->wait = &waiting;
    waiter->getOrder = getOrder;
    waiter->doOrder = run;
}

int waiting() {
    printf("okokoko\n");
    fflush(stdout);
    int i, j, k = 0;
    while (k++ < 3) {
        i = clock();
        printf("i = %d\n", i);
        j = clock();
        printf("j = %d\n", j);
        sleep(3);
    }
    return 0;
}

void getOrder() {
    
}

void run() {
    
}

char*getName() {
    char* temp = (char*)malloc(sizeof(char) * (MAXNAME + 1));
    printf("What is waiter's name?\n");
    printf(">> ");
    scanf("%s", temp);
    printf("Your waiter is %s\n", temp);
    return temp;
}




