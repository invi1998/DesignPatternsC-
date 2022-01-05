/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>

using namespace std;

namespace _nmsp1
{
  // 怪物父类
  class Monster
  {
  public:
    // 构造函数
    Monster(int life, int magic, int attack) : m_life(life), m_magic(magic), m_attack(attack)
    {
    }

    virtual ~Monster() {}

  public:
    virtual Monster *clone() = 0;
    // 怪物创建函数，具体实现放在子类中，遵从原型模式的一般规范，这个函数命名为clone

    // 属性可能会被子类访问，所以这里用protected修饰
  protected:
    int m_life;
    int m_magic;
    int m_attack;
  };

  // 亡灵类
  class M_Undead : public Monster
  {
  public:
    M_Undead(int life, int magic, int attack) : Monster(life, magic, attack)
    {
      std::cout << "一个亡灵怪物出现了" << std::endl;
    }

    Monster *clone()
    {
      // return new M_Undead(500, 100, 60);
      // 调用类的拷贝构造函数实现真正的克隆
      return new M_Undead(*this);
      // 触发拷贝构造函数的调用来创建亡灵类怪物
    }

    // 拷贝构造函数
    // 注意初始化列表中对父类子对象的初始化
    M_Undead(const M_Undead &tmpobj) : Monster(tmpobj)
    {
      std::cout << "调用了 M_Undead::M_Undead拷贝构造函数，创建了一只亡灵怪物" << std::endl;
    }
  };

  // 元素类
  class M_Element : public Monster
  {
  public:
    M_Element(int life, int magic, int attack) : Monster(life, magic, attack)
    {
      std::cout << "一个元素怪物出现了" << std::endl;
    }

    Monster *clone()
    {
      // return new M_Element(700, 300, 30);
      return new M_Element(*this);
      // 触发拷贝构造函数的调用来创建元素类怪物
    }

    // 拷贝构造函数
    // 注意初始化列表中对父类子对象的初始化
    M_Element(const M_Element &tmpobj) : Monster(tmpobj)
    {
      std::cout << "调用了 M_Element::M_Element拷贝构造函数，创建了一只元素怪物" << std::endl;
    }
  };

  // 机械类
  class M_Mechainc : public Monster
  {
  public:
    M_Mechainc(int life, int magic, int attack) : Monster(life, magic, attack)
    {
      std::cout << "一个机械怪物出现了" << std::endl;
    }

    Monster *clone()
    {
      // return new M_Mechainc(1000, 0, 50);
      return new M_Mechainc(*this);
      // 触发拷贝构造函数的调用来创建机械类怪物
    }

    // 拷贝构造函数
    // 注意初始化列表中对父类子对象的初始化
    M_Mechainc(const M_Mechainc &tmpobj) : Monster(tmpobj)
    {
      std::cout << "调用了 M_Mechainc::M_Mechainc拷贝构造函数，创建了一只机械怪物" << std::endl;
    }
  };

  // 这种clone方法其实在某些情况下也会给开发带来便利
  // 比如有如下需求，实现一个全局函数，要求用于创建怪物对象
  // 同时要求创建的怪物类型要和所指向的（传递进来的）怪物类型类型相同，那这里就要用 dynamic_cast
  // 进行类型判断，判断参数 pMonster 到底是什么类型
  void Gbl_CreateMonster(Monster *pMonster)
  {
    Monster *ptmpobj = nullptr;
    if (dynamic_cast<M_Undead *>(pMonster) != nullptr)
    {
      // 判断是亡灵类
      ptmpobj = new M_Undead(300, 200, 43);
    }
    else if (dynamic_cast<M_Mechainc *>(pMonster) != nullptr)
    {
      // 判断为机械类怪物
      ptmpobj = new M_Mechainc(2100, 3, 33);
    }
    else if (dynamic_cast<M_Element *>(pMonster) != nullptr)
    {
      // 判断为元素类怪物
      ptmpobj = new M_Element(899, 200, 44);
    }

    if (ptmpobj != nullptr)
    {
      // ..........

      // ..........
      // 释放资源
      delete ptmpobj;
    }
  }

  // 如果Monster的每个子类都提供了clone方法，那么 Gbl_CreateMonster 函数的实现就简单多了
  // 根本就不需要判断 pMonster 指向的子类的实际类型，直接可用利用已有的对象来创建新对象
  void Gbl_CreateMonster2(Monster *pMonster)
  {
    Monster *ptmpobj = pMonster->clone();
    // 根据已有对象直接创建新对象，不需要知道已有对象的类型

    if (ptmpobj != nullptr)
    {
      // ..........

      // ..........
      // 释放资源
      delete ptmpobj;
    }
  }

}

int main()
{
  _nmsp1::M_Mechainc mPropMecMonster(900, 219, 76);
  // 创建一只机械怪物，该对象作为原型对象用于克隆的目的(栈上创建)

  _nmsp1::Monster *mPropEleMonster = new _nmsp1::M_Element(500, 429, 46);
  // 创建一只元素怪物，该对象作为原型对象用于克隆的目的(堆上创建)

  _nmsp1::Monster *pClone1 = mPropEleMonster->clone();
  // 使用原型对象clone出新的元素类

  _nmsp1::Monster *pClone2 = mPropMecMonster.clone();
  // 使用原型对象clone出新的机械类

  // 一个机械怪物出现了
  // 一个元素怪物出现了
  // 调用了 M_Element::M_Element拷贝构造函数，创建了�只元素怪物
  // 调用了 M_Mechainc::M_Mechainc拷贝构造�数，创建了一只机械怪��

  delete pClone2;
  delete pClone1;

  delete mPropEleMonster;

  return 0;
}
