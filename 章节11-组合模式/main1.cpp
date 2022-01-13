#include <iostream>
#include <list>

using namespace std;

namespace _nmsp1
{
    // 文件相关的类
    class File
    {
    public:
        // 构造函数
        File(string name):m_sname(name)
        {}
        
        // 显示文件名
        void showName(string lvlstr)    // lvlstr 用来显示层次关系的缩进字符串内容
        {
            std::cout << lvlstr << "[-]" << m_sname << std::endl;
            // '-' 代表是一个文件，属于末端节点（与之对应的 + 代表一个目录）
        }
        
    private:
        string m_sname;     // 文件名
    };
    
    // 目录相关的类
    class Dir
    {
    public:
        Dir(string name) : m_sname(name)
        {}
        
    public:
        // 往目录中增加文件
        void addFile(File* tmpv)
        {
            m_childFile.push_back(tmpv);
        }
        
        // 往目录中增加目录
        void addDir(Dir* tmpv)
        {
            m_childDir.push_back(tmpv);
        }
        
        // 显示目录名(同时也要负责旗下的目录和文件名显示)
        void showName(string lvlstr)
        {
            // 输出本目录名（+代表一个目录）
            std::cout << lvlstr << "[+]" << m_sname << std::endl;
            
            // 输出所包含的文件名
            lvlstr += "────";
            // 本目录中的文件和目录的显示，要缩进一些来显示
            for(auto iter = m_childDir.begin(); iter != m_childDir.end(); ++iter)
            {
                (*iter)->showName(lvlstr);
            }
            
            // 输出所包含的文件名
            for(auto iter = m_childFile.begin(); iter != m_childFile.end(); ++iter)
            {
                (*iter)->showName(lvlstr);
            }
            
        }
        
    private:
        string m_sname; // 目录名
        list<File*> m_childFile;    // 目录中包含的文件列表
        list<Dir*> m_childDir;      // 目录中包含的子目录列表
    };
}

// 当前这个范例有什么问题？
// 为了输出树形结构，这里我们对目录和文件进行了区分（写了两个类，其实也就是树形结构里的树枝和树叶）
// 所以，这里就引入组合模式，组合模式就是为了解决在处理这些树形结构的时候，不再需要将叶子和枝干进行区分
// 而是引入一个新的类，比如这里可以引入一个 FileSystem 文件系统抽象类，然后在该抽象类中提供一个接口
// 然后让File类和Dir类分别继承自FileSystem抽象类

namespace _nmsp2
{
    // 抽象父类（文件系统）
    class FileSystem
    {
    public:
        virtual void _showName(int level) = 0;   // 显示名字，参数level表示文件层级
        virtual int _add(FileSystem* pfilesys) = 0;  // 用于向当前目录中增加文件 或者 子目录
        virtual int _remove(FileSystem* pfilesys) = 0;  // 用于从当前目录中移除文件或者子目录
        
        virtual ~FileSystem() {}
    };
    
    // 文件相关的类
    class File : public FileSystem
    {
    public:
        File(string tmpv) : m_sname(tmpv)
        {}
        
        virtual void _showName(int level)
        {
            for (int i = 0; i < level; ++i)
            {
                std::cout << "────";
            }
            
            std::cout << "[-]" << m_sname << std::endl;
        }
        
        virtual int _add(FileSystem* tmpv)
        {
            return -1;
        }
        
        virtual int _remove(FileSystem* tmpv)
        {
            return -1;
        }
        
    private:
        string m_sname;
    };
    
    // 目录相关的类
    class Dir : public FileSystem
    {
    public:
        Dir(string name):m_sname(name)
        {}
        
        virtual void _showName(int level)
        {
            for (int i = 0; i < level; ++i)
            {
                std::cout << "────";
            }
            
            std::cout << "[+]" << m_sname << std::endl;
            
            // 显示的层级向下走一级
            level++;
            // 输出所包含的子类容
            for(auto iter = m_child.begin(); iter!=m_child.end(); ++iter)
            {
                (*iter)->_showName(level);
            }
        }
        
        virtual int _add(FileSystem* tmpv)
        {
            m_child.push_back(tmpv);
            return 0;
        }
        
        virtual int _remove(FileSystem* tmpv)
        {
            m_child.remove(tmpv);
            return 0;
        }
        
    private:
        string m_sname; // 文件目录名
        list<FileSystem*> m_child;  // 目录中包含的文件或者其他目录列表
    };
    
