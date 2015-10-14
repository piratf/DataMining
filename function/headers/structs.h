#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <vector>
#include <iostream>

/**
 * 对象节点，用数组存储每个对象的属性
 */
class Node
{
public:
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
        unsigned len = attribute.size();
        for (unsigned i = 0; i < len; ++i) {
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
        unsigned len = attribute.size();
        for (unsigned i = 0; i < len; ++i) {
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
        unsigned len = attribute.size();
        printf("%d ", id);
        for (unsigned i = 0; i < len; ++i) {
            printf("%lf%c", attribute[i], i == len - 1 ? '\n' : ' ');
        }
    }
};

/**
 * 一些计算距离的静态函数
 */
class Distance
{
public:
    /**
    * 欧氏距离平方
    * @author piratf
    * @param  lhs 左侧节点
    * @param  rhs 右侧节点
    * @return     欧氏距离平方
    */
    static double QuadraticEuclideanDistance(const Node& lhs, const Node& rhs) {
        if (lhs.attribute.size() != rhs.attribute.size()) {
            fprintf(stderr, "%d : %d\n", lhs.attribute.size(), rhs.attribute.size());
            fprintf(stderr, "Different kind of Nodes\n");
            return -1;
        }
        double quadraticSum = 0;
        for (unsigned i = 0; i < lhs.attribute.size(); ++i) {
            quadraticSum += (lhs.attribute[i] - rhs.attribute[i]) * (lhs.attribute[i] - rhs.attribute[i]);
        }
        return quadraticSum;
    }

    static double getAverageNum(const std::vector<double> &dvec) {
        double sum = 0;
        for (double dn : dvec) {
            sum += dn;
        }
        return sum / dvec.size();
    }

    /**
     * 获取两个向量的马氏距离
     * @author piratf
     * @param  lhs 向量1
     * @param  rhs 向量2
     * @return     马氏距离的值 double
     */
    static double getMahalanobisDistance(const std::vector<double> &lhs, const std::vector<double> &rhs) {
        // 获取两个向量的平均值
        double lavg = getAverageNum(lhs), ravg = getAverageNum(rhs);
        // 暂存协方差值, 协方差和
        double cov = 0, covSum = 0;
        Matrix mat(2, 2);
        // 遍历矩阵的行和列
        int r = 0, l = 0;
        for (double dni : lhs) {
            for (double dnj : rhs) {

            }
        }
        return 0;
    }
};

/**
 * 簇
 */
class Group
{
public:
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
        unsigned len = center.attribute.size();
        unsigned nlen = nodes.size();    // 簇中节点的个数
        for (unsigned i = 0; i < len; ++i) {
            double sum = 0;
            for (unsigned j = 0; j < nlen; ++j) {
                sum += nodes[j].attribute[i];
            }
            center.attribute[i] = sum / (double)nlen;
        }
    }

    /**
     * 判断簇中是否已经存在当前id
     * @author piratf
     * @param  _id [description]
     * @return     [description]
     */
    bool idConflict(int _id) {
        unsigned len = nodes.size();
        for (unsigned i = 0; i < len; ++i) {
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
        unsigned len = nodes.size();
        for (unsigned i = 0; i < len; ++i) {
            sum += Distance::QuadraticEuclideanDistance(nodes[i], center);
        }
        return sum;
    }

    /**
     * 获取当前簇的欧氏距离平方和
     * @author piratf
     * @return 当前簇的欧氏距离平方和
     */
    double getEuclideanDistanceWithOtherCenter(const Node& otherCenter) {
        double sum = 0.0;
        unsigned len = nodes.size();
        for (unsigned i = 0; i < len; ++i) {
            sum += Distance::QuadraticEuclideanDistance(nodes[i], otherCenter);
        }
        return sum;
    }

   
};  // 簇，存储一个簇的对象数组。

class Matrix
{
public:
    Matrix(int _x, int _y) {
        std::vector< std::vector<double> > temp(_x);
        data = temp;
        for (auto &row : data) {
            std::vector<double> t(_y);
            row = t;
        }
    }

    Matrix();
    ~Matrix();

    std::vector< std::vector<double> > data;
};

#endif