#include <iostream>

using namespace std;

namespace _nmsp1
{
  class Anew
  {
  public:
    Anew()
    {
      f1();
    }
    virtual ~Anew()
    {
      f2();
    }

    // 定义两个虚函数
    virtual void f1()
    {
      std::cout << "虚函数Anew::f1()执行了" << std::endl;
    }

    virtual void f2()
    {
      std::cout << "虚函数Anew::f2()执行了" << std::endl;
    }

    void AClassFunc()
    {
      f1();
    }
  };

  class Bnew : public Anew
  {
  public:
    Bnew()
    {
      f1();
    }

    ~Bnew()
    {
      f2();
    }

  public:
    virtual void f1()
    {
      std::cout << "虚函数Bnew::f1()执行了" << std::endl;
    }

    virtual void f2()
    {
      std::cout << "虚函数Bnew::f2()执行了" << std::endl;
    }
  };

  void func()
  {
    Anew *pnew = new Bnew();
    std::cout << "-----------------begin---------------" << std::endl;

    pnew->f1();
    pnew->f2();
    pnew->AClassFunc();

    std::cout << "-----------------end---------------" << std::endl;

    delete pnew;

    // 虚函数Anew::f1()执行了
    // 虚函数Bnew::f1()执行了
    // -----------------begin---------------
    // 虚函数Bnew::f1()执行了
    // 虚函数Bnew::f2()执行了
    // ��函数Bnew::f1()执行了
    // -----------------end---------------
    // 虚函数Bnew::f2()执行了
    // 虚函数Anew::f2()执行了

    // 结果中的第一行，展示了类Anew的构造函数中，针对f1虚函数的调用。调用的是类Anew构造函数中的虚函数调用
    // 结果中最后一行，展示了类Anew析构函数中，针对f2（）的调用,实际上调用的是Anew中的虚函数，并不是Bnew中的f2虚函数
  }
}

namespace _nmsp2
{
  class Anew2
  {
  protected:
    ~Anew2()
    {
    }
  };

  class Bnew2 : public Anew2
  {
  };

  // 可以看到，仅仅是使用protected修饰析构函数，就达到了如下几个效果（目的）
  void func()
  {
    Anew2 aobj; // 报错
    // 无法创建父类对象

    Anew2 *paobj = new Anew2;

    delete paobj; // 报错
    // 无法让父类指针指向子类对象（这里表现为只能new，不能delete）

    Anew2 *paobj2 = new Bnew2;

    delete paobj2; // 报错

    Bnew2 *pbobj = new Bnew2;
    // 子类指针指向子类对象
    delete pbobj;
    // 也能成功delete
  }
}

namespace _nmsp3
{
  class PVC
  {
  protected:
    PVC() {} // 构造函数

    PVC(const PVC &) {} // 拷贝构造函数
  };

  clas subPVC : public PVC{};

  // 因为父类的构造函数和拷贝构造函数都使用了protected修饰，这样做就导致没办法生成父类对象，
  // 而只能创建子类subPVC类对象
  void func()
  {
    subPVC obj1;       // 构造函数
    subPVC obj2(obj1); // 使用obj1来拷贝构造
  }
}

namespace _nmsp4
{
  class PVC
  {
  public:
    // 析构函数设置为纯虚函数
    virtual ~PVC() = 0;
  };

  // 类外实现类析构函数（纯虚函数绝大部门都是没有实现体的，但是这里纯虚析构函数是个特例）
  // 这里为了释放资源，所以这里要有实现体
  PVC::~PVC()
  {
  }

  class subPVC : public SVC
  {
  public:
    // 父类中的这个析构函数是虚函数，那么子类中这个不加virtua也是虚函数
    ~subPVC()
    {
    }
  };

  void func()
  {
    subPVC obj1; // 析构时，编译器会先执行该类自己的析构函数，再执行父类的析构函数体

    PVC *p = new subPVC;
    delete p; // delete p的时候，同样会先执行该类自己的析构函数，再执行父类的析构函数
  }
}

namespace _nmsp5
{
  class PVC
  {
  protected:
    ~PVC()
    {
    }
  };

  class subPVC : public PVC
  {
  };

  void func()
  {
    subPVC obj1;
    subPVC obj2(obj1);
    subPVC *obj3 = new subPVC();

    delete obj3;

    PVC obj4;       // 不可以，报错，不能创建父类对象
    PVC obj5(obj4); //  也不可以，报错，不能拷贝构造父类对象

    PVC *obj5 = new PVC;
    delete obj5; // 这行报错，不能delete（能new不能delete，也就相当于不能创建对象）
    PVC *obj6 = new subPVC;
    delete obj6; // 这行报错，也是不能delete
  }
}

int main()
{
  // _nmsp1::func();

  // _nmsp2::func();

  _nmsp3::func();

  _nmsp4::func();

  return 0;
}