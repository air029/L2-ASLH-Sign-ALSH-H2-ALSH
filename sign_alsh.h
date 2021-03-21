// author: air029
#ifndef __SIGN_ALSH_H
#define __SIGN_ALSH_H

#include <iostream>
#include <thread>
#include <cmath>
#include "def.h"
#include "util.h"

void info_s();
void extend_sign(float **ndata, float **norm_ndata, float **nquery, float **ext_data, float **ext_query);
void hash_data_sign(float **ext_data, float **random_vector, float **hash_num_d, int k);
void hash_query_sign(float **ext_query, float **random_vector, float **hash_num_q, int k);

#endif // __SIGN_ALSH_H
