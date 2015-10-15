#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
public:
    std::vector< std::vector<double> > data;

    Matrix();

    Matrix(int _x, int _y) {
        std::vector< std::vector<double> > temp(_x, std::vector<double>(_y));
        data = temp;
    }

    Matrix(std::vector<std::vector<double> > dvec) {
        data = dvec;
    }

    /**
    * 静态函数：获取两个向量的点乘结果
    * @author piratf
    * @param  lhs 向量1
    * @param  rhs 向量2
    * @return     double:点乘的结果
    */
    static double vectorDotProduct(const std::vector<double> lhs, std::vector<double> rhs);

    /**
    * 获得两个向量的协方差矩阵
    * @author piratf
    * @return 一个新的协方差矩阵
    */
    static Matrix getCovarianceMatrixOfTwoVector(const std::vector<double> &lhs, const std::vector<double> &rhs);

    /**
    * 获得矩阵的转置
    * @author piratf
    * @return 原矩阵的转置矩阵
    */
    Matrix getTransposition();

    int doInversion();

    void printData();
};

#endif