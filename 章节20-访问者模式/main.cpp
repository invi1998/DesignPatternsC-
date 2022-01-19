#include <iostream>
#include <list>

using namespace std;

// 情景模拟
// 医院医生开的处方单中包含多种药元素，
// 査看它的划价员和药房工作人员对它的处理方式也不同，
// 划价员根据处方单上面的药品名和数量进行划价（缴费），
// 药房工作人员根据处方单的内容进行抓药（取药）。

namespace _nmsp1
{
  // 药品父类
  class Medicine
  {
  public:
    virtual string getMdcName() = 0; // 获取药品名称
    virtual float getPrice() = 0;    // 获取药品总价

    virtual ~Medicine() {}
  };

  // 药品1
  class M_asplcrp : public Medicine
  {
  public:
    virtual string getMdcName()
    {
      return "阿司匹林肠溶片";
    }

    virtual float getPrice()
    {
      return 154.34f;
    }
  };

  // 药品2
  class M_ffttnrsp : public Medicine
  {
  public:
    virtual string getMdcName()
    {
      return "氟伐他汀钠溶释片";
    }

    virtual float getPrice()
    {
      return 242.85f;
    }
  };

  // 药品3
  class M_dlx : public Medicine
  {
  public:
    virtual string getMdcName()
    {
      return "黛力新";
    }

    virtual float getPrice()
    {
      return 122.12f;
    }
  };

  // 针对药品的处理类
  class MedicineProc
  {
  public:
    // 增加药品到药品列表中
    void addMedicine(Medicine *mdc)
    {
      m_mdclist.push_back(mdc);
    }

    // 缴费动作，取药动作
    void proAction(string strvisitor) // strvisitor 代表拿到药品单的人
    {
      if (strvisitor == "收费人员")
      {
        float totalcost = 0.0f;

        for (auto i = m_mdclist.begin(); i != m_mdclist.end(); ++i)
        {
          std::cout << "药品\"" << (*i)->getMdcName() << "\"的价格: " << (*i)->getPrice() << std::endl;
          totalcost += (*i)->getPrice();
        }

        std::cout << "-------------药品总价-------------" << std::endl;
        std::cout << totalcost << std::endl;
      }
      else if (strvisitor == "取药人员")
      {
        for (auto i = m_mdclist.begin(); i != m_mdclist.end(); ++i)
        {
          std::cout << "已获得药品\"" << (*i)->getMdcName() << std::endl;
        }
      }
    }

  private:
    std::list<Medicine *> m_mdclist; // 药品列表，记录着药品单上的所有药品
  };

  void func()
  {
    Medicine *pm1 = new M_asplcrp();
    Medicine *pm2 = new M_dlx();
    Medicine *pm3 = new M_ffttnrsp();

    MedicineProc poc;

    poc.addMedicine(pm1);
    poc.addMedicine(pm2);
    poc.addMedicine(pm3);

    poc.proAction("收费人员");
    // 药品"阿司匹林肠溶片"的价格: 154.34
    // 药品"黛力新"的价格: 122.12
    // 药品"氟伐他汀钠溶释片"的价格: 242.85
    // -------------药品总价-------------
    // 519.31

    poc.proAction("取药人员");
    // 已获得药品"阿司匹林肠溶片
    // 已获得药品"黛力新
    // 已获得药品"氟伐他汀钠溶释片

    delete pm3;
    delete pm2;
    delete pm1;
  }
}

// 针对上述范例，假设某天，新增一个角色（健身教练），他也要获取这个药品单，然后根据药品情况作出相对应的动作
// （比如，调整健身强度等。。），那就需要去代码里新增if分支。
// 很明显，这样修改代码是违法开闭原则的，每新增一个新角色，就得新增if语句分支

// 引入访问者模式
// 访问者模式：访问者（收费人员，取药人员， 健身教练。。。），被访问者（药品、药品单）

namespace _nmsp2
{
  // 类前向声名
  class Visitor;

  // 药品父类
  class Medicine
  {
  public:
    virtual string getMdcName() = 0; // 获取药品名称
    virtual float getPrice() = 0;    // 获取药品总价

    virtual ~Medicine() {}

