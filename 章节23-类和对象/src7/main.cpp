#include <iostream>

using namespace std;

namespace _nmsp1
{
  class ThirdPartClass
  {
  public:
  };

  class B : public ThirdPartClass
  {
  public:
    char *m_p;

    B()
    {
      m_p = new char[100];
    }

    ~B()
    {
      delete m_p;
    }
  };

  void func()
  {
    ThirdPartClass *mb = new B(); // 父类指针指向子类对象
    delete mb;                    // 因为父类中并没有提供虚析构函数，所以该行内存释放并不会执行子类的析构函数
                                  // 所以这里就会造成子类 m_p 这100字节的内存泄漏。
  }
}

int main()
{
  cout << "Hello World";

  return 0;
}