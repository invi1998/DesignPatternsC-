// 依赖倒置原则的一个案例和改进
/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby,
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>

using namespace std;

namespace _nmsp1
{
  // 亡灵类
  class M_Undead
  {
  public:
    void getinfo()
    {
      std::cout << "亡灵类怪物" << std::endl;
    }
  };

  // 元素类
  class M_Element
  {
  public:
    void getinfo()
    {
      std::cout << "元素类怪物" << std::endl;
    }
  };

  // 机械类
  class M_Mechanic
  {
  public:
    void getinfo()
    {
      std::cout << "机械类怪物" << std::endl;
    }
  };

  // 战士角色
  class F_Warrior
  {
  public:
    void attack_enemy_undead(M_Undead *pobj) // 攻击亡灵类怪物
    {
      // 进行攻击动作
      pobj->getinfo(); // 调用亡灵类怪物类相关的函数
    }

    // 现在是攻击亡灵类怪物，那我要是攻击元素类怪物，岂不是又得在这里新增函数，。。
    void attack_enemy_element(M_Element *pobj) // 攻击元素类怪物
    {
      // 进行攻击动作
      pobj->getinfo(); // 调用元素类怪物类相关的函数
    }
  };
}

namespace _nmsp2
{
  // 作为所有怪物类的父类（抽象层）
  class Monster
  {
  public:
    virtual void getinfo() = 0;

    virtual ~Monster() {}
  };

  // 亡灵类
  class M_Undead : public Monster
  {
  public:
    void getinfo()
    {
      std::cout << "亡灵类怪物" << std::endl;
    }
  };

  // 元素类
  class M_Element : public Monster
  {
  public:
    void getinfo()
    {
      std::cout << "元素类怪物" << std::endl;
    }
  };

  // 机械类
  class M_Mechanic : public Monster
  {
  public:
    void getinfo()
    {
      std::cout << "机械类怪物" << std::endl;
    }
  };

  // 这里怪物类已经足以阐述依赖倒置原则，这里就不对战士类进行抽象了
  // 战士角色
  class F_Warrior
  {
  public:
    void attack_enemy(Monster *pobj) // 攻击怪物
    {
      // 进行攻击动作
      pobj->getinfo(); // 调用怪物类相关的函数
    }
  };
}

int main()
{
  // _nmsp1::M_Undead* pobbj = new _nmsp1::M_Undead();
  // _nmsp1::M_Element* pobbj2 = new _nmsp1::M_Element();
  // _nmsp1::F_Warrior* pf = new _nmsp1::F_Warrior();

  // pf->attack_enemy_undead(pobbj);
  // pf->attack_enemy_element(pobbj2);

  _nmsp2::Monster *pobbj = new _nmsp2::M_Undead();
  _nmsp2::Monster *pobbj2 = new _nmsp2::M_Element();
  _nmsp2::F_Warrior *pf = new _nmsp2::F_Warrior();

  pf->attack_enemy(pobbj);
  pf->attack_enemy(pobbj2);

  // delete。。

  return 0;
}
