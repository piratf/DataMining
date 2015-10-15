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

    /**
    * 获得矩阵的转置
    * @author piratf
    * @return 原矩阵的转置矩阵
    */
    Matrix getTransposition();

    int doInversion();
};

#endif