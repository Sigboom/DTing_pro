#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <sqlite3.h>
#include <stdarg.h>
#include "DxtIO.h"

/*
typedef struct Query {
    char *key;
    int size, len;
} Query;
typedef struct Dxt {
    sqlite3 *db;
    char *name;
    Query *query;
    char *rerrmsg;
} Dxt;
*/

#define INTERVIEWER(a) printf("Dxt: %s\n", a)

/*
int main() {
    char *res = PASTE("a", "b");
    eshow(res, char *);
    free(res);
    return 0;
}
*/

int order_call(void *order_num, int argc, char **argv,char **col) {
    int *temp = (int *)order_num;
    *temp = atoi(argv[0]);
    return 0;
}

int star_name_call(void *star_name, int argc, char **argv, char **col) {
    char **temp = (char **)star_name;
    strcpy(*temp, argv[0]);
    return 0;
}

int callback(void *pv,int argc,char **argv,char **col)
{
    Dxt *temp = (Dxt *)pv;
    for(int cnt_i = 0; cnt_i < argc; cnt_i++) {
        //printf("%s\t%s\n",col[cnt_i],argv[cnt_i]);
        eshow(temp->name, char *);
        eshow(argc, int);
        printf("%s\n", argv[cnt_i]);
    }
    printf("\n");
    return 0;
}

int init_env(Dxt *user) { 
    if (user == NULL) return 0;
    int result = 0;
    char *sql = "CREATE TABLE ORDERMENU("    \
    "ORDERNAME TEXT PRIMARY KEY NOT NULL,"    \
    "ORDERNUM INT8 NOT NULL);";
    
    result = sqlite3_exec(user->db,sql,callback,NULL,&user->rerrmsg);
    if(result != 0) {
        if (strcmp("table ORDERMENU already exists", user->rerrmsg)) {
            printf("creat table err:%s\n",user->rerrmsg);
            sqlite3_free(user->rerrmsg);
            return 0;
        }
    }
    #ifdef DEBUG
    printf("create table successfully!\n");
    #endif
    sql = "CREATE TABLE STARMENU("    \
    "STARNAME TEXT PRIMARY KEY NOT NULL,"    \
    "STAROWNER TEXT NOT NULL,"    \
    "STARNUM INT8 NOT NULL);";
    
    result = sqlite3_exec(user->db,sql,callback,NULL,&user->rerrmsg);
    if(result != 0) {
        if (strcmp("table STARMENU already exists", user->rerrmsg)) {
            printf("creat table err:%s\n",user->rerrmsg);
            sqlite3_free(user->rerrmsg);
            return 0;
        }
    }
    #ifdef DEBUG
    printf("create table successfully!\n");
    #endif
    sql = "INSERT INTO ORDERMENU(ORDERNAME,ORDERNUM)"        \
    "VALUES('exit', 0);"                                     \
    "INSERT INTO ORDERMENU(ORDERNAME,ORDERNUM)"              \
    "VALUES('add star', 100);"                                   \
    "INSERT INTO ORDERMENU(ORDERNAME,ORDERNUM)"              \
    "VALUES('please ask', 200);"                                    \
    "INSERT INTO ORDERMENU(ORDERNAME,ORDERNUM)"              \
    "VALUES('show star', 300);"                                    \
    "INSERT INTO ORDERMENU(ORDERNAME,ORDERNUM)"              \
    "VALUES('testpot', 190226001);"; 

    result = sqlite3_exec(user->db,sql,callback,NULL,&user->rerrmsg);
    if(result != 0) {
        if (strcmp(user->rerrmsg, "column ORDERNAME is not unique")) {
            printf("insert data err:%s\n",user->rerrmsg);
            sqlite3_free(user->rerrmsg);
            return 0;
        }
    }
    #ifdef DEBUG
    printf("insert data successfully!\n");
    #endif
    return 1;
}

