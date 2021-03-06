# DesignPatternsC++
c++设计模式

系统学习C++设计模式方面知识，逐一详解二十多个常见的设计模式。

| 范围\目的 | 创建型模式                | 结构型模式                                  | 行为型模式                                               |
| --------- | ------------------------- | ------------------------------------------- | -------------------------------------------------------- |
| 类模式    | 工厂方法                  | (类）适配器                                 | 模板方法、解释器                                         |
| 对象模式  | 单例 原型 抽象工厂 建造者 | 代理 (对象）适配器 桥接 装饰 外观 享元 组合 | 策略 命令 职责链 状态 观察者 中介者 迭代器 访问者 备忘录 |



**不要在类的构造函数和析构函数中调用类的虚函数，以防出现问题**

注意一个编程技巧：如果类中有 指针成员，那么一般都需要我们手工的为类写拷贝构造函数和拷贝赋值运算符。否者就可能会出现问题。
