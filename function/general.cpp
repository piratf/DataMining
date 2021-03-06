#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include "general.h"

/**
 * 计算并返回聚类结果的离差平方和
 * @author piratf
 * @param  centroid 聚类结果集
 * @param  display  true - 直接打印结果 : false - 不输出结果
 * @return          聚类数据集的离差平方和
 */
double evaluation(std::vector<Group>& centroid, bool display) {
    double sum = 0, var = 0;
    unsigned len = centroid.size();
    for (unsigned i = 0; i < len; ++i) {
        var = centroid[i].getSumOfEuclideanDistance();
        if (display) {
            std::cout << "The sum distance inside cluster " << i + 1 << " is " << var << std::endl;
            std::cout << "The max distance inside cluster " << i + 1 << " is " << centroid[i].getMaxOfEuclideanDistance() << std::endl;
        }
        sum += var;
    }
    if (display) {
        printf("evaluation: %lf\n", sum);
        puts("=====================================");
    }
    return sum;
}

/**
 * 打印聚类数据的各分量均值信息
 * @author piratf
 * @param  centroid 聚类数据集
 */
void evaluateAvg(std::vector<Group>& centroid) {
    printf("evaluation average: \n");
    puts("=====================================\n");
    for (unsigned i = 0; i < centroid.size(); ++i) {
        printf("The content of center %d is: \n", i + 1);
        centroid[i].center.display(true);
        // 打印各簇各分量的均值
        centroid[i].componentAverage();
        puts("-------------------------\n");
    }
    puts("=====================================\n");
}

/**
 * 打印聚类数据的各分量方差
 * @author piratf
 * @param  centroid [description]
 */
void evaluateVariance(std::vector<Group>& centroid) {
    printf("evaluation variance: \n");
    puts("=====================================\n");
    for (Group &g : centroid) {
        std::vector<double> avg = g.componentAverage(false);
        std::vector<double> variance = g.componentVariance(false);
        for (unsigned i = 0; i < variance.size(); ++i) {
            printf("standard accounted for average: %lf%%\n", sqrt(variance[i]) / avg[i] * 100);
        }
        puts("-------------------------\n");
    }
    puts("=====================================\n");
}

/**
 * 打印聚类之后的结果信息
 * @author piratf
 * @param  centroid 聚类的结果集
 * @param  detail   true - 打印每个聚类的点数量和每个点的具体内容 : false - 只打印每个聚类的点数量
 */
void printCentroidInfo(std::vector<Group> &centroid, bool detail) {
    puts("Print the clustering results Data:");
    puts("=====================================");
    for (unsigned i = 0; i < centroid.size(); ++i) {
        if (detail) {
            puts("=====================================\n");
            unsigned nlen = centroid[i].nodes.size();
            for (unsigned j = 0; j < nlen; ++j) {
                centroid[i].nodes[j].display(false);
            }
            puts("\n=====================================\n");
        }
    }
    for (unsigned i = 0; i < centroid.size(); ++i) {
        unsigned nlen = centroid[i].nodes.size();
        printf("Centroid: %d, count: %d\n", i + 1, nlen);
    }
    puts("=====================================");
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
    const unsigned len = centroid.size();
    for (unsigned i = 0; i < len; ++i) {
        sum += centroid[i].getEuclideanDistanceWithOtherCenter(otherCenter);
    }
    return sum;
}

/**
 * 数据归一化
 * @author piratf
 * @param  v 输入的数据集
 */
void normaliztion(Group& v) {
    if (!v.nodes.size()) {
        fprintf(stderr, "Normaliztion: error - empty vector!\n");
        return;
    }
    auto len = v.nodes.size();
    auto alen = v.nodes[0].attribute.size();
    double minv = DINF, maxv = -1;
    for (decltype(len) i = 0; i != len; ++i) {
        for (decltype(len) j = 0; j != alen; ++j) {
            minv = std::min(v.nodes[i].attribute[j], minv);
            maxv = std::max(v.nodes[i].attribute[j], maxv);
        }
    }
    double gap = maxv - minv;
    for (decltype(len) i = 0; i != len; ++i) {
        for (decltype(len) j = 0; j != alen; ++j) {
            v.nodes[i].attribute[j] = (v.nodes[i].attribute[j] - minv) / (gap);
        }
    }
}

/**
 * 直接取遍历点到最近中心点距离的最大值最为下一个中心点
 */
