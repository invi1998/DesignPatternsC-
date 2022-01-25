#include <iostream>
#include <memory>

using namespace std;

namespace _nmsp1
{
  void func()
  {
    shared_ptr<int> myp(new int(5));
    int icount = myp.use_count();
    std::cout << "icount = " << icount << std::endl;
    // icount = 1

    {
      shared_ptr<int> myp2(myp);
      icount = myp2.use_count();
      std::cout << "icount = " << icount << std::endl;
      // icount = 2
    }

    icount = myp.use_count();
    std::cout << "icount = " << icount << std::endl;
    // icount = 1
  }
}

namespace _nmsp2
{
  void func()
  {
    string str1 = "i love China";
    string str2 = str1; // 拷贝构造
    printf("str1所存储的字符串地址 = %p\n", str1.c_str());
    // str1所存储的字符串地址 = 0x7ffe72884940
    printf("str2所存储的字符串地址 = %p\n", str2.c_str());
    // str2所存储的字符串地址 = 0x7ffe72884960
  }
}

int main()
{
  _nmsp1::func();

  _nmsp2::func();

  return 0;
}
