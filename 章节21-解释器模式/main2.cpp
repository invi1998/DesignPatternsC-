#include <iostream>
#include <map>
#include <stack>
#include <cstring>
#include <vector>

using namespace std;

// 机器人运动控制范例
// 规定机器人的行为规则
// 1：运动反向有4个，上（up）下（down）左（left）右（right）
// 2：机器人的运动方式有2种，行走（walk），奔跑（run）
// 机器人能够接收的终结符表达式有 运动方向， 运动方式， 运动距离（单位：米）
// left walk 15; 让机器人向左走15米
// down run 29； 让机器人向下跑29米
// 机器人能接收的非终结符表达式其实就是句子，句子由“运动方向，运动方式，运动距离”构成
// 另一个非终结符表达式“and” ,代表和的意思
// left walk 14 and down run 23;

namespace _nmsp1
{
  // 表达式父类
  class Expression
  {
  public:
    virtual ~Expression() {}

  public:
    // 解析语法树中的单前节点
    virtual string interpreter() = 0;
  };

  // 运动方向终结符表达式
  class DirectionExpression : public Expression
  {
  public:
    DirectionExpression(const string &direction)
    {
      m_direction = direction;
    }

    virtual string interpreter()
    {
      if (m_direction == "up")
      {
        return "向上";
      }
      else if (m_direction == "down")
      {
        return "向下";
      }
      else if (m_direction == "left")
      {
        return "向左";
      }
      else if (m_direction == "right")
      {
        return "向右";
      }
      else
      {
        return "运动方向错误";
      }
    }

  private:
    string m_direction; // 运动反向有4个，上（up）下（down）左（left）右（right）
  };

  // 运动方式终结符表达式
  class ActionExpression : public Expression
  {
  public:
    ActionExpression(const string &action)
    {
      m_action = action;
    }

    virtual string interpreter()
    {
      if (m_action == "walk")
      {
        return "行走";
      }
      else if (m_action == "run")
      {
        return "奔跑";
      }
      else
      {
        return "运动方式错误";
      }
    }

  private:
    string m_action; // 机器人的运动方式有2种，行走（walk），奔跑（run）
  };

  // 运动距离终结符表达式
  class DistanceExpression : public Expression
  {
  public:
    DistanceExpression(const string &distance)
    {
      m_distance = distance;
    }

    virtual string interpreter()
    {
      return m_distance + "米";
    }

  private:
    string m_distance; // 运动距离，用字符串表示
  };

  // 非终结符表达式（句子）
  class SentenceExpression : public Expression
  {
  public:
    SentenceExpression(Expression *direction, Expression *action, Expression *distance)
    {
      m_direction = direction;
      m_action = action;
      m_distance = distance;
    }

    // 获取方向
    Expression *getDirection()
    {
      return m_direction;
    }

    // 获取方式
    Expression *getAction()
    {
      return m_action;
    }

    // 获取距离
    Expression *getDistance()
    {
      return m_distance;
    }

    virtual string interpreter()
    {
      return m_direction->interpreter() + m_action->interpreter() + m_distance->interpreter();
    }

  private:
    Expression *m_direction; // 运动方向
    Expression *m_action;    // 运动方式
    Expression *m_distance;  // 运动距离
  };

  // and 非终结符表达式
  class AndExpression : public Expression
  {
  public:
    AndExpression(Expression *left, Expression *right) : m_left(left), m_right(right)
    {
    }

    Expression *getLeft()
    {
      return m_left;
    }

    Expression *getRight()
    {
      return m_right;
    }

    virtual string interpreter()
    {
      return m_left->interpreter() + "然后，" + m_right->interpreter();
    }

  private:
    // 左右各一个操作数
    Expression *m_left;
    Expression *m_right;
  };

  // 提供一个字符串拆分函数
  void split_string(const string str, vector<string> &vec, const string cut)
  {
    string::size_type begin_index, end_index;
    end_index = str.find(cut);
    begin_index = 0;
    while (string::npos != end_index)
    {
      vec.push_back(str.substr(begin_index, end_index - begin_index));
      begin_index = end_index + cut.size();
      end_index = str.find(cut, begin_index);
    }
    if (begin_index != str.length())
    {
      vec.push_back(str.substr(begin_index));
    }
  }

  // 搭建语法树（分析创建）
  Expression *analyse(string strExp)
  {
    std::stack<Expression *> expStack;
    Expression *direction = nullptr;
    Expression *action = nullptr;
    Expression *distance = nullptr;

    // 左右孩子
    Expression *left = nullptr;
    Expression *right = nullptr;

    // 机器人控制命令指令之间是使用空格进行分割的
    // char *strc = new char[strlen(strExp.c_str()) + 1];
    // strcpy(strc, strExp.c_str());
    // std::vector<string> resultVec;
    // char* tmpStr = strtok(strc, " ");       // 按空格来切割字符串
    // while(tmpStr != nullptr)
    // {
    //     resultVec.push_back(string(tmpStr));
    //     tmpStr = strtok(NULL, " ");
    // }
    // delete[] strc;

    std::vector<string> resultVec;
    split_string(strExp, resultVec, " ");

    // for(auto iter = resultVec.begin(); iter!=resultVec.end(); ++iter)
    // {
    //     std::cout << (*iter) << std::endl;
    // }

    // 开始解析
    for (auto iter = resultVec.begin(); iter != resultVec.end(); ++iter)
    {
      if ((*iter) == "and")
      {
        left = expStack.top(); // 返回栈顶元素
        ++iter;

        direction = new DirectionExpression(*iter);
        ++iter;

        action = new ActionExpression(*iter);
        ++iter;

        distance = new DistanceExpression(*iter);

        // 然后用上面分析出来的节点创建一个新的句子（因为左右孩子都是句子）
        right = new SentenceExpression(direction, action, distance);

        // 把左孩子和右孩子塞到栈中
        expStack.push(new AndExpression(left, right));
      }
      else
      {
        direction = new DirectionExpression(*iter);
        ++iter;

        action = new ActionExpression(*iter);
        ++iter;

        distance = new DistanceExpression(*iter);

        expStack.push(new SentenceExpression(direction, action, distance));
      }
    }
    Expression *result = expStack.top();
    return result;
  }

  // 释放内存
  void release(Expression *expression)
  {
    SentenceExpression *pse = dynamic_cast<SentenceExpression *>(expression);

    if (pse)
    {
      release(pse->getDirection());
      release(pse->getAction());
      release(pse->getDistance());
    }
    else
    {
      // 左孩子右孩子（然后孩子节点会跳进上面这个if里去）
      AndExpression *pae = dynamic_cast<AndExpression *>(expression);
      if (pae)
      {
        release(pae->getLeft());
        release(pae->getRight());
      }
    }
    delete expression;
  }

  void func()
  {
    string zl = "left walk 12 and up run 23";

    Expression *expression = analyse(zl);

    std::cout << expression->interpreter() << std::endl;
    // 向左行走12米然后，向上奔跑23米

    // 释放内存
    release(expression);
  }

}

int main()
{
  _nmsp1::func();

  return 0;
}