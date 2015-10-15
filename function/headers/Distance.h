#ifndef DISTANCE_H
#define DISTANCE_H

#include <iostream>
#include <vector>
#include "Node.h"
#include "Group.h"

/**
 * 一些计算距离的静态函数
 */
class Distance
{
public:
    /**
    * 欧氏距离平方
    * @author piratf
    * @param  lhs 左侧节点
    * @param  rhs 右侧节点
    * @return     欧氏距离平方
    */
    static double QuadraticEuclideanDistance(const Node& lhs, const Node& rhs);

    static double getAverageNum(const std::vector<double> &dvec);

    /**
     * 获取两个向量的马氏距离
     * @author piratf
     * @param  lhs 向量1
     * @param  rhs 向量2
     * @return     马氏距离的值 double
     */
    static double getMahalanobisDistance(const std::vector<double> &lhs, const std::vector<double> &rhs);
};

#endif