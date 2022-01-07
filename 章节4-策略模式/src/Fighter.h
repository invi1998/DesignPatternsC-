#ifndef __RIGHER__
#define __RIGHER__

class ItemStrategy; // 外部类的前向声明

// 从当前这个代码中可以看到，角色是通过调用UseIem这个成员函数来实现血量回复功能，从实现的功能上讲，这代码没什么问题
// 但是从长远的角度，从面相对象的程序设计视角来看，可能会发现这些实现代码存在一些问题
// 如果增加新的能补充生命值的道具，那么我们就需要增加新的枚举型，然后也要在UseItm里增加新的if else 语句来新增判断逻辑
// 这种修改是不符合开闭原则的，而且一旦if else特别多的话，对程序的运行效率和可维护性也会造成影响
// 其次：代码复用性很差。试想如果将来怪物类型也能通过吃丹药回复血量，那将来可能需要将战斗者类中的UseIem拷贝到怪物类中去
// 显然这样会导致很多重复代码
// 第三个问题就是，目前道具的功能比较简单，但是考虑到将来道具功能变得复杂，比如丹药即能回血，也能回蓝等等，那样就会导致
// useiem里的代码逻辑变得复杂

//
// 血量回复丹药
// enum ItenAddLife
// {
//     LP_HX1,     // 1品回血丹
//     LP_HX2,     // 2品回血丹
//     LP_HX3,     // 3品回血丹
// };

// 战斗者父类
class Fighter
{
public:
  Fighter(int life, int magic, int attack) : m_life(life), m_magic(magic), m_attack(attack)
  {
  }

  virtual ~Fighter() {}

public:
  // void UseItem(ItenAddLife djItem) // 复用丹药回复血量
  // {
  //     if(djItem == LP_HX3)
  //     {
  //         m_life += 200;
  //     }
  //     else if (djItem == LP_HX2)
  //     {
  //         m_life += 300;
  //     }
  //     else if (djItem == LP_HX1)
  //     {
  //         m_life += 500;
  //     }
  // }

public:
  // 设置道具使用的策略（设置策略）
  void SetItemStrategy(ItemStrategy *strategy);
  void UseItem();         // 使用道具
  int GetLife();          // 获取生命值
  void SetLife(int life); // 设置生命值

protected:
  int m_life;
  int m_magic;
  int m_attack;

  // 指向策略类的指针
  ItemStrategy *itemstrategy = nullptr;
  // c++ 11中支持这样初始化
};

// 战士 类，父类为Fighter
class F_Warrior : public Fighter
{
public:
  F_Warrior(int life, int magic, int attack) : Fighter(life, magic, attack)
  {
  }
};

// 法师 类，父类为Fighter
class F_Mage : public Fighter
{
public:
  F_Mage(int life, int magic, int attack) : Fighter(life, magic, attack)
  {
  }
};

#endif