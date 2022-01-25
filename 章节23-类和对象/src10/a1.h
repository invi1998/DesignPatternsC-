#ifndef __A1H_
#define __A1H_

class A2;

class A1
{
public:
  A2 *m_pa2;
  // A2 m_obj_a2;	//  A2类型的对象，此时，就算有类A2的前向声明,也会编译报错，因为此时此刻，
  // 它需要的是完整的类A2的定义，它声明一个对象，是需要明确知道类A2的定义体长什么样的

  void funca1();
  // {
  //     int tmpvalue = sizeof(A2);  // 报错 使用了未定义类型A2
  // }

  void funca1_2();
  // {
  //     m_obj_a2->funca2();     // 调用类A2的成员函数 报错 使用了未定义类型A2
  // }
};

#endif