std::vector<Group> buildInitialPoint(unsigned k, const Group &v) {
    std::vector<Group> centroid(k);
    unsigned len = v.nodes.size();
    srand((unsigned)time(NULL));
    centroid[0].nodes.push_back(v.nodes[rand() % len]);
    centroid[0].center = centroid[0].nodes[0];

    unsigned found = 1;
    double minv = DINF, dis = 0, maxv = -1;
    unsigned mid = 0;
    while (found < k) {
        maxv = -1;
        for (unsigned i = 0; i < len; ++i) {
            minv = DINF;
            for (unsigned j = 0; j < found; ++j) {
                dis = Distance::QuadraticEuclideanDistance(centroid[j].center, v.nodes[i]);
                minv = std::min(minv, dis);
            }
            if (minv > maxv) {
                maxv = minv;
                mid = i;
            }
        }
        centroid[found].nodes.push_back(v.nodes[mid]);
        centroid[found].center = v.nodes[mid];
        found++;
    }
    return centroid;
}

/**
 * 让各点到最近中心点距离最大的点概率最大
 */
std::vector<Group> buildInitialPointRandomly(unsigned k, const Group &v) {
    std::vector<Group> centroid(k);
    unsigned len = v.nodes.size();
    srand((unsigned)time(NULL));
    centroid[0].nodes.push_back(v.nodes[rand() % len]);
    centroid[0].center = centroid[0].nodes[0];

    unsigned found = 1;
    double minv = DINF, dis = 0;
    double* disList = (double*)malloc((len + 10) * sizeof(double));

    while (found < k) {
        for (unsigned i = 0; i < len; ++i) {
            minv = DINF;
            for (unsigned j = 0; j < found; ++j) {
                dis = Distance::QuadraticEuclideanDistance(centroid[j].center, v.nodes[i]);
                minv = std::min(minv, dis);
            }
            disList[i] = minv;  // 点到最近中心点的距离
        }

        // 累加
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

        centroid[found].nodes.push_back(v.nodes[cnt]);
        centroid[found].center = v.nodes[cnt];
        found++;
    }
    return centroid;
}

bool cmpByDensity(const Node &lhs, const Node &rhs) {
    return lhs.densityNumber < rhs.densityNumber;
}

/**
 * 根据密度建立初始点
 */
std::vector<Group> buildInitialPointDensity(unsigned k, Group v) {
    std::vector<Group> centroid(k);
    unsigned len = v.nodes.size();

    // 计算密度参数时边界节点数量
    const unsigned LIMIT = 5;
    // 按照密度参数取多少比例的点
    const double FRONT = 0.6;
    const unsigned END = (double)v.nodes.size() * FRONT;

    // 对所有点两两之间计算距离
    std::vector<std::vector<double> > distanceMatrix;
    std::vector<double> densityNumber;

    for (unsigned i = 0; i < len; ++i) {
        distanceMatrix.push_back(std::vector<double>());
        for (unsigned j = 0; j < len; ++j) {
            distanceMatrix[i].push_back(Distance::QuadraticEuclideanDistance(v.nodes[i], v.nodes[j]));
        }
    }

    // 对每个点到其它点的距离排序，获得每个点的密度参数
    for (unsigned i = 0; i < len; ++i) {
        std::sort(distanceMatrix[i].begin(), distanceMatrix[i].end());
        v.nodes[i].densityNumber = (distanceMatrix[i][LIMIT]);
    }

    // 按照密度参数排序
    std::sort(v.nodes.begin(), v.nodes.end(), cmpByDensity);

    Group v2;
    for (unsigned i = 0; i < END; ++i) {
        v2.nodes.push_back(v.nodes[i]);
    }

    return buildInitialPointRandomly(k, v2);
}

/**
 * 获取一个向量的平均值
 * @author piratf
 * @param  v 向量数据
 * @return   向量的平均值
 */
double getAverage(const std::vector<double> &v) {
    double sum = 0;
    for (const double &var : v) {
        sum += var;
    }
    return sum / v.size();
}

/**
 * 获取一个向量的方差
 * @author piratf
 * @param  v 向量数据
 * @return   向量的方差
 */
double getVariance(const std::vector<double> &v, double average) {
    if (average == -1) {
        average = getAverage(v);
    }
    double variance = 0;
    for (const double &var : v) {
        variance += (var - average) * (var - average);
    }
    return variance / v.size();
}