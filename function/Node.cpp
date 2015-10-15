#include <vector>
#include <iostream>
#include <Node.h>

/**
 * 根据属性判断两个对象是否相等
 */
bool Node::operator == (const Node& other) {
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
bool Node::operator != (const Node& other) {
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
void Node::display() {
    unsigned len = attribute.size();
    printf("%d ", id);
    for (unsigned i = 0; i < len; ++i) {
        printf("%lf%c", attribute[i], i == len - 1 ? '\n' : ' ');
    }
}