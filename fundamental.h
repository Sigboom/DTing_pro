/*************************************************************************
	> File Name: fundamental.h
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 二  7/10 23:10:02 2018
 ************************************************************************/

#ifndef _FUNDAMENTAL_H
#define _FUNDAMENTAL_H

#include <stdio.h>
#include <string.h>
#include "printColor.h"


extern void DTPrint();
extern void celitPrint();
extern int getLine(char sentence[], int maxsent);
extern int fgetLine(FILE*fp, char sentence[], int maxsent);
extern void desktop();
extern void nextDesk();
extern int DTExit();
extern void notFoundDesk(char*str);

#endif
