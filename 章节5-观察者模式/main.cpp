
#include <stdio.h>
#include <iostream>
#include <list>
#include <map>

using namespace std;

// 需求，新增群组功能，同一个群组内的成员可以看到成员聊天消息，非同一群组的成员不能看到群组消息

// 当前这种代码虽然实现了聊天功能，但是试想，如果游戏中有上万个玩家，那么这里发一条消息就需要遍历上万次，程序运行效率必然低下
namespace _nmsp1
{
  class Fighter;                // 前向声名
  list<Fighter *> g_PlayerList; // 玩家列表

  // 玩家 父类
  class Fighter
  {
  public:
    Fighter(int tmpID, string name) : m_iPlayerID(tmpID), m_sPlayerName(name)
    {
      m_iFamilyID = -1; // 表示当前玩家没有加入任何家族
    }

    virtual ~Fighter() {}

    // 为玩家设置家族ID
    void SetFamilyID(int tmpID)
    {
      m_iFamilyID = tmpID;
    }

  public:
    void SayWorlds(string content) // 玩家聊天这个动作
    {
      if (m_iFamilyID != -1)
      {
        // 该玩家属于某个家族，将说的话广播通知到家族群的其他玩家
        for (auto iter = g_PlayerList.begin(); iter != g_PlayerList.end(); ++iter)
        {
          if (m_iFamilyID == (*iter)->m_iFamilyID)
          {
            // 同一个家族的其他玩家也应该收到这条信息
            NotifyWorlds((*iter), content);
          }
        }
      }
    }

  private:
    // 其他玩家收到了当前玩家的聊天消息
    void NotifyWorlds(Fighter *fighter, string content)
    {
      // 显示消息
      std::cout << "玩家：" << fighter->m_sPlayerName << "    收到了玩家：" << m_sPlayerName << "     发送的聊天消息" << std::endl;
      std::cout << "聊天消息内容：" << content << std::endl;
    }

  private:
    int m_iPlayerID;      // 玩家ID，全局唯一
    string m_sPlayerName; // 玩家名
    int m_iFamilyID;      // 家族ID
  };

  // 战士角色
  class F_Warrior : public Fighter
  {
  public:
    F_Warrior(int temID, string name) : Fighter(temID, name)
    {
    }
  };

  // 法师角色
  class F_Mage : public Fighter
  {
  public:
    F_Mage(int temID, string name) : Fighter(temID, name)
    {
    }
  };

  // 牧师角色
  class F_Priest : public Fighter
  {
  public:
    F_Priest(int temID, string name) : Fighter(temID, name)
    {
    }
  };
}

namespace _nmsp2
{
  class Fighter; // 类前向声名

  class Notifier // 通知器 父类
  {
  public:
    virtual void addToList(Fighter *player) = 0;              // 把要被通知的玩家加入到列表中
    virtual void removeFromList(Fighter *player) = 0;         // 把不想被通知的玩家从列表中移除
    virtual void notify(Fighter *talker, string content) = 0; // 通知细节信息
    virtual ~Notifier() {}
  };

  // 玩家 父类
  class Fighter
  {
  public:
    Fighter(int tmpID, string name) : m_iPlayerID(tmpID), m_sPlayerName(name)
    {
      m_iFamilyID = -1; // 表示当前玩家没有加入任何家族
    }

    virtual ~Fighter() {}

    // 为玩家设置家族ID
    void SetFamilyID(int tmpID)
    {
      m_iFamilyID = tmpID;
    }

    int GetFamilyID()
    {
      return m_iFamilyID;
    }

    void SayWorlds(string content, Notifier *notifier) // 玩家聊天这个动作
    {
      notifier->notify(this, content);
    }

  public:
    // 其他玩家收到了当前玩家的聊天消息
    void NotifyWorlds(Fighter *talker, string content)
    {
      // 显示消息
      std::cout << "玩家：" << m_sPlayerName << "    收到了玩家：" << talker->m_sPlayerName << "     发送的聊天消息" << std::endl;
      std::cout << "聊天消息内容：" << content << std::endl;
    }

