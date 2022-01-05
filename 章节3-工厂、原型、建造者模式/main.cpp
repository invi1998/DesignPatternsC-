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

  // 怪物工厂类
  class MonsterFactory
  {
  public:
    static Monster *createMonster(string strmontype)
    {
      Monster *prtnobj = nullptr;
      if (strmontype == "udd") // udd 创建亡灵类
      {
        prtnobj = new M_Undead(500, 100, 60);
      }
      else if (strmontype == "ele") // ele 创建元素类
      {
        prtnobj = new M_Element(700, 300, 30);
      }
      else if (strmontype == "mec") // mec 创建机械类
      {
        prtnobj = new M_Mechainc(1000, 0, 50);
      }

      return prtnobj;
    }
  };

  // 虽然通过这个怪物工厂类我们不需要与怪物类名直接打交道，但是还是需要给工厂类传递要创建哪种类

}

// 使用 new + 具体类名来创建对象是一种依赖具体类型的紧耦合关系，
// 简单工厂模式的实现思路：
// 使用工厂类可以实现创建怪物的代码与各个具体的怪物类对象要实现的逻辑代码隔离

int main()
{
  _nmsp1::Monster *p_undead = new _nmsp1::M_Undead(500, 100, 60);
  _nmsp1::Monster *p_element = new _nmsp1::M_Element(700, 300, 30);
  _nmsp1::Monster *p_mechainc = new _nmsp1::M_Mechainc(1000, 0, 50);

  // 释放资源
  delete p_undead;
  delete p_element;
  delete p_mechainc;

  std::cout << "--------------------------------------------------------" << std::endl;

  _nmsp1::Monster *p_undead2 = _nmsp1::MonsterFactory::createMonster("udd");
  _nmsp1::Monster *p_element2 = _nmsp1::MonsterFactory::createMonster("ele");
  _nmsp1::Monster *p_mechainc2 = _nmsp1::MonsterFactory::createMonster("mec");

  // 释放资源
  delete p_undead2;
  delete p_element2;
  delete p_mechainc2;

  return 0;
}
