#include <iostream>
#include "Distance.h"
#include "Matrix.h"

/**
* 欧氏距离平方
* @author piratf
* @param  lhs 左侧节点
* @param  rhs 右侧节点
* @return     欧氏距离平方
*/
double Distance::QuadraticEuclideanDistance(const Node& lhs, const Node& rhs) {
    if (lhs.attribute.size() != rhs.attribute.size()) {
        fprintf(stderr, "%d : %d\n", lhs.attribute.size(), rhs.attribute.size());
        fprintf(stderr, "Different kind of Nodes\n");
        return -1;
    }
    double quadraticSum = 0;
    for (unsigned i = 0; i < lhs.attribute.size(); ++i) {
        quadraticSum += (lhs.attribute[i] - rhs.attribute[i]) * (lhs.attribute[i] - rhs.attribute[i]);
    }
    return quadraticSum;
}

/**
 * 获得向量的平均值
 * @author piratf
 * @param  dvec 参数向量
 * @return      double: 向量平均值
 */
double Distance::getAverageNum(const std::vector<double> &dvec) {
    double sum = 0;
    for (double dn : dvec) {
        sum += dn;
    }
    return sum / dvec.size();
}

/**
 * 获取两个样本的马氏距离
 * @author piratf
 * @param  lhs 向量1
 * @param  rhs 向量2
 * @return     马氏距离的值 double
 */
double Distance::getMahalanobisDistance(const std::vector<double> &lhs, const std::vector<double> &rhs) {
    int lsize = lhs.size(), rsize = rhs.size();
    if (lsize != rsize) {
        std::cerr << "getMahalanobisDistance -> Argument have different size!" << std::endl;
        return -1;
    }
    // 获取两向量的协方差矩阵
    Matrix mat = Matrix::getCovarianceMatrix(std::vector<std::vector<double> > {lhs, rhs});
    if (mat.isSingular()) {
        std::cout << "warning* Distance::getMahalanobisDistance -> The Matrix is Singular, Now will return QuadraticEuclideanDistance" << std::endl;
        return 0;
    }
    // 获得协方差矩阵的转置
    mat.doInversion();
    mat.printData();

    // 获得两向量的差
    Matrix diff(1);
    for (decltype(lhs.size()) i = 0; i != lhs.size(); ++i) {
        diff.data[0].push_back(lhs[i] - rhs[i]);
    }
    diff.printData();

    diff.getTransposition().printData();

    // 本来是需要转置才能用矩阵乘法
    // 这里直接将两个向量的各值相乘，见谅
    double product = 0.0;
    for (decltype(lhs.size()) i = 0; i != lhs.size(); ++i) {
        product += lhs[i] * rhs[i];
    }

    return 0;
}
