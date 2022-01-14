#include <iostream>
#include <map>

using namespace std;

// 情景模拟：
// 围棋游戏棋子范例。

namespace _nmsp1
{
  enum EnumColor // 代表棋子类型（黑棋 白棋）
  {
    Black, // 黑棋
    Whilte // 白棋
  };

  struct Position // 棋子位置
  {
    int m_x;
    int m_y;
    // 构造函数
    Position(int tx, int ty) : m_x(tx), m_y(ty)
    {
    }
  };

  class Piece //  棋子类
  {
  public:
    Piece(EnumColor tc, Position ts) : m_color(tc), m_position(ts)
    {
    }

    // 绘制棋子
    void draw()
    {
      if (m_color == Black)
      {
        std::cout << "黑子落子在----[" << m_position.m_x << ", " << m_position.m_y << "]" << std::endl;
      }
      else
      {
        std::cout << "白子落子在----[" << m_position.m_x << ", " << m_position.m_y << "]" << std::endl;
      }
    }

  private:
    // 棋子颜色
    EnumColor m_color;
    // 棋子位置
    Position m_position;
  };

  void func()
  {
    Piece *pb1 = new Piece(Black, Position(2, 5));
    pb1->draw();
    // 黑子落子在----[2, 5]

    Piece *pw1 = new Piece(Whilte, Position(4, 3));
    pw1->draw();
    // 白子落子在----[4, 3]

    Piece *pb2 = new Piece(Black, Position(9, 4));
    pb2->draw();
    // 黑子落子在----[9, 4]

    Piece *pw2 = new Piece(Whilte, Position(12, 5));
    pw2->draw();
    // 白子落子在----[12, 5]

    delete pb1;
    delete pb2;
    delete pw1;
    delete pw2;
  }
}

// 利用享元模式重写
namespace _nmsp2
{
  struct Position // 棋子位置
  {
    int m_x;
    int m_y;
    // 构造函数
    Position(int tx, int ty) : m_x(tx), m_y(ty)
    {
    }
  };

  // 创建棋子抽象类
  class Piece
  {
  public:
    virtual void draw(Position position) = 0;

    virtual ~Piece() {}
  };

  class BlackPiece : public Piece
  {
  public:
    virtual void draw(Position position)
    {
      std::cout << "黑子落子在----[" << position.m_x << ", " << position.m_y << "]" << std::endl;
    }
  };

  class WhiltePiece : public Piece
  {
  public:
    virtual void draw(Position position)
    {
      std::cout << "白子落子在----[" << position.m_x << ", " << position.m_y << "]" << std::endl;
    }
  };

  enum EnumColor // 代表棋子类型（黑棋 白棋）
  {
    Black, // 黑棋
    Whilte // 白棋
  };

  // 简单工厂类，创建棋子
  class PieceFactory
  {
  public:
    virtual ~PieceFactory()
    {
      // 释放内存
      for (auto iter = m_FlyWeightMap.begin(); iter != m_FlyWeightMap.end(); ++iter)
      {
        Piece *tmpv = iter->second;
        delete tmpv;
      }

      m_FlyWeightMap.clear();
    }

    Piece *getFlyWeight(EnumColor color) // 获取享元对象，黑棋和白棋对象（参数告知获取什么棋子）
    {
      auto iter = m_FlyWeightMap.find(color);

      if (iter == m_FlyWeightMap.end())
      {
        // 第一次获取（对象还没创建出来）
        // 那这里就创建一个
        Piece *tmpv = nullptr;
        if (color == Whilte)
        {
          tmpv = new WhiltePiece();
        }
        else if (color == Black)
        {
          tmpv = new BlackPiece();
        }
        m_FlyWeightMap.insert({color, tmpv});
        return tmpv;
      }
      else
      {
        return iter->second;
      }
    }

  private:
    std::map<EnumColor, Piece *> m_FlyWeightMap; // 用map容器来保存所有的享元对象，一共就两个，黑色棋子一个，白色一个
  };

  void func()
  {
    // 先创建工厂
    PieceFactory *pieceFactory = new PieceFactory();

    Piece *pb1 = pieceFactory->getFlyWeight(Black);
    pb1->draw(Position(2, 12));
    // 黑子落子在----[2, 12]

    Piece *pw1 = pieceFactory->getFlyWeight(Whilte);
    pw1->draw(Position(9, 7));
    // 白子落子在----[9, 7]

    Piece *pb2 = pieceFactory->getFlyWeight(Black);
    pb2->draw(Position(6, 2));
    // 黑子落子在----[6, 2]

    Piece *pw2 = pieceFactory->getFlyWeight(Whilte);
    pw2->draw(Position(12, 4));
    // 白子落子在----[12, 4]

    // 释放资源的时候，只需要释放工厂
    delete pieceFactory;
  }
}

int main()
{
  // _nmsp1::func();
  _nmsp2::func();

  return 0;
}