// author: air029
#include "util.h"

//calc
float uniform( // r.v. from Uniform(min, max)
	float min, // min value
	float max) // max value
{
	int num = rand();
	float base = (float)RAND_MAX - 1.0F;
	float frac = ((float)num) / base;

	return (max - min) * frac + min;
}

float gaussian(	 // r.v. from Gaussian(mean, sigma)
	float mean,	 // mean value
	float sigma) // std value
{
	float v1 = -1.0f;
	float v2 = -1.0f;
	float s = -1.0f;
	float x = -1.0f;

	do
	{
		v1 = 2.0F * uniform(0.0F, 1.0F) - 1.0F;
		v2 = 2.0F * uniform(0.0F, 1.0F) - 1.0F;
		s = v1 * v1 + v2 * v2;
	} while (s >= 1.0F);
	x = v1 * sqrt(-2.0F * log(s) / s);

	x = x * sigma + mean; // x is distributed from N(0, 1)
	return x;
}

float dot(float *a, float *b, int k)
{
	float sum = 0;
	for (int i = 0; i < k; ++i)
	{
		sum += a[i] * b[i];
	}
	return sum;
}

//--------------------------------------------------------------
int read_txt_data(int n, int d, const char *fname, float **data, float **norm_d)
{
	FILE *fp = fopen(fname, "r");
	if (!fp)
	{
		printf("Could not open %s\n", fname);
		return 1;
	}

	int i = 0;
	int j = 0;
	while (!feof(fp) && i < n)
	{
		float tmp = 0.0f;
		memset(norm_d[i], 0.0f, NORM_K * SIZEFLOAT);

		fscanf(fp, "%d", &j);
		for (j = 0; j < d; ++j)
		{
			fscanf(fp, " %f", &tmp);
			data[i][j] = tmp;

			norm_d[i][0] += tmp * tmp;
			for (int t = 1; t < NORM_K; ++t)
			{
				if (j < 8 * t)
					norm_d[i][t] += tmp * tmp;
			}
		}
		fscanf(fp, "\n");

		for (int t = 1; t < NORM_K; ++t)
		{
			norm_d[i][t] = sqrt(norm_d[i][0] - norm_d[i][t]);
		}
		norm_d[i][0] = sqrt(norm_d[i][0]);
		++i;
	}
	assert(feof(fp) && i == n);
	fclose(fp);

	return 0;
}

int read_ground_truth(int qn, const char *fname, Result **R)
{
	FILE *fp = fopen(fname, "r");
	if (!fp)
	{
		printf("Could not open %s\n", fname);
		return 1;
	}

	int tmp1 = -1;
	int tmp2 = -1;
	fscanf(fp, "%d %d\n", &tmp1, &tmp2);
	assert(tmp1 == qn && tmp2 == TOPK);

	for (int i = 0; i < qn; ++i)
	{
		for (int j = 0; j < TOPK; ++j)
		{
			fscanf(fp, "%d %f ", &R[i][j].id_, &R[i][j].key_);
		}
		fscanf(fp, "\n");
	}
	fclose(fp);

	return 0;
}

