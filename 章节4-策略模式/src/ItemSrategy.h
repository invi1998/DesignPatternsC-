#ifndef __ITEMSTRATEGY__
#define __ITEMSTRATEGY__

// 道具策略类父类
class ItemStrategy
{
public:
  virtual void UseItem(Fighter *mainobj) = 0;

  virtual ~ItemStrategy()
  {
  }
};

// 3品回血丹 策略类
class ItemStrategy_HXD3 : public ItemStrategy
{
public:
  virtual void UseItem(Fighter *mainobj)
  {
    mainobj->SetLife(mainobj->GetLife() + 200);
  }
};

// 2品回血丹 策略类
class ItemStrategy_HXD2 : public ItemStrategy
{
public:
  virtual void UseItem(Fighter *mainobj)
  {
    mainobj->SetLife(mainobj->GetLife() + 300);
  }
};

// 1品回血丹 策略类
class ItemStrategy_HXD1 : public ItemStrategy
{
public:
  virtual void UseItem(Fighter *mainobj)
  {
    mainobj->SetLife(mainobj->GetLife() + 500);
  }
};

#endif