int get_order_num(Query *query, sqlite3 *db) {
    int order_num = -1;
    char *rerrmsg = NULL;
    char *sql_select = PASTE("SELECT ORDERNUM FROM ORDERMENU WHERE ORDERNAME == '", query->key, "';");
    
    if(sqlite3_exec(db, sql_select, order_call, (void *)&order_num, &rerrmsg)) order_num = -1;
    free(sql_select);
    sqlite3_free(rerrmsg);
    return order_num;
}

int get_star_num(Query *query, sqlite3 *db) {
    int star_num = -1;
    char *rerrmsg = NULL; 
    char *sql_select = PASTE("SELECT STARNUM FROM STARMENU WHERE STARNAME == '", query->key, "';");
    
    if (sqlite3_exec(db, sql_select, order_call, (void *)&star_num, &rerrmsg)) star_num = -1;
    free(sql_select);
    sqlite3_free(rerrmsg);
    return star_num;
}

int make_star_num() {
    srand(time(NULL));
    return rand() % 1000 + 1;
}

char *get_star_name(sqlite3 *db, int star_num) {
    char *rerrmsg = NULL, *star_name = NULL;
    char *sql_select = PASTE("SELECT STARNAME FROM STARMENU WHERE ORDERNUM == '", itoa(star_num), "';");
    
    if (sqlite3_exec(db, sql_select, star_name_call, (void *)&star_name, &rerrmsg)) star_name = NULL;
    free(sql_select);
    sqlite3_free(rerrmsg);
    return star_name;
}

int insert_star(Dxt *user) {
    int star_num = make_star_num();
    while (get_star_name(user->db, star_num)) star_num = make_star_num();
    eshow(star_num, int);
    char *sql = PASTE("INSERT INTO STARMENU(STARNAME, STAROWNER, STARNUM) VALUES('",
                      user->query->key, "', '", user->name, "', ", itoa(star_num), ");"); 

    if(sqlite3_exec(user->db, sql, callback, NULL, &user->rerrmsg)) {
        if (strcmp(user->rerrmsg, "column ORDERNAME is not unique")) {
            printf("insert data err:%s\n",user->rerrmsg);
            sqlite3_free(user->rerrmsg);
            return 0;
        }
    }
    #ifdef DEBUG
    printf("insert data successfully!\n");
    #endif
    free(sql);
    return 1;
}

int star_empty(sqlite3 *db) {
    int num;
    char *rerrmsg = NULL, *sql = "SELECT COUNT(STARNAME) FROM STARMENU";
    if(sqlite3_exec(db, sql, order_call, (void *)&num, &rerrmsg)) num = 1;
    eshow(num, int);
    sqlite3_free(rerrmsg);
    return !num;
}

char *must_get_star_name(sqlite3 *db) {
    if (star_empty(db)) return NULL;
    char *star_name = NULL;
    while (1) {
        star_name = get_star_name(db, make_star_num());
        if (star_name) return star_name;
    }
    return NULL;
}

void exec_order(Dxt *user, int order_num) {
    switch (order_num) {
        case 0: return ;
        case 100:
            INTERVIEWER("please you star name:");
            dxt_getline(user->query);
            if(get_star_num(user->query, user->db) == -1) { 
                if (insert_star(user)) printf("You can try it!\n");
                else printf("insert star die!\n");
            } else printf("This star had been made!\n");
            break;
        case 200:
            if (star_empty(user->db))  printf("No star has been made!\n"); 
            char *star_name = NULL;
            star_name = must_get_star_name(user->db);
            printf("star is %s\n", star_name); 
            break;
        case 300:
            INTERVIEWER("Which star you like?");
            dxt_getline(user->query);
            int star_num = get_star_num(user->query, user->db);
            eshow(star_num, int);
            break;
        default:
            printf("can't find this order!\n");
            eshow(order_num, int);    
    }
    return ;
}

int main(int argc, char **args) {
    int order_num = 1;
    Dxt *user = dxt_login(argc, args);
    order_num = init_env(user);
    while (order_num) {
        dxt_getline(user->query);
        order_num = get_order_num(user->query, user->db);
        exec_order(user, order_num);
    }
    dxt_clear(user);
    return 0;
}
