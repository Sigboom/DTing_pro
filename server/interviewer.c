/*************************************************************************
	> File Name: sqltest.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 三  2/ 6 13:38:07 2019
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sqlite3.h>

#define NAMELEN 30
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
                                printf(type_format, varb);               \
                                printf("\n");                            \
                            }})


typedef struct Dxt {
    sqlite3 *db;
    char *name;
} Dxt;

int callback(void *pv,int argc,char **argv,char **col)
{
    int cnt_i = 0;
    for(cnt_i =0;cnt_i < argc;cnt_i++)
        printf("%s\t%s\n",col[cnt_i],argv[cnt_i]);
    printf("\n");
    return 0;
}

int name_check(char *name) {
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

void dxt_clear(Dxt *dxt) {
    free(dxt->name);
    free(dxt);
    return ;
}

Dxt *dxt_login(int argc, char **args) {
    Dxt *new_user = (Dxt *)malloc(sizeof(Dxt));
    new_user->name = (char *)calloc(sizeof(char), NAMELEN);
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
    result = sqlite3_open(new_user->name, &new_user->db);
    if(result > 0) {
        printf("open database err:%s\n",sqlite3_errmsg(new_user->db));
        return NULL;
    }
    printf("open database successfully!\n");
    return new_user;
}

int main(int argc, char **args) {
    int result = 0;
    char *rerrmsg = NULL;
    char *sql = NULL;
    char *data = "callback";
    
    Dxt *user = dxt_login(argc, args);
    if (user == NULL) return 0;
    
    sql = "CREATE TABLE STUDENT("    \
    "NUM INT PRIMARY KEY NOT NULL,"    \
    "NAME TEXT NOT NULL,"        \
    "AGE INT NOT NULL,"        \
    "SORCE REAL);";

    result = sqlite3_exec(user->db,sql,callback,NULL,&rerrmsg);
    if(result != 0) {
        printf("creat table err:%s\n",rerrmsg);
        sqlite3_free(rerrmsg);
        return -2;
    }
    printf("create table successfully!\n");

    sql = "INSERT INTO STUDENT(NUM,NAME,AGE,SORCE)"        \
    "VALUES(1,'Paul',13,99.1);"                    \
    "INSERT INTO STUDENT(NUM,NAME,AGE,SORCE)"        \
    "VALUES(2,'Kate',15,94.1);"                    \
    "INSERT INTO STUDENT(NUM,NAME,AGE,SORCE)"        \
    "VALUES(3,'Jim',12,95.1);"                    \
    "INSERT INTO STUDENT(NUM,NAME,AGE,SORCE)"        \
    "VALUES(4,'Tom',13,99.4);"                    \
    "INSERT INTO STUDENT(NUM,NAME,AGE,SORCE)"        \
    "VALUES(5,'Jack',13,89.1);";

    result = sqlite3_exec(user->db,sql,callback,NULL,&rerrmsg);
    if(result != 0) {
        printf("insert data err:%s\n",rerrmsg);
        sqlite3_free(rerrmsg);
        return -3;
    }
    printf("insert data successfully!\n");
    sql = "SELECT * FROM STUDENT";
    result = sqlite3_exec(user->db,sql,callback,(void *)data,&rerrmsg);
    if(result != 0) {
        printf("select data err:%s\n",rerrmsg);
        sqlite3_free(rerrmsg);
        return -4;
    }
    printf("select data successfully!\n");
    sqlite3_close(user->db);

    dxt_clear(user);
    return 0;
}
