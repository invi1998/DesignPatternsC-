#include <iostream>
#include <vector>

using namespace std;

// 情景模拟
// 游戏玩家的进度信息如何进行保存？（当前生命值，蓝量，攻击力。。。）
namespace _nmsp1
{
  // 备忘录类
  class FighterMemento
  {
  private:
    // 构造函数使用私有构造，防止信息泄露
    FighterMemento(int life, int magic, int attack) : m_life(life), m_magic(magic), m_attack(attack)
    {
    }

  private:
    // 提供一些供Fighter类访问的接口，用private修饰防止被任意类访问
    friend class Fighter; // 友元类Fighter可以访问本类的所有私有成员函数

    int getLife() { return m_life; }
    void setLife(int life) { m_life = life; }

    int getMagic() { return m_magic; }
    void setMagic(int magic) { m_magic = magic; }

    int getAttack() { return m_attack; }
    void setAttack(int attack) { m_attack = attack; }

  private:
    // 备忘录中需要保存的角色数据
    int m_life;   // 生命值
    int m_magic;  // 蓝量
    int m_attack; // 攻击力
  };

  // 角色类
  class Fighter
  {
  public:
    Fighter(int life, int magic, int attack) : m_life(life), m_magic(magic), m_attack(attack)
    {
    }

  public:
    // 将玩家数据写入到备忘录
    FighterMemento *createMemento()
    {
      return new FighterMemento(m_life, m_magic, m_attack);
    }

    // 从备忘录中恢复玩家数据
    void restore(FighterMemento *ptm)
    {
      m_life = ptm->m_life;
      m_magic = ptm->m_magic;
      m_attack = ptm->m_attack;
    }

    // 设置玩家死亡状态
    void setToDead()
    {
      m_life = 0;
    }

    // 用于打印
    void display()
    {
      std::cout << "玩家当前状态：" << std::endl;
      std::cout << "血量 ------- " << m_life << std::endl;
      std::cout << "蓝量 ------- " << m_magic << std::endl;
      std::cout << "攻击力 ----- " << m_attack << std::endl;
    }

  private:
    int m_life;   // 生命值
    int m_magic;  // 蓝量
    int m_attack; // 攻击力
  };

  // 管理者类
  class FCareTaker
  {
  public:
    // 构造函数
    FCareTaker(FighterMemento *pfm) : m_pfm(pfm) {}

    // 获取指向备忘录的指针
    FighterMemento *getMemento()
    {
      return m_pfm;
    }

    // 保存指向备忘录的指针
    void setMemento(FighterMemento *pfm)
    {
      m_pfm = pfm;
    }

  private:
    FighterMemento *m_pfm; // 指向备忘录的指针
  };

  // ---------------------------------------------------
  // 支持多个快照的负责人（管理者）类
  class FCareTaker2
  {
  public:
    ~FCareTaker2()
    {
      for (std::vector<FighterMemento *>::iterator i = m_pfmContainer.begin(); i != m_pfmContainer.end(); ++i)
      {
        delete (*i);
      }
    }

    // 保存指向备忘录对象的指针
    void setMemento(FighterMemento *pfm)
    {
      m_pfmContainer.push_back(pfm);
    }

    // 获取指向备忘录对象的指针
    FighterMemento *getMemento(int index)
    {
      auto iter = m_pfmContainer.begin();
      for (int i = 0; i <= index; ++i)
      {
        if (i == index)
        {
          return *iter;
        }
        else
        {
          ++iter;
        }
      }
      return NULL;
    }

  private:
    // 存储备忘录对象指针的容器
    vector<FighterMemento *> m_pfmContainer;
  };

  void func()
  {
    Fighter *play = new Fighter(1000, 200, 56);
    play->display();
    // 玩家当前状态：
    // 血量 ------- 1000
    // 蓝量 ------- 200
    // 攻击力 ----- 56

    // 创建备忘录
    FighterMemento *ptm = play->createMemento();

    // 玩家死亡
    play->setToDead();

    // 显示玩家血量
    play->display();
    // 玩家当前状态：
    // 血量 ------- 0
    // 蓝量 ------- 200
    // 攻击力 ----- 56

    // 读取存档
    play->restore(ptm);

    play->display();
    // 玩家当前状态：
    // 血量 ------- 1000
    // 蓝量 ------- 200
    // 攻击力 ----- 56

    std::cout << "---------------------------------------------------" << std::endl;
    FCareTaker *fc = new FCareTaker(play->createMemento());
    // 玩家死亡
    play->setToDead();
    play->display();
    // 玩家当前状态：
    // 血量 ------- 0
    // 蓝量 ------- 200
    // 攻击力 ----- 56

    play->restore(fc->getMemento());
    play->display();
    // 玩家当前状态：
    // 血量 ------- 1000
    // 蓝量 ------- 200
    // 攻击力 ----- 56

    // 释放资源
    delete play;
    delete ptm;

    delete fc;
  }

  void func2()
  {
    Fighter *pf = new Fighter(1000, 232, 900);
    FCareTaker2 *fc = new FCareTaker2();
    fc->setMemento(pf->createMemento()); // 第一次做快照
    pf->setToDead();
    fc->setMemento(pf->createMemento()); // 第二次做快照
    pf->display();
    // 玩家当前状态：
    // 血量 ------- 0
    // 蓝量 ------- 200
    // 攻击力 ----- 56

    std::cout << "---------------------------------------------------" << std::endl;
    // 恢复第一次快照内容
    pf->restore(fc->getMemento(0));
    pf->display();
    // 玩家当前状态：
    // 血量 ------- 1000
    // 蓝量 ------- 200
    // 攻击力 ----- 56
  }
}

int main()
{
  // _nmsp1::func();
  _nmsp1::func();

  return 0;
}
