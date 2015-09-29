#ifndef KMEANS_H_
#define KMEANS_H_

#include "Structs.h"

/**
 * 评估聚类结果的好坏
 * @author piratf
 * @param  centroid 聚类生成的簇向量
 * @return          簇向量的距离平方和
 */
double evaluation(std::vector<Group>& centroid);

/**
 * 检查聚类算法是否应该继续运行
 * @author piratf
 * @param  k          簇的数量
 * @param  centroid   簇向量
 * @param  preCenters 上一次运行的中心点组
 * @param  times      运行次数
 * @return            是否继续运行 1:继续运行 0:结束算法
 */
bool inline checkProcess(int k, std::vector<Group>& centroid, std::vector<Node>& preCenters, int times = 0) {
    if (times > 100) {
        return false;
    }
    else {
        bool flag = true;
        for (int i = 0; i < k; ++i) {
            if (preCenters[i] != centroid[i].center) {
                flag = false;
                preCenters[i] = centroid[i].center;
            }
        }
        return flag;
    }
    return true;
}

/**
 * 数据归一化
 * @author piratf
 * @param  v 对象向量
 */
void normaliztion(std::vector<Node>& v);

/**
 * 设置初始点簇
 */
std::vector<Group> buildInitialPoint(int k, std::vector<Node>& v);
std::vector<Group> KMeans(std::vector<Node>& v, int k, bool plus = false);

#endif