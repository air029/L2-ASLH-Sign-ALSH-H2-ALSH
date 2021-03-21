// author: air029
//util.h
#ifndef __UTIL_H
#define __UTIL_H

#include <iostream>
#include <cmath>
#include <cstring>
#include <cassert>
#include <ctime>
#include <thread>
#include <fstream>
#include <stdlib.h>

#include "def.h"

//calc
float uniform(float min, float max);
float gaussian(float mean, float sigma);
float dot(float *a, float *b, int k);

//read data
int read_txt_data(int n, int d, const char *fname, float **data, float **norm_d);
int read_ground_truth(int qn, const char *fname, Result **R);
void display_origin_data(int n, int d, float **data, float **norm_d);
void display_origin_query(int qn, int d, float **query, float **norm_q);
void display_ground_truth(int qn, Result **R);
void display_ext(int type, float **ext_data, float **ext_query);
void display_hash_num_d(float **hash_num_d, int k);
void display_hash_num_q(float **hash_num_q, int k);
void display_POINT(POINT **point, int qn, int n);
void display_Result(Result **point, int qn, int n);

//
float max_norm(float **norm_d, int n);
void normalize(float **data, float **norm_d, float **ndata, float **norm_ndata, float **query, float **norm_q, float **nquery, float **norm_nquery, float max_norm_d, int type);
//type 1 l2 2 sign

//random vector
void create_random_vec(float **random_vector);
void display_random_vec(float **random_vector);

//uniform num
void create_uniform_num(float *uniform_num);

float m_recall(Result **result, POINT **candidate);
void retrieve_recall(Result **result, POINT **candidate, int threshhold, const char *output);

void indicator(int i);
void t(int i);

void candidate_reset(POINT **candidate, int qn, int n);

void multimatches(float **hash_num_d, float **hash_num_q, POINT **candidate, int k, int begin, int end);
void matches(float **hash_num_d, float **hash_num_q, POINT **candidate, int k, int type); //k func num

void construct(float **ext_data, float **ext_query, float **ndata, float **norm_ndata, float **nquery, float **norm_nquery, float **hash_num_d, float **hash_num_q, POINT **candidate);

void destruct(float **ext_data, float **ext_query, float **ndata, float **norm_ndata, float **nquery, float **norm_nquery, float **hash_num_d, float **hash_num_q, POINT **candidate);

void reset(float **ext_data, float **ext_query, float **ndata, float **norm_ndata, float **nquery, float **norm_nquery, float **hash_num_d, float **hash_num_q, POINT **candidate);

void loginfo(const char *filename, const char* type, int round, int max_round);
#endif // __UTIL_H
