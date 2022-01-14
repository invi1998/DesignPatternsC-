#include <iostream>

using namespace std;

// 假设有如下日志类，做如下简单的日志操作
namespace _nmsp1
{
  // 日志文件操作相关类
  class LogFile
  {
  public:
    void inifile()
    {
      // 做日志文件初始化工作
      // 。。。
      std::cout << "做日志文件初始化工作" << std::endl;
    }

    void writeFile(const char *pcontent)
    {
      // 将日志内容写入文件
      std::cout << "将日志内容写入文件" << pcontent << std::endl;
    }

    void readfromfile()
    {
      // 从日志文件中读取信息
      std::cout << "从日志文件中读取信息" << std::endl;
    }

    void closefile()
    {
      // 关闭日志文件
      std::cout << "关闭日志文件" << std::endl;
    }
  };

  void func()
  {
    LogFile *_logf = new LogFile();
    _logf->inifile();
    _logf->writeFile("写日志------");
    _logf->readfromfile();
    _logf->closefile();

    delete _logf;
  }
}

// 随着项目迭代，发现这种单纯的向日志文件中记录信息可能会导致日志文件膨胀过大，所以考虑改造日志系统
// 将原有的把日志信息写入到文件改为将日志写入到数据库中

namespace _nmsp2
{
  // 日志文件操作相关类（数据库版本）
  class LogDatebase
  {
  public:
    void initdb()
    {
      // 数据库连接等初始化工作
      // 。。。
    }

    void writetodb(const char *pcontent)
    {
      // 将日志内容写入数据库
    }

    void readfromdb()
    {
      // 从日志数据库中读取信息
    }

    void closedb()
    {
      // 关闭数据库连接
    }
  };

  void func()
  {
    LogDatebase *_logd = new LogDatebase();
    _logd->initdb();
    _logd->writetodb("写日志------");
    _logd->readfromdb();
    _logd->closedb();

    delete _logd;
  }
}

// 假设某天机房断电无法从数据库中读取日志，或者要从文件中读取旧的日志信息
// 那么目前的这两个日志类，要么无法从数据库读，要么无法从日志文件中读。

// 可以考虑使用适配器模式，将LogDatabase中的接口调用适配成LogFile版本
namespace _nmsp3
{
  class LogDatebase
  {
  public:
    virtual void initdb() = 0;
    virtual void writetodb(const char *pcontent) = 0;
    virtual void readfromdb() = 0;
    virtual void closedb() = 0;

    virtual ~LogDatebase() {}
  };

  // 适配器类 （注意这里适配器类中构造函数的形参）
  class LogAdapter : public LogDatebase
  {
  public:
    // 构造函数
    LogAdapter(_nmsp1::LogFile *pfile) : m_logfile(pfile) // 形参是老接口所属的类指针
    {
    }

    virtual void initdb()
    {
      m_logfile->inifile();
    }

    virtual void writetodb(const char *pcontent)
    {
      m_logfile->writeFile(pcontent);
    }

    virtual void readfromdb()
    {
      m_logfile->readfromfile();
    }

    virtual void closedb()
    {
      m_logfile->closefile();
    }

  private:
    _nmsp1::LogFile *m_logfile;
  };

  void func()
  {
    _nmsp1::LogFile *lof = new _nmsp1::LogFile();
    LogDatebase *_logd = new LogAdapter(lof);
    _logd->initdb();
    // 做日志文件初始化工作
    _logd->writetodb("写日志------");
    // 将日志内容写入文件写日志------
    _logd->readfromdb();
    // 从日志文件中读取信息
    _logd->closedb();
    // 关闭日志文件

    delete _logd;
  }
}

// 实现类适配器
namespace _nmsp4
{
  class LogDatebase
  {
  public:
    virtual void initdb() = 0;
    virtual void writetodb(const char *pcontent) = 0;
    virtual void readfromdb() = 0;
    virtual void closedb() = 0;

    virtual ~LogDatebase() {}
  };

  // 类适配器
  // 共有继承新接口，私有继承旧接口
  // 这里公有继承时一个is a关系，也就是通过public继承的子类对象他也一定是一个父类对象
  // 私有继承他是一种组合关系，这里的private继承就是指想通过LogFile这个类来实现出LogAdapter这个类的意思
  // 某些类适配器的实现中不会用private继承（这种其实严格上来说，是不严谨的）
  class LogAdapter : public LogDatebase, private _nmsp1::LogFile
  {
  public:
    // 构造函数
    LogAdapter() // 形参是老接口所属的类指针
    {
    }

    virtual void initdb()
    {
      inifile();
    }

    virtual void writetodb(const char *pcontent)
    {
      writeFile(pcontent);
    }

    virtual void readfromdb()
    {
      readfromfile();
    }

    virtual void closedb()
    {
      closefile();
    }
  };

  void func()
  {
    LogAdapter *_logd = new LogAdapter();
    _logd->initdb();
    // 做日志文件初始化工作
    _logd->writetodb("写日志------");
    // 将日志内容写入文件写日志------
    _logd->readfromdb();
    // 从日志文件中读取信息
    _logd->closedb();
    // 关闭日志文件

    delete _logd;
  }
}

int main()
{
  _nmsp1::func();
  _nmsp2::func();
  _nmsp3::func();
  _nmsp4::func();

  return 0;
}