#include <stdio.h>
#include <string.h>

// 判断内存块是否全为 0
static int is_zero_block(const void *p, size_t n)
{
    const unsigned char *c = (const unsigned char *)p;
    for (size_t i = 0; i < n; ++i)
        if (c[i] != 0)
            return 0;
    return 1;
}

// 添加元素：找到第一个全 0 槽插入
void addElement(void *arr, int length, const void *value, size_t elemSize)
{
    int index = -1;
    char *base = (char *)arr;
    for (int i = 0; i < length; ++i)
    {
        if (is_zero_block(base + i * elemSize, elemSize))
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        printf("数组已满或没有空位！\n");
        return;
    }
    memcpy(base + index * elemSize, value, elemSize);
    printf("已添加元素到索引 %d\n", index);
}

// 删除元素：整体前移 + 尾部清零
void deleteElement(void *arr, int length, int index, size_t elemSize)
{
    if (index < 0 || index >= length)
    {
        printf("下标 %d 无效！\n", index);
        return;
    }
    char *base = (char *)arr;
    char *target = base + index * elemSize;
    if (index < length - 1)
    {
        memmove(target, target + elemSize, (size_t)(length - index - 1) * elemSize);
    }
    memset(base + (length - 1) * elemSize, 0, elemSize);
    printf("已删除索引 %d 的元素（已前移并把尾部置零）\n", index);
}

// 更新元素
void updateElement(void *arr, int length, int index, const void *newValue, size_t elemSize)
{
    if (index < 0 || index >= length)
    {
        printf("下标 %d 无效！\n", index);
        return;
    }
    memcpy((char *)arr + index * elemSize, newValue, elemSize);
    printf("已更新索引 %d 的元素\n", index);
}

// 打印数组（通过回调函数打印每个元素）
void printArray(const void *arr, int length, size_t elemSize, void (*printOne)(const void *))
{
    const char *base = (const char *)arr;
    int shown = 0;
    for (int i = 0; i < length; ++i)
    {
        const void *elem = base + i * elemSize;
        if (is_zero_block(elem, elemSize))
            continue;
        printOne(elem);
        shown = 1;
    }
    if (!shown)
        printf("数组为空。\n");
}
