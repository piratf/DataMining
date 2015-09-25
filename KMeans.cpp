#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include "KMeans.h"

const double DINF = 1e12;
const int IINF = 0x3f3f3f3f;

double evaluation(std::vector<Group>& centroid) {
    double sum = 0;
    int len = centroid.size();
    for (int i = 0; i < len; ++i) {
        sum += centroid[i].getEuclideanDistance();
    }
    return sum;
}

void normaliztion(std::vector<Node>& v) {
    if (v.size() < 1) {
        fprintf(stderr, "Normaliztion: error - empty vector!\n");
        return;
    }
    int len = v.size();
    int alen = v[0].attribute.size();
    for (int i = 0; i < len; ++i) {
        double minv = DINF, maxv = -1;
        for (int j = 0; j < alen; ++j) {
            minv = std::min(v[i].attribute[j], minv);
            maxv = std::max(v[i].attribute[j], maxv);
        }
        double gap = maxv - minv;
        for (int j = 0; j < alen; ++j) {
            v[i].attribute[j] = (v[i].attribute[j] - minv) / (gap);
        }
    }
}

std::vector<Group> buildInitialPoint(int k, std::vector<Node>& v) {
    std::vector<Group> centroid(k);
    int len = v.size();
    srand((unsigned)time(NULL));
    centroid[0].nodes.push_back(v[rand() % len /*0*/]);
    centroid[0].center = centroid[0].nodes[0];

    int found = 1;
    double minv = DINF, dis = 0, maxv = -1;
    int mid = 0;
    while (found < k) {
        maxv = -1;
        for (int i = 0; i < len; ++i) {
            minv = DINF;
            for (int j = 0; j < found; ++j) {
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

std::vector<Group> KMeans(std::vector<Node>& v, int k) {
    std::vector<Node> preCenters(k);
    int testlen = v.size();

    std::vector<Group> centroid = buildInitialPoint(k, v);
    // std::vector<Group> centroid(k);
    // for (int i = 0; i < k; ++i) {
    //     centroid[i].nodes.push_back(v[i]);
    //     centroid[i].center = v[i];
    //     preCenters.push_back(centroid[i].center);
    // }   // 初始化各簇，设置质心

    // std::vector<Group> centroid = buildInitialPoint(k, v);

    printf("Print initial center id:\n");
    for (int i = 0; i < k; ++i) {
        printf("%d\n", centroid[i].center.id);
    }
    puts("=====================================");

    double dis = 0, mdis = 0, mid = 0;
    int times = 0;

    while (checkProcess(k, centroid, preCenters, times++)) {

        for (int i = 0; i < testlen; ++i) {
            mdis = DINF;
            for (int j = 0; j < k; ++j) {
                dis = sqrt(Distance::QuadraticEuclideanDistance(v[i], centroid[j].center));  // 计算欧氏距离
                if (dis < mdis) {
                    mdis = dis;
                    mid = j;
                }   // 找到最小值，最近簇id
            }
            // cout << mid << endl;
            if (!centroid[mid].idConflict(v[i].id)) {
                centroid[mid].nodes.push_back(v[i]);    // 在最近簇中加入节点i
            }
        }
        for (int i = 0; i < k; ++i) {
            centroid[i].reCalCenter();
        }
    }

    printf("evaluation: %lf\n", evaluation(centroid));
    puts("=====================================");

    return centroid;
}