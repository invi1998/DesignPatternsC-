#include <iostream>

using namespace std;

namespace _nmsp1
{
  class Human
  {
  public:
    void eat()
    {
      std::cout << "人类吃食物！" << std::endl;
    }
    virtual ~Human() {}

    // 纯虚函数
    virtual void work() = 0;

    // 虚函数
    // virtual void avlife()
    // {
    //     std::cout << "人类平均寿命75岁" << std::endl;
    // }

    // 纯虚函数
    virtual void avlife() = 0;
  };

  // 父类纯虚函数的类外实现体
  void Human::avlife()
  {
    std::cout << "人类平均寿命75岁" << std::endl;
  }

  // 公有继承
  class Man : public Human
  {
  public:
    // void eat()
    // {
    //     std::cout << "男人喜欢吃面食" << std::endl;
    // }

    virtual void work()
    {
      std::cout << "男人做重体力工作" << std::endl;
    }

    virtual void avlife()
    {
      std::cout << "男人平均寿命70岁" << std::endl;
    }
  };

  class Women : public Human
  {
  public:
    virtual void work()
    {
      std::cout << "女人做轻体力工作" << std::endl;
    }

    virtual void avlife()
    {
      std::cout << "女人平均寿命80岁" << std::endl;
      // 调用父类的纯虚函数接口实现
      Human::avlife();
    }
  };
}

namespace _nmsp2
{
  class A
  {
  };
  class B : public A
  {
  };
  class C : public B
  {
  };

  void myfunc(A tmpa)
  {
    std::cout << "void myfunc(A tmpa)执行了" << std::endl;
  }

  void myfunc(B tmpb)
  {
    std::cout << "void myfunc(B tmpb)执行了" << std::endl;
  }

  void myfunc(C tmpc)
  {
    std::cout << "void myfunc(C tmpc)执行了" << std::endl;
  }

  void func()
  {
    B b1;
    myfunc(b1);
    // void myfunc(A tmpa)执行了
    // 可以看到传递进去一个B类型的实参，调用的是B类型的父类型重载版本的函数
    // 这是因为类B是通过public继承自类A的，因此，类B和类A是一种is-a关系（也就是子类对象一定是父类对象）
    // 也就是B类对象也一定是A类对象，所以这里调用的也就是形参为A类的myfunc()

    C c1;
    myfunc(c1);
    // void myfunc(C tmpc)执行了
  }
}

int main()
{
  _nmsp1::Man myman;
  myman.eat();
  // 男人喜欢吃面食

  // 子类调用父类的eat函数
  myman.Human::eat();
  // 人类吃食物！

  _nmsp1::Women myw;
  myw.avlife();
  // 女人平均寿命80岁
  // 人类平均寿命75岁

  std::cout << "**********************************************" << std::endl;
  _nmsp2::func();

  return 0;
}
