#include "general.h"
#include "kmeans.h"
#include "k-mediods.h"
#include "Distance.h"
#include "Matrix.h"
#include <vector>
#include <iostream>
#include <ctime>

using vecSizeT = std::vector<double>::size_type;

void inline unitTest(Group &test) {
    // 数据归一化
    // normaliztion(test);

    // 输出读入的数据
    puts("Print Input Data:");
    puts("=====================================");
    // test.display();
    puts("=====================================\n");

    // k 值
    const unsigned k = 3;

    /** 准备测试数据 */
    // KMeans++
    // std::vector<Group> centroid = buildInitialPointRandomly(k, test);
    // Kmeans + Density initialize
    // std::vector<Group> centroid = buildInitialPointDensity(k, test);
    // KMeans
    // std::vector<Group> centroid = buildInitialPoint(k, test);


    // 重复运行测试
    std::vector<Group> result;
    std::vector<double> avg(k);
    double SSE = 0;
    // 记录每次的 SSE 值
    std::vector<double> vecSSE;
    time_t start = std::clock();
    // 重复实验的次数
    const double TIMES = 1000;
    for (unsigned i = 0; i < TIMES; ++i) {
        result = KMeans(test, k, buildInitialPoint(k, test), false);
        SSE = 0;
        for (unsigned j = 0; j < result.size(); ++j) {
            SSE += result[j].getSumOfEuclideanDistance();
            vecSSE.push_back(SSE / result.size());
        }
    }
    time_t end = std::clock();
    freopen("buildInitialPoint.txt", "a+", stdout);
    printf("The average of SSE = %lf\n", getAverage(vecSSE));
    printf("The variance of SSE = %lf\n", getVariance(vecSSE));
    printf("the running time is : %f\n", double(end - start) / CLOCKS_PER_SEC);
    puts("===============================================");
    // KMedoids(test, k, centroid);
}

void inline matrixTest(Group &test) {
    Matrix mat = Matrix::getCovarianceMatrix(std::vector<std::vector<double> > {test.nodes[0].attribute, test.nodes[1].attribute});
    mat.printData();
    std::vector<Matrix> lu = mat.luDecomposition();
    lu[0].printData();
    lu[1].printData();
}   // unfinished, could cause error

int main() {
    freopen(".\\data\\iris.txt", "r", stdin);
    int n, m;
    while (~scanf("%d %d", &n, &m)) {
        if (n == 0) {
            break;
        }
        // 数据集
        // std::vector<Node> test;
        Group test;
        double x = 0;
        for (int i = 0; i < n; ++i) {
            test.nodes.push_back(Node(i));
            for (int j = 0; j < m; ++j) {
                scanf("%lf", &x);
                test.nodes[i].id = i + 1;
                test.nodes[i].attribute.push_back(x);
            }
        }

        for (unsigned i = 0; i < 10; ++i) {
            unitTest(test);
        }
    }
    return 0;
}