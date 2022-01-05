/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>

using namespace std;

// 情景模拟
// 芭比娃娃制造：身体（头，躯干，四肢），衣服，鞋子
// 生产芭比娃娃，有 中 ， 日， 美 3国产商进行
// 要求：制作2个芭比娃娃，第一个：身体，衣服，鞋子全部由中国产商制造
// 第二个：身体采用中国产商，衣服采用日本产商，鞋子采用美国产商

// 实现思路：将衣服，鞋子，身体这个3个部件实现为3个抽象类，实现一个抽象工厂，
// 分别用来生产身体，衣服，鞋子这3个部件
// 然后，针对不同厂商的每个部件实现具体的类，以及每个厂商所代表的具体工厂

namespace _nmsp1
{
  // 身体抽象类
  class Body
  {
  public:
    virtual void getName() = 0;
    virtual ~Body() {}
  };

  // 衣服抽象类
  class Clothes
  {
  public:
    virtual void getName() = 0;
    virtual ~Clothes() {}
  };

  // 鞋子抽象类
  class Shoes
  {
  public:
    virtual void getName() = 0;
    virtual ~Shoes() {}
  };

  // --------------------------------------------
  // 抽象工厂类
  class AbstractFactory
  {
  public:
    // 所创建的部件应该稳定的保持这3个部件，才适合抽象工厂模式
    virtual Body *createBody() = 0;       // 创建身体
    virtual Clothes *createClothes() = 0; // 创建衣服
    virtual Shoes *createShoes() = 0;     // 创建鞋子
  };

  // 芭比娃娃类
  class BarbieDoll
  {
  public:
    BarbieDoll(Body *tmpBody, Clothes *tmpClothes, Shoes *tmpShoes)
    {
      body = tmpBody;
      clothes = tmpClothes;
      shoes = tmpShoes;
    }

    // 组装芭比娃娃
    void Assemble()
    {
      std::cout << "成功组装了一个芭比娃娃" << std::endl;
      body->getName();
      clothes->getName();
      shoes->getName();
    }

  private:
    Body *body;
    Clothes *clothes;
    Shoes *shoes;
  };

  // 中国产商实现的三个部件
  class China_Body : public Body
  {
  public:
    void getName()
    {
      std::cout << "中国产商生产的身体部件" << std::endl;
    }
  };

  class China_Clothes : public Clothes
  {
  public:
    void getName()
    {
      std::cout << "中国产商生产的衣服部件" << std::endl;
    }
  };

  class China_Shoes : public Shoes
  {
  public:
    void getName()
    {
      std::cout << "中国产商生产的鞋子部件" << std::endl;
    }
  };
  // 创建一个中国工厂
  class China_Factory : public AbstractFactory
  {
  public:
    Body *createBody() // 创建身体
    {
      return new China_Body();
    }

    Clothes *createClothes() // 创建衣服
    {
      return new China_Clothes();
    }

    Shoes *createShoes() // 创建鞋子
    {
      return new China_Shoes();
    }
  };

  // 日本产商实现的三个部件
  class Japan_Body : public Body
  {
  public:
    void getName()
    {
      std::cout << "日本产商生产的身体部件" << std::endl;
    }
  };

  class Japan_Clothes : public Clothes
  {
  public:
    void getName()
    {
      std::cout << "日本产商生产的衣服部件" << std::endl;
    }
  };

  class Japan_Shoes : public Shoes
  {
  public:
    void getName()
    {
      std::cout << "日本产商生产的鞋子部件" << std::endl;
    }
  };

  // 创建一个日本工厂
  class Japan_Factory : public AbstractFactory
  {
  public:
    Body *createBody() // 创建身体
    {
      return new Japan_Body();
    }

    Clothes *createClothes() // 创建衣服
    {
      return new Japan_Clothes();
    }

    Shoes *createShoes() // 创建鞋子
    {
      return new Japan_Shoes();
    }
  };

  // 美国产商实现的三个部件
  class America_Body : public Body
  {
  public:
    void getName()
    {
      std::cout << "美国产商生产的身体部件" << std::endl;
    }
  };

  class America_Clothes : public Clothes
  {
  public:
    void getName()
    {
      std::cout << "美国产商生产的衣服部件" << std::endl;
    }
  };

  class America_Shoes : public Shoes
  {
  public:
    void getName()
    {
      std::cout << "美国产商生产的鞋子部件" << std::endl;
    }
  };

  // 创建一个美国工厂
  class America_Factory : public AbstractFactory
  {
  public:
    Body *createBody() // 创建身体
    {
      return new America_Body();
    }

    Clothes *createClothes() // 创建衣服
    {
      return new America_Clothes();
    }

    Shoes *createShoes() // 创建鞋子
    {
      return new America_Shoes();
    }
  };

}

int main()
{
  // 创建工厂
  _nmsp1::AbstractFactory *pChinaFactory = new _nmsp1::China_Factory();
  _nmsp1::AbstractFactory *pJapanFactory = new _nmsp1::Japan_Factory();
  _nmsp1::AbstractFactory *pAmricaFacrory = new _nmsp1::America_Factory();

  // 创建部件
  _nmsp1::Body *pb1 = pChinaFactory->createBody();
  _nmsp1::Clothes *pc1 = pChinaFactory->createClothes();
  _nmsp1::Shoes *ps1 = pChinaFactory->createShoes();

  _nmsp1::Body *pb2 = pJapanFactory->createBody();
  _nmsp1::Clothes *pc2 = pJapanFactory->createClothes();
  _nmsp1::Shoes *ps2 = pJapanFactory->createShoes();

  _nmsp1::Body *pb3 = pAmricaFacrory->createBody();
  _nmsp1::Clothes *pc3 = pAmricaFacrory->createClothes();
  _nmsp1::Shoes *ps3 = pAmricaFacrory->createShoes();

  // 组装芭比娃娃1
  _nmsp1::BarbieDoll *doll1 = new _nmsp1::BarbieDoll(pb1, pc1, ps1);
  // 组装芭比娃娃2
  _nmsp1::BarbieDoll *doll2 = new _nmsp1::BarbieDoll(pb1, pc2, ps3);

  doll1->Assemble();
  // 成功组装了一个芭比娃娃
  // 中国产商生产的身体�件
  // 中国产商生产的衣服部件
  // 中国产商生产的鞋子部件

  doll2->Assemble();
  // 成功组装了一�芭比娃娃
  // 中国产商生产的身体部件
  // 日本产商生产的衣服部件
  // 美国产�生产的鞋子部件

  delete pChinaFactory;
  delete pJapanFactory;
  delete pAmricaFacrory;

  delete pb1;
  delete ps1;
  delete pc1;

  delete pb2;
  delete ps2;
  delete pc2;

  delete pb3;
  delete ps3;
  delete pc3;

  delete doll1;
  delete doll2;

  return 0;
}
