#include <iostream>
#include "MonsterStatus.h"
#include "Monster.h"

using namespace std;

// 各个状态子类的 attacked 成员函数实现代码

// 凶悍状态 处理函数
void MonsterStatus_Feroc::attacked(int pover, Monster *monsobj)
{
  int orglife = monsobj->getLife(); // 暂存血量用于与收到攻击后进行比较
  if ((orglife - pover) > 400)      // 怪物原来处于凶悍状态，现在依然处于凶悍状态（状态未变）
  {
    monsobj->setLife(orglife - pover);
    std::cout << "怪物受到" << pover << "点伤害，处于凶悍状态，并开始反击" << std::endl;
  }
  else
  {
    // 不管下一个状态是啥，总之不会是凶悍状态了。
    // 那这里就直接转到不安状态（不管实际上是不是不安状态，这里不管，交给不安状态去管）

    // 先删除当前状态
    delete monsobj->getCurrentStatus();
    // 将状态设置为不安状态
    monsobj->setCurrentStatus(new MonsterStatus_Worr());
    // 无条件交给不安状态进行受攻击处理
    monsobj->getCurrentStatus()->attacked(pover, monsobj);
  }
}

// 不安状态 处理函数
void MonsterStatus_Worr::attacked(int pover, Monster *monsobj)
{
  int orglife = monsobj->getLife(); // 暂存血量用于与收到攻击后进行比较
  if ((orglife - pover) > 100)      // 怪物原来处于不安状态，现在依然处于不安状态（状态未变）
  {
    monsobj->setLife(orglife - pover);
    std::cout << "怪物受到" << pover << "点伤害，处于不安状态，反击的同时在求援" << std::endl;
  }
  else
  {
    // 不管下一个状态是啥，总之不会是不安状态了。
    // 那这里就直接转到恐惧状态（不管实际上是不是恐惧状态，这里不管，交给恐惧状态去管）

    // 先删除当前状态
    delete monsobj->getCurrentStatus();
    // 将状态设置为恐惧状态
    monsobj->setCurrentStatus(new MonsterStatus_Fear());
    // 无条件交给恐惧状态进行受攻击处理
    monsobj->getCurrentStatus()->attacked(pover, monsobj);
  }
}

// 恐惧状态 处理函数
void MonsterStatus_Fear::attacked(int pover, Monster *monsobj)
{
  int orglife = monsobj->getLife(); // 暂存血量用于与收到攻击后进行比较
  if ((orglife - pover) > 0)        // 怪物原来处于恐惧状态，现在依然处于恐惧状态（状态未变）
  {
    monsobj->setLife(orglife - pover);
    std::cout << "怪物受到" << pover << "点伤害，处于恐惧状态，开始逃跑" << std::endl;
  }
  else
  {
    // 不管下一个状态是啥，总之不会是恐惧状态了。
    // 那这里就直接转到死亡状态（不管实际上是不是死亡状态，这里不管，交给死亡状态去管）

    // 先删除当前状态
    delete monsobj->getCurrentStatus();
    // 将状态设置为死亡状态
    monsobj->setCurrentStatus(new MonsterStatus_Dead());
    // 无条件交给死亡状态进行受攻击处理
    monsobj->getCurrentStatus()->attacked(pover, monsobj);
  }
}

// 死亡状态 处理函数
void MonsterStatus_Dead::attacked(int pover, Monster *monsobj)
{
  int orglife = monsobj->getLife(); // 暂存血量用于与收到攻击后进行比较
  if (orglife > 0)
  {
    monsobj->setLife(orglife - pover);
  }
  std::cout << "怪物受到" << pover << "点伤害，处于死亡状态" << std::endl;
}