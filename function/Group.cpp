#include <iostream>
#include <algorithm>
#include <vector>
#include "Group.h"

/**
 * 重新计算簇的中心位置
 * @author piratf
 */
void Group::reCalCenter() {
    unsigned len = center.attribute.size();
    unsigned nlen = nodes.size();    // 簇中节点的个数
    for (unsigned i = 0; i < len; ++i) {
        double sum = 0;
        for (unsigned j = 0; j < nlen; ++j) {
            sum += nodes[j].attribute[i];
        }
        center.attribute[i] = sum / (double)nlen;
    }
}

/**
 * 判断簇中是否已经存在当前id
 * @author piratf
 * @param  _id [description]
 * @return     [description]
 */
bool Group::idConflict(unsigned _id) {
    unsigned len = nodes.size();
    for (unsigned i = 0; i < len; ++i) {
        if (nodes[i].id == _id) {
            return true;
        }
    }
    return false;
}

/**
 * 获取当前簇的欧氏距离平方和
 * @author piratf
 * @return 当前簇的欧氏距离平方和
 */
double Group::getSumOfEuclideanDistance() {
    double sum = 0.0;
    unsigned len = nodes.size();
    for (unsigned i = 0; i < len; ++i) {
        sum += Distance::QuadraticEuclideanDistance(nodes[i], center);
    }
    return sum;
}

/**
 * 获取当前簇的欧氏距离平方最大值
 * @author piratf
 * @return 当前簇的欧氏距离平方最大值
 */
double Group::getMaxOfEuclideanDistance() {
    double maxDistance = 0.0;
    unsigned len = nodes.size();
    for (unsigned i = 0; i < len; ++i) {
        maxDistance = std::max(maxDistance,  Distance::QuadraticEuclideanDistance(nodes[i], center));
    }
    return maxDistance;
}

/**
 * 打印各分量的均值
 * @author piratf
 */
std::vector<double> Group::componentAverage(bool display) {
    if (!nodes.size()) {
        return std::vector<double>();
    }
    std::vector<double> avg;
    const unsigned component = nodes[0].attribute.size();
    double sum = 0;
    for (unsigned i = 0; i < component; ++i) {
        sum = 0;
        for (auto &node : nodes) {
            sum += node.attribute[i];
        }
        avg.push_back(sum / nodes.size());
    }
    if (display) {
        for (unsigned i = 0; i < avg.size(); ++i) {
            printf("The ave of component %d is %lf\n", i + 1, avg[i]);
        }
    }
    return avg;
}

/**
 * 打印各分量方差
 * @author piratf
 */
std::vector<double> Group::componentVariance(bool display) {
    if (!nodes.size()) {
        return std::vector<double>();
    }
    std::vector<double> avg = componentAverage(false);
    std::vector<double> variance;
    const unsigned component = nodes[0].attribute.size();
    double sum = 0;
    for (unsigned i = 0; i < component; ++i) {
        sum = 0;
        for (auto &node : nodes) {
            sum += (node.attribute[i] - avg[i]) * (node.attribute[i] - avg[i]);
        }
        variance.push_back(sum / nodes.size());
    }
    if (display) {
        for (unsigned i = 0; i < variance.size(); ++i) {
            printf("The variance of component %d is %lf\n", i + 1, sum / nodes.size());
        }
    }
    return variance;
}

/**
 * 获取当前簇的欧氏距离平方和
 * @author piratf
 * @return 当前簇的欧氏距离平方和
 */
double Group::getEuclideanDistanceWithOtherCenter(const Node& otherCenter) {
    double sum = 0.0;
    unsigned len = nodes.size();
    for (unsigned i = 0; i < len; ++i) {
        sum += Distance::QuadraticEuclideanDistance(nodes[i], otherCenter);
    }
    return sum;
}

/**
 * 打印当前簇的数据
 * @author piratf
 */
void Group::display(bool detail) {
    for (Node& node : nodes) {
        node.display(detail);
    }
}