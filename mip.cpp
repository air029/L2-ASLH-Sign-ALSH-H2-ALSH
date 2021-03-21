// author: air029
#include "mip.h"

void multibubble(POINT *point, int length, int topk, int type, int begin, int end)
{
    POINT temp;
    for (int i = 0; i < topk; ++i)
    {
        for (int j = length - 1; j > 0; --j)
        {
            if (point[j].value > point[j - 1].value)
            {
                temp = point[j];
                point[j] = point[j - 1];
                point[j - 1] = temp;
            }
        }
    }
}

void bubble(POINT *point, int length, int topk)
{
    POINT temp;
    for (int i = 0; i < topk; ++i)
    {
        for (int j = length - 1; j > 0; --j)
        {
            if (point[j].value > point[j - 1].value)
            {
                temp = point[j];
                point[j] = point[j - 1];
                point[j - 1] = temp;
            }
        }
    }
}

void multisort(POINT **candidate, int begin, int end)
{
    for (int i = begin; i < end; ++i)
    {
        bubble(candidate[i], N, RETRIEVEK);
    }
}

void sort(POINT **candidate, int type)
{
    if (1 == type)
    {
        for (int i = 0; i < QN; ++i)
        {
            bubble(candidate[i], N, RETRIEVEK);
        }
    }
    else if (2 == type)
    {

        int len = QN / THN;
        std::thread th10(multisort, candidate, 0 * len, 1 * len);
        std::thread th11(multisort, candidate, 1 * len, 2 * len);
        std::thread th12(multisort, candidate, 2 * len, 3 * len);
        std::thread th13(multisort, candidate, 3 * len, 4 * len);
        std::thread th14(multisort, candidate, 4 * len, 5 * len);
        std::thread th15(multisort, candidate, 5 * len, 6 * len);
        std::thread th16(multisort, candidate, 6 * len, 7 * len);
        std::thread th17(multisort, candidate, 7 * len, 8 * len);
        std::thread th18(multisort, candidate, 8 * len, 9 * len);
        std::thread th19(multisort, candidate, 9 * len, QN - 9 * len);

        th10.join();
        th11.join();
        th12.join();
        th13.join();
        th14.join();
        th15.join();
        th16.join();
        th17.join();
        th18.join();
        th19.join();
    }
}

//try sort in a new version by using priority queue

void p_sort(POINT **candidate, int type)
{
    if (1 == type)
    {
        for (int i = 0; i < QN; ++i)
        {
            p_bubble(candidate[i], N, RETRIEVEK);
        }
    }
    else if (2 == type)
    {

        int len = QN / THN;
        std::thread th10(p_multisort, candidate, 0 * len, 1 * len);
        std::thread th11(p_multisort, candidate, 1 * len, 2 * len);
        std::thread th12(p_multisort, candidate, 2 * len, 3 * len);
        std::thread th13(p_multisort, candidate, 3 * len, 4 * len);
        std::thread th14(p_multisort, candidate, 4 * len, 5 * len);
        std::thread th15(p_multisort, candidate, 5 * len, 6 * len);
        std::thread th16(p_multisort, candidate, 6 * len, 7 * len);
        std::thread th17(p_multisort, candidate, 7 * len, 8 * len);
        std::thread th18(p_multisort, candidate, 8 * len, 9 * len);
        std::thread th19(p_multisort, candidate, 9 * len, QN - 9 * len);

        th10.join();
        th11.join();
        th12.join();
        th13.join();
        th14.join();
        th15.join();
        th16.join();
        th17.join();
        th18.join();
        th19.join();
    }
}

void p_multisort(POINT **candidate, int begin, int end)
{
    for (int i = begin; i < end; ++i)
    {
        p_bubble(candidate[i], N, RETRIEVEK);
    }
}

void p_bubble(POINT *point, int length, int topk)
{
    //priority_queue<int, vector<int>, greater<int> > q;
    std::priority_queue<POINT> p;
    for (int i = 0; i < topk; ++i)
    {
        p.push(point[i]);
    }
    for (int i = topk; i < length; ++i)
    {
        if (point[i].value > p.top().value)
        {
            p.pop();
            p.push(point[i]);
        }
    }
    for (int i = topk-1; i >= 0; --i)
    {
        point[i] = p.top();
        p.pop();
    }
    
}


void mip(float **data, int dnum, float **query, int qnum, int topk, const char *outpath)
{
    POINT **point = new POINT *[QN];
    for (int i = 0; i < QN; ++i)
    {
        point[i] = new POINT[N];
    }

    //product
    for (int i = 0; i < QN; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            point[i][j].index = j + 1;
            point[i][j].value = dot(query[i], data[j], D);
        }
    }

    for (int i = 0; i < QN; ++i)
    {
        bubble(point[i], N, TOPK);
    }

    std::ofstream Outmip(outpath);
    Outmip << QN << " " << TOPK << std::endl;
    for (int i = 0; i < QN; ++i)
    {
        for (int j = 0; j < TOPK; ++j)
        {
            Outmip << point[i][j].index << " " << point[i][j].value << " ";
        }
        Outmip << std::endl;
    }
    Outmip.close();
}
