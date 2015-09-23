#include <stdio.h>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

const double DINF = 1e12;
const int IINF = 0x3f3f3f3f;

struct Node
{
    std::vector<double> attribute;  // 节点的属性
    int id; // 节点的id

    Node() {
        id = 0;
    }

    /**
     * 输入id的构造函数
     */
     Node(int _id) {
        id = _id;
    }

    /**
     * 根据属性判断两个对象是否相等
     */
     bool operator == (const Node& other) {
        int len = attribute.size();
        for (int i = 0; i < len; ++i) {
            if (attribute[i] -= other.attribute[i] > 1e-8) {
                return false;
            }
        }
        return true;
    }

    /**
     * 根据属性判断两个对象是否不相等
     */
     bool operator != (const Node& other) {
        int len = attribute.size();
        for (int i = 0; i < len; ++i) {
            if (attribute[i] - other.attribute[i] > 1e-8) {
                return true;
            }
        }
        return false;
    }

    /**
     * 在一行内打印当前对象的属性值，以空格隔开
     * @author piratf
     */
     void display() {
        int len = attribute.size();
        printf("%d ", id);
        for (int i = 0; i < len; ++i) {
            printf("%lf%c", attribute[i], i == len - 1 ? '\n' : ' ');
        }
    }
};  // 对象节点，用数组存储每个对象的属性

/**
 * 欧氏距离平方
 * @author piratf
 * @param  lhs 左侧节点
 * @param  rhs 右侧节点
 * @return     欧氏距离平方
 */
 double QuadraticEuclideanDistance(Node& lhs, Node& rhs) {
    if (lhs.attribute.size() != rhs.attribute.size()) {
        printf("%d : %d\n", lhs.attribute.size(), rhs.attribute.size());
        printf("Different kind of Nodes\n");
        return -1;
    }
    double quadraticSum = 0;
    for (unsigned int i = 0; i < lhs.attribute.size(); ++i) {
        quadraticSum += (lhs.attribute[i] - rhs.attribute[i]) * (lhs.attribute[i] - rhs.attribute[i]);
    }
    return quadraticSum;
}

/**
 * 簇
 */
 struct Group
 {   
    std::vector<Node> nodes;    // 簇中的对象向量
    Node center;    // 簇的中心对象

    Group() {
    }

    /**
     * 输入中心点的构造函数
     */
     Group(Node& c) {
        center = c;
        nodes.push_back(center);
    }

    /**
     * 重新计算簇的中心位置
     * @author piratf
     */
     void reCalCenter() {
        int len = center.attribute.size();
        int nlen = nodes.size();    // 簇中节点的个数
        for (int i = 0; i < len; ++i) {
            double sum = 0;
            for (int j = 0; j < nlen; ++j) {
                sum += nodes[j].attribute[i];
            }
            center.attribute[i] = sum / (double)nlen;
        }
    }   // 重新获取中心点


    /**
     * 判断簇中是否已经存在当前id
     * @author piratf
     * @param  _id [description]
     * @return     [description]
     */
     bool idConflict(int _id) {
        int len = nodes.size();
        for (int i = 0; i < len; ++i) {
            if (nodes[i].id == _id) {
                return true;
            }
        }
        return false;
    }

    /**
     * 获取当前簇的欧氏距离平方和
     * @author piratf
     * @return 当前簇的欧氏距离平方和
     */
     double getEuclideanDistance() {
        double sum = 0.0;
        int len = nodes.size();
        for (int i = 0; i < len; ++i) {
            sum += QuadraticEuclideanDistance(nodes[i], center);
        }
        return sum;
    }
};  // 簇，存储一个簇的对象数组。

/**
 * 评估聚类结果的好坏
 * @author piratf
 * @param  centroid 聚类生成的簇向量
 * @return          簇向量的距离平方和
 */
 double evaluation(std::vector<Group>& centroid) {
    double sum = 0;
    int len = centroid.size();
    for (int i = 0; i < len; ++i) {
        sum += centroid[i].getEuclideanDistance();
    }
    return sum;
}

/**
 * 检查聚类算法是否应该继续运行
 * @author piratf
 * @param  k          簇的数量
 * @param  centroid   簇向量
 * @param  preCenters 上一次运行的中心点组
 * @param  times      运行次数
 * @return            是否继续运行 1:继续运行 0:结束算法
 */
 bool inline checkProcess(int k, std::vector<Group>& centroid, std::vector<Node>& preCenters, int times = 0) {
    if (times > 100) {
        return false;
    }
    else {
        bool flag = true;
        for (int i = 0; i < k; ++i) {
            if (preCenters[i] != centroid[i].center) {
                flag = false;
                preCenters[i] = centroid[i].center;
            }
        }
        return flag;
    }
    return true;
}

void normaliztion(std::vector<Node>& v) {
    if (v.size() < 1) {
        printf("Normaliztion: error - empty vector!\n");
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
    centroid[0].nodes.push_back(v[/*rand() % len*/ 0]);
    centroid[0].center = centroid[0].nodes[0];

    int found = 1;
    double minv = DINF, mid = -1, dis = 0, maxv = -1;
    while (found < k) {
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < found; ++j) {
                dis = QuadraticEuclideanDistance(centroid[j].center, v[i]);
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
    
    // std::vector<Group> centroid = buildInitialPoint(k, v);
    std::vector<Group> centroid(k);
    int testlen = v.size();
    for (int i = 0; i < k; ++i) {
        centroid[i].nodes.push_back(v[i]);
        centroid[i].center = v[i];
        preCenters.push_back(centroid[i].center);
    }   // 初始化各簇，设置质心

    // std::vector<Group> centroid = buildInitialPoint(k, v);

    double dis = 0, mdis = 0, mid = 0;
    int times = 0;

    while (checkProcess(k, centroid, preCenters, times++)) {

        for (int i = 0; i < testlen; ++i) {
            mdis = DINF;
            for (int j = 0; j < k; ++j) {
                dis = sqrt(QuadraticEuclideanDistance(v[i], centroid[j].center));  // 计算欧氏距离
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

    return centroid;
}

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