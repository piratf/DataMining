#ifndef NODE_H
#define NODE_H

#include <vector>

/**
 * 对象节点，用数组存储每个对象的属性
 */
class Node
{
public:
    std::vector<double> attribute;  // 节点的属性
    int id; // 节点的id
    int gid; // 记录节点所属组的id

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
    bool operator == (const Node& other);

    /**
     * 根据属性判断两个对象是否不相等
     */
    bool operator != (const Node& other);

    /**
     * 在一行内打印当前对象的属性值，以空格隔开
     * @author piratf
     */
    void display();
};

#endif