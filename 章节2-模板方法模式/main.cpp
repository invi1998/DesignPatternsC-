/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>


// 情景模拟，假设公司现有一个游戏项目组，开发一款单机闯关类游戏。
// 策划提出各种玩法及其游戏数值（游戏人物 血量，攻击力类，魔法值），程序进行功能实现
// 策划给出需求如下，游戏主角是一个战士，（攻击力不高，但是血厚），主角通过不断的闯关，攻防过程中
// 游戏主角的数值（生命值 --- 初值1000 ，蓝量 --- 0，攻击力 --- 初值 200）

// ---------------------------------------------------------------------

// 策划提出给主角增加技能（燃烧，扣除自己300点血，范围内所有敌人照成500点伤害），

// ---------------------------------------------------------------------

// 策划提出增加法师 职业，属性数值（生命值 --- 初值800 ，蓝量 --- 200，攻击力 --- 初值 300）
// 然后策划提出，法师也有一个技能 燃烧 （扣除自己100点蓝量，范围内所有敌人照成650点伤害）

// ---------------------------------------------------------------------
// 新增 奶妈 职业，她也有燃烧技能 .....

// ---------------------------------------------------------------------
// 归纳下来，发现，这些技能都会对敌人产生影响，也会对角色自身产生影响

namespace _nmsp1
{
    // 战士类
    class Warrior
    {
    public:
        // 构造函数
        Warrior(int life, int magic, int attack):m_life(life), m_magic(magic), m_attack(attack)
        {}
        
        // ...其他成员函数（实现战士角色的各种功能）
        
    public:
        // 技能 燃烧
        void JN_Burn()
        {
            std::cout << "燃烧，扣除自己300点血，范围内所有敌人照成500点伤害" << std::endl;
            m_life -= 300;
        }
    
    private:
        // 角色属性
        int m_life; // 血量
        int m_magic;    // 蓝量
        int m_attack;   // 攻击力
        
    };
}

namespace _nmsp2
{
    // 角色基类
    class Fighter
    {
    public:
        // 构造函数
        Fighter(int life, int magic, int attack):m_life(life), m_magic(magic), m_attack(attack)
        {}
        
        // 虚析构函数
        ~Fighter()
        {}
        
        // 技能都会对敌人产生影响，也会对角色自身产生影响
        // 因为不同的角色该技能特效不同，对自己，对敌人都不一样，
        // 所以,在基类中可以考虑提供这两个函数,一个用于技能释放后对自己的影响,一个用于技能释放后对敌人产生的影响
        // 所以这2个函数应该是一个虚函数,在父类中定义,然后在子类中重新实现
        // 然后提供一个技能特效函数,用于进行特效释放(因为这里所有角色技能特效都一样,所以这里不用写为虚函数,只在父类中实现即可)
        
        // 技能 燃烧
        void JN_Burn()
        {
            effect_enemy(); // 对敌人产生的影响
            effect_shelf(); // 对自身产生的影响
            play_effect(); // 播放技能特效
        }
        
    private:
        virtual void effect_enemy() = 0;
        // 函数体为空，表示父类啥也不做，如果需要子类必须实现该函数，可以把该函数声明为纯虚函数
        virtual void effect_shelf() = 0;
        
        void play_effect()
        {
            std::cout << "~~~~~~~~燃烧~~~~~~" << std::endl;
        }
        
    // 这里考虑到未来子类可能会用到（访问）这些角色属性，所以这里不把属性设置为private，而是写为protected
    protected:
        // 角色属性
        int m_life; // 血量
        int m_magic;    // 蓝量
        int m_attack;   // 攻击力
        
    };
    
    
    // ---------------------------------------------------------------------
    // 战士类
    class F_Warrior : public Fighter
    {
    public:
    // 构造函数
        F_Warrior(int life, int magic, int attack):Fighter(life, magic, attack)
        {}
        
    private:
        // 对敌人产生的影响
        void effect_enemy()
        {
            std::cout << "燃烧，扣除自己300点血，范围内所有敌人照成500点伤害" << std::endl;
        }
        
        // 对自身产生的影响
        void effect_shelf()
        {
            m_life -= 300;
        }
    };
    
    // ---------------------------------------------------------------------
    // 法师类
    class F_Magic : public Fighter
    {
    public:
    // 构造函数
        F_Magic(int life, int magic, int attack):Fighter(life, magic, attack)
        {}
        
    private:
        // 对敌人产生的影响
        void effect_enemy()
        {
            std::cout << "扣除自己100点蓝量，范围内所有敌人照成650点伤害" << std::endl;
        }
        
        // 对自身产生的影响
        void effect_shelf()
        {
            m_magic -= 100;
        }
    };
}

// 测试发现，代码有不完善的地方，战士类角色，如果血量不够300点，那么应该不允许释放燃烧技能，
// 同样，法师类角色也应该在蓝量不足100点的时候，不允许释放燃烧技能

namespace _nmsp3
{
    // 角色基类
    class Fighter
    {
    public:
        // 构造函数
        Fighter(int life, int magic, int attack):m_life(life), m_magic(magic), m_attack(attack)
        {}
        
        // 虚析构函数
        ~Fighter()
        {}
        
