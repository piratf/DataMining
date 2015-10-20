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
bool inline checkProcess(unsigned k, std::vector<Group> &centroid, std::vector<Group> &preCenters, int times = 0) {
    if (times > 1000) {
        return false;
    }
    else {
        bool flag = false;
        // printf("preCenters size = %d\n", preCenters.size());
        // 检查 preCenters 中是否已经存在当前中心点
        for (unsigned i = 0; i < preCenters.size(); ++i) {
            flag = false;
            for (unsigned j = 0; j < k; ++j) {
                if (preCenters[i].nodes[j] != centroid[j].center) {
                    flag = true;
                    break;
                }
            }
            // 如果找到已经出现的组就结束
            if (!flag) {
                break;
            }
        }

        // 如果没有找到，整个组保存一份
        if (flag) {
            Group temp;
            for (unsigned i = 0; i < k; ++i) {
                temp.nodes.push_back(centroid[i].center);
            }
            preCenters.push_back(temp);
        }
        return flag;
    }
    return true;
}

std::vector<Group> KMeans(Group &v, unsigned k, std::string algorithm = "KMeans");
#endif