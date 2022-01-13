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

int Monster::getLife()
{
  return m_life;
}

void Monster::setLife(int life)
{
  if (life < 0)
  {
    m_life = 0;
  }
  else
  {
    m_life = life;
  }
}

MonsterStatus *Monster::getCurrentStatus()
{
  return m_status;
}

void Monster::setCurrentStatus(MonsterStatus *status)
{
  m_status = status;
}

// 被攻击函数
void Monster::attacked(int pover)
{
  m_status->attacked(pover, this);
}