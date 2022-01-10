#include <iostream>

using namespace std;

// 计算水果饮料价格范例
// 一杯单纯的饮料售价 10 元
// 如果向饮料中增加砂糖，额外增加1元
// 如果向饮料中增加牛奶，额外增加2元
// 如果向饮料中增加椰果，额外增加2元

// 现在 顾客要求 又加椰果又加糖 = 10 + 1 + 2 = 13元

namespace _nmsp1
{
  // 抽象饮料类
  class Drink
  {
  public:
    // 获取价格
    virtual int getprice() = 0;

    virtual ~Drink() {}
  };

  // 水果饮料类
  class FruitDrink : public Drink
  {
  public:
    virtual int getprice()
    {
      return 10;
    }
  };

  // 装饰器抽象类
  class Decorator : public Drink
  {
  public:
    Decorator(Drink *dk) : m_drink(dk) {}

    virtual int getprice()
    {
      return m_drink->getprice();
    }

  private:
    Drink *m_drink;
  };

  // 砂糖饮料装饰类
  class SugarDec : public Decorator
  {
  public:
    SugarDec(Drink *dec) : Decorator(dec) {}

    virtual int getprice()
    {
      return Decorator::getprice() + 1;
    }
  };

  // 牛奶饮料装饰类
  class MullkDec : public Decorator
  {
  public:
    MullkDec(Drink *dec) : Decorator(dec) {}

    virtual int getprice()
    {
      return Decorator::getprice() + 2;
    }
  };

  // 椰果饮料装饰类
  class CoconutDec : public Decorator
  {
  public:
    CoconutDec(Drink *dec) : Decorator(dec) {}

    virtual int getprice()
    {
      return Decorator::getprice() + 2;
    }
  };

}

int main()
{
  // 计算一杯加糖椰果水果饮料价格
  _nmsp1::Drink *dk = new _nmsp1::FruitDrink();

  _nmsp1::Decorator *dec1 = new _nmsp1::SugarDec(dk);
  _nmsp1::Decorator *dec2 = new _nmsp1::CoconutDec(dec1);

  std::cout << "价格 = " << dec2->getprice() << std::endl;
  // 价格 = 13

  return 0;
}
