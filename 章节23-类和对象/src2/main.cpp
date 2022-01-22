#include <iostream>
#include <cstring>

using namespace std;

namespace _nmsp1
{
  class A
  {
  public:
    // 构造函数
    A() : m_caa(0), m_cab(0) {}
    // 拷贝构造函数
    A(const A &tmpA) : m_caa(tmpA.m_caa), m_cab(tmpA.m_cab) {}

    // 拷贝赋值运算符
    A &operator=(const A &tmpA)
    {
      m_caa = tmpA.m_caa;
      m_cab = tmpA.m_cab;
      return *this;
    }

  public:
    int m_caa;
    int m_cab;
  };

  void func()
  {
    A gc1;
    gc1.m_caa = 100;
    gc1.m_cab = 200;

    // 调用拷贝构造函数
    A gc2(gc1);
    std::cout << gc2.m_caa << std::endl; // 100
    std::cout << gc2.m_cab << std::endl; // 200

    // 调用拷贝构造函数
    A gc3 = gc1;
    std::cout << gc3.m_caa << std::endl; // 100
    std::cout << gc3.m_cab << std::endl; // 200

    A gc4;
    // 调用拷贝赋值运算符
    gc4 = gc3;
  }
}

namespace _nmsp2
{
  class A
  {
  public:
    // 构造函数
    A() : m_caa(0), m_cab(0), m_cpp(new char[100]) {}
    ~A() // 析构函数
    {
      delete[] m_cpp;
    }

    // 拷贝构造函数
    A(const A &tmpA) : m_caa(tmpA.m_caa), m_cab(tmpA.m_cab)
    {
      // 数组的拷贝构造
      m_cpp = new char[sizeof(tmpA.m_cpp)];
      memcpy(m_cpp, tmpA.m_cpp, sizeof(tmpA.m_cpp));
    }

    // 拷贝赋值运算符
    // A& operator=(const A& tmpA)
    // {
    //     // 判断是不是自己（自己给自己赋值）
    //     if(this == &tmpA)
    //     {
    //         return *this;
    //     }

    //     // 数组的拷贝赋值
    //     // 原来已经有了（在执行构造函数的时候new出来的）
    //     // 所以这里得先将拷贝构造里new出来的先释放掉
    //     delete[] m_cpp;
    //     m_cpp = new char[sizeof(tmpA.m_cpp)];
    //     memcpy(m_cpp, tmpA.m_cpp, sizeof(tmpA.m_cpp));

    //     m_caa = tmpA.m_caa;
    //     m_cab = tmpA.m_cab;
    //     return *this;
    // }

    A &operator=(const A &tmpA)
    {
      // 先生成一个临时的指针，来分配这拷贝的字节
      char *ptmp = new char[sizeof(tmpA.m_cpp)];
      // 然后将待拷贝的内容拷贝到这个临时指针中
      memcpy(ptmp, tmpA.m_cpp, sizeof(tmpA.m_cpp));

      // 然后这个时候，再把自己的内存进行释放
      delete[] m_cpp;
      // 然后在把这个临时指针中的内容拷贝到本m_cpp中，完成拷贝
      m_cpp = ptmp;

      m_caa = tmpA.m_caa;
      m_cab = tmpA.m_cab;
      return *this;
    }

  public:
    int m_caa;
    int m_cab;
    char *m_cpp; // 指向定长100的数组
  };

  void func()
  {
    A obj1;
    obj1.m_caa = 100;
    obj1.m_cab = 200;
    A obj2 = obj1; // 调用拷贝构造函数
    obj2 = obj1;   // 调用拷贝赋值运算符

    strcpy(obj2.m_cpp, "asfdfgsdg"); // 给对象obj2的成员m_cpp拷贝一个字符串

    // 自己给自己赋值
    // 自己肯定不会这么写，但是不排除某些代码书写上的原因，导致产生类似的效果
    obj2 = obj2;
    // 这行代码会照成什么后果，
    // 因为这行代码执行的是拷贝赋值运算符，所以对于我们现在这个范例，在执行拷贝赋值运算符的时候
    // 就会导致在进行成员 m_cpp的拷贝的时候，因为首先要把原来的m_cpp释放掉，然后在new一个新的地址，
    // 然后将拷贝对象的m_cpp拷贝给这块内存，那如果是自己给自己赋值，这里就会出现在delete的时候，
    // 把原对象和目标对象都给释放掉（因为原对象和拷贝对象都是自己），就会导致memcpy执行为空，啥也没拷贝到
    std::cout << obj2.m_cpp << std::endl;
  }
}

namespace _nmsp3
{
  class A
  {
  public:
    // 构造函数
    A() : m_caa(0), m_cab(0), m_cpp(new char[100]) {}
    virtual ~A() // 析构函数
    {
      delete[] m_cpp;
    }

    // 拷贝构造函数
    A(const A &tmpA) : m_caa(tmpA.m_caa), m_cab(tmpA.m_cab)
    {
      // 数组的拷贝构造
      m_cpp = new char[sizeof(tmpA.m_cpp)];
      memcpy(m_cpp, tmpA.m_cpp, sizeof(tmpA.m_cpp));
    }

    // 拷贝赋值运算符
    A &operator=(const A &tmpA)
    {
      // 判断是不是自己（自己给自己赋值）
      if (this == &tmpA)
      {
        return *this;
      }

      // 数组的拷贝赋值
      // 原来已经有了（在执行构造函数的时候new出来的）
      // 所以这里得先将拷贝构造里new出来的先释放掉
      delete[] m_cpp;
      m_cpp = new char[sizeof(tmpA.m_cpp)];
      memcpy(m_cpp, tmpA.m_cpp, sizeof(tmpA.m_cpp));

      m_caa = tmpA.m_caa;
      m_cab = tmpA.m_cab;
      return *this;
    }

  public:
    int m_caa;
    int m_cab;
    char *m_cpp; // 指向定长100的数组
  };

  class B : public A
  {
  public:
    B() {}
    B(const B &tmpB) : A(tmpB) // 类B的拷贝构造函数
    {
      // 手动调用父类的拷贝构造函数
      // 这里掉一共父类的拷贝构造函数（或者调用父类构造函数）只能在初始化列表中书写
      // 在函数体中写会报语法错的
    }
    B &operator=(const B &tmpB) // 类B的拷贝赋值运算符
    {
      // 手动调用父类的拷贝赋值运算符
      A::operator=(tmpB);
      return *this;
    }
  };

  void func()
  {
    B bobj1;
    bobj1.m_caa = 109;
    bobj1.m_cab = 243;
    strcpy(bobj1.m_cpp, "tisdgasdgajksd");

    B bobj2 = bobj1;
    // 在没有自己的拷贝构造函数的时候
    // 执行类A的拷贝构造函数
    bobj2 = bobj1;
    // 在没有自己的拷贝赋值运算符的时候
    // 执行类A的拷贝赋值运算符
  }
}

int main()
{
  // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  // 本行代码可以在程序退出的时候检测内存泄漏并输出到窗口（windows vs下才能使用）

  // _nmsp1::func();

  // _nmsp2::func();

  _nmsp3::func();
  return 0;
}