// author: air029
#ifndef __H2_ALSH_H
#define __H2_ALSH_H

#include <iostream>
#include <thread>
#include <cmath>
#include "def.h"
#include "util.h"

void info_h();
void extend_h2(float **data, float **norm_d, float **query, float **norm_q, float **ext_data, float **ext_query, float max_norm_d);
void hash_data_h2(float **ext_data, float **random_vector, float *uniform_num, float **hash_num_d, int k); //k hash num
void hash_query_h2(float **ext_query, float **random_vector, float *uniform_num, float **hash_num_q, int k);

#endif // __SIGN_ALSH_H
