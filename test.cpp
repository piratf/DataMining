#include "KMeans.h"

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

        for (int i = 0; i < n; ++i) {
            test[i].display();
        }
        puts("=====================================");

        int k = 3;

        std::vector<Group> g = KMeans(test, k);

        for (int i = 0; i < k; ++i) {
            printf("Centroid: %d\n", i+1);
            int len = g[i].nodes.size();
            for (int j = 0; j < len; ++j) {
                g[i].nodes[j].display();
            }
        }
    }
}