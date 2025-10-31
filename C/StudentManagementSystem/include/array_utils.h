#ifndef STUDENT_OPERATING_METHOD_H
#define STUDENT_OPERATING_METHOD_H

#include "../models/student_model.h"
#include <stddef.h>

// 添加元素：找到第一个全 0 槽插入
void addElement(void *arr, int length, const void *value, size_t elemSize);

// 删除元素：整体前移 + 尾部清零
void deleteElement(void *arr, int length, int index, size_t elemSize);

// 更新元素
void updateElement(void *arr, int length, int index, const void *newValue, size_t elemSize);

#endif
