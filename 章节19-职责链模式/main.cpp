#include <iostream>

using namespace std;

// 加薪请求
// 加薪 <= 1000, 部门经理审批
// 加薪 <= 5000, 加薪 > 1000,  技术总监审批
// 加薪 > 5000， 总经理审批

// 传统方法处理加薪请求
namespace _nmsp1
{
  // 薪水处理类
  class SalaryHander
  {
  public:
    // 处理加薪请求
    void raiseRequest(const string sname, int salfigure) // 员工名， 加薪数额
    {
      if (salfigure <= 1000)
      {
        depManagerSP(sname, salfigure);
      }
      else if (salfigure <= 5000)
      {
        CTOSP(sname, salfigure);
      }
      else
      {
        CEOSP(sname, salfigure);
      }
    }

  private:
    // 部门经理审批加薪请求
    void depManagerSP(const string &sname, int salfigure)
    {
      std::cout << sname << " 的加薪要求为：" << salfigure << "元， 部门经理审批通过" << std::endl;
    }

    // 技术总监审批加薪请求
    void CTOSP(const string &sname, int salfigure)
    {
      std::cout << sname << " 的加薪要求为：" << salfigure << "元， 技术总监审批通过" << std::endl;
    }

    // 总经理审批加薪请求
    void CEOSP(const string &sname, int salfigure)
    {
      std::cout << sname << " 的加薪要求为：" << salfigure << "元， 总经理审批通过" << std::endl;
    }
  };

  void func()
  {
    SalaryHander sh;
    sh.raiseRequest("张三", 7823);
    // 张三 的加薪要求为：7823元， 总经理审批通过
    sh.raiseRequest("李四", 1200);
    // 李四 的加薪要求为：1200元， 技术总监审批通过
    sh.raiseRequest("万五", 11000);
    // 万五 的加薪要求为：11000元， 总经理审批通过
  }
}

// 职责链模式处理加薪请求
namespace _nmsp2
{
  // 加薪请求类
  class RaiseRequest
  {
  public:
    // 构造函数
    RaiseRequest(const string &sname, int salfigure) : m_sname(sname), m_salfigure(salfigure)
    {
    }

    // 获取加薪员工名字
    const string &getName() const
    {
      return m_sname;
    }

    // 获取加薪数额
    int getSalfigure() const
    {
      return m_salfigure;
    }

  private:
    string m_sname;  // 加薪员工名
    int m_salfigure; // 加薪数额
  };

  // 创建职责链
  // 薪水审批者抽象类
  class ParSalApprover
  {
  public:
    ParSalApprover() : m_nextChain(nullptr) {}
    virtual ~ParSalApprover() {}

    // 设置指向职责链中的下一个审批者
    void setNextChain(ParSalApprover *next)
    {
      m_nextChain = next;
    }

    // 处理加薪请求
    virtual void processRequest(const RaiseRequest &req) = 0;

  protected:
    // 找链中的下一个对象并把请求投递给链中的下一个对象
    void sendRequestToNextHandler(const RaiseRequest &req)
    {
      // 找链中的下一个对象
      if (m_nextChain != nullptr)
      {
        // 把加薪请求传递给链中的下一个对象
        m_nextChain->processRequest(req);
      }
      else
      {
        // 没找到链中的下一个对象，程序执行流程走到这里
        std::cout << req.getName() << " 的加薪要求为：" << req.getSalfigure() << "元，无人处理" << std::endl;
      }
    }

  private:
    ParSalApprover *m_nextChain; // 指向下一个审批者对象的多态指针（指向自身类型）
                                 // 每个都指向下一个，就会构成一个链表格式的职责链数据结构
  };

  // 创建部门经理
  class depManager_SA : public ParSalApprover
  {
  public:
    // 处理加薪请求
    virtual void processRequest(const RaiseRequest &req)
    {
      int salfigure = req.getSalfigure();
      if (salfigure <= 1000)
      {
        std::cout << req.getName() << " 的加薪要求为：" << req.getSalfigure() << "元，由部门经理审批通过" << std::endl;
      }
      else
      {
        // 自己处理不了，找链中的下一个对象来处理
        sendRequestToNextHandler(req);
      }
    }
  };

