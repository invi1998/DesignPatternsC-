#include <iostream>

using namespace std;

namespace _nmsp1
{
  class A
  {
  public:
    explicit A(int a)
    {
      std::cout << a << std::endl;
    }
  };

  void func()
  {
    // A obj = 15;
    // 15
    // 这行代码导致类A的构造函数执行了。这行代码发生了隐式类型装换
    // 加了explicit之后，本行代码就报编译错误，无法将15隐式转换为A类型对象
    // 就得将代码改为
    A obj = A(15);
  }
}

namespace _nmsp2
{
  class A
  {
  private:
    // 重载new操作符
    static void *operator new(size_t size);

    // 重载delete操作符
    static void operator delete(void *phead);

    // 禁止new 数组
    static void *operator new[](size_t szie);
    // 禁止delete数组
    static void operator delete[](void *phead);
  };

  void func()
  {
    // 这样就达到了无法使用new（也就是强制不能再堆上分配内存的效果）

    A *pa = new A;
    // 无法调用私有 new
    delete pa;
    // 无法调用私有 delete

    A *ar = new A[2]();
    // 也不行
    delete[] ar;
    // 也不行
  }
}

namespace _nmsp3
{
  class A
  {
  public:
    void destroy()
    {
      delete this;
    }

  private:
    ~A() {}
  };

  void func()
  {
    A a;
    // 无法成功编译，因为他的析构函数是private修饰

    A *pa = new A;
    // delete pa;   // 不行，析构函数private修饰，没办法成功调用
    pa->destroy(); // 释放内存
  }
}

int main()
{
  _nmsp1::func();

  return 0;
}