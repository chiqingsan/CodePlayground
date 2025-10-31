#include "./include/global.h"


/** 函数声明 */
void printStudent(const struct studentModel *student);
void addStudent(struct studentModel students[], int length);
void deleteStudent(struct studentModel students[], int length);
void updateStudent(struct studentModel students[], int length);
void queryStudent(struct studentModel students[], int length);

/** 辅助函数：安全读取单字符输入 */
char readChar()
{
    char c;
    scanf(" %c", &c);
    return c;
}

/** 主程序入口 */ 
int main()
{
    struct studentModel students[100] = {0};
    const char *dataFile = "students.txt";

    // 启动时加载
    loadStudentsFromFile(students, 100, dataFile);

    int choice;
    while (1)
    {
        printf("%s\n%s\n", welcome_statement, enter_boot);
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudent(students, 100);
            saveStudentsToFile(students, 100, dataFile); // 每次修改后自动保存
            break;
        case 2:
            deleteStudent(students, 100);
            saveStudentsToFile(students, 100, dataFile);
            break;
        case 3:
            updateStudent(students, 100);
            saveStudentsToFile(students, 100, dataFile);
            break;
        case 4:
            queryStudent(students, 100);
            break;
        case 5:
            for (size_t i = 0; i < 100; i++)
            {
                if (students[i].studentId == 0)
                    break;
                printf("第%zu位学生信息：\n", i + 1);
                printStudent(&students[i]);
                printf("------------------------------------------------------\n");
            }
            printf("已显示所有学生信息。\n\n");
            break;
        case 6:
            printf("退出系统！\n");
            saveStudentsToFile(students, 100, dataFile);
            return 0;
        default:
            printf("输入错误，请重新输入。\n");
        }
    }
}

/** 添加学生 */
void addStudent(struct studentModel students[], int length)
{
    struct studentModel student;

    printf("%s\n", add_statement_name);
    scanf("%19s", student.name);

    printf("%s\n", add_statement_id);
    scanf("%u", &student.studentId);

    printf("%s\n", add_statement_sex);
    scanf(" %d", &student.sex);

    printf("%s\n", add_statement_age);
    scanf("%u", &student.age);

    printf("%s\n", add_statement_class);
    scanf("%19s", student.className);

    printf("%s\n", add_statement_phone);
    scanf("%19s", student.phone);

    printf("%s\n", add_statement_success);
    addElement(students, length, &student, sizeof(student));
}

/** 删除学生 */
void deleteStudent(struct studentModel students[], int length)
{
    int mode;
    printf("\n\n请输入数字进行操作\n1. 根据姓名删除\n2. 根据学号删除\n3. 返回上级菜单\n");
    scanf("%d", &mode);

    if (mode == 3)
        return;

    char name[20];
    unsigned int id = 0;
    if (mode == 1)
    {
        printf("请输入学生姓名：\n");
        scanf("%19s", name);
    }
    else if (mode == 2)
    {
        printf("请输入学生学号：\n");
        scanf("%u", &id);
    }

    for (size_t i = 0; i < length; i++)
    {
        if ((mode == 1 && strcmp(students[i].name, name) == 0) ||
            (mode == 2 && students[i].studentId == id))
        {
            printStudent(&students[i]);
            printf("确认删除该学生？(y/n)\n");
            if (readChar() == 'y')
            {
                deleteElement(students, length, i, sizeof(students[i]));
                printf("删除成功！\n");
            }
            return;
        }
    }
    printf("未找到匹配的学生信息。\n");
}

/** 修改学生 */
void updateStudent(struct studentModel students[], int length)
{
    int mode;
    printf("\n\n请输入数字进行操作\n1. 根据姓名修改\n2. 根据学号修改\n3. 返回上级菜单\n");
    scanf("%d", &mode);
    if (mode == 3)
        return;

    char name[20];
    unsigned int id = 0;
    if (mode == 1)
    {
        printf("请输入学生姓名：\n");
        scanf("%19s", name);
    }
    else
    {
        printf("请输入学生学号：\n");
        scanf("%u", &id);
    }

    for (size_t i = 0; i < length; i++)
    {
        if ((mode == 1 && strcmp(students[i].name, name) == 0) ||
            (mode == 2 && students[i].studentId == id))
        {
            struct studentModel new_student = students[i];
            int editing = 1;
            while (editing)
            {
                printf("请选择要修改的字段：\n");
                printf("1. 姓名\n2. 学号\n3. 性别\n4. 年龄\n5. 班级\n6. 电话\n7. 保存修改并退出\n");
                int field;
                scanf("%d", &field);
                switch (field)
                {
                case 1:
                    printf("新姓名: ");
                    scanf("%19s", new_student.name);
                    break;
                case 2:
                    printf("新学号: ");
                    scanf("%u", &new_student.studentId);
                    break;
                case 3:
                    printf("新性别(1男 0女 -1未知): ");
                    scanf("%d", &new_student.sex);
                    break;
                case 4:
                    printf("新年龄: ");
                    scanf("%u", &new_student.age);
                    break;
                case 5:
                    printf("新班级: ");
                    scanf("%19s", new_student.className);
                    break;
                case 6:
                    printf("新电话: ");
                    scanf("%19s", new_student.phone);
                    break;
                case 7:
                    editing = 0;
                    break;
                }
            }
            printf("修改后的信息为：\n");
            printStudent(&new_student);

            printf("确认保存修改？(y/n)\n");
            if (readChar() == 'y')
            {
                updateElement(students, length, i, &new_student, sizeof(students[i]));
                printf("修改成功！\n");
            }
            return;
        }
    }
    printf("未找到匹配的学生信息。\n");
}

/** 查询学生 */
void queryStudent(struct studentModel students[], int length)
{
    int mode;
    printf("\n\n请输入数字进行操作\n1. 按姓名查询\n2. 按学号查询\n3. 返回上级菜单\n");
    scanf("%d", &mode);
    if (mode == 3)
        return;

    char name[20];
    unsigned int id = 0;
    if (mode == 1)
    {
        printf("请输入学生姓名：\n");
        scanf("%19s", name);
    }
    else
    {
        printf("请输入学生学号：\n");
        scanf("%u", &id);
    }

    for (size_t i = 0; i < length; i++)
    {
        if ((mode == 1 && strcmp(students[i].name, name) == 0) ||
            (mode == 2 && students[i].studentId == id))
        {
            printStudent(&students[i]);
            return;
        }
    }
    printf("未找到匹配的学生信息。\n");
}

/** 打印学生结构体 */
void printStudent(const struct studentModel *s)
{
    printf("姓名：%s\n学号：%u\n性别：%d\n年龄：%u\n班级：%s\n电话：%s\n",
           s->name, s->studentId, s->sex, s->age, s->className, s->phone);
}
