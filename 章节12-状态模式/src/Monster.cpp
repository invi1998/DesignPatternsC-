#include <iostream>
#include "Monster.h"
#include "MonsterStatus.h"

using namespace std;

// 构造函数(初始化怪物血量和状态)
Monster::Monster(int life) : m_life(life), m_status(nullptr)
{
  m_status = new MonsterStatus_Feroc();
}

Monster::~Monster()
{
  delete m_status;
  m_status = nullptr;
}

// 被攻击函数
void Monster::attacked(int pover)
{
  int orglife = m_life; // 暂存原来的血量用于与后续受攻击后的血量进行比较
  m_life -= pover;
  if (orglife > 400) // 怪物原来处于凶悍状态
  {
    if (m_life > 400) // 状态不变
    {
      m_status->attacked(pover, this);
      //   其逻辑代码被本Monster类委托给了具体的状态类来处理
    }
    else if (m_life > 100) // 凶悍 变为 不安
    {
      // 释放原有状态项
      delete m_status;
      m_status = new MonsterStatus_Worr(); // 怪物变成不安状态
      m_status->attacked(pover, this);
    }
    else if (m_life > 0) // 凶悍变为恐惧
    {
      // 释放原有状态项
      delete m_status;
      m_status = new MonsterStatus_Fear(); // 怪物变成恐惧状态
      m_status->attacked(pover, this);
    }
    else // 凶悍变成死亡
    {
      // 释放原有状态项
      delete m_status;
      m_status = new MonsterStatus_Dead(); // 怪物变成死亡状态
      m_status->attacked(pover, this);
    }
  }
  else if (orglife > 100) // 怪物原来处于不安状态
  {
    if (m_life > 100) // 不安 状态不变
    {
      m_status->attacked(pover, this);
      //   其逻辑代码被本Monster类委托给了具体的状态类来处理
    }
    else if (m_life > 0) // 不安变为恐惧
    {
      // 释放原有状态项
      delete m_status;
      m_status = new MonsterStatus_Fear(); // 怪物变成恐惧状态
      m_status->attacked(pover, this);
    }
    else // 不安变成死亡
    {
      // 释放原有状态项
      delete m_status;
      m_status = new MonsterStatus_Dead(); // 怪物变成死亡状态
      m_status->attacked(pover, this);
    }
  }
  else if (orglife > 0) // 怪物原来处于恐惧状态
  {
    if (m_life > 0) // 恐惧状态不变
    {
      m_status->attacked(pover, this);
    }
    else // 恐惧变成死亡
    {
      // 释放原有状态项
      delete m_status;
      m_status = new MonsterStatus_Dead(); // 怪物变成死亡状态
      m_status->attacked(pover, this);
    }
  }
  else // 怪物死亡
  {
    m_status->attacked(pover, this);
  }
}