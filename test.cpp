#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    double a[] = {   4,  2,  -2,
                     2,  2,  -3,
                    -2, -3,  14 };

    double *L = NULL;
    double *U = NULL;
    double tmp=0;
    int n;                //矩阵内总数据个数
    int s;                //矩阵的阶数
    
    n = sizeof(a)/sizeof(double);
    s = sqrtl(n);

    L = new double[n];
    U = new double[n];

    for (int i = 0; i < s; i++)
    {
        for (int j = 0; j < s; j++)
        {
            if (i == j)
                L[i*s+j] = 1;
            if (i < j)
                L[i*s+j] = 0;
            if (i > j)
                U[i*s+j] = 0;

            U[0*s+j] = a[0*s+j];
            L[i*s+0] = a[i*s+0] / U[0*s+0];
        }
    }

    for (int k = 1; k < s; k++)
    {

        for (int j = k; j < s; j++)
        {
            tmp = 0;
            for (int m = 0; m < k; m++)
            {
                tmp += L[k*s+m] * U[m*s+j];
            }

            U[k*s+j] = a[k*s+j] - tmp;
        }

        for (int i = k+1; i < s; i++)
        {
            tmp = 0;
            for (int m = 0; m < k; m++)
            {
                tmp += L[i*s+m] * U[m*s+k];
            }

            L[i*s+k] = ( a[i*s+k] - tmp ) / U[k*s+k];
        }

    }

    // printf("%d %d\n", s, n);

    for (int i = 0; i < n; ++i) {
        printf("%lf ", L[i]);
        if ((i + 1) % s == 0) {
            printf("\n");
        }
    }

    for (int i = 0; i < n; ++i) {
        printf("%lf ", U[i]);
        if ((i + 1) % s == 0) {
            printf("\n");
        }
    }
    //这里就得到L和U矩阵的值了

    delete [] L;
    delete [] U;
    system("pause");
    return 0;
}