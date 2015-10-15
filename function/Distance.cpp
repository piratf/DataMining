#include <iostream>
#include "Distance.h"

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

double Distance::getAverageNum(const std::vector<double> &dvec) {
    double sum = 0;
    for (double dn : dvec) {
        sum += dn;
    }
    return sum / dvec.size();
}

/**
 * 获取两个向量的马氏距离
 * @author piratf
 * @param  lhs 向量1
 * @param  rhs 向量2
 * @return     马氏距离的值 double
 */
double getMahalanobisDistance(const std::vector<double> &lhs, const std::vector<double> &rhs) {
    int lsize = lhs.size(), rsize = rhs.size();
    if (lsize != rsize) {
        std::cerr << "getMahalanobisDistance -> Argument have different size!" << std::endl;
        return -1;
    }
    // 获取两个向量的平均值
    double lavg = Distance::getAverageNum(lhs), ravg = Distance::getAverageNum(rhs);
    // 暂存协方差值, 协方差和
    double cov = 0, covSum = 0;
    Matrix mat(lsize, rsize);
    // 获得协方差矩阵
    int r = 0, l = 0;
    for (size_t i = 0; i < lhs.size(); ++i) {
        for (size_t j = 0; j < rhs.size(); ++j) {
            mat.data[i][j] = (lhs[i] - lavg) * (rhs[j] - ravg);
        }
    }
    // 获得矩阵的转置
    mat = mat.getTransposition();
    
    return 0;
}
