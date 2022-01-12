#include <iostream>
#include <vector>
#include <list>

using namespace std;

namespace _nmsp1
{
  void func()
  {
    std::vector<int> msgVector;
    msgVector.push_back(1);
    msgVector.push_back(2);
    msgVector.push_back(3);
    msgVector.push_back(4);
    msgVector.push_back(5);

    for (std::vector<int>::iterator pos = msgVector.begin(); pos != msgVector.end(); ++pos)
    {
      std::cout << *pos << std::endl;
    }

    std::cout << "--------------------------------------------------" << std::endl;

    std::list<int> msglist;
    msglist.push_back(1);
    msglist.push_front(2);
    msglist.push_back(3);
    msglist.push_front(4);

    for (std::list<int>::iterator pos = msglist.begin(); pos != msglist.end(); ++pos)
    {
      std::cout << *pos << std::endl;
    }
  }
}

namespace _nmsp2
{
  // 抽象迭代器类模板
  template <class T>
  class MyIter
  {
  public:
    virtual void First() = 0;     // 指向容器中的第一个元素
    virtual void Next() = 0;      // 指向下一个元素
    virtual bool IsDone() = 0;    // 是否遍历完
    virtual T &CurrentItem() = 0; // 获取当前元素
    virtual ~MyIter() {}
  };

  // 抽象容器
  template <class T>
  class MyContainer
  {
  public:
    virtual MyIter<T> *CreateIterator() = 0; // 创建迭代器
    virtual T &getItem(int index) = 0;       // 获取当前元素
    virtual int getSize() = 0;               // 获取容器元素数量
    virtual ~MyContainer() {}
  };

  // 具体迭代器类模板。这里为了简单起见，本迭代器针对的是大小为10的数组
  template <class T>
  class myVectorIter : public MyIter<T>
  {
  public:
    myVectorIter(MyContainer<T> *tmpc) : myvector(tmpc)
    {
      m_current = 0;
    }

    virtual void First() // 指向容器中的第一个元素
    {
      m_current = 0;
    }

    virtual void Next() // 指向下一个元素
    {
      m_current += 1;
    }

    virtual bool IsDone() // 是否遍历完
    {
      if (m_current >= myvector->getSize())
      {
        return true;
      }
      return false;
    }

    virtual T &CurrentItem() // 获取当前元素
    {
      return myvector->getItem(m_current);
    }

  private:
    MyContainer<T> *myvector;
    int m_current; // 记录数组当前下标（迭代器在当前容器中的位置）
  };

  // 具体容器类
  template <class T>
  class myVector : public MyContainer<T>
  {
  public:
    myVector()
    {
      // 将数据中的元素进行初始化
      for (int i = 0; i < 10; ++i)
      {
        m_eleme[i] = i;
      }
    }

    virtual MyIter<T> *CreateIterator() // 创建迭代器
    {
      // 工厂模式：注意实参传递进去的是该容器的this指针
      return new myVectorIter<T>(this);
      // 要考虑在哪里释放
    }

    virtual T &getItem(int index) // 获取当前元素
    {
      return m_eleme[index];
    }

    virtual int getSize() // 获取容器元素数量
    {
      return 10;
    }

  private:
    // 为了简化代码，这里将容器实现为装入固定10个元素的数组
    T m_eleme[10];
  };
}

int main()
{
  _nmsp1::func();

  // 创建容器
  _nmsp2::MyContainer<int> *p_container = new _nmsp2::myVector<int>();

  // 创建迭代器
  _nmsp2::MyIter<int> *iter = p_container->CreateIterator();

  // 考虑在栈中分配
  _nmsp2::myVectorIter<int> iter2(p_container);

  std::cout << "--------------------------------------------------" << std::endl;

  // 遍历容器 (多态机制，效率上不是很高，尽量考虑栈机制)
  for (iter->First(); !iter->IsDone(); iter->Next())
  {
    std::cout << iter->CurrentItem() << std::endl;
  }

  for (iter2.First(); !iter2.IsDone(); iter2.Next())
  {
    std::cout << iter2.CurrentItem() << std::endl;
  }

  // 0
  // 1
  // 2
  // 3
  // 4
  // 5
  // 6
  // 7
  // 8
  // 9

  // 释放资源
  delete p_container;
  delete iter;

  return 0;
}