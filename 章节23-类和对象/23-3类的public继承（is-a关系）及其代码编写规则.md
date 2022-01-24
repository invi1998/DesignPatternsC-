# 类的public继承（is-a关系）及其代码编写规则

c++类与类之间的关系这个话题比较重要，在实际开发中也多有应用，所以这里有必要总结一下。子类继承父类的继承关系有3中

## C++中的三种继承关系

------

### 先看类中声明成员时的三种访问权限

- **public** : 可以被任意实体访问
- **protected** : 只允许子类及本类的成员函数访问
- **private** : 只允许本类的成员函数访问

在类继承时也是 public、protected 和 private 三种方式， 当成员的访问权限和继承相结合时，得到的就是C++中对成员的综合权限了。

------

### 声明类成员时的权限与继承时的权限组合后的结果：

|  基类中   | 继承方式  | 子类中对基类成员的访问权限 |
| :-------: | :-------: | :------------------------: |
|  public   |  public   |           public           |
|  public   | protected |         protected          |
|  public   |  private  |          private           |
| protected |  public   |         protected          |
| protected | protected |         protected          |
| protected |  private  |          private           |
|  private  |  public   |        子类无权访问        |
|  private  | protected |        子类无权访问        |
|  private  |  private  |        子类无权访问        |

### 由以上组合结果可以看出

1、public继承不改变基类成员的访问权限

2、private继承使得基类所有成员在子类中的访问权限变为private

3、protected继承将基类中public成员变为子类的protected成员，其它成员的访问 权限不变。

4、基类中的private成员不受继承方式的影响，子类永远无权访问。

------

## 在子类中恢复基类的访问权限

C++支持以两种方式实现该目的

- 方法一，使用using 语句，这是C++标准建议使用的方式
- 方法二，使用访问声明，形式为 base-class::member;， 位置在子类中适当的访问声明处。(注，只能恢复原有访问权限， 而不能提高或降低访问权限)

牢记一点：public继承代表的是一种 is-a（is a kind of）关系，是一个 的意思。也就是说一个子类通过public继承一个父类，这就表示程序员高数编译器，通过这个子类产生的对象一定也是一个父类对象。

比如一个父类（Human）,子类（Men）：这就是一个is-a关系，子类男人一定是人类，但是人类不一定是男人。也就是父类表示一种更泛化的概念，而子类是一种更为特化的概念

public继承检验规则：能够在父类对象上做的行为，也必然能够在子类对象上做，每个子类对象同时也都是一个父类对象

```c++
    class Human
    {
    public:
        
    };
    
    // 共有继承
    class Man : public Human
    {
    public:
    
    };
```

public继承引入的目的虽然与代码重用有关，比如我们子类可能有些时候需要使用父类的一些代码，但是它并不是通常我们所理解的 为了让子类重用父类的代码来实现子类的功能。 子类的功能还可以用后续我会提到的类之间的组合关系，或者private继承来实现，public继承它更强调的是一种is-a关系。换句话说在需要用到父类对象的场合下，可以用子类对象来代替。这里就涉及到一个叫做 【里式替换 Liskov替换】的原则，这个原则说的就是：任何使用基类的地方都应该可以使用子类进行无差别的替换。

## 子类遮蔽父类的普通成员函数

```c++
namespace _nmsp1
{
    class Human
    {
    public:
        void eat()
        {
            std::cout << "人类吃食物！" << std::endl;
        }
        virtual ~Human() {}
    };
    
    // 公有继承
    class Man : public Human
    {
    public:
        void eat()
        {
            std::cout << "男人喜欢吃面食" << std::endl;
        }
    
    };
}

int main()
{
    _nmsp1::Man myman;
    myman.eat();
    // 男人喜欢吃面食

    return 0;
}
```

从执行结果来看，调用eat函数是调用的子类的eat函数，子类的eat函数遮蔽了父类的同名eat函数。当然如果非要调用父类的eat函数，可以使用 子类对象名.父类名：：eat()；来进行调用

```c++
myman.Human::eat();
// 人类吃食物！
```

从范例中可以看到，虽然语法上能够做到子类对父类同名函数的覆盖（遮蔽），但是并不建议子类写一个同名eat函数去覆盖父类的同名函数，因为对于public继承来讲，在自己的子类中你重新实现了eat函数，就等于违反了父类和子类之间的这种is-a关系。所以对于public继承来讲，不建议也不应该用子类内的普通成员函数覆盖（遮蔽）父类的同名普通函数。既然它在父类中是一个普通成员函数，那么就代表它在子类中不会有不同行为，代表的是一种不变性。

## 父类的纯虚函数接口

纯虚函数做到了让子类继承父类的成员函数接口。

##### 纯虚函数意味着什么？

> 纯虚函数所在的类变为抽象类，抽象类是不能用来生成该类对象的。

> 任何从抽象类继承的子类都要定义该纯虚函数自己的实现方法，也就是说子类从父类中只继承了一个成员函数的接口。

日后如果需要在子类中来实现具体的函数代码的时候，就可以在父类中定义一个纯虚函数。

```c++
namespace _nmsp1
{
    class Human
    {
    public:
        virtual ~Human() {}
        
        // 纯虚函数
        virtual void work() = 0;
    };
    
    // 公有继承
    class Man : public Human
    {
    public:
        virtual void work()
        {
            std::cout << "男人做重体力工作" << std::endl;
        }
    
    };
    
    class Women : public Human
    {
    public:
        virtual void work()
        {
            std::cout << "女人做轻体力工作" << std::endl;
        }
    };
}
```



