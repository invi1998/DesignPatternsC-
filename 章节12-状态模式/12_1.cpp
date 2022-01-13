#include <iostream>

using namespace std;

// 有限状态机（Finite State Mache， 缩写 FSM），简称状态机
// 当某个事件（转移条件）发生时，会根据当前状态决定你执行哪种动作，然后进入下一种状态

// 情景模拟：
// 假设游戏中怪物 血量500点，
// 1）血量 > 400的点，怪物->凶悍状态，反击
// 2）血量 <= 400 && 血量 > 100, 怪物->不安状态，反击并呼唤其他怪物支援。
// 3) 血量 <= 100，怪物 -> 恐惧状态， 逃跑并不再反击
// 4）血量 <= 0， 怪物 -> 死亡状态

namespace _nmsp1
{
  // 定义怪物状态 枚举值
  enum MonsterState
  {
    MonS_Fer,  // 凶悍状态
    MonS_Vorr, // 不安状态
    MonS_Fear, // 恐惧状态
    MonS_Dead  // 死亡状态
  };

  // 怪物类
  class Monster
  {
  public:
    Monster(int life) : m_life(life), m_status(MonS_Fer)
    {
    }

  public:
    // 怪物被攻击，pover表示受到的伤害（扣血多少）
    void attacked(int pover)
    {
      m_life -= pover;
      if (m_status == MonS_Fer)
      {
        if (m_life > 400)
        {
          std::cout << "怪物受到" << pover << "点伤害，并对主角进行反击" << std::endl;
        }
        else if (m_life > 100)
        {
          std::cout << "怪物受到" << pover << "点伤害，并对主角进行反击, 同时开始向附近怪物求援" << std::endl;
          m_status = MonS_Vorr;
        }
        else if (m_life > 0)
        {
          std::cout << "怪物受到" << pover << "点伤害，并停止反击, 开始逃跑" << std::endl;
          m_status = MonS_Fear;
        }
        else
        {
          std::cout << "怪物受到" << pover << "点伤害，死亡" << std::endl;
          m_status = MonS_Dead;
        }
      }
      else if (m_status == MonS_Vorr)
      {
        if (m_life > 100)
        {
          std::cout << "怪物受到" << pover << "点伤害，并对主角进行反击, 变得不安" << std::endl;
          m_status = MonS_Vorr;
        }
        else if (m_life > 0)
        {
          std::cout << "怪物受到" << pover << "点伤害，并停止反击, 开始逃跑" << std::endl;
          m_status = MonS_Fear;
        }
        else
        {
          std::cout << "怪物受到" << pover << "点伤害，死亡" << std::endl;
          m_status = MonS_Dead;
        }
      }
      else if (m_status == MonS_Fear)
      {
        if (m_life > 0)
        {
          std::cout << "怪物受到" << pover << "点伤害，并停止反击, 开始逃跑" << std::endl;
          m_status = MonS_Fear;
        }
        else
        {
          std::cout << "怪物受到" << pover << "点伤害，死亡" << std::endl;
          m_status = MonS_Dead;
        }
      }
      else if (m_status == MonS_Dead)
      {
        std::cout << "怪物死亡" << std::endl;
      }
    }

  private:
    int m_life;            // 血量
    MonsterState m_status; // 初始状态
  };

  void func()
  {
    Monster mon(500);
    mon.attacked(20);
    // 怪物受到20点伤害，并对主角进行反击
    mon.attacked(100);
    // 怪物受到100点伤害，并对主角进行反击, 同时开始向附近怪物求援
    mon.attacked(200);
    // 怪物受到200点�害，并对主角进行反击, 变得不安
    mon.attacked(20);
    // 怪物受到20点伤害，并对主角进行反�, 变得不安
    mon.attacked(100);
    // 怪物受到100点伤害，并停止反击, 开始逃跑
    mon.attacked(200);
    // 怪物受到200点伤害，死亡
  }

}

int main()
{
  _nmsp1::func();

  return 0;
}
