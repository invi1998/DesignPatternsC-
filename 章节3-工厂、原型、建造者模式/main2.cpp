/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby,
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>

using namespace std;

// 情景模拟
// 假设游戏中有三类怪物，亡灵类，元素类，机械类，都有生命值，蓝量，攻击力基本属性
// Monster作为父类，M_Undead（亡灵类），M_Element（元素类），M_Mechainc（机械类）
// 现在使用工厂方法模式进行改造，就需要为每个怪物类提供一个工厂，然后些工厂可以有一个基类工厂类
// M_UndeadFactory, M_ElementFactory, M_MechaincFactory,他们有一个共同父类，M_ParFactory (工厂抽象类)
// 符合开闭原则，付出的代价就是需要新增多个新的工厂类

namespace _nmsp1
{
  // 怪物基类
  class Monster
  {
  public:
    Monster(int life, int magic, int attack) : m_life(life), m_magic(magic), m_attack(attack)
    {
    }

    virtual ~Monster()
    {
    }

    // 可能会被子类访问的成员
  protected:
    int m_life;   // 生命值
    int m_magic;  // 蓝量
    int m_attack; // 攻击力
  };

  // 亡灵类
  class M_Undead : public Monster
  {
  public:
    M_Undead(int life, int magic, int attack) : Monster(life, magic, attack)
    {
      std::cout << "一个亡灵怪出现了" << std::endl;
    }
  };

  // 元素类
  class M_Element : public Monster
  {
  public:
    M_Element(int life, int magic, int attack) : Monster(life, magic, attack)
    {
      std::cout << "一个元素怪出现了" << std::endl;
    }
  };

  // 机械类
  class M_Mechainc : public Monster
  {
  public:
    M_Mechainc(int life, int magic, int attack) : Monster(life, magic, attack)
    {
      std::cout << "一个机械怪出现了" << std::endl;
    }
  };

  // --------------------
  // 工厂抽象类 (工厂基类)
  class M_ParFactory
  {
  public:
    virtual Monster *createMonster() = 0; // 具体实现在子类中进行
    virtual ~M_ParFactory() {}
  };

  // M_UndeadFactory,
  class M_UndeadFactory : public M_ParFactory
  {
  public:
    Monster *createMonster()
    {
      return new M_Undead(500, 100, 60);
    }
  };

  // M_ElementFactory,
  class M_ElementFactory : public M_ParFactory
  {
  public:
    Monster *createMonster()
    {
      return new M_Element(700, 300, 30);
    }
  };

  // M_MechaincFactory
  class M_MechaincFactory : public M_ParFactory
  {
  public:
    Monster *createMonster()
    {
      return new M_Mechainc(1000, 0, 50);
    }
  };

  // 全局的，用于创建怪物对象的函数，注意形参类型是工厂父类类型指针，返回类型是怪物父类类型的指针
  Monster *Gbl_createMonster(M_ParFactory *factory)
  {
    return factory->createMonster();
    // 调用的 createMonster 是一个虚函数，所以这里会因为多态而去调用实际子类对象的 createMonster
    // 该虚函数扮演了多态new的行为，给进来的factory指向的具体怪物工厂类不同，实际创建的怪物类也不同

    // 所以这里就将改变的部分抽象到了这个函数里，根据你给定的工厂类不同，我就给你创建相对应的怪物类
    // 要新增怪物类,那就新增怪物工厂,然后这里也不需要做改动
  }

  // 思路扩展
  // 不想创建太多工厂类，又想封装变化
  // 可以创建一个怪物工厂子类模板
  template <class T>
  class M_ChildFactory : public M_ParFactory
  {
  public:
    virtual Monster *createMonster()
    {
      return new T(300, 50, 45);
      // 如果这里需要不同的值，那么可以考虑传递一个非类型模板参数进来，根据非类型模板参数进行不同的初值new
    }
  };
}

int main()
{
  // 多态工厂，注意指针类型
  _nmsp1::M_ParFactory *p_ele_fy = new _nmsp1::M_ElementFactory();
  _nmsp1::M_ParFactory *p_udd_fy = new _nmsp1::M_UndeadFactory();
  _nmsp1::M_ParFactory *p_mec_fy = new _nmsp1::M_MechaincFactory();

  _nmsp1::Monster *pm1 = _nmsp1::Gbl_createMonster(p_mec_fy);
  _nmsp1::Monster *pm2 = _nmsp1::Gbl_createMonster(p_ele_fy);
  _nmsp1::Monster *pm3 = _nmsp1::Gbl_createMonster(p_udd_fy);

  delete p_ele_fy;
  delete p_udd_fy;
  delete p_mec_fy;

  delete pm1;
  delete pm2;
  delete pm3;

  std::cout << "-----------------------------------------------------" << std::endl;

  _nmsp1::M_ChildFactory<_nmsp1::M_Undead> c_fac1;
  _nmsp1::M_ChildFactory<_nmsp1::M_Element> c_fac2;
  _nmsp1::M_ChildFactory<_nmsp1::M_Mechainc> c_fac3;

  _nmsp1::Monster *pm4 = c_fac1.createMonster();
  _nmsp1::Monster *pm5 = c_fac2.createMonster();
  _nmsp1::Monster *pm6 = c_fac3.createMonster();

  delete pm6;
  delete pm5;
  delete pm4;

  return 0;
}
