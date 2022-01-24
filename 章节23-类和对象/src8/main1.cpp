#include <iostream>

using namespace std;

namespace _nmsp1
{
  class A1
  {
  public:
    int m_a;
  };

  class A2
  {
  public:
    int &getA()
    {
      return m_a;
    }

  private:
    int m_a;
  };

  void func()
  {
    A1 a1obj;
    a1obj.m_a = 10;
    std::cout << a1obj.m_a << std::endl;
    // 10
    A2 a2obj;
    a2obj.getA() = 110; // 因为getA返回的是一个左值引用，所以这里可以给左值赋值
    std::cout << a2obj.getA() << std::endl;
    // 110
  }
}

namespace _nmsp2
{
  class A
  {
  public:
    // 这里的myfunc其实就相当于myvirfunc的一个通道性质的代码
    // 像一个通道一样直接调用虚函数
    void myfunc()
    {
      myvirfunc();
    }

    virtual ~A() {}

  private:
    virtual void myvirfunc()
    {
      std::cout << "A::myvirfunc()虚函数执行了" << std::endl;
    }
  };

  class B : public A
  {
  private:
    virtual void myvirfunc()
    {
      std::cout << "B::myvirfunc()虚函数执行了" << std::endl;
    }
  };

  void func()
  {
    A *pobj = new B();
    pobj->myfunc();
    // B::myvirfunc()虚函数执行了

    // 当然如果正常情况下，父类的虚函数没有用private修饰的话，我们是可以正常访问的，不需要通过这个通道
    // pobj->A::myvirfunc();

    // 当然，这里就是因为父类不希望自己的 myvirfunc 虚函数被子类调用，所以他这里才使用private修饰

    delete pobj;
  }
}

int main()
{
  // _nmsp1::func();

  _nmsp2::func();

  return 0;
}