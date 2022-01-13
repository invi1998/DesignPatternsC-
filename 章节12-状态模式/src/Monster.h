#ifndef __MONSTERH__
#define __MONSTERH__

class MonsterStatus;

class Monster
{
public:
  Monster(int life);
  ~Monster();

public:
  void attacked(int pover); // 怪物被攻击

private:
  int m_life;              // 血量
  MonsterStatus *m_status; // 状态对象
};

#endif