/*************************************************************************
	> File Name: sqltest.c
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 三  2/ 6 13:38:07 2019
 ************************************************************************/

#include <stdio.h>
#include <sqlite3.h>

int callback(void *pv,int argc,char **argv,char **col) {
    int cnt_i = 0;
    for(cnt_i =0;cnt_i < argc;cnt_i++)
        printf("%s\t%s\n",col[cnt_i],argv[cnt_i]);
    printf("\n");
    return 0;
}

int main(void) {
    sqlite3 *db;
    int result = 0;
    char *rerrmsg = NULL;
    char *sql = NULL;
    char *data = "callback";

    result = sqlite3_open("sample.db",&db);
    if(result > 0) {
        printf("open database err:%s\n",sqlite3_errmsg(db));
        return -1;
    } else {
        printf("open database successfully!\n");
        sql = "CREATE TABLE STUDENT("    \
              "NUM INT PRIMARY KEY NOT NULL,"    \
              "NAME TEXT NOT NULL,"        \
              "AGE INT NOT NULL,"        \
              "SORCE REAL);";
        
        result = sqlite3_exec(db,sql,callback,NULL,&rerrmsg);
        if(result != 0) {
            printf("creat table err:%s\n",rerrmsg);
            sqlite3_free(rerrmsg);
            return -2;
        } else {
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

            result = sqlite3_exec(db,sql,callback,NULL,&rerrmsg);
            if(result != 0) {
                printf("insert data err:%s\n",rerrmsg);
                sqlite3_free(rerrmsg);
                return -3;
            } else {
                printf("insert data successfully!\n");

                sql = "SELECT * FROM STUDENT";
                result = sqlite3_exec(db,sql,callback,(void *)data,&rerrmsg);
                if(result != 0) {
                    printf("select data err:%s\n",rerrmsg);
                    sqlite3_free(rerrmsg);
                    return -4;
                } else {
                    printf("select data successfully!\n");
                }
            }
        }
    }
    sqlite3_close(db);

    return 0;
}