    void func()
    {
        FileSystem* pdir1 = new Dir("root");
        FileSystem* pdir2 = new Dir("src");
        FileSystem* pdir3 = new Dir("lib");
        FileSystem* pdir4 = new Dir("net");
        FileSystem* pdir5 = new Dir("commpoment");
        
        FileSystem* file1 = new File("vue.config.js");
        FileSystem* file2 = new File("main.ts");
        FileSystem* file3 = new File("shims-vue.d.ts");
        FileSystem* file4 = new File("README.md");
        
        FileSystem* file5 = new File("hello.vue");
        FileSystem* file6 = new File("world.vue");
        FileSystem* file7 = new File("plugin.ts");
        FileSystem* file8 = new File("config.tsx");
        
        FileSystem* file9 = new File(".bable.rc");
        FileSystem* file10 = new File("socket.ts");
        FileSystem* file11 = new File("include.h");
        FileSystem* file12 = new File("error.ts");
        
        FileSystem* file13 = new File("index.vue");
        FileSystem* file14 = new File("big.vue");
        
        pdir5->_add(file13);
        pdir5->_add(file14);
        
        pdir2->_add(pdir5);
        
        pdir4->_add(file12);
        pdir4->_add(file11);
        pdir4->_add(file10);
        
        pdir3->_add(file9);
        
        pdir2->_add(file5);
        pdir2->_add(file6);
        pdir2->_add(file7);
        pdir2->_add(file8);
        
        pdir1->_add(pdir2);
        pdir1->_add(pdir3);
        pdir1->_add(pdir4);
        
        pdir1->_add(file1);
        pdir1->_add(file2);
        pdir1->_add(file3);
        pdir1->_add(file4);
        
        pdir1->_showName(0);
        // [+]root
        // ────[+]src
        // ────────[+]commpoment
        // ────────────[-]index.vue
        // ────────────[-]big.vue
        // ────────[-]hello.vue
        // ────────[-]world.vue
        // ────────[-]plugin.ts
        // ────────[-]config.tsx
        // ────[+]lib
        // ────────[-].bable.rc
        // ────[+]net
        // ────────[-]error.ts
        // ────────[-]include.h
        // ────────[-]socket.ts
        // ────[-]vue.config.js
        // ────[-]main.ts
        // ────[-]shims-vue.d.ts
        // ────[-]README.md
    }
}

int main()
{
    // 创建一个目录树结构
    _nmsp1::Dir* pdir1 = new _nmsp1::Dir("root");
    _nmsp1::Dir* pdir2 = new _nmsp1::Dir("src");
    _nmsp1::Dir* pdir3 = new _nmsp1::Dir("lib");
    _nmsp1::Dir* pdir4 = new _nmsp1::Dir("net");
    _nmsp1::Dir* pdir5 = new _nmsp1::Dir("commpoment");
    
    _nmsp1::File* file1 = new _nmsp1::File("vue.config.js");
    _nmsp1::File* file2 = new _nmsp1::File("main.ts");
    _nmsp1::File* file3 = new _nmsp1::File("shims-vue.d.ts");
    _nmsp1::File* file4 = new _nmsp1::File("README.md");
    
    _nmsp1::File* file5 = new _nmsp1::File("hello.vue");
    _nmsp1::File* file6 = new _nmsp1::File("world.vue");
    _nmsp1::File* file7 = new _nmsp1::File("plugin.ts");
    _nmsp1::File* file8 = new _nmsp1::File("config.tsx");
    
    _nmsp1::File* file9 = new _nmsp1::File(".bable.rc");
    _nmsp1::File* file10 = new _nmsp1::File("socket.ts");
    _nmsp1::File* file11 = new _nmsp1::File("include.h");
    _nmsp1::File* file12 = new _nmsp1::File("error.ts");
    
    _nmsp1::File* file13 = new _nmsp1::File("index.vue");
    _nmsp1::File* file14 = new _nmsp1::File("big.vue");
    
    pdir5->addFile(file13);
    pdir5->addFile(file14);
    
    pdir2->addDir(pdir5);
    
    pdir4->addFile(file12);
    pdir4->addFile(file11);
    pdir4->addFile(file10);
    
    pdir3->addFile(file9);
    
    pdir2->addFile(file5);
    pdir2->addFile(file6);
    pdir2->addFile(file7);
    pdir2->addFile(file8);
    
    pdir1->addDir(pdir2);
    pdir1->addDir(pdir3);
    pdir1->addDir(pdir4);
    
    pdir1->addFile(file1);
    pdir1->addFile(file2);
    pdir1->addFile(file3);
    pdir1->addFile(file4);
    
    
    // 输出目录结构
    pdir1->showName("┼");
    // ┼[+]root
    // ┼────[+]src
    // ┼────────[+]commpoment
    // ┼────────────[-]index.vue
    // ┼────────────[-]big.vue
    // ┼────────[-]hello.vue
    // ┼────────[-]world.vue
    // ┼────────[-]plugin.ts
    // ┼────────[-]config.tsx
    // ┼────[+]lib
    // ┼────────[-].bable.rc
    // ┼────[+]net
    // ┼────────[-]error.ts
    // ┼────────[-]include.h
    // ┼────────[-]socket.ts
    // ┼────[-]vue.config.js
    // ┼────[-]main.ts
    // ┼────[-]shims-vue.d.ts
    // ┼────[-]README.md
    
    
    std::cout << "-------------------------------------------" << std::endl;
    _nmsp2::func();

    // 内存释放。。。
    return 0;
}

