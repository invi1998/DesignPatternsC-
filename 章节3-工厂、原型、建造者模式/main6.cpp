/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

// 情景模拟
// 怪物：亡灵类，元素类，机械类
// 怪物组成：头部，躯干，肢体，3个部分组成，这几个部分的模型都是分开制作的，

// 编码步骤：
// 将怪物躯干信息读入内存，将怪物头部信息和肢体读入内存，将头部和肢体模型以正确的位置和反向挂接到躯干上
// 最终装配出完整的怪物模型
// Assemble, LoadTrunkMode, LoadHeadMode, LoadLimbsMode这几个函数称为构建过程相关的函数

namespace _nmsp1
{
  // 怪物父类
  class Monster
  {
  public:
    virtual ~Monster() {}

    // 装配函数
    void Assemble(string strmodelNo) // strmodelNo 模型编号 形如“12992329532990”这种字符串
    {
      LoadTrunkMode(strmodelNo.substr(4, 3));  // 载入躯干模型，截取部分字符串以表示躯干编号
      LoadHeadMode(strmodelNo.substr(7, 3));   // 载入头部模型，截取部分字符串以表示头部编号
      LoadLimbsMode(strmodelNo.substr(10, 3)); // 载入肢体模型，截取部分字符串以表示肢体编号

      // 将模型挂接到躯干。。。。
    }

    // 载入躯干
    virtual void LoadTrunkMode(string strNo) = 0;

    // 载入头部
    virtual void LoadHeadMode(string strNo) = 0;

    // 载入肢体
    virtual void LoadLimbsMode(string strNo) = 0;
  };

  // 亡灵类
  class M_Undead : public Monster
  {
  public:
    // 载入躯干
    void LoadTrunkMode(string strNo)
    {
      std::cout << "载入亡灵类躯干模型....." << std::endl;
    }

    // 载入头部
    void LoadHeadMode(string strNo)
    {
      std::cout << "载入亡灵类头部模型.....将模型挂接到躯干......" << std::endl;
    }

    // 载入肢体
    void LoadLimbsMode(string strNo)
    {
      std::cout << "载入亡灵类肢体模型.....将模型挂接到躯干......" << std::endl;
    }
  };

  // 元素类
  class M_Element : public Monster
  {
  public:
    // 载入躯干
    void LoadTrunkMode(string strNo)
    {
      std::cout << "载入元素类躯干模型....." << std::endl;
    }

    // 载入头部
    void LoadHeadMode(string strNo)
    {
      std::cout << "载入元素类头部模型.....将模型挂接到躯干......" << std::endl;
    }

    // 载入肢体
    void LoadLimbsMode(string strNo)
    {
      std::cout << "载入元素类肢体模型.....将模型挂接到躯干......" << std::endl;
    }
  };

  // 机械类
  class M_Mechanic : public Monster
  {
  public:
    // 载入躯干
    void LoadTrunkMode(string strNo)
    {
      std::cout << "载入机械类躯干模型....." << std::endl;
    }

    // 载入头部
    void LoadHeadMode(string strNo)
    {
      std::cout << "载入机械类头部模型.....将模型挂接到躯干......" << std::endl;
    }

    // 载入肢体
    void LoadLimbsMode(string strNo)
    {
      std::cout << "载入机械类肢体模型.....将模型挂接到躯干......" << std::endl;
    }
  };
}

// 引入与怪物类同层次的相关的构建器类，把怪物类相关的构建代码迁移到构建器中

namespace _nmsp2
{
  // 怪物父类
  class Monster
  {
  public:
    virtual ~Monster() {}
  };

  // 亡灵类
  class M_Undead : public Monster
  {
  };

  // 元素类
  class M_Element : public Monster
  {
  };

  // 机械类
  class M_Mechanic : public Monster
  {
  };

  // ------------------------------
  // 怪物构建器父类
  class MonsterBuilder
  {
  public:
    virtual ~MonsterBuilder() {}

    // // 装配函数
    // void Assemble(string strmodelNo)    // strmodelNo 模型编号 形如“12992329532990”这种字符串
    // {
    //     LoadTrunkMode(strmodelNo.substr(4, 3));    // 载入躯干模型，截取部分字符串以表示躯干编号
    //     LoadHeadMode(strmodelNo.substr(7, 3));    // 载入头部模型，截取部分字符串以表示头部编号
    //     LoadLimbsMode(strmodelNo.substr(10, 3));    // 载入肢体模型，截取部分字符串以表示肢体编号

    // }

    // 载入躯干
    virtual void LoadTrunkMode(string strNo) = 0;

    // 载入头部
    virtual void LoadHeadMode(string strNo) = 0;

    // 载入肢体
    virtual void LoadLimbsMode(string strNo) = 0;

    // 返回指向Monster类的成员变量指针 m_pMonster
    // 目的：当一个复杂的对象构造完成后可以通过该成员函数把对象返回
    Monster *GetResult()
    {
      return m_pMonster;
    }

  protected:
    Monster *m_pMonster;
    // 指向Monster类的成员变量指针
  };

