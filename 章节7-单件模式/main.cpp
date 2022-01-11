#include <iostream>

using namespace std;

// 情景模拟，假设现在需要添加游戏配置相关的类，全局控制游戏音量，游戏画质，等全局游戏配置

namespace _nmsp1
{
  class GameConfig
  {
  private:
    GameConfig() {}
    GameConfig(const GameConfig &tmpobj);            // 拷贝构造私有
    GameConfig &operator=(const GameConfig &tmpobj); // 拷贝赋值私有
    ~GameConfig() {}

  public:
    static GameConfig *getInstance()
    {
      // 这种代码在多线程
      if (m_instance == nullptr)
      {
        // 懒汉式内存释放方式2，需要在这里定义一个静态的内存释放嵌套类对象
        // 实现原理就是，在程序执行这行代码的时候，掉一共getinstance获取单例对象，
        // 那么在这里就会创建该内存回收类对象，该对象在程序执行结束之前会由系统进行内存回收，
        // 然后调用析构函数，在析构函数中对单例类对象进行内存释放
        static Garbo garbobj;
        m_instance = new GameConfig();
      }
      return m_instance;
    }

    // 内存回收方案1
    // 这种手工提供新的内存释放函数的方式，并不方便，而且要考虑线程安全问题（下面这里没有考虑）
  public:
    static void freeInstance()
    {
      if (m_instance != nullptr)
      {
        delete GameConfig::m_instance;
        GameConfig::m_instance = nullptr;
      }
    }

    // 内存回收方案2
    // 类中套一个类。手工释放单件例对象引入的GameConfig类中的嵌套类
  private:
    class Garbo
    {
    public:
      ~Garbo()
      {
        if (GameConfig::m_instance != nullptr)
        {
          delete GameConfig::m_instance;
          GameConfig::m_instance = nullptr;
        }
      }
    };

  private:
    static GameConfig *m_instance; // 指向本类对象的指针
  };

  GameConfig *GameConfig::m_instance = nullptr; // 在类外（在某个.cpp源文件开头位置，为静态成员变量赋值）
}

namespace _nmsp2
{
  class GameConfig
  {
  private:
    GameConfig() {}
    GameConfig(const GameConfig &tmpobj);            // 拷贝构造私有
    GameConfig &operator=(const GameConfig &tmpobj); // 拷贝赋值私有
    ~GameConfig() {}

  public:
    static GameConfig *getInstance()
    {
      return m_instance;
    }

    // 内存回收方案
    // 类中套一个类。手工释放单件例对象引入的GameConfig类中的嵌套类
  private:
    class Garbo
    {
    public:
      ~Garbo()
      {
        if (GameConfig::m_instance != nullptr)
        {
          delete GameConfig::m_instance;
          GameConfig::m_instance = nullptr;
        }
      }
    };

    // 饿汉式释放产生的内存
    // 首先，如果单件类代码是以饿汉式编写，那么不管单件类是否被调用，该单件类对象都是存在的，
    // 这个时候，我们可以在GameConfig类定义中增加一个private修饰的静态成员变量
    // 然后在累外面，某个.cpp源文件开头位置，给这个静态成员变量进行定义
  private:
    static Garbo garbobj;

  private:
    static GameConfig *m_instance; // 指向本类对象的指针
  };

  GameConfig *GameConfig::m_instance = new GameConfig();
  // 蹭静态成员变量初始化的时机，直接进行初始化是允许的，即使构造函数是private修饰也是允许的
  // 因为这行代码是在main函数之前就执行了，所以在main函数中，创建多线程的时候，m_instance已经有有效值了

  // 这就是饿汉式单例实现，也就是程序代码一执行，不管你掉没调用getinstance这个成员函数，这个单件里就已经被创建了
  // 该模式下的单件类创建方式，不受多线程问题的困扰

  // 内存释放
  // 在累外面，某个.cpp源文件开头位置，给这个静态成员变量进行定义赋值
  GameConfig::Garbo GameConfig::garbobj;
}

namespace _nmsp3
{
  class GameConfig
  {
  private:
    GameConfig() {}
    GameConfig(const GameConfig &tmpobj);            // 拷贝构造私有
    GameConfig &operator=(const GameConfig &tmpobj); // 拷贝赋值私有
    ~GameConfig() {}

  public:
    static GameConfig *getInstance()
    {
      return &m_instance;
    }

  private:
    static GameConfig m_instance;
  };

  GameConfig GameConfig::m_instance;
}

namespace _nmsp4
{
  // 实现方法是让getInstance返回局部静态变量的引用class GameConfig
  class GameConfig
  {
  private:
    GameConfig() {}
    GameConfig(const GameConfig &tmpobj);            // 拷贝构造私有
    GameConfig &operator=(const GameConfig &tmpobj); // 拷贝赋值私有
    ~GameConfig() {}

  public:
    static GameConfig &getInstance()
    {
      static GameConfig intance;
      // 注意区别 函数第一次执行时被初始化的静态变量      与
      //          通过编译期常量进行初始化的基本类型静态变量

      // 这里 instance 就是属于第一种情况。
      // 这里的 instance 他不是基本类型，他是类类型
      // 类类型静态变量他不一样，在这里你不调用getInstance这个静态变量instance就不会被初始化

      return intance;
    }
  };
}

// 通过编译期常量进行初始化的基本类型静态变量
// 比如在这里写一个函数
int myfunc()
{
  static int stec = 100;
  // 这里 就属于 通过编译期常量进行初始化的基本类型静态变量
  // 这里的 stec 什么时候等于100？
  // 不需要掉一共myfun函数，stec就已经等于100了
  // 这里如果采用断点调试，会发现，如果你调用这个方法，然后断点调试走进来的时候
  // 会发现根本就不会执行这行代码，会直接跳过这行static代码，玩下执行

  stec += 100;
  return stec;
}

int main()
{
  _nmsp1::GameConfig *g_gc = _nmsp1::GameConfig::getInstance();

  // 因为我们把构造函数进行了私有化，所以我们没办法在外部在栈上或者堆上创建该对象

  _nmsp4::GameConfig &g_gc4 = _nmsp4::GameConfig::getInstance();

  return 0;
}
