# 类的private继承探讨

```c++
namespace _nmsp1
{
    class Human
    {
    public:
        virtual ~Human()
        {}
        
    };
    
    class Man : public Human
    {
    public:
    };
    
    void func()
    {
        Man myman;
        Human& myhuman = myman; // 父类引用绑定子类对象
        Human* myhuman2 = new Man;  // 父类指针指向子类对象
    }
}
```

如上代码，Man类public继承自Human，可以使用父类引用绑定子类对象，也可以让父类指针指向子类对象。

但是如果这时候我们把继承方式改为private继承，那么可以看到这两行代码都会报错。

```c++
namespace _nmsp1
{
    class Human
    {
    public:
        virtual ~Human()
        {}
        
    };
    
    class Man : private Human
    {
    public:
    };
    
    void func()
    {
        Man myman;
        Human& myhuman = myman; // 父类引用绑定子类对象
        Human* myhuman2 = new Man;  // 父类指针指向子类对象
    }
}
```

报错如下

```shell
main.cpp:23:26: error: ‘_nmsp1::Human’ is an inaccessible base of ‘_nmsp1::Man’
   23 |         Human& myhuman = myman; // 父类引用绑定子类对象
      |                          ^~~~~
main.cpp:24:31: error: ‘_nmsp1::Human’ is an inaccessible base of ‘_nmsp1::Man’
   24 |         Human* myhuman2 = new Man;  // 父类指针指向子类对象
      |
```

private继承其实是一种组合关系。更确切的说，是组合关系中的 `is-implemented-in-terms-of关系`根据...实现出...关系。所以这里建议在使用private继承的时候，就不要把子类和父类单做父子关系来进行理解看待。

一般优先考虑使用组合关系，只有在一些比较特殊的情况和必要的情况下，比如牵扯到一些protected 成员，private成员，虚函数等的时候，才考虑使用private继承来表达组合关系。