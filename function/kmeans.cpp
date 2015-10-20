#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include "general.h"
#include "kmeans.h"

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
bool inline checkProcess(unsigned k, std::vector<Group> &centroid, std::vector<Group> &preCenters, int times) {
    if (times > 1000) {
        return false;
    }
    else {
        bool flag = false;
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

std::vector<Group> KMeans(Group &v, unsigned k, std::vector<Group> centroid, bool display) {
    if (display) {
        std::cout << "Start KMeans" << std::endl;
        puts("=====================================");
    }

    // 用于在 checkProcess 中保存上一次运算的中心点，用于计算两次处理的差值，判断是否结束算法
    std::vector<Group> preCenters(1);
    unsigned dataSize = v.nodes.size();

    for (unsigned i = 0; i < v.nodes[0].attribute.size(); ++i) {
        preCenters[0].nodes.push_back(Node());
    }

    if (display) {
        printf("Print initial center id:\n");
        for (unsigned i = 0; i < k; ++i) {
            centroid[i].center.display(false);
        }
        puts("=====================================");
    }

    double dis = 0, mdis = 0, mid = 0;
    unsigned times = 0;

    while (checkProcess(k, centroid, preCenters, times++)) {
        for (unsigned i = 0; i < dataSize; ++i) {
            mdis = DINF;
            for (unsigned j = 0; j < k; ++j) {
                dis = sqrt(Distance::QuadraticEuclideanDistance(v.nodes[i], centroid[j].center));  // 计算欧氏距离
                if (dis < mdis) {
                    mdis = dis;
                    mid = j;
                }   // 找到最小值，最近簇id
            }
            // 标记应该加入的簇 id
            v.nodes[i].gid = mid;
        }
        // 清空簇
        for (Group &g : centroid) {
            g.nodes.clear();
        }
        // 根据 id 重新添加簇节点，这一步是为了去重
        for (Node &node : v.nodes) {
            centroid[node.gid].nodes.push_back(node);
        }
        // 重新计算中心点
        for (unsigned i = 0; i < k; ++i) {
            centroid[i].reCalCenter();
        }
    }

    if (display) {
        evaluation(centroid, true);
        evaluateAvg(centroid);
        evaluateVariance(centroid);
        printCentroidInfo(centroid, true);
        std::cout << "End Of KMeans" << std::endl;
        puts("=====================================\n");
    }
    return centroid;
}