  // 创建技术总监
  class CTO_SA : public ParSalApprover
  {
  public:
    // 处理加薪请求
    virtual void processRequest(const RaiseRequest &req)
    {
      int salfigure = req.getSalfigure();
      if (salfigure <= 5000)
      {
        std::cout << req.getName() << " 的加薪要求为：" << req.getSalfigure() << "元，由技术经理审批通过" << std::endl;
      }
      else
      {
        // 自己处理不了，找链中的下一个对象来处理
        sendRequestToNextHandler(req);
      }
    }
  };

  // 创建总监理
  class CEO_SA : public ParSalApprover
  {
  public:
    // 处理加薪请求
    virtual void processRequest(const RaiseRequest &req)
    {
      int salfigure = req.getSalfigure();
      if (salfigure > 5000)
      {
        std::cout << req.getName() << " 的加薪要求为：" << req.getSalfigure() << "元，由总经理审批通过" << std::endl;
      }
      else
      {
        // 自己处理不了，找链中的下一个对象来处理
        sendRequestToNextHandler(req);
      }
    }
  };

  // ----------------------------------------------------------
  void func()
  {
    // 创建职责链中包含的各个对象
    ParSalApprover *dep = new depManager_SA();
    ParSalApprover *cto = new CTO_SA();
    ParSalApprover *ceo = new CEO_SA();

    // 将这些职责链对象串在一起构成一个完整的职责链
    dep->setNextChain(cto);
    cto->setNextChain(ceo);

    // 创建员工
    string li = "李四";
    string wa = "万五";
    string zs = "张三";

    // 创建加薪请求
    const RaiseRequest req1(li, 353);
    const RaiseRequest req2(wa, 3153);
    const RaiseRequest req3(zs, 35123);

    dep->processRequest(req1);
    // 李四 的加薪要求为：353元，由部门经理审批通过
    dep->processRequest(req2);
    // 万五 的加薪要求为：3153元，由技术经理审批�过
    dep->processRequest(req3);
    // 张三 的加薪要求为：35123元，由总经理审批通过

    // 释放资源
    delete dep;
    delete cto;
    delete ceo;
  }
}

// 功能链（这里以敏感词过滤为例）
namespace _nmsp3
{
  // 敏感词过滤器父类
  class ParVordFitter
  {
  public:
    ParVordFitter() : m_nextChain(nullptr) {}

    virtual ~ParVordFitter() {}

    void setNextChain(ParVordFitter *next)
    {
      m_nextChain = next;
    }

    // 处理敏感词过滤请求
    virtual string processRequest(string strWord) = 0;

  protected:
    // 找到链中的下一个对象，并把请求投递给下一个对象
    string sendRequestToNextHandler(string strWord)
    {
      if (m_nextChain != nullptr)
      {
        return m_nextChain->processRequest(strWord);
      }
      return strWord;
    }

  private:
    ParVordFitter *m_nextChain;
  };

  // 黄赌毒3个敏感词过滤器
  // 黄
  class SexVordFilter : public ParVordFitter
  {
    virtual string processRequest(string strWord)
    {
      std::cout << "敏感词过滤替换中...." << std::endl;
      strWord += "xxx";
      return sendRequestToNextHandler(strWord);
    }
  };

  // 赌
  class GambleVordFilter : public ParVordFitter
  {
    virtual string processRequest(string strWord)
    {
      std::cout << "敏感词过滤替换中...." << std::endl;
      strWord += "ffff";
      return sendRequestToNextHandler(strWord);
    }
  };

  // 毒
  class PoisonVordFilter : public ParVordFitter
  {
    virtual string processRequest(string strWord)
    {
      std::cout << "敏感词过滤替换中...." << std::endl;
      strWord += "dddd";
      return sendRequestToNextHandler(strWord);
    }
  };

  void func()
  {
    ParVordFitter *filter1 = new SexVordFilter();
    ParVordFitter *filter2 = new GambleVordFilter();
    ParVordFitter *filter3 = new PoisonVordFilter();

    filter1->setNextChain(filter2);
    filter2->setNextChain(filter3);

    string ward = "0-0-0-0-0-0";

    string result = filter1->processRequest(ward);
    // 敏感词过滤替换中....
    // 敏感词过滤替换中....
    // 敏感词过滤替换中....

    std::cout << result << std::endl;
    // 0-0-0-0-0-0xxxffffdddd
  }
}

int main()
{
  _nmsp1::func();

  std::cout << "*********************************" << std::endl;

  _nmsp2::func();

  std::cout << "*********************************" << std::endl;

  _nmsp3::func();

  return 0;
}
