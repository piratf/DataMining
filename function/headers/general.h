#ifndef GENERAL_H_
#define GENERAL_H_

#include <vector>
#include "Node.h"
#include "Distance.h"
#include "Group.h"

// INF of Double and Int
const double DINF = 1e12;
const int IINF = 0x3f3f3f3f;

/**
 * Kmeans++ 版本设置初始点簇，有较低概率选择较差的点
 */
std::vector<Group> buildInitialPointPlus(unsigned k, Group &v);

/**
 * Kmeans 版本设置初始点簇
 */
std::vector<Group> buildInitialPoint(unsigned k, Group &v);

/**
 * 数据归一化
 * @author piratf
 * @param  v 对象向量
 */
void normaliztion(Group &v);

/**
 * 评估聚类结果的好坏
 * @author piratf
 * @param  centroid 聚类生成的簇向量
 * @return          簇向量的距离平方和
 */
double evaluation(std::vector<Group>& centroid, bool display = false);


/**
 * 获取用于测试的SSE值
 * @author piratf
 * @param  centroid [description]
 * @param  center   [description]
 * @return          [description]
 */
double getSSE(const std::vector<Group>& centroid, const Node& center);

#endif