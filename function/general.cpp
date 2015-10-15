#include <iostream>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include "general.h"

// get SSE
double evaluation(std::vector<Group>& centroid, bool display) {
    double sum = 0;
    unsigned len = centroid.size();
    for (unsigned i = 0; i < len; ++i) {
        sum += centroid[i].getEuclideanDistance();
    }
    if (display) {
        printf("evaluation: %lf\n", sum);
        puts("=====================================");

        puts("Print the clustering results Data:");
        puts("=====================================");
        for (unsigned i = 0; i < len; ++i) {
            unsigned nlen = centroid[i].nodes.size();
            printf("Centroid: %d, count: %d\n", i + 1, nlen);
            puts("=====================================");
            for (unsigned j = 0; j < nlen; ++j) {
                centroid[i].nodes[j].display();
            }
        }
        puts("=====================================");
    }
    return sum;
}

/**
 * 通过欧氏距离获得误差平方和
 * @author piratf
 * @param  centroid    聚类簇的集合
 * @param  otherCenter 中心点
 * @return             欧氏距离
 */
double getSSE(std::vector<Group>& centroid, const Node& otherCenter) {
    double sum = 0;
    int len = centroid.size();
    for (int i = 0; i < len; ++i) {
        sum += centroid[i].getEuclideanDistanceWithOtherCenter(otherCenter);
    }
    return sum;
}

/**
 * 数据归一化
 * @author piratf
 * @param  v 输入的数据集
 */
void normaliztion(std::vector<Node>& v) {
    if (!v.size()) {
        fprintf(stderr, "Normaliztion: error - empty vector!\n");
        return;
    }
    auto len = v.size();
    auto alen = v[0].attribute.size();
    double minv = DINF, maxv = -1;
    for (decltype(len) i = 0; i != len; ++i) {
        for (decltype(len) j = 0; j != alen; ++j) {
            minv = std::min(v[i].attribute[j], minv);
            maxv = std::max(v[i].attribute[j], maxv);
        }
    }
    double gap = maxv - minv;
    for (decltype(len) i = 0; i != len; ++i) {
        for (decltype(len) j = 0; j != alen; ++j) {
            v[i].attribute[j] = (v[i].attribute[j] - minv) / (gap);
        }
    }
}

/**
 * 直接取遍历点到最近中心点距离的最大值最为下一个中心点
 */
std::vector<Group> buildInitialPoint(unsigned k, std::vector<Node>& v) {
    std::vector<Group> centroid(k);
    unsigned len = v.size();
    srand((unsigned)time(NULL));
    centroid[0].nodes.push_back(v[rand() % len /*0*/]);
    centroid[0].center = centroid[0].nodes[0];

    unsigned found = 1;
    double minv = DINF, dis = 0, maxv = -1;
    unsigned mid = 0;
    while (found < k) {
        maxv = -1;
        for (unsigned i = 0; i < len; ++i) {
            minv = DINF;
            for (unsigned j = 0; j < found; ++j) {
                dis = Distance::QuadraticEuclideanDistance(centroid[j].center, v[i]);
                minv = std::min(minv, dis);
            }
            if (minv > maxv) {
                maxv = minv;
                mid = i;
            }
        }
        centroid[found].nodes.push_back(v[mid]);
        centroid[found].center = v[mid];
        found++;
    }
    return centroid;
}

/**
 * 让各点到最近中心点距离最大的点概率最大
 */
std::vector<Group> buildInitialPointPlus(unsigned k, std::vector<Node>& v) {
    std::vector<Group> centroid(k);
    unsigned len = v.size();
    srand((unsigned)time(NULL));
    centroid[0].nodes.push_back(v[rand() % len /*0*/]);
    centroid[0].center = centroid[0].nodes[0];

    unsigned found = 1;
    double minv = DINF, dis = 0;
    double* disList = (double*)malloc((len + 10) * sizeof(double));
    std::cout << disList[0] << std::endl;

    while (found < k) {
        for (unsigned i = 0; i < len; ++i) {
            minv = DINF;
            for (unsigned j = 0; j < found; ++j) {
                dis = Distance::QuadraticEuclideanDistance(centroid[j].center, v[i]);
                minv = std::min(minv, dis);
            }
            disList[i] = minv;  // 点到最近中心点的距离
        }

        double disSum = std::accumulate(disList, disList + len, 0);

        disSum = 0;
        for (unsigned i = 0; i < len; ++i) {
            disSum += disList[i];
        }

        srand((unsigned)time(0));
        double randNum = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / disSum));
        int cnt = -1;   // 初始化偏移量
        while (randNum >= 0) {
            randNum -= disList[++cnt];
        }

        centroid[found].nodes.push_back(v[cnt]);
        centroid[found].center = v[cnt];
        found++;
    }
    return centroid;
}