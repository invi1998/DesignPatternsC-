/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include "Fighter.h"
#include "ItemStrategy.h"

using namespace std;

// 情景模拟，随着游戏迭代，现在计划新增为角色加血的道具，当角色击杀或者走到特定位置的时候，这些回血道具就会出现
// 3品回血丹：回复200点生命值，2品回血丹：回复300点生命值，1品回血丹：回复500点生命值，
// Fighter 父类，F_Warrior,F_Magic,

int main()
{
  // Fighter* prole_war = new F_Warrior(2000, 0, 60);

  // prole_war->UseItem(LP_HX2);

  // --------------------------策略模式改造之后的代码--------------------------

  // 创建角色
  Fighter *prole_war = new F_Warrior(2000, 0, 60);

  // 创建3品回血丹
  ItemStrategy *strategy = new ItemStrategy_HXD3();
  prole_war->SetItemStrategy(strategy);
  // 回血 + 200
  prole_war->UseItem();

  // 创建1品回血丹
  ItemStrategy *strategy2 = new ItemStrategy_HXD1();
  prole_war->SetItemStrategy(strategy2);
  // 回血 + 500
  prole_war->UseItem();

  std::cout << "查看角色血量：" << prole_war->GetLife() << std::endl;
  // 查看角色血量：2700

  // 释放资源
  delete prole_war;
  delete strategy;
  delete strategy2;

  return 0;
}
