// author: air029
#include "h2_alsh.h"

void info_h()
{
	std::cout << "\n\n------------------------------------------------------------------------------------" << std::endl;
	std::cout << "H2ALSH:" << std::endl;
	std::cout << "Parameter:" << std::endl;
}

void extend_h2(float **data, float **norm_d, float **query, float **norm_q, float **ext_data, float **ext_query, float max_norm_d)
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < D; ++j)
		{
			ext_data[i][j] = data[i][j];
		}
		ext_data[i][D] = sqrt(pow(max_norm_d, 2) - pow(norm_d[i][0], 2));
	}

	//query
	float lambda;
	for (int i = 0; i < QN; ++i)
	{
		lambda = max_norm_d / norm_q[i][0];
		for (int j = 0; j < D; ++j)
		{
			ext_query[i][j] = lambda * query[i][j];
		}
		ext_query[i][D] = 0;
	}
}

void hash_data_h2(float **ext_data, float **random_vector, float *uniform_num, float **hash_num_d, int k) //k hash num
{
	float data_inner_product;
	for (int i = 0; i < N; ++i) //each data
	{
		for (int p = 0; p < k; ++p) //each hash func
		{
			data_inner_product = dot(ext_data[i], random_vector[p], D + 1);
			hash_num_d[i][p] = floor((data_inner_product + uniform_num[p]) / R);
		}
	}
}

void hash_query_h2(float **ext_query, float **random_vector, float *uniform_num, float **hash_num_q, int k)
{
	float query_inner_product;
	for (int i = 0; i < QN; ++i) //each query
	{
		for (int p = 0; p < k; ++p) //each hash func
		{
			query_inner_product = dot(ext_query[i], random_vector[p], D + 1);
			hash_num_q[i][p] = floor((query_inner_product + uniform_num[p]) / R);
		}
	}
}
