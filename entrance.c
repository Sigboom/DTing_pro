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

Env env;

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
    //portal();
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
