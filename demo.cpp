#include "general.h"
#include "kmeans.h"
#include "kmedoids.h"
#include "Distance.h"
#include "Matrix.h"
#include <vector>
#include <iostream>

using vecSizeT = std::vector<double>::size_type;

void inline unitTest(std::vector<Node> &test) {
    // 数据归一化
    normaliztion(test);

    // 输出读入的数据
    puts("Print Input Data:");
    puts("=====================================");

    for (vecSizeT i = 0; i != test.size(); ++i) {
        test[i].display();
    }
    puts("=====================================\n");

    const unsigned k = 3;

    // KMeans(test, k);
    KMeans(test, k, true);
    // KMedoids(test, k);
}

void inline matrixTest(std::vector<Node> &test) {
    Matrix mat = Matrix::getCovarianceMatrix(std::vector<std::vector<double> > {test[0].attribute, test[1].attribute});
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
        std::vector<Node> test;
        double x = 0;
        for (int i = 0; i < n; ++i) {
            test.push_back(Node(i));
            for (int j = 0; j < m; ++j) {
                scanf("%lf", &x);
                test[i].id = i + 1;
                test[i].attribute.push_back(x);
            }
        }

        unitTest(test);
    }
    return 0;
}