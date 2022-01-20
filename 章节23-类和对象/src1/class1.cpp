#include <iostream>
#include "class1.h"
#include "class2.h"
#include "func.h"

using namespace std;

// 外部变量声明
// extern CLASS2 gc2;

CLASS1::CLASS1()
{
    // std::cout << gc2.m_i << std::endl;// 0
    // 这里打印的是 0 而不是我们期望的100
    
    std::cout << getClass2Obj().m_i << std::endl;
    // 这里会报错说 getClass2Obj该函数为定义，为了解决这个定义问题，我们可以创建一个func.h头文件
    
    std::cout << "CLASS1::CLASS1()构造函数执行了" << std::endl;
}

CLASS1::~CLASS1()
{
    std::cout << "CLASS1::~CLASS1()析构函数执行了" << std::endl;
}