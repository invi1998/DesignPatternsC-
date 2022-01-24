# C++ 将对象的构造和析构函数声明为Protected的结果

在看代码的过程中，有时会发现析构函数被定义成virtual，有一些没有定义成virtual但被放置于protected下。网上搜了下了解了原因，下面是较好的解答：



## 1、如果一个类被继承，同时定义了基类以外的成员对象，且基类析构函数不是virtual修饰的，

那么当***\*基类指针或引用指向派生类对象并析构\****（例如自动对象在函数作用域结束时；或者通过delete）时，***\*会调用基类的析构函数而导致派生类定义的成员没有被析构，产生\**\**内存泄露\**\**等问题\****。虽然把析构函数定义成virtual的可以解决这个问题，但是当其它成员函数都不是virtual函数时，**会在基类和派生类引入vtable，实例引入vptr造成运行时的性能损失**。



如果确定不需要直接而是只通过派生类对象使用基类，可以把析构函数定义为***\*protected\****（这样会导致***\*基类和派生类外使用自动对象和delete时的错误\****，因为访问权限禁止调用析构函数），就不会导致以上问题。





## 2、将构造和析构都声明为protected的用法。

从语法上来讲，一个函数被声明为protected或者private，那么这个函数就不能从**“外部”**直接被调用了。
对于protected的函数，子类的“内部”的其他函数可以调用之。
而对于private的函数，只能被本类“内部”的其他函数说调用。



通常使用的场景如下：

### A）如果你 不想让外面的用户直接构造一个类  （假设这个类的名字为A）的对象，而希望用户只能构造这个类A的子类

那你就可以将***\*类A的构造函数/析构函数声明为\**\**protected\****，而***\*将类A的子类的构造函数/析构函数声明为\**\**public\****。例如：

```cpp
class A



{ protected: A(){}



  public: ....



};



calss B : public A



{ public: B(){}



  ....



};



A a; // error



B b; // ok
```



### B) 保证对象只生成在堆上



当我们想**禁止在栈中产生对象**时，如何来实现呢？

将构造函数设为private行吗？no！这样***对象虽然不能在栈中产生，但同样也不能在堆中产生***了。

将析构函数设为private行吗？bad！这样虽然限制了栈对象，但同时也**限制了**继承。

将析构函数设为protected行吗？yes！

例如：

```cpp
class A



{ 　



protected: 　　



           A() { }



　　  ~A() { } 　



public: 　　



         static A* create()



　　{ 　　　return new A() ;//调用保护的构造函数 　　} 　　



         void destroy() 　　



         { 　　　delete this ;//调用保护的析构函数 　　}



};
```

我们可以这样来使用它：

```cpp
A* pa= A::create();

pa->destroy() ;
```



### C) 单例模式

```c++
class A
{
private:
    A(){  }
    ~A(){ }
 
 
public:
    void Instance()//类A的内部的一个函数
    {
        A a;
    }
};
```

上面的代码是能通过编译的。上面代码里的Instance函数就是类A的内部的一个函数。Instance函数体里就构建了一个A的对象。但是，这个Instance函数还是不能够被外面调用的。为什么呢？ 如果要调用Instance函数，必须有一个对象被构造出来。但是构造函数被声明为private的了。外部不能直接构造一个对象出来。

```c++
A aObj; // 编译通不过
aObj.Instance();
```

但是，如果Instance是一个static静态函数的话，就可以不需要通过一个对象，而可以直接被调用。如下：

```c++
class A
{
private:
    A():data(10){ cout << "A" << endl; }
    ~A(){ cout << "~A" << endl; }
 
 
    public:
    static A& Instance()
    {
        static A a;
        return a;
    }
    void Print()
    {
        cout << data << endl;
    }
private:
    int data;
};
 
 
A& ra = A::Instance();
ra.Print();
```

上面的代码其实是设计模式singleton模式的一个简单的C++代码实现。