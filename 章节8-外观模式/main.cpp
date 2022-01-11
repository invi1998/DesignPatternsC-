#include <iostream>

using namespace std;

// 情景模拟
// 程序计划将界面配置，游戏音量配置，语音聊天配置 设计成单件类

namespace _nmsp1
{
  // 图形相关的配置类
  class Graphic
  {
  private:
    Graphic() {}
    Graphic(const Graphic &tmpobj);
    Graphic &operator=(const Graphic &tmpobj);
    ~Graphic() {}

  public:
    static Graphic &getInstance()
    {
      static Graphic instance;
      return instance;
    }

  public:
    // 是否全屏显示
    void dispaly(bool enable)
    {
      std::cout << "图形设置 -> 是否全屏显示 ？ " << enable << std::endl;
    }
    // 是否开启游戏特效
    void effect(bool enable)
    {
      std::cout << "图形设置 -> 是否开启特效 ？ " << enable << std::endl;
    }
    // 设置游戏分辨率
    void resolution(int index)
    {
      std::cout << "图形设置 -> 设置游戏分辨率 ？ " << index << std::endl;
    }
    // 是否开启抗锯齿
    void antialiasing(bool enable)
    {
      std::cout << "图形设置 -> 是否开启抗锯齿 ？ " << enable << std::endl;
    }
  };

  // 声音相关的配置类
  class Sound
  {
  private:
    Sound() {}
    Sound(const Sound &tmpobj);
    Sound &operator=(const Sound &tmpobj);
    ~Sound() {}

  public:
    static Sound &getInstance()
    {
      static Sound instance;
      return instance;
    }

  public:
    // 游戏背景音
    void bgsound(int level)
    {
      std::cout << "游戏声音配置 -> 背景音量？" << level << std::endl;
    }

    // 游戏环境音
    void envsound(int level)
    {
      std::cout << "游戏声音配置 -> 环境音量？" << level << std::endl;
    }

    // 游戏人物音
    void npcsound(int level)
    {
      std::cout << "游戏声音配置 -> 游戏人物音量？" << level << std::endl;
    }

    // 设置全局总音量
    void setVolume(int level)
    {
      std::cout << "游戏声音配置 -> 全局音量？" << level << std::endl;
    }
  };

  // 语音聊天相关的配置类
  class ChatVoice
  {
  private:
    ChatVoice() {}
    ChatVoice(const ChatVoice &tmpobj);
    ChatVoice &operator=(const ChatVoice &tmpobj);
    ~ChatVoice() {}

  public:
    static ChatVoice &getInstance()
    {
      static ChatVoice instance;
      return instance;
    }

  public:
    // 话筒音量
    void micvolume(int level)
    {
      std::cout << "语音聊天 -> 麦克风音量大小 ？" << level << std::endl;
    }

    // 降噪等级
    void noiseReduction(int level)
    {
      std::cout << "语音聊天 -> 降噪等级 ？" << level << std::endl;
    }

    // 音量设置
    void chatvolume(int level)
    {
      std::cout << "语音聊天 -> 聊天音量 ？" << level << std::endl;
    }
  };

  // ----------------------------------------------------------------------------------------
  // 引入外观模式
  // 扮演外观模式角色的类
  class Conffacade
  {
  private:
    Conffacade() {}
    Conffacade(const Conffacade &tmpobj);
    Conffacade &operator=(const Conffacade &tmpobj);
    ~Conffacade() {}

  public:
    static Conffacade &getInstance()
    {
      static Conffacade instance;
      return instance;
    }

  public:
    // 低配机通用配置设置
    void LowConfComputer()
    {
      Graphic &g_gp = Graphic::getInstance();
      g_gp.dispaly(true);
      g_gp.effect(false);
      g_gp.resolution(720);
      g_gp.antialiasing(false);

      Sound &g_sound = Sound::getInstance();
      g_sound.bgsound(0);
      g_sound.envsound(55);
      g_sound.npcsound(80);
      g_sound.setVolume(36);

      ChatVoice &g_chat = ChatVoice::getInstance();
      g_chat.micvolume(50);
      g_chat.noiseReduction(0);
      g_chat.chatvolume(45);
    }

    // 高配置通用配置设置
    void HighConfComputer()
    {
      Graphic &g_gp = Graphic::getInstance();
      g_gp.dispaly(true);
      g_gp.effect(true);
      g_gp.resolution(2048);
      g_gp.antialiasing(true);

      Sound &g_sound = Sound::getInstance();
      g_sound.bgsound(65);
      g_sound.envsound(55);
      g_sound.npcsound(80);
      g_sound.setVolume(66);

      ChatVoice &g_chat = ChatVoice::getInstance();
      g_chat.micvolume(100);
      g_chat.noiseReduction(100);
      g_chat.chatvolume(65);
    }
  };

}

int main()
{
  _nmsp1::Graphic &g_gp = _nmsp1::Graphic::getInstance();

  g_gp.dispaly(false);
  g_gp.effect(true);
  g_gp.resolution(2048);
  g_gp.antialiasing(true);
  // 图形设置 -> 是否全屏显示 ？ 0
  // 图形设置 -> 是否开启特效 ？ 1
  // 图形设置 -> 设置游戏分辨率 ？ 2048
  // 图形设置 -> 是否开启抗锯齿 ？ 1

  _nmsp1::Sound &g_sound = _nmsp1::Sound::getInstance();

  g_sound.bgsound(65);
  g_sound.envsound(55);
  g_sound.npcsound(80);
  g_sound.setVolume(36);
  // 游戏声音配置 -> 背景音量？65
  // 游戏声音配置 -> 环境音量？55
  // 游戏声音配置 -> 游戏人物音量？80
  // 游戏声音配置 -> 全局音量？36

  _nmsp1::ChatVoice &g_chat = _nmsp1::ChatVoice::getInstance();

  g_chat.micvolume(70);
  g_chat.noiseReduction(100);
  g_chat.chatvolume(66);
  // 语�聊天 -> 麦克风音量大小 ？70
  // 语音聊天 -> 降噪等级 ？100
  // 语音聊天 -> 聊天音量 ？66

  std::cout << "----------------------------------------------------------------------------------------" << std::endl;

  _nmsp1::Conffacade &conf = _nmsp1::Conffacade::getInstance();
  // 低配机调用
  conf.LowConfComputer();
  // 高配机调用
  conf.HighConfComputer();

  return 0;
}