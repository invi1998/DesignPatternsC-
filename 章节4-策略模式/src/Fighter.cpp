#include "Fighter.h"
#include "ItemStrategy.h"
#include <iostream>

using namespace std;

// 设置道具使用的策略
void Fighter::SetItemStrategy(ItemStrategy *strategy)
{
  itemstrategy = strategy;
}

// 使用道具
void Fighter::UseItem()
{
  itemstrategy->UseItem(this);
}

// 获取生命值
int Fighter::GetLife()
{
  return m_life;
}

// 设置生命值
void Fighter::SetLife(int life)
{
  m_life = life;
}