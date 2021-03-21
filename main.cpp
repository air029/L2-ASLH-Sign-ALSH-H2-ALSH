// author: air029
//main.cpp

#include <iostream>
#include <fstream>
#include "def.h"
#include "util.h"
#include "l2_alsh.h"
#include "sign_alsh.h"
#include "h2_alsh.h"
#include "mip.h"

float **data = NULL;   // data objects
float **query = NULL;  // query objects
float **norm_d = NULL; // l2-norm of data  objects
float **norm_q = NULL; // l2-norm of query objects
float **ndata = NULL;
float **nquery = NULL;
float **norm_ndata = NULL;
float **norm_nquery = NULL;
float **ext_data = NULL;	  // data objects
float **ext_query = NULL;	  // query objects
float **ext_norm_d = NULL;	  // l2-norm of data  objects
float **ext_norm_q = NULL;	  // l2-norm of query objects
float **hash_num_d = NULL;	  // l2-norm of data  objects
float **hash_num_q = NULL;	  // l2-norm of query objects
float **random_vector = NULL; // ramdom vector
float *uniform_num = NULL;
POINT **candidate = NULL;
Result **result = NULL; // truth set

const char *data_set = "data/Netflix_b.ds";
const char *query_set = "data/Netflix.q";
const char *truth_set = "data/Netflix_b.mip"; // address of ground truth file
const char *output = "result.txt";
const char *logfile = "log.txt";
const bool test = false;

