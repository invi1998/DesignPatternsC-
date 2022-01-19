#include <iostream>
#include <map>
#include <stack>

using namespace std;

// 情景模拟
// 假设存在一些变量，这些变量都用一个 字母 来表示。（a,b,c,d）
// 这些变量的值希望在运行时进行指定，同时希望对这些变量进行加减法运算
// 比如：程序运行，我们给a,b,c,d值为7,9,3,2 然后给他一个字符串“a-b+c+d”
// 希望程序能够进行如下运算 7-9+3+2 = 3

// 分析：
// 字符串表达式是可以做任意变量之间的任意加减操作的。比如上面提到的，我们可以先算a-b.
// 然后将得到的结构在 +c,然后得到的结果再+d。所以这是一个从左到右的计算规则（或者从左到右的语法规则）
// 如果将这些规则表达为一个句子，来代表a-b+c+d，然后构建一个解释器来解释这个句子。
// 这就是解释器模式所做的事情
// 实质或者说难点就是如何将计算规则表达为一颗语法树【表达式树】
namespace _nmsp1
{
  // 表达式（节点）父类
  class Expression
  {
  public:
    Expression(int num, char sign) : m_dgb_num(num), m_dgb_sign(sign)
    {
    }

    virtual ~Expression() {}

  public:
    // 解析语法树中单前节点的函数
    // map中的键值对用于保存变量名以及对应的值
    virtual int interpreter(std::map<char, int> var) = 0;

  public:
    // 一下两个成员变量只是为了跟踪调试，便于观察而引入
    int m_dgb_num;   // 创建该对象时的一个编号，用于记录本对象是第几个创建的
    char m_dgb_sign; // 标记本对象类型，v代表是变量（终结表达式），+、-表示是一个非终结符表达式
  };

  // 终结符表达式
  class VarExpression : public Expression
  {
  public:
    VarExpression(const char &key, int num, char sign) : Expression(num, sign)
    {
      m_k = key;
    }

    virtual int interpreter(std::map<char, int> var)
    {
      return var[m_k]; // 返回该变量名对应的数值
    }

  private:
    char m_k; // 保存变量名
  };

  // 运算符表达式（非终结表达式）父类
  class SymbolExpression : public Expression
  {
  public:
    SymbolExpression(Expression *left, Expression *right, int num, char sign) : Expression(num, sign)
    {
      m_left = left;
      m_right = right;
    }

    // 获取左孩子
    Expression *getLeft()
    {
      return m_left;
    }

    // 获取右孩子
    Expression *getRight()
    {
      return m_right;
    }

  protected:
    // 对于非终结表达式，左右各有一个操作数
    Expression *m_left;
    Expression *m_right;
  };

  // 加法运算符表达式
  class AddExpression : public SymbolExpression
  {
  public:
    AddExpression(Expression *left, Expression *right, int num, char sign) : SymbolExpression(left, right, num, sign)
    {
    }

    virtual int interpreter(std::map<char, int> var)
    {
      // 递归调用左操作数interpreter方法
      int value1 = m_left->interpreter(var);
      // 递归调用右操作数interpreter方法
      int value2 = m_right->interpreter(var);
      int result = value1 + value2;
      return result;
    }
  };

  // 减法运算符表达式
  class SubExpression : public SymbolExpression
  {
  public:
    SubExpression(Expression *left, Expression *right, int num, char sign) : SymbolExpression(left, right, num, sign)
    {
    }

    virtual int interpreter(std::map<char, int> var)
    {
      // 递归调用左操作数interpreter方法
      int value1 = m_left->interpreter(var);
      // 递归调用右操作数interpreter方法
      int value2 = m_right->interpreter(var);
      int result = value1 - value2;
      return result;
    }
  };

  // 创建语法树的函数
  // strExp 表示要计算的表达式的字符串
  Expression *analyse(string strExp)
  {
    std::stack<Expression *> expSatck; // 这里用到了栈这种顺序容器
    Expression *right = nullptr;
    Expression *left = nullptr;
    int icount = 1;

    // 循环遍历字符串中每一个字符
    for (size_t i = 0; i < strExp.size(); ++i)
    {
      switch (strExp[i])
      {
      // 加减运算就是将计算的结果反倒栈顶，然后下一次运算的时候再从栈顶取出来
      case '+':
        // 加法符号（非终结表达式）
        left = expSatck.top(); // 返回栈顶元素作为左孩子
        ++i;
        right = new VarExpression(strExp[i], icount++, 'v');
        // 将加法运行结果压栈处理
        expSatck.push(new AddExpression(left, right, icount++, '+'));
        break;
      case '-':
        // 减法符号（非终结表达式）
        left = expSatck.top(); // 返回栈顶元素做为左孩子
        ++i;
        right = new VarExpression(strExp[i], icount++, 'v');
        // 将减法运算压栈处理
        expSatck.push(new SubExpression(left, right, icount++, '-'));
        break;
      default:
        // 终结符表达式
        expSatck.push(new VarExpression(strExp[i], icount++, 'v'));
        // 遇到变量，压栈处理
      }
    }

    Expression *expression = expSatck.top();

    return expression;
  }

  // 资源释放函数 (从根节点)
  void release(Expression *expression)
  {
    // 释放表达式树的节点内存
    SymbolExpression *pSe = dynamic_cast<SymbolExpression *>(expression);
    // 此处代码有优化空间（不使用dynamic_cast）
    if (pSe)
    {
      release(pSe->getLeft());
      release(pSe->getRight());
    }
    delete expression;
  }

  void func()
  {
    string strExp = "a-b+c-d+e+f";
    std::map<char, int> varmap;
    // 下面给字符串表达式中每个参与运算的变量赋一个对应的数值
    varmap.insert(make_pair('a', 23));
    varmap.insert(make_pair('b', 3));
    varmap.insert(make_pair('c', 223));
    varmap.insert(make_pair('d', 3));
    varmap.insert(make_pair('e', 7));
    varmap.insert(make_pair('f', 19));

    // 创建语法树
    Expression *expression = analyse(strExp);
    // 调用interpreter接口求解字符串表达式的结果
    int result = expression->interpreter(varmap);
    std::cout << "字符串" << strExp << "的计算结果为：" << result << std::endl;
    // 字符串a-b+c-d+e+f的计算结果为：266

    // 释放资源
    release(expression);
  }
}

int main()
{
  _nmsp1::func();

  return 0;
}