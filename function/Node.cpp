#include <vector>
#include <iostream>
#include <Node.h>

/**
 * 根据属性判断两个对象是否相等
 */
bool Node::operator == (const Node& other) {
    if (attribute.size() != other.attribute.size()) {
        return false;
    }
    unsigned len = attribute.size();
    for (unsigned i = 0; i < len; ++i) {
        if ((attribute[i] - other.attribute[i]) > 1e-8) {
            return false;
        }
    }
    return true;
}

/**
 * 根据属性判断两个对象是否不相等
 */
bool Node::operator != (const Node& other) {
    if (attribute.size() != other.attribute.size()) {
        return true;
    }
    unsigned len = attribute.size();
    for (unsigned i = 0; i < len; ++i) {
        if ((attribute[i] - other.attribute[i]) > 1e-8) {
            return true;
        }
    }
    return false;
}

/**
 *  拷贝
 */
void Node::operator = (const Node& other) {
    attribute = other.attribute;
    id = other.id;
    gid = other.gid;
    densityNumber = other.densityNumber;
}

/**
 * 在一行内打印当前对象的属性值，以空格隔开
 * @author piratf
 */
void Node::display(bool detail) {
    unsigned len = attribute.size();
    printf("%d ", id);
    // printf("id = %d\n", id);
    if (detail) {
        for (unsigned i = 0; i < len; ++i) {
            printf("%lf%c", attribute[i], i == len - 1 ? '\n' : ' ');
        }
    }
}