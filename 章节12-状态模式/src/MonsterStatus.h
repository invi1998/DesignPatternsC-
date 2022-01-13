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
  virtual void attacked(int pover, Monster *monsobj);
};

// 不安状态类
class MonsterStatus_Worr : public MonsterStatus
{
public:
  virtual void attacked(int pover, Monster *monsobj);
};

// 恐惧状态类
class MonsterStatus_Fear : public MonsterStatus
{
public:
  virtual void attacked(int pover, Monster *monsobj);
};

// 死亡状态类
class MonsterStatus_Dead : public MonsterStatus
{
public:
  virtual void attacked(int pover, Monster *monsobj);
};

#endif