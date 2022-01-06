/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby,
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

// 情景模拟：公司员工的工作日报，包含标题，内容主题，结尾三部分
// 标题部分 包含 部门名称，日报生成日期
// 内容主题部分 包含 具体描述（可能有多条）
// 结尾：包含姓名

// 将日报导出成多种格式的文件，比如纯文本，XML格式，JSON格式

// 不用设计模式实现上述需求
namespace _nmsp1
{
  // 标题部分
  class DailyHeaderData
  {
  public:
    DailyHeaderData(string name, string date) : m_strDepName(name), M_strGenDate(date)
    {
    }

    // 获取部门名称
    string getDepName()
    {
      return m_strDepName;
    }

    // 获取日报生成日期
    string getGenDate()
    {
      return M_strGenDate;
    }

  private:
    string m_strDepName; // 部门名称
    string M_strGenDate; // 日报生成日期
  };

  // 日报主题部分 日报主题中的每一条描述数据
  class DailyContentData
  {
  public:
    DailyContentData(string content, double dsTime) : m_strContent(content), m_dspendTime(dsTime)
    {
    }

    // 获取工作内容
    string getContent()
    {
      return m_strContent;
    }

    // 获取工作时长
    double getDspenTime()
    {
      return m_dspendTime;
    }

  private:
    string m_strContent; // 该项工作内容描述
    double m_dspendTime; // 完成该项工作花费的时间（单位小时）
  };

  // 日报中的结尾部分
  class DailyFooterData
  {
  public:
    DailyFooterData(string name) : m_strUserName(name)
    {
    }

    // 获取日报所属员工姓名
    string getUserName()
    {
      return m_strUserName;
    }

  private:
    string m_strUserName; // 日报所属的员工姓名
  };

  // 将日报导出 为 纯文本
  class EportToTextFile
  {
  public:
    // 实现导出动作
    void doExport(DailyHeaderData &dailiHeadobj, std::vector<DailyContentData *> &vec_dailycontobj, DailyFooterData &dailyFooterobj)
    {
      string strtmp = "";
      // 拼标题
      strtmp += dailiHeadobj.getDepName() + "," + dailiHeadobj.getGenDate() + "\n";

      // 拼接内容主题（内容可能会有多条，所以这里需要迭代一下）
      for (auto iter = vec_dailycontobj.begin(); iter != vec_dailycontobj.end(); ++iter)
      {
        ostringstream oss; // #include <sstream>
        oss << (*iter)->getDspenTime();
        strtmp += (*iter)->getContent() + ": 【花费的时间:" + oss.str() + "小时】" + "\n";
      }

      // 拼接结尾
      strtmp += "报告人：" + dailyFooterobj.getUserName() + "\n";

      // 导出文件（略），只展示到屏幕
      std::cout << strtmp << std::endl;
    }
  };

  // 将日报导出成xml格式
  class ExportToXmlFile
  {
  public:
    // 实现导出动作
    void doExport(DailyHeaderData &dailiHeadobj, std::vector<DailyContentData *> &vec_dailycontobj, DailyFooterData &dailyFooterobj)
    {
      string strtmp = "";
      // 拼标题
      strtmp += "<?xml version = \"1.0.0\" encoding=\"utf-8\" ?> \n";
      strtmp += "<DailyReport>\n";
      strtmp += "     <Header>\n";
      strtmp += "         <Depname>" + dailiHeadobj.getDepName() + "</Depname>\n";
      strtmp += "         <GenDate>" + dailiHeadobj.getGenDate() + "</GenDate>\n";
      strtmp += "     </Header>\n";

      // 拼接内容主题（内容可能会有多条，所以这里需要迭代一下）
      strtmp += "     <Body>\n";
      for (auto iter = vec_dailycontobj.begin(); iter != vec_dailycontobj.end(); ++iter)
      {
        ostringstream oss; // #include <sstream>
        oss << (*iter)->getDspenTime();

        strtmp += "         <Content>" + (*iter)->getContent() + "</Content>\n";
        strtmp += "         <SpendTime>花费的时间:" + oss.str() + "小时</SpendTime>\n";
      }
      strtmp += "     </Body>\n";

      // 拼接结尾
      strtmp += "     <Footer>\n";
      strtmp += "         <UserName>报告人：" + dailyFooterobj.getUserName() + "</UserName>\n";
      strtmp += "     </Footer>\n";

      strtmp += "</DailyReport>\n";

      // 导出文件（略），只展示到屏幕
      std::cout << strtmp << std::endl;
    }
  };

}

// 导出到文件，有3个步骤保持不变
// 1：拼接标题
// 2：拼接内容
// 3：拼接结尾

// 所以，考虑把这3个步骤（复杂对象的构建过程）提炼抽象出来，形成一个通用的处理过程
// 建造者模式的初衷：将构建不同格式数据的细节实现代码与具体的构建步骤分离达到复用构建步骤的目的

namespace _nmsp2
{
  // 标题部分
  class DailyHeaderData
  {
  public:
    DailyHeaderData(string name, string date) : m_strDepName(name), M_strGenDate(date)
    {
    }