## 父类的虚函数接口

虚函数：让子类继承父类的成员函数接口和实现，同时子类还可以提供自己的新的实现。

```c++
namespace _nmsp1
{
    class Human
    {
    public:
        // 虚函数
        virtual void avlife()
        {
            std::cout << "人类平均寿命75岁" << std::endl; 
        }
    };
    
    // 公有继承
    class Man : public Human
    {
    public:
        virtual void avlife()
        {
            std::cout << "男人平均寿命70岁" << std::endl;
        }
    
    };
    
    class Women : public Human
    {
    public:
        virtual void avlife()
        {
            std::cout << "女人平均寿命80岁" << std::endl;
        }
    };
}
```



## 为纯虚函数指定实现体

首先纯虚函数也是可以有实现体的。

```c++
namespace _nmsp1
{
    class Human
    {
    public:
        virtual ~Human() {}
        
        // 纯虚函数
        virtual void avlife() = 0;
    };
    
    // 父类纯虚函数的类外实现体
    void Human::avlife()
    {
        std::cout << "人类平均寿命75岁" << std::endl; 
    }
    
    // 公有继承
    class Man : public Human
    {
    public:
        virtual void avlife()
        {
            std::cout << "男人平均寿命70岁" << std::endl;
        }
    
    };
    
    class Women : public Human
    {
    public:
        virtual void avlife()
        {
            std::cout << "女人平均寿命80岁" << std::endl;
            // 调用父类的纯虚函数接口实现
            Human::avlife();
        }
    };
}
```



##### 可能会有人产生疑惑，说给这个纯虚函数增加实现体合适吗？

当然，他有不合适的地方，因为纯虚函数存在的初衷就是希望在父类中没有实现体，而是在子类中进行实现，那这里你给这个纯虚函数添加实现体就显然违背了这个原则。那为什么还要给这个纯虚函数添加实现体呢？其实这是一个偷懒目的，试想如果一个抽象类他的子类众多，而且他的纯虚函数接口子类实现绝大多数代码都相同，那么对于这块相同的代码放到父类中来实现是合适的。

##### 所以给父类的纯虚函数增加实现体有两个目的：

> 强制子类必须实现纯虚函数接口

> 让一些确实不需要试下纯虚函数接口的子类有机会直接使用父类的纯虚函数接口实现（其实也就是把公共代码放到父类纯虚函数接口实现中去）

## 类的public继承（is-a关系）综合范例

```c++
namespace _nmsp2
{
    class A{};
    class B:public A {};
    class C:public B {};
    
    void myfunc(A tmpa)
    {
        std::cout << "void myfunc(A tmpa)执行了" << std::endl;
    }
    
    void myfunc(C tmpc)
    {
        std::cout << "void myfunc(C tmpc)执行了" << std::endl;
    }
    
    void func()
    {
        B b1;
        myfunc(b1);
        // void myfunc(A tmpa)执行了
    }
}
```

可以看到传递进去一个B类型的实参，调用的是B类型的父类型重载版本的函数，这是因为类B是通过public继承自类A的，因此，类B和类A是一种is-a关系（也就是子类对象一定是父类对象），也就是B类对象也一定是A类对象，所以这里调用的也就是形参为A类的myfunc()

```c++
void myfunc(A tmpa)
    {
        std::cout << "void myfunc(A tmpa)执行了" << std::endl;
    }

void func()
    {
        B b1;
        myfunc(b1);
        // void myfunc(A tmpa)执行了
        
        C c1;
        myfunc(c1);
        // void myfunc(A tmpa)执行了
    }
```

如果这时候我们只体用A类型的形参的myfunc，那么B类型实参和C类型实参调用的也都是这个A类型形参版本的myfunc。很容易理解，因为B和A是is-a关系，所以B类型对象是A类型对像，同时C public继承B，所以C与B也是is-a关系，所以C类型对象也是B类型对象，所以C类型对象也就是A类型对象，所以调用myfunc(A tmpa) 是没有毛病的。

```c++
void myfunc(A tmpa)
    {
        std::cout << "void myfunc(A tmpa)执行了" << std::endl;
    }
    
    void myfunc(B tmpb)
    {
        std::cout << "void myfunc(B tmpb)执行了" << std::endl;
    }
```

如果我们这个时候提供A类型重载和B类型重载，那么B对象和C对象的调用情况都应该是B类型重载版本的myfunc，B对象自然不用多说，C对象因为和B是父子关系，和A是爷孙关系，和B对象关系更为亲近，所以调用的是B版本的重载

## public继承关系下的代码编写规则

1. 父类的普通成员函数，子类不应该去覆盖。如果需要覆盖，那么应该将父类中该普通成员函数修改为虚函数。
2. 父类的纯虚函数是用来定义一个接口的，子类继承父类的时候等于继承了该接口，具体的实现代码要求子类自己取实现
3. 父类的普通成员函数（非纯虚函数），不但定义了一个接口，还书写了实现代码（缺省代码），子类继承了该接口，子类可以书写自己的实现代码，也可以不写而是使用父类的缺省实现。
4. 在可以使用非public继承时，就不要使用public继承。（这里为什么要强调这点呢？因为很多程序员在涉及到继承的时候，一律不假思索的全都使用public继承）