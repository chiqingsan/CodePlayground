#include <stdio.h>
#include "../models/student_model.h"

void saveStudentsToFile(struct studentModel students[], int length, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        printf("无法打开文件 %s 进行写入。\n", filename);
        return;
    }

    for (int i = 0; i < length; i++)
    {
        if (students[i].studentId == 0)
            continue;

        fprintf(fp, "%s %u %d %u %s %s\n",
                students[i].name,
                students[i].studentId,
                students[i].sex,
                students[i].age,
                students[i].className,
                students[i].phone);
    }

    fclose(fp);
    printf("数据已成功保存到文件 %s\n", filename);
}

void loadStudentsFromFile(struct studentModel students[], int length, const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("未找到数据文件 %s，将创建新文件。\n", filename);
        return;
    }

    struct studentModel temp;
    int count = 0;

    while (fscanf(fp, "%19s %u %d %u %19s %19s",
                  temp.name,
                  &temp.studentId,
                  &temp.sex,
                  &temp.age,
                  temp.className,
                  temp.phone) == 6)
    {
        if (count < length)
        {
            students[count++] = temp;
        }
    }

    fclose(fp);
    printf("已从文件 %s 读取 %d 条学生数据。\n", filename, count);
}