  private:
    int m_iPlayerID;      // 玩家ID，全局唯一
    string m_sPlayerName; // 玩家名
    int m_iFamilyID;      // 家族ID
  };

  // 战士角色
  class F_Warrior : public Fighter
  {
  public:
    F_Warrior(int temID, string name) : Fighter(temID, name)
    {
    }
  };

  // 法师角色
  class F_Mage : public Fighter
  {
  public:
    F_Mage(int temID, string name) : Fighter(temID, name)
    {
    }
  };

  // 牧师角色
  class F_Priest : public Fighter
  {
  public:
    F_Priest(int temID, string name) : Fighter(temID, name)
    {
    }
  };

  // ---------------------------------------------------------
  // 聊天信息通知器 子类
  class TalkNotifier : public Notifier
  {
  public:
    // 将玩家增加到家族列表中来
    virtual void addToList(Fighter *player)
    {
      int tmpfamilyid = player->GetFamilyID();
      if (tmpfamilyid != -1) // 加入了某个家族
      {
        auto iter = m_familyMap.find(tmpfamilyid);
        if (iter != m_familyMap.end())
        {
          // 该家族id在map中已经存在
          iter->second.push_back(player);
        }
        else
        {
          // 如果该玩家没有加过家族（该家族id在map中不存在）
          list<Fighter *> tmpfamilylist;
          m_familyMap.insert(make_pair(tmpfamilyid, tmpfamilylist));
          // 以该家族id为key，新增条目到map
          m_familyMap[tmpfamilyid].push_back(player);
          // 像该家族中增加第一个玩家
        }
      }
    }

    // 将玩家从家族列表中删除
    virtual void removeFromList(Fighter *player)
    {
      int tmpfamilyid = player->GetFamilyID();

      if (tmpfamilyid != -1)
      {
        auto iter = m_familyMap.find(tmpfamilyid);
        if (iter != m_familyMap.end())
        {
          m_familyMap[tmpfamilyid].remove(player);
        }
      }
    }

    // 将玩家消息广播到家族群
    virtual void notify(Fighter *talker, string content)
    {
      int tmpfamilyid = talker->GetFamilyID();

      if (tmpfamilyid != -1)
      {
        auto iter = m_familyMap.find(tmpfamilyid);
        if (iter != m_familyMap.end())
        {
          // 遍历该玩家所属家族的所有成员
          for (auto iterl = iter->second.begin(); iterl != iter->second.end(); ++iterl)
          {
            (*iterl)->NotifyWorlds(talker, content);
          }
        }
      }
    }

  private:
    // map 中的 key 表示家族id，list表示家族成员列表
    map<int, list<Fighter *>> m_familyMap;
  };

}

