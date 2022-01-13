#ifndef __MONSTERSTATUS__
#define __MONSTERSTATUS__

class Monster; // 类前向声名

class MonsterStatus
{
public:
  virtual void attacked(int pover, Monster *monsobj) = 0;
  virtual ~MonsterStatus() {}
};

// 凶悍状态类
class MonsterStatus_Feroc : public MonsterStatus
{
public:
  virtual void attacked(int pover, Monster *monsobj)
  {
    std::cout << "怪物受到" << pover << "点伤害，处于凶悍状态，并开始反击" << std::endl;
  }
};

// 不安状态类
class MonsterStatus_Worr : public MonsterStatus
{
public:
  virtual void attacked(int pover, Monster *monsobj)
  {
    std::cout << "怪物受到" << pover << "点伤害，处于不安状态，反击的同时在求援" << std::endl;
  }
};

// 恐惧状态类
class MonsterStatus_Fear : public MonsterStatus
{
public:
  virtual void attacked(int pover, Monster *monsobj)
  {
    std::cout << "怪物受到" << pover << "点伤害，处于恐惧状态，开始逃跑" << std::endl;
  }
};

// 死亡状态类
class MonsterStatus_Dead : public MonsterStatus
{
public:
  virtual void attacked(int pover, Monster *monsobj)
  {
    std::cout << "怪物受到" << pover << "点伤害，处于死亡状态" << std::endl;
  }
};

#endif