  // ------------------------------
  // 亡灵类怪物构建器类
  class M_UndeadBuilder : public MonsterBuilder
  {
  public:
    // 构造函数
    M_UndeadBuilder()
    {
      m_pMonster = new M_Undead();
    }

    // 载入躯干
    void LoadTrunkMode(string strNo)
    {
      std::cout << "载入亡灵类躯干模型....." << std::endl;
      // 具体要做的事情其实是委托给怪物子类完成，委托指的是把本该自己实现的功能转给其他类实现
      // m_pMonster->....
    }

    // 载入头部
    void LoadHeadMode(string strNo)
    {
      std::cout << "载入亡灵类头部模型.....将模型挂接到躯干......" << std::endl;
      // m_pMonster->....
    }

    // 载入肢体
    void LoadLimbsMode(string strNo)
    {
      std::cout << "载入亡灵类肢体模型.....将模型挂接到躯干......" << std::endl;
      // m_pMonster->....
    }
  };

  // 元素类怪物构建器类
  class M_ElementBuilder : public MonsterBuilder
  {
  public:
    // 构造函数
    M_ElementBuilder()
    {
      m_pMonster = new M_Element();
    }

    // 载入躯干
    void LoadTrunkMode(string strNo)
    {
      std::cout << "载入元素类躯干模型....." << std::endl;
    }

    // 载入头部
    void LoadHeadMode(string strNo)
    {
      std::cout << "载入元素类头部模型.....将模型挂接到躯干......" << std::endl;
    }

    // 载入肢体
    void LoadLimbsMode(string strNo)
    {
      std::cout << "载入元素类肢体模型.....将模型挂接到躯干......" << std::endl;
    }
  };

  // 机械类怪物构建器类
  class M_MechanicBuilder : public MonsterBuilder
  {
  public:
    // 构造函数
    M_MechanicBuilder()
    {
      m_pMonster = new M_Mechanic();
    }

    // 载入躯干
    void LoadTrunkMode(string strNo)
    {
      std::cout << "载入机械类躯干模型....." << std::endl;
    }

    // 载入头部
    void LoadHeadMode(string strNo)
    {
      std::cout << "载入机械类头部模型.....将模型挂接到躯干......" << std::endl;
    }

    // 载入肢体
    void LoadLimbsMode(string strNo)
    {
      std::cout << "载入机械类肢体模型.....将模型挂接到躯干......" << std::endl;
    }
  };

  // ------------------------------
  // 创建一个指挥者类
  class MonsterDirector
  {
  public:
    // 构造函数
    MonsterDirector(MonsterBuilder *ptmBuilder)
    {
      m_pMonsterBuilder = ptmBuilder;
    }

    // 指定新的构建器(该函数就可以让程序后期自行随意更改构建器)
    void SetBuilder(MonsterBuilder *ptmBuilder)
    {
      m_pMonsterBuilder = ptmBuilder;
    }

    // 装配函数
    // 原 MonsterBuilder中的Assemble成员函数迁移到该指挥类
    Monster *Construct(string strmodelNo) // strmodelNo 模型编号 形如“12992329532990”这种字符串
    {
      m_pMonsterBuilder->LoadTrunkMode(strmodelNo.substr(4, 3));  // 载入躯干模型，截取部分字符串以表示躯干编号
      m_pMonsterBuilder->LoadHeadMode(strmodelNo.substr(7, 3));   // 载入头部模型，截取部分字符串以表示头部编号
      m_pMonsterBuilder->LoadLimbsMode(strmodelNo.substr(10, 3)); // 载入肢体模型，截取部分字符串以表示肢体编号

      return m_pMonsterBuilder->GetResult();
      // 返回构建后的对象
    }

  private:
    // 同样的，就需要在该指挥类中放一个指向MonsterBuilder类的指针
    MonsterBuilder *m_pMonsterBuilder;
    // 指向所有构建器父类
  };

}

int main()
{
  _nmsp1::Monster *pm1 = new _nmsp1::M_Mechanic();

  pm1->Assemble("98723529927932579");
  // 载入机械类躯干模型.....
  // 载入机械类头部模型.....将模型挂接到躯干......
  // 载入机械类肢体模型.....将模型挂接到躯干......

  // 先生成生成器
  _nmsp2::MonsterBuilder *pMonsterBuilder = new _nmsp2::M_UndeadBuilder();
  // 创建亡灵类怪物构建器

  _nmsp2::MonsterDirector *pDierector = new _nmsp2::MonsterDirector(pMonsterBuilder);

  // 创建怪物
  _nmsp2::Monster *pm2 = pDierector->Construct("98723529927932579");
  // 这里就构建出了一个完整的怪物对象

  // 载入亡灵类躯干模型.....
  // 载入亡灵类头部模型.....将模型挂接到躯干......
  // 载入亡灵类肢体模型.....将模型挂接到躯干......

  // 释放资源
  delete pm1;
  delete pMonsterBuilder;
  delete pDierector;
  delete pm2;

  return 0;
}
