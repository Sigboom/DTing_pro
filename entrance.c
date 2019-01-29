/*************************************************************************
	> File Name: entrance.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 日  7/15 09:43:49 2018
 ************************************************************************/

#include "foundation.h"
#include "guard.h"

#define DXNode_t int
#define DXKey_t char

typedef struct DXMap {
    DXKey_t *key;
    DXNode_t *value;
    int n;
} DXMap;

void signboard();
void portal();

void clear(Guard *g) {
    free(g);
    for (int i = 0; i < env.cnt; ++i) {
        free(env.key[i]);
        free(env.value[i]);
    }
    return ;
}

int main() {
    init_env();
    signboard();
    Guard *daniel = guard_init("daniel");
    //if (!daniel->open(daniel->name)) daniel->attack();
    portal();
    clear(daniel);
    return 0;
}

void signboard() {
    printf("Welcome to DXTing~~\n");
    return ;
}

void portal() {
    printf("portal is running~\n");
    return ;
}
