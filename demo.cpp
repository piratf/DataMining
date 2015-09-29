#include "general.h"
#include "structs.h"
#include "kmeans.h"
#include "kmedoids.h"

int main() {
#ifndef ONLINE_JUDGE
    freopen("KMeans.txt", "r", stdin);
#endif
    int n, m;
    while (~scanf("%d %d", &n, &m)) {
        if (n == 0) {
            break;
        }
        std::vector<Node> test;
        double x = 0;
        for (int i = 0; i < n; ++i) {
            test.push_back(Node(i));
            for (int j = 0; j < m; ++j) {
                scanf("%lf", &x);
                test[i].id = i;
                test[i].attribute.push_back(x);
            }
        }

        normaliztion(test);

        puts("Print Input Data:");
        puts("=====================================");

        for (int i = 0; i < n; ++i) {
            test[i].display();
        }
        puts("=====================================\n");

        unsigned k = 3;

        KMeans(test, k);
        KMeans(test, k, true);
        KMedoids(test, k);
    }
    return 0;
}