    // 在访问者模式中，被访问者通常称为元素，在元素中，我们会申明一个叫做 accept这样一个方法
    // 用于接收访问者的访问，作为被访问者接收访问者的访问是必须的
    virtual void Accept(Visitor *visiter) = 0;
  };

  // 药品1
  class M_asplcrp : public Medicine
  {
  public:
    virtual string getMdcName()
    {
      return "阿司匹林肠溶片";
    }

    virtual float getPrice()
    {
      return 154.34f;
    }

    virtual void Accept(Visitor *visiter);
  };

  // 药品2
  class M_ffttnrsp : public Medicine
  {
  public:
    virtual string getMdcName()
    {
      return "氟伐他汀钠溶释片";
    }

    virtual float getPrice()
    {
      return 242.85f;
    }

    virtual void Accept(Visitor *visiter);
  };

  // 药品3
  class M_dlx : public Medicine
  {
  public:
    virtual string getMdcName()
    {
      return "黛力新";
    }

    virtual float getPrice()
    {
      return 122.12f;
    }

    virtual void Accept(Visitor *visiter);
  };

  // 访问者 父类（抽象类）
  class Visitor
  {
  public:
    virtual ~Visitor() {}

    // virtual void Visit_elm_asplcrp(M_asplcrp* pelem) = 0;   // 访问元素 阿司匹林肠溶片
    // virtual void Visit_elm_ffttnrsp(M_ffttnrsp* pelem) = 0;   // 访问元素 氟伐他汀钠溶释片
    // virtual void Visit_elm_dlx(M_asplcrp* pelem) = 0;   // 访问元素 黛力新

    // 当然这里也可以写成函数重载方式 （看个人习惯）
    virtual void Visit(M_asplcrp *pelem) = 0;  // 访问元素 阿司匹林肠溶片
    virtual void Visit(M_ffttnrsp *pelem) = 0; // 访问元素 氟伐他汀钠溶释片
    virtual void Visit(M_dlx *pelem) = 0;      // 访问元素 黛力新

    // 从这里也可以看出来，访问者模式的一个局限性
    // 那就是要求被访问者他的一个类型要尽可能固定
  };

  // Accept具体实现
  void M_asplcrp::Accept(Visitor *visitor)
  {
    visitor->Visit(this);
  }

  void M_ffttnrsp::Accept(Visitor *visitor)
  {
    visitor->Visit(this);
  }

  void M_dlx::Accept(Visitor *visitor)
  {
    visitor->Visit(this);
  }

  // 收费人员访问者
  class Visitor_SFRY : public Visitor
  {
  public:
    Visitor_SFRY() : m_totalcost(0.0f) {}

  public:
    virtual void Visit(M_asplcrp *pelem) // 访问元素 阿司匹林肠溶片
    {
      std::cout << "药品\"" << pelem->getMdcName() << "\"的价格：" << pelem->getPrice() << std::endl;
      m_totalcost += pelem->getPrice();
    }
    virtual void Visit(M_ffttnrsp *pelem) // 访问元素 氟伐他汀钠溶释片
    {
      std::cout << "药品\"" << pelem->getMdcName() << "\"的价格：" << pelem->getPrice() << std::endl;
      m_totalcost += pelem->getPrice();
    }
    virtual void Visit(M_dlx *pelem) // 访问元素 黛力新
    {
      std::cout << "药品\"" << pelem->getMdcName() << "\"的价格：" << pelem->getPrice() << std::endl;
      m_totalcost += pelem->getPrice();
    }

  public:
    // 返回总费用
    float getTotal()
    {
      return m_totalcost;
    }

  private:
    float m_totalcost; // 总费用
  };

  // 取药人员访问者
  class Visitor_QYRY : public Visitor
  {
  public:
    virtual void Visit(M_asplcrp *pelem) // 访问元素 阿司匹林肠溶片
    {
      std::cout << "获得药品\"" << pelem->getMdcName() << std::endl;
    }
    virtual void Visit(M_ffttnrsp *pelem) // 访问元素 氟伐他汀钠溶释片
    {
      std::cout << "获得药品\"" << pelem->getMdcName() << std::endl;
    }
    virtual void Visit(M_dlx *pelem) // 访问元素 黛力新
    {
      std::cout << "获得药品\"" << pelem->getMdcName() << std::endl;
    }
  };

