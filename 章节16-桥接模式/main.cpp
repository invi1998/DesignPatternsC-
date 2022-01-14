#include <iostream>

using namespace std;

// 情景模拟
// 图像文件有多种格式：png,jpg，svg等。现在需要做的事就是将这些不同格式的图像文件读出来，
// 读成统一的格式，然后把图像显示出来
namespace _nmsp1
{
  // 图像显示类
  class Image
  {
  public:
    // 根据pDate（缓冲区）中的内容以及iDtatalen所指示的缓冲区的长度，将这些数据显示出来
    void draw(const char *pfilename)
    {
      int iLen = 0;
      char *pdata = parsefile(pfilename, iLen);
      if (iLen > 0)
      {
        std::cout << "显示pData所指向的缓冲区的图像数据" << std::endl;
        // 。。。
        delete pdata;
        // 模拟代码中 因为pdata的内存是new出来的，所以这里需要进行内存释放
      }
    }

    virtual ~Image() {}

  private:
    // 根据文件名分析文件内容，每个子类因为图像文件格式不同，所以会有不同的读取和处理代码
    virtual char *parsefile(const char *pfilename, int &iLen) = 0;
  };

  // png 图像格式处理类
  class Image_png : public Image
  {
  private:
    // 读取png文件内容并进行解析,最终整理成统一的二进制数据格式返回
    virtual char *parsefile(const char *pfilename, int &iLen)
    {
      // 以下是模拟代码，模拟从文件中取得数据，然后最终转换得到了100字节的数据格式（事先约定好的规范）
      std::cout << "开始分析png文件中的数据，并将分析结果放到pData中" << std::endl;
      iLen = 100;
      char *presult = new char[iLen];
      // ...
      return presult;
    }
  };

  // jpg 图像格式处理类
  class Image_jpg : public Image
  {
  private:
    // 读取jpg文件内容并进行解析,最终整理成统一的二进制数据格式返回
    virtual char *parsefile(const char *pfilename, int &iLen)
    {
      // 以下是模拟代码，模拟从文件中取得数据，然后最终转换得到了100字节的数据格式（事先约定好的规范）
      std::cout << "开始分析jpg文件中的数据，并将分析结果放到pData中" << std::endl;
      iLen = 100;
      char *presult = new char[iLen];
      // ...
      return presult;
    }
  };

  // svg 图像格式处理类
  class Image_svg : public Image
  {
  private:
    // 读取svg文件内容并进行解析,最终整理成统一的二进制数据格式返回
    virtual char *parsefile(const char *pfilename, int &iLen)
    {
      // 以下是模拟代码，模拟从文件中取得数据，然后最终转换得到了100字节的数据格式（事先约定好的规范）
      std::cout << "开始分析svg文件中的数据，并将分析结果放到pData中" << std::endl;
      iLen = 100;
      char *presult = new char[iLen];
      // ...
      return presult;
    }
  };

  void func()
  {
    Image *pngObj = new Image_png();
    pngObj->draw("c::\\somedir\\png\\pic1.png");
    // 开始分析png文件中的数�，并将分析结果放到pData中
    // 显示pData所指向的缓冲区的图像数据

    // 释放资源
    delete pngObj;
  }
}

// 目前我们支持的文件类型是 ： png, svg, jpg
// 然后我们支持的操作系统是：windows, liunx, macos
namespace _nmsp2
{
  // 操作系统类型相关抽象类
  class ImageOS
  {
  public:
    virtual void draw(char *pdata, int iLen) = 0;

    virtual ~ImageOS(){};
  };

  // windows操作系统
  class ImageOS_Windows : public ImageOS
  {
  public:
    virtual void draw(char *pdata, int iLen)
    {
      std::cout << "windows下进行图像绘制，绘制pdata指向的缓冲区图像...." << std::endl;
    }
  };

  // linux操作系统
  class ImageOS_Linux : public ImageOS
  {
  public:
    virtual void draw(char *pdata, int iLen)
    {
      std::cout << "linux下进行图像绘制，绘制pdata指向的缓冲区图像...." << std::endl;
    }
  };

  // mac操作系统
  class ImageOS_Mac : public ImageOS
  {
  public:
    virtual void draw(char *pdata, int iLen)
    {
      std::cout << "mac下进行图像绘制，绘制pdata指向的缓冲区图像...." << std::endl;
    }
  };

  // 图像文件格式抽象类
  class ImageFornat
  {
  public:
    ImageFornat(ImageOS *pos) : m_pImgOS(pos)
    {
    }

    virtual void parsefile(const char *pfilename) = 0;
    // 根据文件名分析文件内容，每个文件因为文件格式不同，所以需要做不同的文件处理

    virtual ~ImageFornat() {}

  protected:
    ImageOS *m_pImgOS; // 委托
  };

  // png 格式图像文件
  class Image_png : public ImageFornat
  {
  public:
    Image_png(ImageOS *os) : ImageFornat(os)
    {
    }

    virtual void parsefile(const char *pfilename)
    {
      // 以下是模拟代码，模拟从文件中取得数据，然后最终转换得到了100字节的数据格式（事先约定好的规范）
      std::cout << "开始分析png文件中的数据，并将分析结果放到pData中" << std::endl;
      int iLen = 100;
      char *presult = new char[iLen];
      m_pImgOS->draw(presult, iLen);
      // ...
      delete presult;
    }
  };

  // jpg 格式图像文件
  class Image_jpg : public ImageFornat
  {
  public:
    Image_jpg(ImageOS *os) : ImageFornat(os)
    {
    }

    virtual void parsefile(const char *pfilename)
    {
      // 以下是模拟代码，模拟从文件中取得数据，然后最终转换得到了100字节的数据格式（事先约定好的规范）
      std::cout << "开始分析JPG文件中的数据，并将分析结果放到pData中" << std::endl;
      int iLen = 100;
      char *presult = new char[iLen];
      m_pImgOS->draw(presult, iLen);
      // ...
      delete presult;
    }
  };

  // svg 格式图像文件
  class Image_svg : public ImageFornat
  {
  public:
    Image_svg(ImageOS *os) : ImageFornat(os)
    {
    }

    virtual void parsefile(const char *pfilename)
    {
      // 以下是模拟代码，模拟从文件中取得数据，然后最终转换得到了100字节的数据格式（事先约定好的规范）
      std::cout << "开始分析SVG文件中的数据，并将分析结果放到pData中" << std::endl;
      int iLen = 100;
      char *presult = new char[iLen];
      m_pImgOS->draw(presult, iLen);
      // ...
      delete presult;
    }
  };

  void func()
  {
    // 针对windows操作系统
    ImageOS *osWindows = new ImageOS_Windows();
    // 运行时把图像文件格式png和操作系统动态组合到一起
    ImageFornat *pngImage = new Image_png(osWindows);
    pngImage->parsefile("c::\\somedir\\png\\pic1.png");

    // 开始分析png文件中的数据，并�分析结果放到pData中
    // windows下进行图像绘制，绘制pdata指向的缓冲区图像....

    delete pngImage;
    delete osWindows;
  }
}

int main()
{
  _nmsp1::func();

  _nmsp2::func();

  return 0;
}