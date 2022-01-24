#include <iostream>
#include <map>

using namespace std;

namespace _nmsp1
{
  class Info
  {
  private:
    std::string m_name; // 名字
    int m_gender;       // 性别
    int m_age;          // 年龄
  };

  class Human
  {
  public:
    Info m_info;
  };
}

namespace _nmsp2
{
  // 现在希望开发一个不允许键重复的容器，smap

  void func()
  {
    std::multimap<int, int> tmpc;
    tmpc.insert(std::make_pair(1, 1));
    tmpc.insert(std::make_pair(2, 3));
    tmpc.insert(std::make_pair(1, 5));

    std::cout << "tmpc.size() = " << tmpc.size() << std::endl;
    // tmpc.size() = 3
  }
}

namespace _nmsp3
{
  template <typename T, typename U>
  class smap
  {
  public:
    void insert(const T &key, const U &value)
    {
      if (container.find(key) != container.end())
        return;
      container.insert(std::make_pair(key, value));
    }

    size_t size()
    {
      return container.size();
    }

  private:
    std::multimap<T, U> container;
  };

  void func()
  {
    smap<int, int> tmpsmap;
    tmpsmap.insert(1, 1);
    tmpsmap.insert(2, 3);
    tmpsmap.insert(1, 5);

    std::cout << "tmpsmap.size() = " << tmpsmap.size() << std::endl;
    // tmpsmap.size() = 2
  }
}

namespace _nmsp4
{
  class A
  {
  public:
    void funca()
    {
      std::cout << "A::funca()被执行了" << std::endl;
    }
  };

  class B
  {
  public:
    B(A *tmpA) : m_pa(tmpA)
    {
    }

    void funcB()
    {
      m_pa->funca();
    }

  private:
    A *m_pa;
  };

  void func()
  {
    A *oba = new A();
    B *obb = new B(oba);

    obb->funcB();
    // A::funca()被执行了

    delete oba;
    delete obb;
  }
}

int main()
{
  _nmsp2::func();

  _nmsp3::func();

  _nmsp4::func();

  return 0;
}