  // 营养师访问者
  class Visitor_YYS : public Visitor
  {
  public:
    virtual void Visit(M_asplcrp *pelem) // 访问元素 阿司匹林肠溶片
    {
      std::cout << "营养师看到 【" << pelem->getMdcName() << "】，建议多吃粗粮！" << std::endl;
    }
    virtual void Visit(M_ffttnrsp *pelem) // 访问元素 氟伐他汀钠溶释片
    {
      std::cout << "营养师看到 【" << pelem->getMdcName() << "】，建议多休息，不要熬夜" << std::endl;
    }
    virtual void Visit(M_dlx *pelem) // 访问元素 黛力新
    {
      std::cout << "营养师看到 【" << pelem->getMdcName() << "】，建议放松心情，不要焦虑" << std::endl;
    }
  };

  // 对象结构 (对一批元素提供同一种操作)
  class ObjectStructor
  {
  public:
    // 增加药品到药品列表中
    void addMedicine(Medicine *mdc)
    {
      m_mdclist.push_back(mdc);
    }

    // 处理 （用传进来的访问者进行处理）
    void proAction(Visitor *visitor)
    {
      for (auto iter = m_mdclist.begin(); iter != m_mdclist.end(); ++iter)
      {
        (*iter)->Accept(visitor);
      }
    }

  private:
    std::list<Medicine *> m_mdclist; // 药品列表
  };

  void func()
  {
    Medicine *pm1 = new M_asplcrp();
    Medicine *pm2 = new M_dlx();
    Medicine *pm3 = new M_ffttnrsp();

    Visitor_SFRY visitor_sf;
    Visitor_QYRY visitor_qy;
    Visitor_YYS visitor_yys;

    // 各个元素调用Accept来接收收费者的访问
    pm1->Accept(&visitor_sf);
    pm2->Accept(&visitor_sf);
    pm3->Accept(&visitor_sf);

    // 药品"阿司匹林肠溶片"的价格：154.34
    // 药品"黛力新"的价格：122.12
    // 药品"氟伐他汀钠溶释片"的价格：242.85

    std::cout << "-------------药品总价-------------" << std::endl;
    std::cout << "共计缴费：" << visitor_sf.getTotal() << std::endl;
    // 共计缴费: 519.31

    std::cout << "-------------窗口取药-------------" << std::endl;
    pm1->Accept(&visitor_qy);
    pm2->Accept(&visitor_qy);
    pm3->Accept(&visitor_qy);
    // 获得药品"阿司匹林肠溶片
    // 获得药品"黛力新
    // 获得药品"氟伐他汀钠溶释片

    std::cout << "-------------咨询营养师-------------" << std::endl;
    pm1->Accept(&visitor_yys);
    pm2->Accept(&visitor_yys);
    pm3->Accept(&visitor_yys);
    // 营养师看到 【阿司匹林肠溶片】，建议多吃粗粮��
    // 营养师看到 【黛力新】，建议放松心情，不要焦虑
    // 营养师看到 【氟��他汀钠溶释片】，建议多休息，不要熬夜

    // 使用对象结构进行测试
    ObjectStructor objc;
    objc.addMedicine(pm1);
    objc.addMedicine(pm2);
    objc.addMedicine(pm3);

    objc.proAction(&visitor_sf);
    // 药品"阿司匹林肠溶片"的价格：154.34
    // 药品"黛力新"的价格：122.12
    // 药品"氟伐他汀钠溶释片"的价格：242.85
    objc.proAction(&visitor_qy);
    // 获得药品"阿司匹林肠溶片
    // 获得药品"黛力新
    // 获得药品"氟伐他汀钠溶��片
    objc.proAction(&visitor_yys);
    // 营养师看到 【阿司匹林肠溶片】，建议多吃粗粮！
    // 营养师看到 【黛力新】，建议放松心情，不要焦虑
    // 营养师看到 【氟伐他汀钠溶释片】，建议多休息，不要熬夜

    delete pm3;
    delete pm2;
    delete pm1;
  }
}

int main()
{
  // _nmsp1::func();
  _nmsp2::func();

  return 0;
}
