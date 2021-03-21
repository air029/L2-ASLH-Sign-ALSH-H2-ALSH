// author: air029
#ifndef __MIP_H
#define __MIP_H

#include <fstream>
#include <queue>
#include "def.h"
#include "util.h"

void bubble(POINT *point, int length, int topk);

void multisort(POINT **candidate, int begin, int end);

void sort(POINT **candidate, int type);

void p_sort(POINT **candidate, int type);

void p_multisort(POINT **candidate, int begin, int end);

void p_bubble(POINT *point, int length, int topk);

void mip(float **data, int dnum, float **query, int qnum, int topk, const char *outpath);

#endif // __MIP_H
