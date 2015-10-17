#include <cmath>
#include <iostream>
#include <vector>
#include "Matrix.h"
#include "Distance.h"

/**
 * 建立一个n行的空矩阵
 */
Matrix::Matrix(int _x) {
    std::vector< std::vector<double> > temp(_x);
    data = temp;
}

/**
 * 通过矩阵的行列数构造空矩阵
 */
Matrix::Matrix(int _x, int _y) {
    std::vector< std::vector<double> > temp(_x, std::vector<double>(_y));
    data = temp;
}

/**
 * 矩阵深拷贝构造函数，调用了vector的拷贝方法
 */
Matrix::Matrix(std::vector<std::vector<double> > dvec) {
    data = dvec;
}

/**
 * 获得矩阵的转置
 * @author piratf
 * @return 原矩阵的转置矩阵
 */
Matrix Matrix::getTransposition() {
    decltype(data.size()) sizeRow = data.size();
    if (sizeRow == 0) {
        std::cerr << "error** Matrix::getTransposition -> empty Matrix!" << std::endl;
    }
    decltype(data.size()) sizeCol = data[0].size();

    Matrix tran(sizeCol, sizeRow);
    for (int i = 0; i < sizeRow; ++i) {
        for (int j = 0; j < sizeCol; ++j) {
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
 * 获得两个样本的协方差矩阵
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
 * 获得样本矩阵的协方差矩阵
 * 参数矩阵中的各样本需按行排列
 * @author piratf
 * @return 一个新的协方差矩阵
 */
Matrix Matrix::getCovarianceMatrix(const std::vector< std::vector<double> > &input) {
    Matrix mat(input);
    mat = mat.getTransposition();
    using vecSizeT = decltype(mat.data.size());
    const vecSizeT sizeRow = mat.data.size();
    if (sizeRow == 0) {
        std::cerr << "error** Matrix::getCovarianceMatrix -> empty Matrix argument!" << std::endl;
        return Matrix();
    }
    const vecSizeT sizeCol = mat.data[0].size();
    std::vector<double> avgVec;
    // 对于每一行求其均值
    for (auto &row : mat.data) {
        avgVec.push_back(Distance::getAverageNum(row));
    }
    // 获得协方差矩阵参数
    Matrix temp(sizeRow, sizeCol);
    for (vecSizeT i = 0; i != sizeRow; ++i) {
        for (vecSizeT j = 0; j != sizeCol; ++j) {
            temp.data[i][j] = mat.data[i][j] - avgVec[i];
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
 * 矩阵的LU分解
 * 结果有误差，正在改进
 * @author piratf
 * @return vector<Matrix>，0是L矩阵，1是U矩阵, 如果出错返回空vector
 */
std::vector<Matrix> Matrix::luDecomposition() {
    if (data.size() == 0) {
        std::cerr << "error** Matrix::luDecomposition -> empty Matrix." << std::endl;
        return std::vector<Matrix>();
    }
    if (!isSquare()) {
        std::cerr << "error** Matrix::luDecomposition -> rows and columns not equal." << std::endl;
        return std::vector<Matrix>();
    }

    using vecSizeT = decltype(data.size());
    double tmp = 0;
    vecSizeT s = data.size();                //矩阵的阶数
    vecSizeT n = s * s;                //矩阵内总数据个数

    Matrix L(s, s);
    Matrix U(s, s);

    for (vecSizeT i = 0; i != s; i++) {
        for (vecSizeT j = 0; j != s; j++) {
            if (i == j)
                L.data[i][j] = 1;
            if (i < j)
                L.data[i][j] = 0;
            if (i > j)
                U.data[i][j] = 0;

            U.data[0][j] = data[0][j];
            L.data[i][0] = data[i][0] / U.data[0][0];
        }
    }

    for (vecSizeT k = 1; k != s; k++) {
        for (vecSizeT j = k; j != s; j++) {
            tmp = 0;
            for (vecSizeT m = 0; m < k; m++) {
                tmp += L.data[k][m] * U.data[m][j];
            }
            U.data[k][j] = data[k][j] - tmp;
        }
        for (vecSizeT i = k + 1; i != s; i++) {
            tmp = 0;
            for (vecSizeT m = 0; m != k; m++) {
                tmp += L.data[i][m] * U.data[m][k];
            }
            L.data[i][k] = ( data[i][k] - tmp ) / U.data[k][k];
        }
    }

    return std::vector<Matrix> {L, U};
}

/**
 * 获得矩阵位置(x, y)元素的余子式
 * @author piratf
 * @param  x 元素行坐标
 * @param  y 元素列坐标
 * @return   Matrix: 余子式
 */
Matrix Matrix::left(const unsigned x, const unsigned y) {
    std::cout << x << " : " << y << std::endl;
    using vecSizeT = decltype(data.size());
    vecSizeT rowSize = data.size();
    if (rowSize == 0) {
        return Matrix();
    }
    vecSizeT colSize = data[0].size();

    if ((x >= rowSize) || (y >= colSize)) {
        std::cerr << "error** Matrix::left -> input out of range." << std::endl;
        return Matrix();
    }

    Matrix leftMatrix(rowSize, colSize);
    bool testx = false;
    bool testy = false;
    for (vecSizeT i = 0; i != rowSize - 1; i++) {
        testy = 0;
        for (vecSizeT j = 0; j != colSize - 1; j++) {
            if (i == x)
                testx = true;
            if (j == y)
                testy = true;
            if ((!testx) && (!testy))
                leftMatrix.data[i][j] = data[i][j];
            else if (testx && (!testy))
                leftMatrix.data[i][j] = data[i + 1][j];
            else if ((!testx) && testy)
                leftMatrix.data[i][j] = data[i][j + 1];
            else
                leftMatrix.data[i][j] = data[i + 1][j + 1];
        }
    }
    return leftMatrix;
}

/**
 * 判断是否是空矩阵
 * @author piratf
 * @return 1 : 0 -> 空矩阵 : 不是空矩阵
 */
bool Matrix::empty() {
    return data.size();
}

/**
 * 判断矩阵是否是方阵
 * @author piratf
 * @return 1 : 0 -> 方阵 : 不是方阵
 */
bool Matrix::isSquare() {
    if (empty()) {
        return 0;
    }
    return data.size() == data[0].size();
}

/**
 * 求矩阵行列式
 * @author piratf
 * @return double: 行列式的值
 */
double Matrix::det() {
    // 通过LU分解求矩阵的行列式
    return 0;
}

/**
 * 判断当前矩阵是否是奇异矩阵
 * @author piratf
 * @return 1: 是奇异矩阵 0: 不是奇异矩阵
 */
bool Matrix::isSingular() {
    std::vector<Matrix> v = luDecomposition();
    return false;
    // return det() ? false : true;
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
            std::cerr << "error** Matrix::doInversion -> empty Matrix!" << std::endl;
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
    std::cout << "==================Print End==================" << std::endl << std::endl;;
}