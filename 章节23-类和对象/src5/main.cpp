#include <iostream>

using namespace std;

namespace _nmsp1
{
  class Human
  {
  public:
    virtual ~Human()
    {
    }
  };

  class Man : private Human
  {
  public:
  };

  void func()
  {
    Man myman;
    // Human& myhuman = myman; // 父类引用绑定子类对象
    // Human* myhuman2 = new Man;  // 父类指针指向子类对象
  }
}

// 希望每隔10秒中就向屏幕输出当前队列中有多少条消息，（这些消息属于尚未被处理的，如果被处理过的，就会被从消息队列中拿走了）

namespace _nmsp2
{

  class Timer
  {
  public:
    Timer(int inttimer); // inttimer表示间隔多少ms调用一次

    virtual void CallBack(); // 一个到时间后就会被调用的虚函数
  };

  // 消息队列类
  class MsgQueue : private Timer
  {
  public:
    // 构造函数，。。。
  private:
    virtual void CallBack();
  };

}

int main()
{
  cout << "Hello World";

  return 0;
}