#include "general.h"
#include "kmeans.h"
#include "kmedoids.h"
#include <iostream>

int main() {
#ifndef ONLINE_JUDGE
    freopen(".\\data\\iris.txt", "r", stdin);
#endif
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

        // normaliztion(test);

        // 输出读入的数据
        puts("Print Input Data:");
        puts("=====================================");

        for (int i = 0; i < n; ++i) {
            test[i].display();
        }
        puts("=====================================\n");

        unsigned k = 3;

        // KMeans(test, k);
        KMeans(test, k, true);
        // KMedoids(test, k);
    }
    return 0;
}