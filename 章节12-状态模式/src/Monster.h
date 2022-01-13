#ifndef __MONSTERH__
#define __MONSTERH__

class MonsterStatus;

class Monster
{
public:
  Monster(int life);
  ~Monster();

public:
  int getLife(); // 获取怪物血量

  void setLife(int life); // 设置怪物血量

  MonsterStatus *getCurrentStatus(); // 获取当前怪物所处状态

  void setCurrentStatus(MonsterStatus *status); // 设置怪物当前状态

public:
  void attacked(int pover); // 怪物被攻击

private:
  int m_life;              // 血量
  MonsterStatus *m_status; // 状态对象
};

#endif