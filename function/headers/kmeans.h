#ifndef KMEANS_H_
#define KMEANS_H_

/**
 * 检查聚类算法是否应该继续运行
 * @author piratf
 * @param  k          簇的数量
 * @param  centroid   簇向量
 * @param  preCenters 上一次运行的中心点组
 * @param  times      运行次数
 * @return            是否继续运行 1:继续运行 0:结束算法
 */
bool inline checkProcess(unsigned k, std::vector<Group>& centroid, std::vector<Node>& preCenters, int times = 0) {
    if (times > 100) {
        return false;
    }
    else {
        bool flag = true;
        for (unsigned i = 0; i < k; ++i) {
            if (preCenters[i] != centroid[i].center) {
                flag = false;
                preCenters[i] = centroid[i].center;
            }
        }
        return flag;
    }
    return true;
}

std::vector<Group> KMeans(Group &v, unsigned k, bool plus = false);
#endif