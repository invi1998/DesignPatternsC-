#include <iostream>

using namespace std;

// 情景模拟：
// 实现一个家庭影院的外观模式：HomeTheaterFacade
// 与电器设备想关联
// 屏幕（screen）灯光（light）音响（speaker）DVD播放器（dvdPlayer）游戏机（playerStation）
// 提供两个接口
// 1：看电影模式    WatchMoive(屏幕打开，音响打开，灯光关闭，dvd打开，游戏机关闭)
// 2：游戏娱乐模式  PlayGame(屏幕打开，音响打开，灯光打开，dvd关闭，游戏机打开)

namespace _nmsp1
{
  // 屏幕：
  class Screen
  {
  public:
    void on()
    {
      std::cout << "屏幕打开！" << std::endl;
    }
    void off()
    {
      std::cout << "屏幕关闭！" << std::endl;
    }
  };

  // 音响：
  class Speaker
  {
  public:
    void on()
    {
      std::cout << "音响打开！" << std::endl;
    }
    void off()
    {
      std::cout << "音响关闭！" << std::endl;
    }
  };

  // 灯光：
  class Light
  {
  public:
    void on()
    {
      std::cout << "灯光打开！" << std::endl;
    }
    void off()
    {
      std::cout << "灯光关闭！" << std::endl;
    }
  };

  // DVD：
  class DvdPlayer
  {
  public:
    void on()
    {
      std::cout << "DVD打开！" << std::endl;
    }
    void off()
    {
      std::cout << "DVD关闭！" << std::endl;
    }
  };

  // 游戏机：
  class PlayerStation
  {
  public:
    void on()
    {
      std::cout << "游戏机打开！" << std::endl;
    }
    void off()
    {
      std::cout << "游戏机关闭！" << std::endl;
    }
  };

  // 家庭影院外观模式类
  class HomeTheaterFacade
  {
  public:
    void WatchMoive()
    {
      // (屏幕打开，音响打开，灯光关闭，dvd打开，游戏机关闭)
      screenObj.on();
      lightObj.off();
      speakerObj.on();
      dvdObj.on();
      playerObj.off();
    }

    void PlayGame()
    {
      // (屏幕打开，音响打开，灯光打开，dvd关闭，游戏机打开)
      screenObj.on();
      lightObj.on();
      speakerObj.on();
      dvdObj.off();
      playerObj.on();
    }

  private:
    Screen screenObj;
    Light lightObj;
    DvdPlayer dvdObj;
    Speaker speakerObj;
    PlayerStation playerObj;
  };

}

int main()
{
  _nmsp1::HomeTheaterFacade homet;
  std::cout << "-----------------影音模式-----------------" << std::endl;
  homet.WatchMoive();
  // -----------------影音模式-----------------
  // 屏幕打开！
  // 灯光关闭！
  // 音响打开！
  // DVD打开！
  // 游戏机关闭！

  std::cout << "-----------------游戏模式-----------------" << std::endl;
  homet.PlayGame();
  // -----------------游戏模��-----------------
  // 屏幕打开！
  // 灯光打开！
  // 音响打开！
  // DVD关闭！
  // 游戏机��开！

  return 0;
}