#ifndef STUDENT_MODEL_H
#define STUDENT_MODEL_H

struct studentModel
{
    /** 学生姓名 */
    char name[20];

    /** 学生学号 */
    unsigned int studentId;

    /** 学生性别 男:1 或者女:0 , 未知:-1 */
    int sex;

    /** 学生年龄 */
    unsigned int age;

    /** 学生班级 */
    char className[20];

    /** 学生电话 */
    char phone[20];
};

#endif
