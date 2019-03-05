/*************************************************************************
	> File Name: DxtIO.h
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 四  2/28 17:59:00 2019
 ************************************************************************/

#ifndef _DXTIO_H
#define _DXTIO_H


#define eshow(varb, type) ({            \
                            char type_format[4] = "";                    \
                            if (strcmp(#type, "char") == 0)              \
                            strcpy(type_format, "%d");                   \
                            else if (strcmp(#type, "int") == 0)          \
                            strcpy(type_format, "%d");                   \
                            else if (strcmp(#type, "long") == 0)         \
                            strcpy(type_format, "%ld");                  \
                            else if (strcmp(#type, "float") == 0)        \
                            strcpy(type_format, "%.2f");                 \
                            else if (strcmp(#type, "double") == 0)       \
                            strcpy(type_format, "%.2lf");                \
                            else if (strcmp(#type, "char *") == 0)       \
                            strcpy(type_format, "%s");                   \
                            else if (strcmp(#type, "char*") == 0)       \
                            strcpy(type_format, "%s");                   \
                            else if (strcmp(#type, "unsigned int") == 0) \
                            strcpy(type_format, "%u");                   \
                            else printf("%s is not easy type!\n", #type);\
                            if (strcmp(type_format, "") != 0) {          \
                                printf("%s = ", #varb);                  \
                                printf(type_format, (type)varb);               \
                                printf("\n");                            \
                            }})

#define PASTE(...) paste(__VA_ARGS__, NULL)
char *paste(char *str, ...) {
    #define BLOCK 100
    va_list ap;
    va_start(ap, str);
    int len = strlen(str), size = BLOCK;
    char *temp, *res = (char *)malloc(sizeof(char) * size);
    strcpy(res, str);
    while ((temp = va_arg(ap, char *))) {
        while (len + strlen(temp) > size) {
            size += BLOCK;
            res = realloc(res, sizeof(char) * size);
        }
        len += strlen(temp);
        strcat(res, temp);
    }
    va_end(ap);
    #undef BLOCK
    return res;
}

#include "RBTree.c"

typedef struct Query {
    char *key;
    int size, len;
} Query;

typedef struct Dxt {
    sqlite3 *db;
    Query *query;
    RBTNode *rbtree;
    char *name;
    char *rerrmsg;
} Dxt;

int name_check(char *name) {
    #define NAMELEN 30
    if (strlen(name) > NAMELEN) {
        printf("Your database name is too long!\n");
        return 0;
    }
    if (!islower(name[0]) && !isupper(name[0]) && (name[0] != '_')) {
        printf("The database name should begin with alphabet or '_'.\n");
       return 0;
    }
    for (int i = 0; name[i]; ++i) {
        if (!islower(name[i]) && !isupper(name[i]) && !isdigit(name[i]) && name[i] != '_' && name[i] != '.') {
            printf("The database name should not contain special characters\n");
            return 0;
        }
    }
    return 1;
}

char *itoa(int num) {
    char *res = (char *)malloc(sizeof(char) * 100);
    int top = floor(log10(num)) + 1;
    while(top--) {
        res[top] = num % 10 + '0';
        num /= 10;
    }
    return res;
}

void dxt_getline(Query *query) {
    char ch = '\n';
    int len = 0, size = query->size;
    #define BLOCK 100
    if (query->key == NULL) {
        query->key = (char *)malloc(sizeof(char) * BLOCK);
        query->size = 1;
    }
    printf(">>> ");
    while (ch == '\n' || ch == ' ') ch = getchar();
    do {
        query->key[len++] = ch;
        if (len > size * BLOCK) {
            size++;
            char *temp = (char *)malloc(sizeof(char) * (size * BLOCK));
            strcpy(temp, query->key);
            free(query->key);
            query->key = temp;
        }
    } while ((ch = getchar()) != '\n');
    #undef BLOCK
    query->key[len] = '\0';
    query->len = len;
    query->size = size;
    return ;
}

void dxt_clear(Dxt *user) {
    if (user == NULL) return ;
    sqlite3_close(user->db);
    free(user->query->key);
    free(user->query);
    free(user->name);
    free(user);
    return ;
}

Dxt *dxt_login(int argc, char **args) {
    Dxt *new_user = (Dxt *)malloc(sizeof(Dxt));
    new_user->name = (char *)calloc(sizeof(char), NAMELEN);
    new_user->query = (Query *)malloc(sizeof(Query));
    new_user->query->key = NULL;
    new_user->rbtree = NULL;
    strcpy(new_user->name, "dxt_sample.db");
    char answer[50];
    if (argc != 1) { 
        if (name_check(args[1])) {
            int len  = strlen(args[1]);
            strcpy(new_user->name, args[1]);
            if (len < 4 || new_user->name[len - 1] != 'b' || 
                new_user->name[len - 2] != 'd' || new_user->name[len - 3] != '.')
                strcat(new_user->name, ".db");
        } else {
            printf("I'm go to sleep!\n");
            dxt_clear(new_user);
            return NULL;
        }
    } else {
        printf("You want to use default database name(dxt_sample.db)? (y/n)\n"); 
        scanf("%s", answer);
        if (strcmp(answer, "Y") && strcmp(answer, "yes") && strcmp(answer, "y") && strcmp(answer, "1")) {
            for (int i = 0; i < 3; i++) {
                printf("input your database name: ");
                scanf("%s", answer);
                if (!name_check(answer)) continue;
                int len  = strlen(answer);
                strcpy(new_user->name, answer);
                if (len < 4 || new_user->name[len - 1] != 'b' || 
                    new_user->name[len - 2] != 'd' || new_user->name[len - 3] != '.')
                strcat(new_user->name, ".db");
                break;
            }
            if (!name_check(answer)) {
                printf("I'm go to sleep!\n");
                dxt_clear(new_user);
                return NULL;
            }
        }
    }
    #ifdef DEBUG
    eshow(new_user->name, char *);
    #endif
    int result = sqlite3_open(new_user->name, &new_user->db);
    if(result > 0) {
        printf("open database err:%s\n",sqlite3_errmsg(new_user->db));
        return NULL;
    }
    printf("open database successfully!\n");
    return new_user;
}

#endif
