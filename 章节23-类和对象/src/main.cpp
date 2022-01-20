#include <iostream>
#include "class1.h"
#include "class2.h"

using namespace std;

CLASS1 gc1;
// CLASS2 gc2;

namespace _nmsp1
{
    class A
    {
    public:
        A()
        {
            m_i = 0;
            std::cout << "A::A()缺省构造函数执行了" << std::endl;
        }
        ~A()
        {
            std::cout << "析构函数执行了" << std::endl;
        }
        
        int m_i;
    };
    
    class B
    {
    public:
        static A m_sa;  // 静态成员变量声明（声明是没有分配内存空间的）
        
        // 如果在main中没有用到类B的静态成员变量m_sa的话，这里只声明不定义是可以的。
    };
    
    A B::m_sa;  // 这行是堆类B的静态成员变量m_sa的定义
    
    // 对于这行静态成员定义行为，假如我们在main中既没有用到类B，更没有用到类B的静态成员变量m_sa
    // 那么我们在执行程序的时候，会发现类A的构造和析构执行了
    // 这就说明该行静态成员比变量定义行为被执行了
    // 那这里就会很郁闷，我明明在程序中都没有用到类B，也没有用到类B的静态成员m_sa
    
    // 所以这里就证明了，类中的静态类类型成员变量，即使没有被使用，也会被构造和析构。
    // 只要你有静态成员变量的定义代码，对静态成员变量进行了定义，静态成员变量就会被分配内存空间
    // （对应到类类型静态成员变量上，就是会被构造和析构）
    
    // inline这个关键字，一般用来声明内联函数，但是在C++17中引入了一个叫做 “inline 静态成员变量” 
    // 有了这个inline之后，我们就不用再类B之外的某个.cpp源文件中对类B的静态成员变量进行定义了
    // 我们只需要在类B内，声明这个静态成员变量的时候前面加一个inline就可以了

    
    class C
    {
    public:
        inline static A m_sa;
        // inline在c++17中，放在静态成员变量之前，就表示该静态成员变量即声明，又定义
    };
    
}

namespace _nmsp2
{
    class AF
    {
    public:
        AF()
        {
            m_i = 0;
            std::cout << "AF::AF()缺省构造函数执行了" << std::endl;
        }
        ~AF()
        {
            std::cout << "AF析构函数执行了" << std::endl;
        }
        
        int m_i;
    };
    
    // -------------------------------------
    void myfunc()
    {
        static AF obja;
        
    }
}

int main()
{
    _nmsp1::B bobj;
    // 没有使用到类B的静态成员变量，所以就算静态成员变量没有定义，也不会报错，是允许的
    
    std::cout << bobj.m_sa.m_i << std::endl;
    // 这个时候用到了类B的静态成员变量m_sa，但是m_sa此时此刻只声明没有进行定义，所以会报链接错误
    // undefined reference to `_nmsp1::B::m_sa'
    
    std::cout << _nmsp1::C::m_sa.m_i << std::endl;

    return 0;
}