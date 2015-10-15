#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
public:
    std::vector< std::vector<double> > data;

    /** 默认构造函数，0x0空矩阵 */
    Matrix() {

    }

    /**
     * 建立一个n行的空矩阵
     */
    Matrix(int _x);

    /**
     * 通过矩阵的行列数构造空矩阵
     */
    Matrix(int _x, int _y);

    /**
     * 矩阵深拷贝构造函数，调用了vector的拷贝方法
     */
    Matrix(std::vector<std::vector<double> > dvec);

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
     * 获得一个矩阵的协方差矩阵
     * @author piratf
     * @return 一个新的协方差矩阵
     */
    static Matrix getCovarianceMatrix(const std::vector< std::vector<double> > &input);

    /**
     * 判断是否是空矩阵
     * @author piratf
     * @return 1 : 0 -> 空矩阵 : 不是空矩阵
     */
    bool empty();

    /**
     * 判断矩阵是否是方阵
     * @author piratf
     * @return 1 : 0 -> 方阵 : 不是方阵
     */
    bool isSquare();

    /**
     * 获得矩阵位置(x, y)元素的余子式
     * @author piratf
     * @param  x 元素行坐标
     * @param  y 元素列坐标
     * @return   Matrix: 余子式
     */
    Matrix left(const unsigned x, const unsigned y);

    /**
     * 求矩阵行列式
     * @author piratf
     * @return double: 行列式的值
     */
    double det();

    /**
     * 判断当前矩阵是否是奇异矩阵
     * @author piratf
     * @return 1: 是奇异矩阵 0: 不是奇异矩阵
     */
    bool isSingular();

    /**
     * 矩阵的LU分解
     * @author piratf
     * @return vector<Matrix>，0是L矩阵，1是U矩阵, 如果出错返回空vector
     */
    std::vector<Matrix> luDecomposition();

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