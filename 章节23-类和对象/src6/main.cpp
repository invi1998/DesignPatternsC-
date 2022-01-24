#include <iostream>

using namespace std;

namespace _nmsp1
{
  class A
  {
  public:
    //  默认构造函数
    A() {}

    // 禁止拷贝构造
    A(const A &tmpa) = delete;

    // 禁止拷贝赋值
    A &operator=(const A &tmpa) = delete;
  };

  void func()
  {
    A obj1;
    // A obj2(obj1);   // 拷贝构造
    A obj3;
    // obj3 = obj1;    // 拷贝赋值
  }
}

namespace _nmsp2
{
  class A
  {
  public:
    //  默认构造函数
    A() {}

  public:
    void func(const A &tmpa)
    {
      *this = tmpa; // 这个写法就会调用拷贝赋值运算符
      A obj2(tmpa); // 这个写法就会调用拷贝构造函数
    }

  private:
    // 禁止拷贝构造
    A(const A &tmpa){};

    // 禁止拷贝赋值
    A &operator=(const A &tmpa)
    {
      return *this;
    };
  };

  void func()
  {
    A obj1;
    // A obj2(obj1);   // 拷贝构造
    A obj3;
    // obj3 = obj1;    // 拷贝赋值
  }
}

namespace _nmsp3
{
  class noncopyable
  {
  protected: // 值允许被类或者子类对象进行访问
    noncopyable() {}
    ~noncopyable() {}

  private:
    noncopyable(const noncopyable &);
    noncopyable &operator=(const noncopyable &);
  };

  // 然后将你的类私有继承这个 noncopyable 类
  class A : private noncopyable
  {
  public:
    void func(const A &tmpa)
    {
      *this = tmpa; // 这个写法就会调用拷贝赋值运算符
      A obj2(tmpa); // 这个写法就会调用拷贝构造函数
    }
  };
}

int main()
{
  _nmsp1::func();

  return 0;
}