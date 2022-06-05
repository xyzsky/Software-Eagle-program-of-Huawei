/*
 * @Author: xyz
 * @Date: 2022-06-02 17:44:11
 * @LastEditTime: 2022-06-06 04:59:00
 * @LastEditors: xyz
 * @Description: 
 * @FilePath: \C语言\test.c
 */
//附：测试代码
#include<stdio.h>
#define WARING(str) printf("%s, line = %d, file=%s, data=%s, time=%s\n", str, __LINE__, __FILE__, __DATE__, __TIME__)
#define x 5

#define y x + 1

#define z y *x / 2

typedef enum {
    E1 = 0,
    E2,
    E3 = 5,
    E4
}ENUM_1;
int main()
{
    WARING("test");
    int a;

    a = y;

    printf("%d\n", z);

    printf("%d\n", --a);
    printf("%d\n", sizeof(ENUM_1));
    return 0;
}