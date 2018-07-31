/*************************************************************************
	> File Name: entrance.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 日  7/15 09:43:49 2018
 ************************************************************************/

#include "foundation.h"

#define WAIT     bigboom->wait
#define GETORDER bigboom->getOrder
#define DOORDER  bigboom->doOrder

int wait_test();

int main() {
    Waiter* bigboom = NULL;
    waiterInit(bigboom);
    bigboom->wait = wait_test;
    while(WAIT()) {
        GETORDER();
        DOORDER();
    }
    return 0;
}

int wait_test() {
    printf("-------\n");
    sleep(2);
    return 0;
}

