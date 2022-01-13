#include <iostream>
#include "MonsterStatus.h"
#include "Monster.h"

using namespace std;

int main()
{
  Monster mon(500);
  mon.attacked(20);
  // 怪物受到20点伤害，处于凶悍状态，并开始反击
  mon.attacked(100);
  // 怪物受到100点伤害，处于不安状态，反击的同时在求援
  mon.attacked(200);
  // 怪物受到200点伤��，处于不安状态，反击的同时在求援
  mon.attacked(100);
  // 怪物受到100点伤害，处于恐惧状�，开始逃跑
  mon.attacked(100);
  // 怪物受到100点伤害，处于死亡状态
  mon.attacked(20);
  // 怪物受到20点伤害，处�死亡状态

  return 0;
}