int main()
{
  // 创建游戏玩家
  _nmsp1::Fighter *play1 = new _nmsp1::F_Warrior(10, "法维安");
  _nmsp1::Fighter *play2 = new _nmsp1::F_Priest(11, "哈辛达");
  _nmsp1::Fighter *play3 = new _nmsp1::F_Mage(12, "菲奥娜");
  _nmsp1::Fighter *play4 = new _nmsp1::F_Warrior(13, "沙木亚");
  _nmsp1::Fighter *play5 = new _nmsp1::F_Mage(14, "哈比");
  _nmsp1::Fighter *play6 = new _nmsp1::F_Warrior(15, "周虹");
  _nmsp1::Fighter *play7 = new _nmsp1::F_Priest(16, "蓝焰女王");

  play1->SetFamilyID(100);
  play2->SetFamilyID(100);
  play3->SetFamilyID(110);
  play4->SetFamilyID(100);
  play5->SetFamilyID(140);
  play6->SetFamilyID(140);
  play7->SetFamilyID(100);

  _nmsp1::g_PlayerList.push_back(play1);
  _nmsp1::g_PlayerList.push_back(play2);
  _nmsp1::g_PlayerList.push_back(play3);
  _nmsp1::g_PlayerList.push_back(play4);
  _nmsp1::g_PlayerList.push_back(play5);
  _nmsp1::g_PlayerList.push_back(play6);
  _nmsp1::g_PlayerList.push_back(play7);

  // 当某个玩家聊天时，同家族的人都应该收到聊天消息
  play1->SayWorlds("断罪之书，终将夺回！");

  // 玩家：法维安    收到了��家：法维安     发送的��天消息
  // 聊天消息内容��断罪之书，终将夺回！
  // 玩家：哈辛达    收到了玩家：法维安     发送�聊天消息
  // 聊天消息内容：断罪之书，终将夺回！
  // 玩家：沙木亚    收到了玩家：法维安     发送的聊天消息
  // 聊天消息内容：断罪之书，终将夺�！
  // 玩家：蓝焰女王    收到了玩家：法维安     发送的聊天消息
  // 聊天消��内容：断罪之书，终将夺回！

  std::cout << "---------------------------------------------------------" << std::endl;

  // 创建游戏玩家
  _nmsp2::Fighter *play12 = new _nmsp2::F_Warrior(10, "法维安");
  _nmsp2::Fighter *play22 = new _nmsp2::F_Priest(11, "哈辛达");
  _nmsp2::Fighter *play32 = new _nmsp2::F_Mage(12, "菲奥娜");
  _nmsp2::Fighter *play42 = new _nmsp2::F_Warrior(13, "沙木亚");
  _nmsp2::Fighter *play52 = new _nmsp2::F_Mage(14, "哈比");
  _nmsp2::Fighter *play62 = new _nmsp2::F_Warrior(15, "周虹");
  _nmsp2::Fighter *play72 = new _nmsp2::F_Priest(16, "蓝焰女王");

  play12->SetFamilyID(100);
  play22->SetFamilyID(100);
  play32->SetFamilyID(110);
  play42->SetFamilyID(100);
  play52->SetFamilyID(140);
  play62->SetFamilyID(140);
  play72->SetFamilyID(100);

  // 创建通知器
  _nmsp2::Notifier *ptalk = new _nmsp2::TalkNotifier();

  // 将玩家增加到家族列表中来，这样才能收到家族消息
  ptalk->addToList(play72);
  ptalk->addToList(play62);
  ptalk->addToList(play52);
  ptalk->addToList(play42);
  ptalk->addToList(play32);
  ptalk->addToList(play22);
  ptalk->addToList(play12);

  // 某玩家聊天时，同组人都应该收到消息

  ptalk->removeFromList(play42);
  // 将玩家 play42 踢出群聊

  play72->SayWorlds("断剑重铸之日，骑士归来之时！", ptalk);
  // ---------------------------------------------------------
  // 玩家：蓝焰女王    收到了玩家：蓝焰女王     发送的聊天消息
  // 聊天消息内容：断剑重铸之日，骑士归来之时！
  // 玩家：哈辛达    收到了玩家：蓝焰女王     发送的聊天消息
  // 聊天消息内容：断剑重铸之日，骑士归来之时！
  // 玩��：法维安    收到了玩家：蓝焰女王     发送的聊天消息
  // 聊天消息内容�断剑重铸之日，骑士归来之时！

  std::cout << "---------------------------------------------------------" << std::endl;

  play62->SayWorlds("越千山红尘险峻，历无常覆水难收", ptalk);
  // ---------------------------------------------------------
  // 玩家：周虹    收到了玩家：周虹     发送的聊天消息
  // 聊天消息内容：越千山红尘险峻，历无常覆水难收
  // 玩家：哈比    收到了玩家：周虹     发送的聊天消息
  // 聊天消息内容：越千山红尘险峻，历无常覆水难收

  return 0;
}
