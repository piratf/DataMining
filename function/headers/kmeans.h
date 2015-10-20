#ifndef KMEANS_H_
#define KMEANS_H_

#include <string>

/**
 * 检查聚类算法是否应该继续运行
 * 如果聚类出现了以前出现过的组就停止算法
 * 确保不会出现循环在几个值中进行无用计算
 * @author piratf
 * @param  k          簇的数量
 * @param  centroid   簇向量
 * @param  preCenters 上一次运行的中心点组
 * @param  times      运行次数
 * @return            是否继续运行 1:继续运行 0:结束算法
 */
bool inline checkProcess(unsigned k, std::vector<Group> &centroid, std::vector<Group> &preCenters, int times = 0);

std::vector<Group> KMeans(Group &v, unsigned k, std::vector<Group> centroid, bool display = true);
#endif