void display_origin_data(int n, int d, float **data, float **norm_d)
{
	std::cout << "DataNum: " << n << std::endl;
	std::cout << "DataDimension: " << d << std::endl;
	for (int i = 0; i < n; ++i)
	{
		std::cout << "norm" << i + 1 << ": " << norm_d[i][0] << "	data" << i + 1 << ": ";
		for (int j = 0; j < D; ++j)
		{
			std::cout << data[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void display_origin_query(int qn, int d, float **query, float **norm_q)
{

	std::cout << "QueryNum: " << qn << std::endl;
	std::cout << "QueryDimension: " << d << std::endl;
	for (int i = 0; i < qn; ++i)
	{
		std::cout << "norm" << i + 1 << ": " << norm_q[i][0] << "	query" << i + 1 << ": ";
		for (int j = 0; j < d; ++j)
		{
			std::cout << query[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void display_ground_truth(int qn, Result **R)
{
	for (int i = 0; i < QN; ++i)
	{
		//std::cout << "Index: " << result[i].index;
		for (int j = 0; j < TOPK; ++j)
		{
			std::cout << "Id: " << R[i][j].id_ << " Key: " << R[i][j].key_ << std::endl;
		}
		std::cout << std::endl;
	}
}

void display_ext(int type, float **ext_data, float **ext_query)
{
	assert(type == 1 || type == 2 || type == 3);
	if (type == 1 || type == 2)
	{
		std::cout << "ExtDataNum: " << N << std::endl;
		std::cout << "ExtDataDimension: " << D + M << std::endl;
		for (int i = 0; i < N; ++i)
		{
			//std::cout << "norm" << i+1 << ": " << norm_d[i][0] <<
			std::cout << "ext_data" << i + 1 << ": ";
			for (int j = 0; j < D + M; ++j)
			{
				std::cout << ext_data[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;

		std::cout << "ExtQueryNum: " << QN << std::endl;
		std::cout << "ExtQueryDimension: " << D + M << std::endl;
		for (int i = 0; i < QN; ++i)
		{
			//std::cout << "norm" << i+1 << ": " << norm_q[i][0] << "	ext_query" << i+1 << ": ";
			std::cout << "ext_query" << i + 1 << ": ";
			for (int j = 0; j < D + M; ++j)
			{
				std::cout << ext_query[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	else
	{
		std::cout << "ExtDataNum: " << N << std::endl;
		std::cout << "ExtDataDimension: " << D << std::endl;
		for (int i = 0; i < N; ++i)
		{
			//std::cout << "norm" << i+1 << ": " << norm_d[i][0] <<
			std::cout << "ext_data" << i + 1 << ": ";
			for (int j = 0; j < D; ++j)
			{
				std::cout << ext_data[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;

		std::cout << "ExtQueryNum: " << QN << std::endl;
		std::cout << "ExtQueryDimension: " << D << std::endl;
		for (int i = 0; i < QN; ++i)
		{
			//std::cout << "norm" << i+1 << ": " << norm_q[i][0] << "	ext_query" << i+1 << ": ";
			std::cout << "ext_query" << i + 1 << ": ";
			for (int j = 0; j < D; ++j)
			{
				std::cout << ext_query[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

float max_norm(float **norm_d, int n)
{
	float max_norm_ = 0;
	for (int i = 0; i < n; ++i)
	{
		if (max_norm_ < norm_d[i][0])
		{
			max_norm_ = norm_d[i][0];
		}
	}
	return max_norm_;
}

void normalize(float **data, float **norm_d, float **ndata, float **norm_ndata, float **query, float **norm_q, float **nquery, float **norm_nquery, float max_norm_d, int type)
{
	float U;
	if (type == 1)
	{
		U = U_E;
	}
	else if (type == 2)
	{
		U = U_C;
	}

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < D; ++j)
		{
			ndata[i][j] = (U / max_norm_d) * data[i][j];
		}
		norm_ndata[i][0] = (U / max_norm_d) * norm_d[i][0];
	}

	for (int i = 0; i < QN; ++i)
	{
		for (int j = 0; j < D; ++j)
		{
			nquery[i][j] = query[i][j] / norm_q[i][0];
		}
		norm_nquery[i][0] = 1;
	}
}

void create_random_vec(float **random_vector)
{
	//random_vector
	for (int i = 0; i < K_MAX; ++i)
	{
		for (int j = 0; j < D + M; ++j)
		{
			random_vector[i][j] = gaussian(0, 1);
		}
	}
}

void display_random_vec(float **random_vector)
{
	std::cout << "RandomVectorNum: " << K_MAX << std::endl;
	std::cout << "RandomVectorDimension: " << D + M << std::endl;
	for (int i = 0; i < K_MAX; ++i)
	{
		std::cout << "random_vector" << i + 1 << ": ";
		for (int j = 0; j < D + M; ++j)
		{
			std::cout << random_vector[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void create_uniform_num(float *uniform_num)
{
	//uniform_num
	for (int i = 0; i < K_MAX; ++i)
	{
		uniform_num[i] = uniform(0, R);
	}
}

void display_hash_num_d(float **hash_num_d, int k)
{
	for (int i = 0; i < N; ++i) //each data
	{
		std::cout << "index:" << i + 1 << ":";
		for (int p = 0; p < k; ++p) //each hash func
		{
			std::cout << hash_num_d[i][p] << " ";
		}
		std::cout << "\n";
	}
}

void display_hash_num_q(float **hash_num_q, int k)
{
	for (int i = 0; i < QN; ++i) //each data
	{
		std::cout << "index:" << i + 1 << ":";
		for (int p = 0; p < k; ++p) //each hash func
		{
			std::cout << hash_num_q[i][p] << " ";
		}
		std::cout << "\n";
	}
}

void display_POINT(POINT **point, int qn, int n)
{
	for (int i = 0; i < qn; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			std::cout << "ID:" << point[i][j].index << " KEY:" << point[i][j].value << " ";
		}
		std::cout << std::endl;
	}
}

void display_Result(Result **point, int qn, int n)
{
	for (int i = 0; i < qn; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			std::cout << "ID:" << point[i][j].id_ << " KEY:" << point[i][j].key_ << " ";
		}
		std::cout << std::endl;
	}
}

float m_recall(Result **result, POINT **candidate) //m hash num
{
	float recall = 0;
	for (int i = 0; i < QN; ++i)
	{
		for (int j = 0; j < TOPK; ++j)
		{
			if (result[i][j].id_ == candidate[i][j].index) //not accurate!!!!!!!!!!!!!!!!
			{
				recall++;
			}
		}
	}
	//std::cout << "RECALL:" << float(recall) / float(QN * TOPK) << "\n";
	return float(recall) / float(QN * TOPK);
}

void retrieve_recall(Result **result, POINT **candidate, int threshhold, const char *output)
{
	int temp_recall;
	bool true_item;
	int *retrieve_item = new int[threshhold];
	float *recall = new float[threshhold];
	//init
	for (int i = 0; i < threshhold; ++i)
	{
		retrieve_item[i] = i + 1;
		recall[i] = 0;
	}

	//calc
	for (int i = 0; i < QN; ++i) //for each query
	{
		temp_recall = 0;
		for (int j = 0; j < threshhold; ++j) //for each item
		{
			true_item = false;
			for (int p = 0; p < TOPK; ++p) //true item or not
			{
				if (result[i][p].id_ == candidate[i][j].index) //result num is topk
				{
					true_item = true;
				}
			}
			if (true_item) //refresh recall
			{
				temp_recall++;
			}
			recall[j] += temp_recall;
		}
	}

	//output
	std::ofstream Output(output);
	for (int i = 0; i < threshhold; ++i)
	{
		std::cout << "retrieve_item: " << retrieve_item[i] << "\trecall: " << recall[i] / QN / TOPK << "\n";
		Output << "retrieve_item: " << retrieve_item[i] << "\trecall: " << recall[i] / QN / TOPK << "\n";
	}

	//destruct
	delete[] retrieve_item;
	delete[] recall;
}

void indicator(int i)
{
	std::cout << "step" << i << "DONE\n--------------------------------------------------------------------\n";
}

void t(int i)
{
	time_t tt = time(NULL);
	tm *t = localtime(&tt);
	std::cout << "time" << i << ":	" << t->tm_year + 1900 << "-" << t->tm_mon + 1 << "-" << t->tm_mday << " "
			  << t->tm_hour << "-" << t->tm_min << "-" << t->tm_sec << " \n";
}

void candidate_reset(POINT **candidate, int qn, int n)
{
	for (int i = 0; i < qn; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			candidate[i][j].index = j + 1;
			candidate[i][j].value = 0;
		}
	}
}

void multimatches(float **hash_num_d, float **hash_num_q, POINT **candidate, int k, int begin, int end)
{
	for (int i = begin; i < end; ++i) //each data
	{
		for (int j = 0; j < N; ++j) //each query
		{
			for (int p = 0; p < k; ++p)
			{
				{
					if (hash_num_q[i][p] == hash_num_d[j][p])
					{
						candidate[i][j].value = candidate[i][j].value + 1;
					}
				}
			}
		}
	}
}

void matches(float **hash_num_d, float **hash_num_q, POINT **candidate, int k, int type) //k func num
{
	if (1 == type)
	{
		for (int i = 0; i < QN; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				for (int p = 0; p < k; ++p)
				{
					if (hash_num_q[i][p] == hash_num_d[j][p])
					{
						candidate[i][j].value = candidate[i][j].value + 1;
					}
				}
			}
		}
	}
	else if (2 == type)
	{

		int len = QN / THN;
		std::thread th0(multimatches, hash_num_d, hash_num_q, candidate, k, 0 * len, 1 * len);
		std::thread th1(multimatches, hash_num_d, hash_num_q, candidate, k, 1 * len, 2 * len);
		std::thread th2(multimatches, hash_num_d, hash_num_q, candidate, k, 2 * len, 3 * len);
		std::thread th3(multimatches, hash_num_d, hash_num_q, candidate, k, 3 * len, 4 * len);
		std::thread th4(multimatches, hash_num_d, hash_num_q, candidate, k, 4 * len, 5 * len);
		std::thread th5(multimatches, hash_num_d, hash_num_q, candidate, k, 5 * len, 6 * len);
		std::thread th6(multimatches, hash_num_d, hash_num_q, candidate, k, 6 * len, 7 * len);
		std::thread th7(multimatches, hash_num_d, hash_num_q, candidate, k, 7 * len, 8 * len);
		std::thread th8(multimatches, hash_num_d, hash_num_q, candidate, k, 8 * len, 9 * len);
		std::thread th9(multimatches, hash_num_d, hash_num_q, candidate, k, 9 * len, QN - 9 * len);

		th0.join();
		th1.join();
		th2.join();
		th3.join();
		th4.join();
		th5.join();
		th6.join();
		th7.join();
		th8.join();
		th9.join();
	}
}

void construct(float **ext_data, float **ext_query, float **ndata, float **norm_ndata, float **nquery, float **norm_nquery, float **hash_num_d, float **hash_num_q, POINT **candidate)
{
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
}

void destruct(float **ext_data, float **ext_query, float **ndata, float **norm_ndata, float **nquery, float **norm_nquery, float **hash_num_d, float **hash_num_q, POINT **candidate)
{
	//extdata
	for (int i = 0; i < N; ++i)
	{
		delete[] ext_data[i];
	}
	delete[] ext_data;

	//extquery
	ext_query = new float *[QN];
	for (int i = 0; i < QN; ++i)
	{
		delete[] ext_query[i];
	}
	delete[] ext_query;

	//normdata
	for (int i = 0; i < N; ++i)
	{
		delete[] ndata[i];
		delete[] norm_ndata[i];
	}
	delete[] ndata;
	delete[] norm_ndata;

	//normquery
	for (int i = 0; i < N; ++i)
	{
		delete[] nquery[i];
		delete[] norm_nquery[i];
	}
	delete[] nquery;
	delete[] norm_nquery;

	//hash num
	//hash_num_d
	for (int i = 0; i < N; ++i)
	{
		delete[] hash_num_d;
	}
	delete hash_num_d;

	//hash_num_q
	hash_num_q = new float *[QN];
	for (int i = 0; i < QN; ++i)
	{
		delete[] hash_num_q;
	}
	delete hash_num_q;

	//candidate
	for (int i = 0; i < QN; ++i)
	{
		delete[] candidate[i];
	}
	delete[] candidate;
}

void reset(float **ext_data, float **ext_query, float **ndata, float **norm_ndata, float **nquery, float **norm_nquery, float **hash_num_d, float **hash_num_q, POINT **candidate)
{
	//extdata
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < D + M; ++j)
		{
			ext_data[i][j] = 0;
		}
	}
	//extquery
	for (int i = 0; i < QN; ++i)
	{
		for (int j = 0; j < D + M; ++j)
		{
			ext_query[i][j] = 0;
		}
	}

	//normdata
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < D; ++j)
		{
			ndata[i][j] = 0;
		}
		for (int j = 0; j < NORM_K; ++j)
		{
			norm_ndata[i][j] = 0;
		}
	}

	//normquery

	for (int i = 0; i < QN; ++i)
	{
		for (int j = 0; j < D; ++j)
		{
			nquery[i][j] = 0;
		}
		for (int j = 0; j < NORM_K; ++j)
		{
			norm_nquery[i][j] = 0;
		}
	}
	//hash num
	//hash_num_d
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < K_MAX; ++j)
		{
			hash_num_d[i][j] = 0;
		}
	}
	//hash_num_q
	for (int i = 0; i < QN; ++i)
	{
		for (int j = 0; j < K_MAX; ++j)
		{
			hash_num_q[i][j] = 0;
		}
	}

	//candidate
	for (int i = 0; i < QN; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			candidate[i][j].index = j + 1;
			candidate[i][j].value = 0;
		}
	}
}

void loginfo(const char *filename, const char* type, int round, int max_round)
{
    std::fstream log;
    log.open(filename, std::fstream::app);
    time_t now = time(0);
    char *dt = ctime(&now);
    log << "Date and Time：" << dt << "---";
    log << "Type:" << type << "\tRound:" << round << "\tTotal Round:" << max_round << std::endl;
    log.close();
}
