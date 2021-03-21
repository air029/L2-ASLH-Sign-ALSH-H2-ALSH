// author: air029
#ifndef __DEF_H
#define __DEF_H

#include <iostream>

const float MAXREAL = 3.402823466e+38F;
const float MINREAL = -MAXREAL;
const int MAXINT = 2147483647;
const int MININT = -MAXINT;
const int SIZEBOOL = (int)sizeof(bool);
const int SIZEINT = (int)sizeof(int);
const int SIZECHAR = (int)sizeof(char);
const int SIZEFLOAT = (int)sizeof(float);
const int SIZEDOUBLE = (int)sizeof(double);
const float E = 2.7182818F;
const float PI = 3.141592654F;
const float FLOATZERO = 1e-6F;
const float ANGLE = PI / 8.0f;

const int K[] = {64, 128, 256, 512}; //hash num
const int K_ROUND = 4;                                //number of hash
const int K_MAX = 512;
const int NORM_K = 1; //max extension length
const int M = 3;      //extension length
const float U_E = 0.83;
const float U_C = 0.85;
const float R = 2.5; //paremeter r for l2

//data parameter
const int N = 17770; //data number
const int QN = 1000;   //query number
const int D = 300;     //dimension
const int TOPK = 100;  //top_K
const int RETRIEVEK = 17770;

const int THN = 10; //thread num

struct Result
{               // structure for furthest neighbor / hash value
    float key_; // distance / random projection value
    int id_;    // object id
};

struct POINT
{
    int index;
    float value; //product or matches
    friend bool operator < (POINT p1, POINT p2)
    {
        return p1.value > p2.value;
    }
};

#endif // __DEF_H
