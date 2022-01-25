#include <iostream>
#include <cstring>

using namespace std;

namespace _nmsp1
{
  class mystring
  {
  public:
    // 在构造函数中把这个 stringValue 构造出来
    mystring(const char *tmpstr = "") : pvalue(new stringValue(tmpstr)) // 构造函数
    {
    }

    // 拷贝构造函数
    mystring(const mystring &tmpv) // :pvalue(tmpv.pvalue)
    {
      if (tmpv.pvalue->shareable)
      {
        pvalue = tmpv.pvalue;
        ++pvalue->refcount; // 引用计数加1
      }
      else
      {
        // 不能共享，只能自己自立门户
        pvalue = new stringValue(tmpv.pvalue->point);
      }
    }

    // 析构函数
    ~mystring()
    {
      --pvalue->refcount;
      if (pvalue->refcount == 0)
      {
        delete pvalue;
      }
    }

    // 拷贝赋值运算符
    mystring &operator=(const mystring &tmpv)
    {
      if (this == &tmpv)
      {
        return *this;
      }

      // 将原来的那个(也就是自己） mystring 对象的引用计数 -1
      --pvalue->refcount;
      if (pvalue->refcount == 0)
      {
        delete pvalue;
      }

      // 然后将自己指向新的 mystring 对象，
      pvalue = tmpv.pvalue;
      // 然后引用计数 + 1
      ++pvalue->refcount;

      return *this;
    }

    // 重载[]操作符
    // const char& operator[](int index)
    // {
    //     return pvalue->point[index];
    // }

    // 重载非const版本的operator[]，实现写时复制
    char &operator[](int index)
    {
      if (pvalue->refcount > 1)
      {
        // 说明有其他mystring对象也指向该字符串。那这个时候就得将其复制出来
        --pvalue->refcount;
        pvalue = new stringValue(pvalue->point); // 写时复制，自立门户，开辟新内存
      }

      // 一旦这个 operator[] 操作符被调用，那么就意味着这个字符串将不能再被其他 mystring 对象共享了
      pvalue->shareable = false;

      return pvalue->point[index];
    }

  private:
    // 创建一个类中类，用来保存引用计数和指向的字符串指针
    struct stringValue
    {
      bool shareable; // 一个是否能被共享的标记，这个是否能被共享就是只是否能够被其他mystring对象共享
      // 刚创建一个mystring对象的时候，所指向的那个字符串当然应该是能够被共享的

      size_t refcount; // 引用计数
      char *point;     // 指向实际字符串

      // 构造函数
      stringValue(const char *tmpstr) : refcount(1), shareable(true)
      {
        // 因为是共享内存，所以只有在第一次指向某个字符串的时候，才会开辟内存（才会指向这个构造函数）
        point = new char[strlen(tmpstr) + 1];
        strcpy(point, tmpstr);
      }

      // 析构函数
      ~stringValue()
      {
        delete[] point;
      }
    };

  private:
    stringValue *pvalue; // mystring类中指向 stringValue对象的指针
  };
}

int main()
{
  _nmsp1::mystring str1("i love china");
  _nmsp1::mystring str2 = ("i love china");

  _nmsp1::mystring str3(str1); // 调用拷贝构造函数
  str2 = str1;                 // 调用拷贝赋值运算符

  _nmsp1::mystring str4 = str1; // 调用拷贝构造函数；

  std::cout << str1[0] << std::endl; // i
  str1[0] = 'u';
  std::cout << str1[0] << std::endl; // u

  _nmsp1::mystring str5 = "i love china";
  char *pmypoint = &str5[0]; // 也就是 pmypoint 也是指向的 "i love china"
  _nmsp1::mystring str6 = str5;

  *pmypoint = 'L';

  std::cout << sizeof(string) << std::endl;
  std::cout << sizeof(_nmsp1::mystring) << std::endl;

  return 0;
}