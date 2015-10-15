#include <iostream>
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
bool Group::idConflict(int _id) {
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
double Group::getEuclideanDistance() {
    double sum = 0.0;
    unsigned len = nodes.size();
    for (unsigned i = 0; i < len; ++i) {
        sum += Distance::QuadraticEuclideanDistance(nodes[i], center);
    }
    return sum;
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
