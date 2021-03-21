// author: air029
#include "l2_alsh.h"

void info_l()
{
	std::cout << "\n\n------------------------------------------------------------------------------------" << std::endl;
	std::cout << "L2ALSH:" << std::endl;
	std::cout << "Parameter:"
			  << "	M:" << M << "	U:" << U_E << "	R:" << R << std::endl;
}

void extend_l2(float **ndata, float **norm_ndata, float **nquery, float **ext_data, float **ext_query)
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < D + M; ++j)
		{
			if (j < D)
			{
				ext_data[i][j] = ndata[i][j];
			}
			else
			{
				ext_data[i][j] = pow(norm_ndata[i][0], 2 * (j - D + 1));
				;
			}
		}
	}

	//query
	for (int i = 0; i < QN; ++i)
	{
		for (int j = 0; j < D + M; ++j)
		{
			if (j < D)
			{
				ext_query[i][j] = nquery[i][j];
			}
			else
			{
				ext_query[i][j] = 0.5;
			}
		}
	}
}

void hash_data_l2(float **ext_data, float **random_vector, float *uniform_num, float **hash_num_d, int k) //k hash num
{
	float data_inner_product;
	for (int i = 0; i < N; ++i) //each data
	{
		for (int p = 0; p < k; ++p) //each hash func
		{
			data_inner_product = dot(ext_data[i], random_vector[p], D + M);
			hash_num_d[i][p] = floor((data_inner_product + uniform_num[p]) / R);
		}
	}
}

void hash_query_l2(float **ext_query, float **random_vector, float *uniform_num, float **hash_num_q, int k)
{
	float query_inner_product;
	for (int i = 0; i < QN; ++i) //each query
	{
		for (int p = 0; p < k; ++p) //each hash func
		{
			query_inner_product = dot(ext_query[i], random_vector[p], D + M);
			hash_num_q[i][p] = floor((query_inner_product + uniform_num[p]) / R);
		}
	}
}