    // 获取部门名称
    string getDepName()
    {
      return m_strDepName;
    }

    // 获取日报生成日期
    string getGenDate()
    {
      return M_strGenDate;
    }

  private:
    string m_strDepName; // 部门名称
    string M_strGenDate; // 日报生成日期
  };

  // 日报主题部分 日报主题中的每一条描述数据
  class DailyContentData
  {
  public:
    DailyContentData(string content, double dsTime) : m_strContent(content), m_dspendTime(dsTime)
    {
    }

    // 获取工作内容
    string getContent()
    {
      return m_strContent;
    }

    // 获取工作时长
    double getDspenTime()
    {
      return m_dspendTime;
    }

  private:
    string m_strContent; // 该项工作内容描述
    double m_dspendTime; // 完成该项工作花费的时间（单位小时）
  };

  // 日报中的结尾部分
  class DailyFooterData
  {
  public:
    DailyFooterData(string name) : m_strUserName(name)
    {
    }

    // 获取日报所属员工姓名
    string getUserName()
    {
      return m_strUserName;
    }

  private:
    string m_strUserName; // 日报所属的员工姓名
  };

  // 抽象构建器类
  // 文件构建器父类
  class FileBuilder
  {
  public:
    ~FileBuilder() {}

  public:
    virtual void buildHeader(DailyHeaderData &dailyHeadobj) = 0;      // 拼接标题
    virtual void buildBody(std::vector<DailyContentData *> &vec) = 0; // 拼接内容
    virtual void buildFooter(DailyFooterData &dailyFooterobj) = 0;    // 拼接结尾

    string GetResult()
    {
      return m_strResult;
    }

  protected:
    string m_strResult;
  };

  // 纯文本文件构建器
  class TxtFileBuilder : public FileBuilder
  {
  public:
    virtual void buildHeader(DailyHeaderData &dailyHeadobj) // 拼接标题
    {
      m_strResult += dailyHeadobj.getDepName() + "," + dailyHeadobj.getGenDate() + "\n";
    }

    virtual void buildBody(std::vector<DailyContentData *> &vec) // 拼接内容
    {
      for (auto iter = vec.begin(); iter != vec.end(); ++iter)
      {
        ostringstream oss; // #include <sstream>
        oss << (*iter)->getDspenTime();
        m_strResult += (*iter)->getContent() + ": 【花费的时间:" + oss.str() + "小时】" + "\n";
      }
    }

    virtual void buildFooter(DailyFooterData &dailyFooterobj) // 拼接结尾
    {
      m_strResult += "报告人：" + dailyFooterobj.getUserName() + "\n";
    }
  };

  // xml文件构建器
  class XmlFileBuilder : public FileBuilder
  {
  public:
    virtual void buildHeader(DailyHeaderData &dailyHeadobj) // 拼接标题
    {
      m_strResult += "<?xml version = \"1.0.0\" encoding=\"utf-8\" ?> \n";
      m_strResult += "<DailyReport>\n";
      m_strResult += "     <Header>\n";
      m_strResult += "         <Depname>" + dailyHeadobj.getDepName() + "</Depname>\n";
      m_strResult += "         <GenDate>" + dailyHeadobj.getGenDate() + "</GenDate>\n";
      m_strResult += "     </Header>\n";
    }

    virtual void buildBody(std::vector<DailyContentData *> &vec) // 拼接内容
    {
      m_strResult += "     <Body>\n";
      for (auto iter = vec.begin(); iter != vec.end(); ++iter)
      {
        ostringstream oss; // #include <sstream>
        oss << (*iter)->getDspenTime();

        m_strResult += "         <Content>" + (*iter)->getContent() + "</Content>\n";
        m_strResult += "         <SpendTime>花费的时间:" + oss.str() + "小时</SpendTime>\n";
      }
      m_strResult += "     </Body>\n";
    }

    virtual void buildFooter(DailyFooterData &dailyFooterobj) // 拼接结尾
    {
      m_strResult += "     <Footer>\n";
      m_strResult += "         <UserName>报告人：" + dailyFooterobj.getUserName() + "</UserName>\n";
      m_strResult += "     </Footer>\n";

      m_strResult += "</DailyReport>\n";
    }
  };

  // 实现文件指挥者类
  class FileDirector
  {
  public:
    FileDirector(FileBuilder *ptmpBuilder) // 构造函数
    {
      m_pFileBuilder = ptmpBuilder;
    }

    // 组装文件
    string Construct(DailyHeaderData &dailyHeadobj, std::vector<DailyContentData *> &vec_dailycontobj, DailyFooterData &dailyFooterobj)
    {
      // 有时指挥者需要和构建器通过参数传递的方式交换数据（这里你交给我指挥者做的事情，我直接委托给构建器来做）
      m_pFileBuilder->buildHeader(dailyHeadobj);
      m_pFileBuilder->buildBody(vec_dailycontobj);
      m_pFileBuilder->buildFooter(dailyFooterobj);

      return m_pFileBuilder->GetResult();
    }

