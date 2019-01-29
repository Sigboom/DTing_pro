/*************************************************************************
	> File Name: DxtIO.h
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 二  1/29 17:29:43 2019
 ************************************************************************/

#ifndef _DXTIO_H
#define _DXTIO_H

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
