#include <cmath>
#include <iostream>
#include <vector>
#include "Matrix.h"
#include "Distance.h"

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
 * 静态函数：获取两个向量的点乘结果
 * @author piratf
 * @param  lhs 向量1
 * @param  rhs 向量2
 * @return     double:点乘的结果
 */
double Matrix::vectorDotProduct(const std::vector<double> lhs, std::vector<double> rhs) {
    double ans = 0;
    for (decltype(lhs.size()) i = 0; i != lhs.size(); ++i) {
        ans += lhs[i] * rhs[i];
    }
    return ans;
}

/**
 * 获得两个向量的协方差矩阵
 * @author piratf
 * @return 一个新的协方差矩阵
 */
Matrix Matrix::getCovarianceMatrixOfTwoVector(const std::vector<double> &lhs, const std::vector<double> &rhs) {
    const auto lsize = lhs.size();
    double lavg = Distance::getAverageNum(lhs), ravg = Distance::getAverageNum(rhs);
    Matrix mat(2, 2);
    // 获得协方差矩阵参数
    std::vector<double> vl, vr;
    for (double dValue : lhs) {
        vl.push_back(dValue - lavg);
    }
    for (double dValue : rhs) {
        vr.push_back(dValue - ravg);
    }
    // 获得协方差矩阵
    mat.data[0][0] = Matrix::vectorDotProduct(vl, vl) / (lsize - 1);
    mat.data[0][1] = Matrix::vectorDotProduct(vl, vr) / (lsize - 1);
    mat.data[1][0] = Matrix::vectorDotProduct(vr, vl) / (lsize - 1);
    mat.data[1][1] = Matrix::vectorDotProduct(vr, vr) / (lsize - 1);
    return mat;
}

/**
 * 获得一个矩阵的协方差矩阵
 * 参数矩阵中的各向量需按行排列
 * @author piratf
 * @return 一个新的协方差矩阵
 */
Matrix Matrix::getCovarianceMatrix(const std::vector< std::vector<double> > &mat) {
    using vecSizeT = decltype(mat.size());
    const vecSizeT sizeRow = mat.size();
    if (sizeRow == 0) {
        std::cerr << "getCovarianceMatrix -> empty Matrix argument!" << std::endl;
        return Matrix();
    }
    const vecSizeT sizeCol = mat[0].size();
    std::vector<double> avgVec;
    // 对于每一行求其均值
    for (auto &row : mat) {
        avgVec.push_back(Distance::getAverageNum(row));
    }
    // 获得协方差矩阵参数
    Matrix temp(sizeRow, sizeCol);
    for (vecSizeT i = 0; i != sizeRow; ++i) {
        for (vecSizeT j = 0; j != sizeCol; ++j) {
            temp.data[i][j] = mat[i][j] - avgVec[i];
        }
    }
    // 获得协方差矩阵
    Matrix cov(sizeRow, sizeRow);
    for (vecSizeT i = 0; i != sizeRow; ++i) {
        for (vecSizeT j = 0; j != sizeRow; ++j) {
            cov.data[i][j] = Matrix::vectorDotProduct(temp.data[i], temp.data[j]) / (sizeCol - 1);
        }
    }
    return cov;
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
    for ( k = 0; k != len; k++) {
        dMinValue = 0.0;
        for (i = k; i != len; i++) {
            for (j = k; j != len; j++) {
                // printf("i = %d, j = %d, data = %lf\n", i, j, data[i][j]);
                p = fabs(data[i][j]);
                // printf("p = %lf\n", p);
                if (p > dMinValue) {
                    dMinValue = p; is[k] = i; js[k] = j;
                }
            }
        }
        if ( dMinValue - 0.0 < 1e-8 ) {
            std::cerr << "err**not inv" << std::endl;
            return -1;
        }
        if (is[k] != k) {
            for (j = 0; j != len; j++) {
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
        for (j = 0; j != len; j++) {
            if (j != k) {
                data[k][j] *= data[k][k];
            }
        }
        for (i = 0; i != len; i++) {
            if (i != k) {
                for (j = 0; j != len; j++) {
                    if (j != k) {
                        data[i][j] -= data[i][k] * data[k][j];
                    }
                }
            }
        }
        // printData();
        for (i = 0; i != len; i++) {
            if (i != k) {
                data[i][k] = -data[i][k] * data[k][k];
            }
        }
    }
    for ( k = len - 1; k != -1; k--) {
        if (js[k] != k) {
            for (j = 0; j <= len - 1; j++) {
                p = data[k][j];
                data[k][j] = data[js[k]][j];
                data[js[k]][j] = p;
            }
        }
        if (is[k] != k) {
            for (i = 0; i != len; i++) {
                p = data[i][k];
                data[i][k] = data[i][is[k]];
                data[i][is[k]] = p;
            }
        }
    }
    return 0;
}

/**
 * 输出矩阵的内容
 * @author piratf
 */
void Matrix::printData() {
    std::cout << "===========Printing data of Matrix===========" << std::endl;
    for (auto &row : data) {
        for (double dValue : row) {
            printf("%+.8lf ", dValue);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "==================Print End==================" << std::endl;
}