#include <iostream>
#include "class1.h"
#include "class2.h"
#include "func.h"

using namespace std;


// 该函数返回的是一个静态局部对象的引用（这里用这个静态局部对象替换了之前的那个全局对象）
CLASS2& getClass2Obj()
{
    static CLASS2 gc2;
    return gc2;
}

CLASS2::CLASS2():m_i(100)
{
    std::cout << "CLASS2::CLASS2()构造函数执行了" << std::endl;
}

CLASS2::~CLASS2()
{
    std::cout << "CLASS2::~CLASS2()析构函数执行了" << std::endl;
}