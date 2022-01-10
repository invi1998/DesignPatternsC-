#include <stdio.h>
#include <iostream>

using namespace std;

// 情景模拟：以一个列表控件为例，如何丰富控件上的内容。先后为一个普通的列表控件增加边框，垂直滚动条，水平滚动条

// ListCtrl 代表最普通的列表控件，提供一个draw方法，来绘制自己
// BorderListCtrl 继承自ListCtrl，用于表示增加了边框的控件，提供draw方法
// VerScBorderListCtrl 继承自 BorderListCtrl  ，用于表示增加了边框又增加了垂直滚动条的控件，提供draw方法
// HorScVerScBorderListCtrl 继承自 VerScBorderListCtrl，表示增加了边框，垂直和水平滚动条的控件，提供draw方法

// 试想这种代码编写方式有什么弊端，如果我们又有一个新需求，比如加个阴影，加个外发光。。。岂不是又得继承下去，实现更多继承关系的类
// 即，如果我们又新的需求，就得创建新的子类，就会导致类数量的泛滥，灵活性也会变得很差。
// 所以在这种情形下，采用继承机制来解决我们控件创建问题，显然不是一个好的方法

// 继承改为组装方法来解决，防止类泛滥
// ListCtrl 代表最普通的列表控件，提供一个draw方法，来绘制自己
// 增加边框 -> 带边框的列表控件
// 增加垂直滚动条->带垂直滚动条的控件，再给这个带垂直滚动条的列表控件增加一个水平滚动条 -> 即带垂直又带水平滚动条

// 这种通过装饰方法将一个类的功能不断的增强的思想（动态的增加新的功能），就是装饰模式的核心设计思想

namespace _nmsp1
{
  // 创建一个抽象控件类
  class Control
  {
  public:
    virtual void draw() = 0;
    // draw 方法，用于将自身绘制到屏幕

  public:
    virtual ~Control() {}
  };

  // 控件类本体
  class ListCtrl : public Control
  {
  public:
    virtual void draw()
    {
      std::cout << "绘制了普通的列表控件" << std::endl;
      // 具体绘制可以使用DirectX或者OpenGL进行
    }
  };

  // 抽象装饰器类（用于做装饰器的父类）
  // 这里做点额外说明，经过装饰器装饰过的列表控件，他任然还是一个列表控件，这里不要把装饰器单纯的理解为装饰器
  // 而是理解成经过包装后的新控件。所以抽象装饰器类继承自Control并不突兀，也合情合理
  // 同时注意到，抽象装饰器类中有一个成员变量 m_control，他的类型是抽象控件类指针，从这里可以看到
  // 抽象装饰器和抽象控件类之间不仅是以职工继承关系，也是一种组合关系
  class Decorator : public Control
  {
  public:
    // 构造函数
    Decorator(Control *tmpCtrl) : m_control(tmpCtrl)
    {
    }

    virtual void draw()
    {
      m_control->draw(); // 调用是哪个draw,取决于m_control指向的对象
    }

  private:
    Control *m_control; // 需要被装饰的其他控件，这里用的是Control*
  };

  // 边框装饰器类
  class BorderDec : public Decorator
  {
  public:
    BorderDec(Control *tmpCtrl) : Decorator(tmpCtrl) {}

    virtual void draw()
    {
      Decorator::draw(); // 绘制本体
      // 调用父类的draw方法，以保持过往已经绘制出的内容
      // 注意这行写法，这里就是装饰模式的典型写法

      drawBorder(); // 绘制边框
    }

  private:
    void drawBorder()
    {
      std::cout << "绘制边框" << std::endl;
    }
  };

  // 垂直滚动条装饰器类
  class VerScrollBarDec : public Decorator
  {
  public:
    VerScrollBarDec(Control *tmpCtrl) : Decorator(tmpCtrl) {}

    virtual void draw()
    {
      Decorator::draw(); // 绘制本体
      // 调用父类的draw方法，以保持过往已经绘制出的内容
      // 注意这行写法，这里就是装饰模式的典型写法

      drawVerScrollBar(); // 绘制垂直滚动条
    }

  private:
    void drawVerScrollBar()
    {
      std::cout << "绘制垂直滚动条" << std::endl;
    }
  };

  // 水平滚动条装饰器类
  class HorScrollBarDec : public Decorator
  {
  public:
    HorScrollBarDec(Control *tmpCtrl) : Decorator(tmpCtrl) {}

    virtual void draw()
    {
      Decorator::draw(); // 绘制本体
      // 调用父类的draw方法，以保持过往已经绘制出的内容
      // 注意这行写法，这里就是装饰模式的典型写法

      drawHorScrollBar(); // 绘制水平滚动条
    }

  private:
    void drawHorScrollBar()
    {
      std::cout << "绘制水平滚动条" << std::endl;
    }
  };

}

int main()
{
  // 创建一个即带边框又带垂直滚动条的列表控件
  // 首先绘制一个普通的列表控件
  // 创建控件本体
  _nmsp1::Control *ctl = new _nmsp1::ListCtrl();

  // 接着借助普通的列表控件，可以绘制出一个 带边框的列表控件

  // 创建装饰器
  // 其实这里 用 _nmsp1::Control* 去指也可以，只是这里为了更直接，就使用直接父类指针了

  // 带边框的
  _nmsp1::Decorator *dcB = new _nmsp1::BorderDec(ctl);

  // 将带边框的再装饰一层垂直滚动条
  _nmsp1::Decorator *dcV = new _nmsp1::VerScrollBarDec(dcB);

  // 绘制
  dcV->draw();
  // 绘制了普通的列表控件
  // 绘制边框
  // 绘制垂直滚动条

  std::cout << "---------------------------------------------------------------------" << std::endl;

  // 装饰一个 只带水平滚动条的控件
  // 首先绘制普通控件
  _nmsp1::Control *ctl2 = new _nmsp1::ListCtrl();

  // 然后用水平滚动条进行装饰
  _nmsp1::Decorator *dcH = new _nmsp1::HorScrollBarDec(ctl2);

  // 最终绘制
  dcH->draw();
  // 绘制了普通的�表控件
  // 绘制水平滚动条

  // 资源释放。。。。
  return 0;
}
