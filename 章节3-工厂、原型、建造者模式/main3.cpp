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

// 新增按战斗场景分类，沼泽地区，山脉地区，城镇地区
// 然后这3个场景中又分别都有上述3中怪物，每个不同地区，怪物属性数值不一样
// 那如果按照上面我们的工厂方法模式来创建怪物的话，就需要写9个工厂
// 如果一个工厂子类能够创建不止一种而是具有多种相同规则的怪物对象，
// 那么就可以有效减少所创建的工厂子类的数量，这就是抽象工厂的核心思想

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

  // 沼泽地区 亡灵类
  class M_Undead_Swamp : public Monster
  {
  public:
    M_Undead_Swamp(int life, int magic, int attack) : Monster(life, magic, attack)
    {
      std::cout << "沼泽地区出现了一个 亡灵类 怪物" << std::endl;
    }
  };

  // 沼泽地区 元素类
  class M_Element_Swamp : public Monster
  {
  public:
    M_Element_Swamp(int life, int magic, int attack) : Monster(life, magic, attack)
    {
      std::cout << "沼泽地区出现了一个 元素类 怪物" << std::endl;
    }
  };

  // 沼泽地区 机械类
  class M_Mechainc_Swamp : public Monster
  {
  public:
    M_Mechainc_Swamp(int life, int magic, int attack) : Monster(life, magic, attack)
    {
      std::cout << "沼泽地区出现了一个 机械类 怪物" << std::endl;
    }
  };

  // ----------------------------------------------------------------

  // 山脉地区 亡灵类
  class M_Undead_Mountain : public Monster
  {
  public:
    M_Undead_Mountain(int life, int magic, int attack) : Monster(life, magic, attack)
    {
      std::cout << "山脉地区出现了一个 亡灵类 怪物" << std::endl;
    }
  };

  // 山脉地区 元素类
  class M_Element_Mountain : public Monster
  {
  public:
    M_Element_Mountain(int life, int magic, int attack) : Monster(life, magic, attack)
    {
      std::cout << "山脉地区出现了一个 元素类 怪物" << std::endl;
    }
  };

  // 山脉地区 机械类
  class M_Mechainc_Mountain : public Monster
  {
  public:
    M_Mechainc_Mountain(int life, int magic, int attack) : Monster(life, magic, attack)
    {
      std::cout << "山脉地区出现了一个 机械类 怪物" << std::endl;
    }
  };

  // ----------------------------------------------------------------

  // 城镇地区 亡灵类
  class M_Undead_Town : public Monster
  {
  public:
    M_Undead_Town(int life, int magic, int attack) : Monster(life, magic, attack)
    {
      std::cout << "城镇地区出现了一个 亡灵类 怪物" << std::endl;
    }
  };

  // 城镇地区 元素类
  class M_Element_Town : public Monster
  {
  public:
    M_Element_Town(int life, int magic, int attack) : Monster(life, magic, attack)
    {
      std::cout << "城镇地区出现了一个 元素类 怪物" << std::endl;
    }
  };

  // 城镇地区 机械类
  class M_Mechainc_Town : public Monster
  {
  public:
    M_Mechainc_Town(int life, int magic, int attack) : Monster(life, magic, attack)
    {
      std::cout << "城镇地区出现了一个 机械类 怪物" << std::endl;
    }
  };

  // *******************************************************************************

  // 所有工厂的父类
  class M_ParFactory
  {
  public:
    virtual Monster *creatMonster_Undead() = 0;   // 创建亡灵类怪物
    virtual Monster *creatMonster_Element() = 0;  // 创建元素类怪物
    virtual Monster *creatMonster_Mechainc() = 0; // 创建机械类怪物

    virtual ~M_ParFactory() {}
  };

  // 创建工厂子类
  // 沼泽工厂
  class M_Factory_Swamp : public M_ParFactory
  {
  public:
    Monster *creatMonster_Undead() // 创建亡灵类怪物
    {
      return new M_Undead_Swamp(1200, 500, 80);
    }

    Monster *creatMonster_Element() // 创建元素类怪物
    {
      return new M_Element_Swamp(1000, 300, 40);
    }

    Monster *creatMonster_Mechainc() // 创建机械类怪物
    {
      return new M_Mechainc_Swamp(400, 0, 30);
    }
  };

  // 山脉工厂
  class M_Factory_Mountain : public M_ParFactory
  {
  public:
    Monster *creatMonster_Undead() // 创建亡灵类怪物
    {
      return new M_Undead_Mountain(900, 400, 50);
    }

    Monster *creatMonster_Element() // 创建元素类怪物
    {
      return new M_Element_Mountain(1300, 600, 70);
    }

    Monster *creatMonster_Mechainc() // 创建机械类怪物
    {
      return new M_Mechainc_Mountain(800, 0, 50);
    }
  };

  // 城镇工厂
  class M_Factory_Town : public M_ParFactory
  {
  public:
    Monster *creatMonster_Undead() // 创建亡灵类怪物
    {
      return new M_Undead_Town(500, 100, 32);
    }

    Monster *creatMonster_Element() // 创建元素类怪物
    {
      return new M_Element_Town(400, 200, 30);
    }

    Monster *creatMonster_Mechainc() // 创建机械类怪物
    {
      return new M_Mechainc_Town(1400, 0, 90);
    }
  };
}

int main()
{
  _nmsp1::M_ParFactory *p_mou_fy = new _nmsp1::M_Factory_Mountain(); // 多态工厂 山脉工厂
  _nmsp1::M_ParFactory *p_swa_fy = new _nmsp1::M_Factory_Swamp();    // 多态工厂 沼泽工厂
  _nmsp1::M_ParFactory *p_tow_fy = new _nmsp1::M_Factory_Town();     // 多态工厂 城镇工厂

  _nmsp1::Monster *pm1 = p_mou_fy->creatMonster_Undead();
  _nmsp1::Monster *pm2 = p_mou_fy->creatMonster_Mechainc();
  _nmsp1::Monster *pm3 = p_mou_fy->creatMonster_Element();
  // 山脉地区出现了一个 亡灵类 怪物
  // 山脉地区出现了一个 机械类 怪物
  // 山脉地区出现了一个 元素类 怪物

  _nmsp1::Monster *pm4 = p_swa_fy->creatMonster_Undead();
  _nmsp1::Monster *pm5 = p_swa_fy->creatMonster_Mechainc();
  _nmsp1::Monster *pm6 = p_swa_fy->creatMonster_Element();
  // 沼泽地区出现了��个 亡灵类 怪物
  // 沼泽地区出现了一个 机械类 怪物
  // 沼泽地区出现了一� 元素类 怪物

  _nmsp1::Monster *pm7 = p_tow_fy->creatMonster_Undead();
  _nmsp1::Monster *pm8 = p_tow_fy->creatMonster_Mechainc();
  _nmsp1::Monster *pm9 = p_tow_fy->creatMonster_Element();
  // 城镇地区出现了一个 亡灵类 怪物
  // 城镇地区出现了一个 �械类 怪物
  // 城镇地区出现了一个 元素类 怪物

  delete pm1;
  delete pm2;
  delete pm3;
  delete pm4;
  delete pm5;
  delete pm6;
  delete pm7;
  delete pm8;
  delete pm9;

  delete p_mou_fy;
  delete p_swa_fy;
  delete p_tow_fy;

  return 0;
}
