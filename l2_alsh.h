// author: air029
#ifndef __L2_ALSH_H
#define __L2_ALSH_H

#include <iostream>
#include <thread>
#include <cmath>
#include "def.h"
#include "util.h"

void info_l();
void extend_l2(float **ndata, float **norm_ndata, float **nquery, float **ext_data, float **ext_query);
void hash_data_l2(float **ext_data, float **random_vector, float *uniform_num, float **hash_num_d, int k);
void hash_query_l2(float **ext_query, float **random_vector, float *uniform_num, float **hash_num_q, int k);

#endif // 