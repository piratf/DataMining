#include <cmath>
#include <iostream>
#include <vector>
#include "Matrix.h"

/**
 * 获得矩阵的转置
 * @author piratf
 * @return 原矩阵的转置矩阵
 */
Matrix Matrix::getTransposition() {
    Matrix tran(data[0].size(), data.size());
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data.size(); ++j) {
            tran.data[j][i] = data[i][j];
        }
    }
    return tran;
}

/**
 * 将矩阵的内容变成矩阵的逆
 * @author piratf
 * @param  data 二位数据集
 * @param  len 数据集的边长
 * @return   [description]
 */
int Matrix::doInversion()
{
    // double *is = new double[len];
    // double *js = new double[len];
    auto len = data.size();
    std::vector<double> is(len);
    std::vector<double> js(len);
    int i, j, k;
    double dMinValue, p;
    for ( k = 0; k < len; k++) {
        dMinValue = 0.0;
        for (i = k; i <= len - 1; i++) {
            for (j = k; j <= len - 1; j++) {
                p = fabs(data[i][j]);
                if (p > dMinValue) {
                    dMinValue = p; is[k] = i; js[k] = j;
                }
            }
        }
        if ( 0.0 == dMinValue ) {
            std::cerr << "err**not inv" << std::endl;
            return -1;
        }
        if (is[k] != k) {
            for (j = 0; j <= len - 1; j++) {
                p = data[k][j];
                data[k][j] = data[is[k]][j];
                data[is[k]][j] = p;
            }
        }
        if (js[k] != k) {
            for (i = 0; i <= len - 1; i++) {
                p = data[i][k];
                data[i][k] = data[i][js[k]];
                data[i][js[k]] = p;
            }
        }
        data[k][k] = 1.0 / data[k][k];
        for (j = 0; j <= len - 1; j++) {
            if (j != k) {
                data[k][j] *= data[k][k];
            }
        }
        for (i = 0; i <= len - 1; i++) {
            if (i != k) {
                for (j = 0; j <= len - 1; j++) {
                    if (j != k) {
                        data[i][j] -= data[i][k] * data[k][j];
                    }
                }
            }
        }
        for (i = 0; i <= len - 1; i++) {
            if (i != k) {
                data[i][k] = -data[i][k] * data[k][k];
            }
        }
    }
    for ( k = len - 1; k >= 0; k--) {
        if (js[k] != k) {
            for (j = 0; j <= len - 1; j++) {
                p = data[k][j];
                data[k][j] = data[js[k]][j];
                data[js[k]][j] = p;
            }
        }
        if (is[k] != k) {
            for (i = 0; i <= len - 1; i++) {
                p = data[i][k];
                data[i][k] = data[i][is[k]];
                data[i][is[k]] = p;
            }
        }
    }
    return 0;
}