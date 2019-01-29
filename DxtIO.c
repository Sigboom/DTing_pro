/*************************************************************************
	> File Name: DxtIO.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 二  1/29 17:30:42 2019
 ************************************************************************/

#include <stdio.h>
#include "order.h"

void DTPrint() {
    printf(L_BLUE "DT: " L_PURPLE);
}

void celitPrint() {
    printf(">> ");
}

int getLine(char sentence[], int maxsent) {
    int length = 0;
    char ch;
    celitPrint();
    while ((ch = getchar()) == '\n' || ch == ' ');
    do {
        sentence[length++] = ch;
        ch = getchar();
    } while (ch != '\n' && length < maxsent);
    sentence[length] = '\0';
    return length;    
}

int fgetLine(FILE*fp, char sentence[], int maxsent) {
    int length = 0;
    char ch;
    while ((ch = fgetc(fp)) == '\n' || ch == ' ');
    if(ch == EOF) return EOF;
    do {
        sentence[length++] = ch;
        ch = fgetc(fp);
    } while(ch != '\n' && length < maxsent);
    sentence[length] = '\0';
    return length;
}

void desktop() {
    DTPrint();
    printf("Welcome to Daniel's DTing!\n" NONE);
    printf("Here is menu...\n");
    showOrderMenu();
    DTPrint();
    printf("What can I do for you?\n" NONE);
}

void nextDesk() {
    DTPrint();
    printf("What else can I do for you?\n" NONE);
}

int DTExit() {
    DTPrint();
    printf("BYE BYE ~~~\n" NONE);
    printf("Log out...\n");
    return 0;
}

void notFoundDesk(char*str) {
    DTPrint();
    printf("What is \"%s\"? I can't understand...\n" NONE, str);
}