        // 技能都会对敌人产生影响，也会对角色自身产生影响
        // 因为不同的角色该技能特效不同，对自己，对敌人都不一样，
        // 所以,在基类中可以考虑提供这两个函数,一个用于技能释放后对自己的影响,一个用于技能释放后对敌人产生的影响
        // 所以这2个函数应该是一个虚函数,在父类中定义,然后在子类中重新实现
        // 然后提供一个技能特效函数,用于进行特效释放(因为这里所有角色技能特效都一样,所以这里不用写为虚函数,只在父类中实现即可)
        
        // 技能 燃烧
        void JN_Burn()
        {
            // 如果不能使用该技能，就直接返回
            if (canUseJN() == false)
            {
                return;
            }
            effect_enemy(); // 对敌人产生的影响
            effect_shelf(); // 对自身产生的影响
            play_effect(); // 播放技能特效
        }
        
    private:
        virtual bool canUseJN() = 0;
        virtual void effect_enemy() = 0;
        // 函数体为空，表示父类啥也不做，如果需要子类必须实现该函数，可以把该函数声明为纯虚函数
        virtual void effect_shelf() = 0;
        
        void play_effect()
        {
            std::cout << "~~~~~~~~燃烧~~~~~~" << std::endl;
        }
        
    // 这里考虑到未来子类可能会用到（访问）这些角色属性，所以这里不把属性设置为private，而是写为protected
    protected:
        // 角色属性
        int m_life; // 血量
        int m_magic;    // 蓝量
        int m_attack;   // 攻击力
        
    };
    
    
    // ---------------------------------------------------------------------
    // 战士类
    class F_Warrior : public Fighter
    {
    public:
    // 构造函数
        F_Warrior(int life, int magic, int attack):Fighter(life, magic, attack)
        {}
        
    private:
        // 对敌人产生的影响
        void effect_enemy()
        {
            std::cout << "燃烧，扣除自己300点血，范围内所有敌人照成500点伤害" << std::endl;
        }
        
        // 对自身产生的影响
        void effect_shelf()
        {
            m_life -= 300;
        }
        
        // 判断能否释放技能
        bool canUseJN()
        {
            return m_life > 300;
        }
    };
    
    // ---------------------------------------------------------------------
    // 法师类
    class F_Magic : public Fighter
    {
    public:
    // 构造函数
        F_Magic(int life, int magic, int attack):Fighter(life, magic, attack)
        {}
        
    private:
        // 对敌人产生的影响
        void effect_enemy()
        {
            std::cout << "扣除自己100点蓝量，范围内所有敌人照成650点伤害" << std::endl;
        }
        
        // 对自身产生的影响
        void effect_shelf()
        {
            m_magic -= 100;
        }
        
        // 判断能否释放技能
        bool canUseJN()
        {
            return m_magic >= 100;
        }
    };
}

int main()
{
    // _nmsp1::Warrior mroleObj(1000, 0, 200);
    // mroleObj.JN_Burn();
    
    // 父类指针指向子类对象
    _nmsp2::Fighter *prole_War = new _nmsp2::F_Warrior(2000, 0, 200);
    _nmsp2::Fighter *prole_Mag = new _nmsp2::F_Magic(800, 200, 300);
    
    prole_War->JN_Burn();
    // 燃烧，扣除自己300点血，范围内所有敌人照成500��伤害
    // ~~~~~~~~燃烧~~~~~~
    std::cout << "---------------------------------------------------------------------" << std::endl;
    prole_Mag->JN_Burn();
    // 扣除自己100点蓝量，范围内所有敌人照成650点伤�
    // ~~~~~~~~燃烧~~~~~~
    
    
    // 释放资源
    delete prole_Mag;
    delete prole_War;
    
    std::cout << "---------------------------------------------------------------------" << std::endl;
    // 父类指针指向子类对象
    _nmsp3::Fighter *prole_War2 = new _nmsp3::F_Warrior(1000, 0, 200);
    _nmsp3::Fighter *prole_Mag2 = new _nmsp3::F_Magic(800, 200, 300);
    
    
    prole_War2->JN_Burn();
    prole_Mag2->JN_Burn();
    // 燃烧，扣除自己300点血，范围内所有敌人照成500点伤害
    // ~~~~~~~~燃烧~~~~~~
    // 扣除自己100点蓝量，范围内所有敌人照成650点伤害
    // ~~~~~~~~燃烧~~~~~~
    
    prole_War2->JN_Burn();
    prole_Mag2->JN_Burn();
    // 燃烧，扣除自己300点血，范围内所有敌人照成500点伤害
    // ~~~~~~~~燃烧~~~~~~
    // 扣除自己100点蓝量，范围内所有敌人照成650点伤害
    // ~~~~~~~~燃烧~~~~~~
    
    prole_War2->JN_Burn();
    prole_Mag2->JN_Burn();
    // 燃烧，扣除自己300点血，范围内所有敌人照成500点伤害
    // ~~~~~~~~燃烧~~~~~~
    
    prole_War2->JN_Burn();
    prole_Mag2->JN_Burn();
    
    prole_War2->JN_Burn();
    prole_Mag2->JN_Burn();
    
    
    // 释放资源
    delete prole_Mag2;
    delete prole_War2;

    return 0;
}