int main()
{
	//output
	std::ofstream Output(output);

	//data
	data = new float *[N];
	norm_d = new float *[N];
	for (int i = 0; i < N; ++i)
	{
		data[i] = new float[D];
		norm_d[i] = new float[NORM_K];
	}
	//query
	query = new float *[QN];
	norm_q = new float *[QN];
	for (int i = 0; i < QN; ++i)
	{
		query[i] = new float[D];
		norm_q[i] = new float[NORM_K];
	}

	int qn = QN;
	//result
	result = new Result *[qn];
	for (int i = 0; i < qn; ++i)
	{
		result[i] = new Result[TOPK];
	}

	//random vec
	random_vector = new float *[K_MAX];
	for (int i = 0; i < K_MAX; ++i)
	{
		random_vector[i] = new float[D + M];
	}

	//uniform num
	uniform_num = new float[K_MAX];

	create_random_vec(random_vector);
	//display_random_vec(random_vector);

	create_uniform_num(uniform_num);

	//---------------------------------------------

	//------------------------------------------------------------
	//extdata
	ext_data = new float *[N];
	for (int i = 0; i < N; ++i)
	{
		ext_data[i] = new float[D + M];
	}
	//extquery
	ext_query = new float *[QN];
	for (int i = 0; i < QN; ++i)
	{
		ext_query[i] = new float[D + M];
	}

	//normdata
	ndata = new float *[N];
	norm_ndata = new float *[N];
	for (int i = 0; i < N; ++i)
	{
		ndata[i] = new float[D];
		norm_ndata[i] = new float[NORM_K];
	}

	//normquery
	nquery = new float *[QN];
	norm_nquery = new float *[QN];
	for (int i = 0; i < QN; ++i)
	{
		nquery[i] = new float[D];
		norm_nquery[i] = new float[NORM_K];
	}

	//hash num
	//hash_num_d
	hash_num_d = new float *[N];
	for (int i = 0; i < N; ++i)
	{
		hash_num_d[i] = new float[K_MAX];
	}

	//hash_num_q
	hash_num_q = new float *[QN];
	for (int i = 0; i < QN; ++i)
	{
		hash_num_q[i] = new float[K_MAX];
	}

	//candidate
	candidate = new POINT *[QN];
	for (int i = 0; i < QN; ++i)
	{
		candidate[i] = new POINT[N];
	}

	for (int i = 0; i < QN; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			candidate[i][j].index = j + 1;
			candidate[i][j].value = 0;
		}
	}

	//------------------------------------------------------------

	//----------------------------begin---------------------------------------
	read_txt_data(N, D, data_set, data, norm_d);
	read_txt_data(QN, D, query_set, query, norm_q);
	read_ground_truth(QN, truth_set, result);

	if (true == test)
	{
		return 0;
	}
	else
	{
	}

	//display_origin_data(N, D, data, norm_d);
	//display_origin_query(QN, D, query, norm_q);
	//display_ground_truth(QN, result);

	float max_norm_d = max_norm(norm_d, N);
	float max_norm_q = max_norm(norm_q, QN);

	//---------------------h2 alsh------------------------------------

	info_h();
	Output << "-------------------------------------h2alsh--------------------------------------------\n";
	//normalize
	normalize(data, norm_d, ndata, norm_ndata, query, norm_q, nquery, norm_nquery, max_norm_d, 1);

	extend_h2(ndata, norm_ndata, nquery, norm_nquery, ext_data, ext_query, U_E);
	//display_ext(2, ext_data, ext_query);

	hash_data_h2(ext_data, random_vector, uniform_num, hash_num_d, K_MAX);
	hash_query_h2(ext_query, random_vector, uniform_num, hash_num_q, K_MAX);

	//display_hash_num_d(hash_num_d,K_MAX);
	//display_hash_num_q(hash_num_q,K_MAX);

	for (int i = 0; i < K_ROUND; ++i)
	{
		matches(hash_num_d, hash_num_q, candidate, K[i], 2); //k func num
		p_sort(candidate, 2);
		//---------------------K-RECALL----------------------
		//std::cout << "K:" << K[i] << "\t";
		//Output << "K:" << K[i] << "\t";
		//std::cout << "RECALL:" << m_recall(result, candidate) << "\n";
		//Output << "RECALL:" << m_recall(result, candidate) << "\n";
		//---------------------K-RECALL----------------------

		//---------------------RETRIEVE-RECALL----------------------
		std::cout << "K:" << K[i] << "\n";
		Output << "K:" << K[i] << "\n";
		retrieve_recall(result, candidate, RETRIEVEK, output);
		//---------------------RETRIEVE-RECALL----------------------
		candidate_reset(candidate, QN, N);
		loginfo(logfile, "H2", i+1, K_ROUND);
	}

	reset(ext_data, ext_query, ndata, norm_ndata, nquery, norm_nquery, hash_num_d, hash_num_q, candidate);
	//---------------------l2 alsh------------------------------------

	info_l();
	Output << "-------------------------------------l2alsh--------------------------------------------\n";
	normalize(data, norm_d, ndata, norm_ndata, query, norm_q, nquery, norm_nquery, max_norm_d, 1);
	extend_l2(ndata, norm_ndata, nquery, ext_data, ext_query);
	hash_data_l2(ext_data, random_vector, uniform_num, hash_num_d, K_MAX);
	hash_query_l2(ext_query, random_vector, uniform_num, hash_num_q, K_MAX);
	for (int i = 0; i < K_ROUND; ++i)
	{
		matches(hash_num_d, hash_num_q, candidate, K[i], 2); //k func num
		p_sort(candidate, 2);
		//---------------------K-RECALL----------------------
		//std::cout << "K:" << K[i] << "\t";
		//Output << "K:" << K[i] << "\t";
		//std::cout << "RECALL:" << m_recall(result, candidate) << "\n";
		//Output << "RECALL:" << m_recall(result, candidate) << "\n";
		//---------------------K-RECALL----------------------

		//---------------------RETRIEVE-RECALL----------------------
		std::cout << "K:" << K[i] << "\n";
		Output << "K:" << K[i] << "\n";
		retrieve_recall(result, candidate, RETRIEVEK, output);
		//---------------------RETRIEVE-RECALL----------------------
		candidate_reset(candidate, QN, N);
		loginfo(logfile, "L2", i+1, K_ROUND);
	}

	reset(ext_data, ext_query, ndata, norm_ndata, nquery, norm_nquery, hash_num_d, hash_num_q, candidate);

	//---------------------sign alsh------------------------------------

	info_s();
	Output << "-------------------------------------signalsh--------------------------------------------\n";
	normalize(data, norm_d, ndata, norm_ndata, query, norm_q, nquery, norm_nquery, max_norm_d, 2);

	extend_sign(ndata, norm_ndata, nquery, ext_data, ext_query);

	hash_data_sign(ext_data, random_vector, hash_num_d, K_MAX);
	hash_query_sign(ext_query, random_vector, hash_num_q, K_MAX);

	for (int i = 0; i < K_ROUND; ++i)
	{
		matches(hash_num_d, hash_num_q, candidate, K[i], 2); //k func num
		p_sort(candidate, 2);

		//---------------------K-RECALL----------------------
		//std::cout << "K:" << K[i] << "\t";
		//Output << "K:" << K[i] << "\t";
		//std::cout << "RECALL:" << m_recall(result, candidate) << "\n";
		//Output << "RECALL:" << m_recall(result, candidate) << "\n";
		//---------------------K-RECALL----------------------

		//---------------------RETRIEVE-RECALL----------------------
		std::cout << "K:" << K[i] << "\n";
		Output << "K:" << K[i] << "\n";
		retrieve_recall(result, candidate, RETRIEVEK, output);
		//---------------------RETRIEVE-RECALL----------------------
		candidate_reset(candidate, QN, N);
		loginfo(logfile, "Sign", i+1, K_ROUND);
	}

	reset(ext_data, ext_query, ndata, norm_ndata, nquery, norm_nquery, hash_num_d, hash_num_q, candidate);

	Output.close();
	std::cout << "-------------------------------------------------DONE-----------------------------------------------\n";

	//display_Result(result, QN, TOPK);
	//display_POINT(candidate, QN, N);
	//display_POINT(candidate, QN, N);

	//for each hashfunction
	//data query extdata extquery normdata normquery hash_data hash_query

	//for each method
	//data query
	//change:extdata extquery normdata normquery hash_data hash_query
	return 0;
}
