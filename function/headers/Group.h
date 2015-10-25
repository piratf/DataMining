#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include "Node.h"
#include "Distance.h"

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
    void reCalCenter();

    /**
     * 判断簇中是否已经存在当前id
     * @author piratf
     * @param  _id [description]
     * @return     [description]
     */
    bool idConflict(unsigned _id);

    /**
     * 获取当前簇的欧氏距离平方和
     * @author piratf
     * @return 当前簇的欧氏距离平方和
     */
    double getSumOfEuclideanDistance();

    /**
     * 获取当前簇的欧氏距离平方最大值
     * @author piratf
     * @return 当前簇的欧氏距离平方最大值
     */
    double getMaxOfEuclideanDistance();

    /**
     * 返回当前簇到特定点的欧式距离平方和
     * @author piratf
     * @param  otherCenter 特定的店
     * @return             当前簇到特定点的欧式距离平方和
     */
    double getEuclideanDistanceWithOtherCenter(const Node& otherCenter);

    /**
     * 打印各分量的均值
     * @author piratf
     */
    std::vector<double> componentAverage(bool display = true);

    /**
     * 打印各分量方差
     * @author piratf
     */
    std::vector<double> componentVariance(bool display = true);

    /**
     * 打印当前簇的数据
     * @author piratf
     */
    void display(bool detail = false);

   
};  // 簇，存储一个簇的对象数组。

#endif