  private:
    FileBuilder *m_pFileBuilder; // 指向所有构建器类的父类指针
  };

  void func()
  {
    DailyHeaderData *pdhd = new DailyHeaderData("大数据中心", "2022年1月6日19:53:24");
    DailyContentData *pdcd1 = new DailyContentData("完成数据模型分析整理工作", 3.55);
    DailyContentData *pdcd2 = new DailyContentData("完成代码编辑合数据建模工作", 5.95);
    DailyContentData *pdcd3 = new DailyContentData("完成完站制作和测试优化工作", 0.34);

    std::vector<DailyContentData *> vec_dcd;
    vec_dcd.push_back(pdcd1);
    vec_dcd.push_back(pdcd2);
    vec_dcd.push_back(pdcd3);

    DailyFooterData *pdfd = new DailyFooterData("invi");

    // 创建一个Xml构建器
    FileBuilder *pfb = new XmlFileBuilder();
    // 把XML构建器传递给指挥者，实例化一个指挥者
    FileDirector *fdr = new FileDirector(pfb);

    string file = fdr->Construct(*pdhd, vec_dcd, *pdfd);

    std::cout << file << std::endl;
    // <?xml version = "1.0.0" encoding="utf-8" ?>
    // <DailyReport>
    //      <Header>
    //          <Depname>大数据��心</Depname>
    //          <GenDate>2022年1月6日19:53:24</GenDate>
    //      </Header>
    //      <Body>
    //          <Content>完成数据模型分析整理工作</Content>
    //          <SpendTime>花费的时间:3.55小时</SpendTime>
    //          <Content>完成代码编辑合数据建模工作</Content>
    //          <SpendTime>花费的时间:5.95小时</SpendTime>
    //          <Content>完成完站制作和测试优化工作</Content>
    //          <SpendTime>花费的时间:0.34小时</SpendTime>
    //      </Body>
    //      <Footer>
    //          <UserName>报告人：invi</UserName>
    //      </Footer>
    // </DailyReport>

    // 释放内存
    delete pfb;
    delete fdr;

    delete pdhd;

    for (auto iter = vec_dcd.begin(); iter != vec_dcd.end(); ++iter)
    {
      delete *iter;
    }

    delete pdfd;
  }
}

int main()
{
  _nmsp1::DailyHeaderData *pdhd = new _nmsp1::DailyHeaderData("游戏事业部", "2022年1月6日14:13:03");
  _nmsp1::DailyContentData *pdcd1 = new _nmsp1::DailyContentData("完成aaaaaaaaaaaaaaaaaa------工作", 3.55);
  _nmsp1::DailyContentData *pdcd2 = new _nmsp1::DailyContentData("完成代码编辑------工作", 5.95);
  _nmsp1::DailyContentData *pdcd3 = new _nmsp1::DailyContentData("完成对外打包发布------工作", 0.34);

  std::vector<_nmsp1::DailyContentData *> vec_dcd;
  vec_dcd.push_back(pdcd1);
  vec_dcd.push_back(pdcd2);
  vec_dcd.push_back(pdcd3);

  _nmsp1::DailyFooterData *pdfd = new _nmsp1::DailyFooterData("invi");

  _nmsp1::EportToTextFile file_ettxt;
  file_ettxt.doExport(*pdhd, vec_dcd, *pdfd);
  // 游戏事业部,2022年1月6日14:13:03
  // 完成aaaaaaaaaaaaaaaaaa------工作: 【花费的时间:3.55小时】
  // 完成代码编辑------工作: 【花费的时间:5.95小时】
  // 完成对外打包发布------工作: 【花费的时间:0.34小时】
  // 报�人：invi

  std::cout << "---------------------------xml---------------------------" << std::endl;

  _nmsp1::ExportToXmlFile file_etxml;
  file_etxml.doExport(*pdhd, vec_dcd, *pdfd);
  // <?xml version = "1.0.0" encoding="utf-8" ?>
  // <DailyReport>
  //      <Header>
  //          <Depname>游戏事业部</Depname>
  //          <GenDate>2022年1月6日14:13:03</GenDate>
  //      </Header>
  //      <Body>
  //          <Content>完成aaaaaaaaaaaaaaaaaa------工作</Content>
  //          <SpendTime>花费的时间:3.55��时</SpendTime>
  //          <Content>完成代码编辑------工作</Content>
  //          <SpendTime>花费的时间:5.95小时</SpendTime>
  //          <Content>完成对外打包发布------工�</Content>
  //          <SpendTime>花费的时间:0.34小时</SpendTime>
  //      </Body>
  //      <Footer>
  //          <UserName>报告人：invi</UserName>
  //      </Footer>
  // </DailyReport>

  delete pdhd;

  for (auto iter = vec_dcd.begin(); iter != vec_dcd.end(); ++iter)
  {
    delete *iter;
  }

  delete pdfd;

  _nmsp2::func();

  return 0;
}
