#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

namespace _nmsp1
{
  // 缓存 / 缓冲代理范例（Cache Proxy）
  std::vector<string> g_fileItemList;

  // 抽象主题
  class ReadInfo
  {
  public:
    virtual void read() = 0;

    virtual ~ReadInfo() {}
  };

  // 真实主题 (真正从文件中读取信息的)
  class ReadInfoFromFile : public ReadInfo
  {
  public:
    virtual void read()
    {
      ifstream fin("file.txt");
      if (!fin)
      {
        std::cout << "文件打开失败" << std::endl;
        return;
      }

      string linebuf;
      while (getline(fin, linebuf)) // 从文件中逐行读入内容
      {
        if (!linebuf.empty()) // 读的不是空行
        {
          g_fileItemList.push_back(linebuf); // 将文件中的每一行都保存到容器中
        }
      }

      fin.close(); // 关闭文件输入流
    }
  };

  // 代理主题
  class ReadInfoProxy : public ReadInfo
  {
  public:
    virtual void read()
    {
      if (!m_loaded)
      {
        // 没有从文件中载入信息，则载入
        m_loaded = true;
        std::cout << "从文件中读取了如下数据--------" << std::endl;
        ReadInfoFromFile *rf = new ReadInfoFromFile();
        rf->read();
        delete rf;
      }
      else
      {
        std::cout << "从缓存中读取了如下数据---------" << std::endl;
      }

      // 现在数据一定在g_fileItemList中，开始显示
      for (auto iter = g_fileItemList.begin(); iter != g_fileItemList.end(); ++iter)
      {
        std::cout << *iter << std::endl;
      }
    }

  private:
    bool m_loaded = false; // 表示是否真实的从文件中读取内容（false表示没有从文件中读数据到内存）
  };

  void func()
  {
    ReadInfo *pread = new ReadInfoProxy();
    // 第一次使用代理，从真实文件中拿取数据
    pread->read();
    // 从文件中读取了如下数据--------
    // 1-----------1-line-----------1
    // 2-----------2-line-----------2
    // 3-----------3-line-----------3
    // 4-----------4-line-----------4
    // 5-----------5-line-----------5
    // 6-----------6-line-----------6
    // 7-----------7-line-----------7

    // 第二次调用代理，从缓存中拿取数据
    pread->read();
    // 从缓存中读取了如下数据---------
    // 1-----------1-line-----------1
    // 2-----------2-line-----------2
    // 3-----------3-line-----------3
    // 4-----------4-line-----------4
    // 5-----------5-line-----------5
    // 6-----------6-line-----------6
    // 7-----------7-line-----------7

    delete pread;
  }
}

int main()
{
  _nmsp1::func();
  return 0;
}