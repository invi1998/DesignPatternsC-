#include <iostream>
#include <list>

using namespace std;

// 情景模拟
// 饭馆点菜：

namespace _nmsp1
{
  // 厨师类
  class Cook
  {
  public:
    // 做红烧鱼
    void cook_fish()
    {
      std::cout << "做红烧鱼" << std::endl;
    }

    // 做锅包肉
    void cook_meat()
    {
      std::cout << "做锅包肉" << std::endl;
    }
  };

  // 试想一下，如果这个饭馆里来的顾客较多，每个顾客都直接把菜品报给厨师的话，厨师容易记错，产生混乱
  // 使用需要引入一个新类（便签命令类），每个顾客一个便签，然后顾客将菜品写在便签上，
  // 厨师依据收到的便签顺序以及每个便签上的菜品编号进行做菜
  // 怎么写这个命令模式？
  // 首先我们需要将厨师能做的每样菜看成一个命令，首先创建命令对应的抽象父类（Command）

  // 菜单命令（抽象类）
  class Command
  {
  public:
    Command(Cook *p_cook)
    {
      m_pcook = p_cook;
    }

    virtual ~Command()
    {
      if (m_pcook != nullptr)
      {
        delete m_pcook;
        m_pcook = nullptr;
      }
    }

    virtual void Excute() = 0;
    // 纯虚函数（子类要在Excute中要具体实现厨师要制作的菜品）

  protected:
    Cook *m_pcook; // 子类需要访问（定义为protected修饰）
  };

  // 做红烧鱼命令
  class CommandFish : public Command
  {
  public:
    CommandFish(Cook *pcook) : Command(pcook)
    {
    }

    virtual void Excute()
    {
      m_pcook->cook_fish();
    }
  };

  // 做锅包肉命令
  class CommandMeat : public Command
  {
  public:
    CommandMeat(Cook *pcook) : Command(pcook)
    {
    }

    virtual void Excute()
    {
      m_pcook->cook_meat();
    }
  };

  // 上面的命令其实就是将一个动作封装成了一个对象

  // 现在改成这种命令模式是顾客直接下单，为了提高效率，可以引入一个服务员类，然后顾客将菜品写到便签上
  // 交给服务员,由服务员进行下单

  // 服务员类
  class Vaiter
  {
  public:
    void SetCommand(Command *pconm) // 顾客将便签交给服务员
    {
      m_pComand = pconm;
    }

    void Notify() // 服务员将菜品便签交到厨师手里，让厨师开始做菜
    {
      m_pComand->Excute();
    }

  private:
    Command *m_pComand;
    // 服务员手中的顾客点的菜品便签（顾客的点菜命令）
  };

  // 实习服务员类（其实和上面的vaiter服务员类一样，都是一道菜一道菜进行点菜的）
  class TrailingVaiter
  {
  public:
    TrailingVaiter(Command *pcom) : m_pComand(pcom)
    {
    }

    void Notify()
    {
      m_pComand->Excute();
    }

    ~TrailingVaiter()
    {
      if (m_pComand != nullptr)
      {
        delete m_pComand;
        m_pComand = nullptr;
      }
    }

  private:
    Command *m_pComand;
  };

  // 现在这个服务员一次只能通知一道菜品，假设顾客在便签上写了多到菜品（或者一次性给服务递了多个便签）
  // 那这个时候就需要重新设计和这个服务员类了

  // 高级服务员
  class VaiterHighLevel
  {
  public:
    void addCommand(Command *pconm) // 顾客将便签交给服务员
    {
      m_ComandList.push_back(pconm);
    }

    // 如果顾客想撤单，则将便签从列表中移除
    void delCommand(Command *pconm)
    {
      m_ComandList.remove(pconm);
    }

    void Notify() // 服务员将菜品便签交到厨师手里，让厨师开始做菜
    {
      for (auto iter = m_ComandList.begin(); iter != m_ComandList.end(); ++iter)
      {
        (*iter)->Excute();
      }
    }

  private:
    list<Command *> m_ComandList;
    // 服务员手中的顾客点的菜品便签（顾客的点菜命令）
    // 菜品列表
  };

  // ------------------------------
  // 宏命令：把多个命令组合
  class CommandMacro : public Command
  {
  public:
    void addCommand(Command *pcom)
    {
      m_commlist.push_back(pcom);
    }

    void Notify() // 服务员将菜品便签交到厨师手里，让厨师开始做菜
    {
      for (auto iter = m_commlist.begin(); iter != m_commlist.end(); ++iter)
      {
        (*iter)->Excute();
      }
    }

  private:
    list<Command *> m_commlist;
  };
}

// 在上面这个范例中，我们在构造这个对象的时候，往往需要通过参数传递进去一个事先构造好的对象，
// 考虑到Command对象独立使用的时候的方便性，我们可以调整一下Command的代码，在Command对象的析构函数中
// 释放m_pcook所指向的对象内存

// 然后考虑到确实有需求可能需要一道一道菜品单独交给厨师，所以这里实现一个TrailingVaiter类，
// 他和我们上面实现的Viter类其实是一样的，只是考虑到TrailingVaiter这个类独立使用的方便性，
// 这里我们就取消掉这个setCommand成员函数，考虑加一个构造函数和一个析构函数

int main()
{
  _nmsp1::Cook *cook = new _nmsp1::Cook();
  cook->cook_fish();
  cook->cook_meat();

  std::cout << "命令模式" << std::endl;

  // _nmsp1::Command* com1 = new _nmsp1::CommandFish(cook);

  // _nmsp1::Command* com2 = new _nmsp1::CommandMeat(cook);

  _nmsp1::Command *com1 = new _nmsp1::CommandFish(new _nmsp1::Cook());

  _nmsp1::Command *com2 = new _nmsp1::CommandMeat(new _nmsp1::Cook());

  std::cout << "顾客直接点菜" << std::endl;

  com1->Excute();
  // 做红烧鱼
  com2->Excute();
  // 做锅包肉

  std::cout << "顾客点菜交给服务员，让服务员交给厨师" << std::endl;

  _nmsp1::Vaiter *vait = new _nmsp1::Vaiter();

  vait->SetCommand(com1);
  vait->Notify();
  // 做红烧鱼

  vait->SetCommand(com2);
  vait->Notify();
  // 做锅包肉

  std::cout << "实习服务员点菜" << std::endl;
  _nmsp1::TrailingVaiter *tvaiter = new _nmsp1::TrailingVaiter(new _nmsp1::CommandFish(new _nmsp1::Cook()));

  tvaiter->Notify();
  // 做红烧鱼

  std::cout << "顾客批量点菜" << std::endl;

  _nmsp1::VaiterHighLevel *hv = new _nmsp1::VaiterHighLevel();
  hv->addCommand(com1);
  hv->addCommand(com2);

  hv->Notify();
  // 做红烧鱼
  // 做锅包肉

  delete cook;

  return 0;
}