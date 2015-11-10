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
std::vector<Group> buildInitialPointRandomly(unsigned k, const Group &v);

/**
 * Kmeans 版本设置初始点簇
 */
std::vector<Group> buildInitialPoint(unsigned k, const Group &v);

bool cmpByDensity(const Node &lhs, const Node &rhs);

/**
 * 根据密度建立初始点
 */
std::vector<Group> buildInitialPointDensity(unsigned k, Group v);

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
 * 打印聚类数据的各分量均值信息
 * @author piratf
 * @param  centroid 聚类数据集
 */
void evaluateAvg(std::vector<Group>& centroid);

/**
 * 打印聚类数据的各分量方差
 * @author piratf
 * @param  centroid [description]
 */
void evaluateVariance(std::vector<Group>& centroid);

/**
 * 获取用于测试的SSE值
 * @author piratf
 * @param  centroid [description]
 * @param  center   [description]
 * @return          [description]
 */
double getSSE(const std::vector<Group>& centroid, const Node& center);

/**
 * 打印聚类之后的结果信息
 * @author piratf
 * @param  centroid [description]
 */
void printCentroidInfo(std::vector<Group> &centroid, bool detail = false);

/**
 * 获取一个向量的平均值
 * @author piratf
 * @param  v 向量数据
 * @return   向量的平均值
 */
double getAverage(const std::vector<double> &v);

/**
 * 获取一个向量的方差
 * @author piratf
 * @param  v 向量数据
 * @return   向量的方差
 */
double getVariance(const std::vector<double> &v, double average = -1);

#endif