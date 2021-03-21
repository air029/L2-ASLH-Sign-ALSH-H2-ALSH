// author: air029
#include "sign_alsh.h"

void info_s()
{
	std::cout << "\n\n------------------------------------------------------------------------------------" << std::endl;
	std::cout << "CosineALSH:" << std::endl;
	std::cout << "Parameter:"
			  << "	M:" << M << "	U:" << U_C << std::endl;
}

void extend_sign(float **ndata, float **norm_ndata, float **nquery, float **ext_data, float **ext_query)
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
				ext_data[i][j] = 0.5 - pow(norm_ndata[i][0], 2 * (j - D + 1));
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
				ext_query[i][j] = 0.0;
			}
		}
	}
}

void hash_data_sign(float **ext_data, float **random_vector, float **hash_num_d, int k) //k hash num
{
	float data_inner_product;
	for (int i = 0; i < N; ++i) //each data
	{
		for (int p = 0; p < k; ++p) //each hash func
		{
			data_inner_product = dot(ext_data[i], random_vector[p], D + M);
			if (data_inner_product > 0)
			{
				hash_num_d[i][p] = 1;
			}
			else if (data_inner_product < 0)
			{
				hash_num_d[i][p] = -1;
			}
			else
			{
				hash_num_d[i][p] = 0;
			}
		}
	}
}

void hash_query_sign(float **ext_query, float **random_vector, float **hash_num_q, int k)
{
	float query_inner_product;
	for (int i = 0; i < QN; ++i) //each query
	{
		for (int p = 0; p < k; ++p) //each hash func
		{
			query_inner_product = dot(ext_query[i], random_vector[p], D + M);
			if (query_inner_product > 0)
			{
				hash_num_q[i][p] = 1;
			}
			else if (query_inner_product < 0)
			{
				hash_num_q[i][p] = -1;
			}
			else
			{
				hash_num_q[i][p] = 0;
			}
		}
	}
}
