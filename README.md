# 课程安排

### 00 序言
1. 前言
2. 语言基础说明<br>
   >
   > VEX程序可以支持 _C++_ 和 _python_ ，但是在这里只涉及 ___C++___ <br>
   > 如果有 _python_ 基础而没有 _C++_ 基础，建议访问[菜鸟教程](https://www.runoob.com/cplusplus/cpp-tutorial.html)来学习语法知识<br>
   > 如果编程基础近似为0而对编程有兴趣的同学，建议先在[洛谷题单](https://www.luogu.com.cn/training/list)完成入门系列之后再来看VEX的教程
   >
4. 编译环境
   > 支持VEX程序的软件有 [vscode](https://code.visualstudio.com/sha/download?build=stable&os=win32-x64-user) 、_VEXcode pro v5_ 等，本教程只介绍 ___vscode___ 的使用<br>
   > 点击此处的链接可以下载到 _vscode_ 的安装包<br>
   > 打开 _vscode_ 之后，需要下载拓展 _chinese_ , _c/c++_ , _VEX Robotics_ <br>
   > `如果有兴趣可以追加拓展 Better C++ Syntax 、 C/C++ Compile Run 、 Dracula Official等` <br>
   > 另外，为了防患于未然，下载一个 _git_ 和及时把代码上传到 _github_ 是相当的有必要的<br>
   >（我才不会告诉你我有一次文件损坏了只好从头重写呢）<br>
   > 下载 _git_ 只需要跟着 _vscode_ 的窗口一通按就好了，如何使用请看网上的[教程](https://www.runoob.com/git/git-tutorial.html)<br>
   > 可以点击 _打开文件夹_ 来开始你的代码
6. 硬件条件
   > 主机<br>
      ![主机图](/image/imageless_qwq_short.png)<br>
   > 手柄<br>
      ![手柄图](/image/imageless_qwq_short.png)<br>
   > 场控<br>
      ![场控图](/image/imageless_qwq_short.png)<br>
   > 钢条<br>
      ![钢条图](/image/imageless_qwq_short.png)<br>
   > 传感器<br>
      ![传感器图](/image/imageless_qwq_short.png)<br>
   > 电机<br>
      ![电机图](/image/imageless_qwq_short.png)<br>
   > 气泵<br>
      ![气泵图](/image/imageless_qwq_short.png)<br>
8. VEX社区
   > VEX在[B站](https://www.bilibili.com/)中并不算极小众的，其中更新的比较多的up主是[TXTaylor297992](https://space.bilibili.com/1684280853)<br>
   > 此外，VEX有[中文官方论坛](https://vexforum.cn/)，在这里可以下载到官方给出的规则文档和场地拼接的文档

### 01 面向对象
1. 面向对象思维的介绍及引入
   > [wiki介绍](https://zh.wikipedia.org/wiki/%E9%9D%A2%E5%90%91%E5%AF%B9%E8%B1%A1%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1)<br>
   > 程序设计思维中，与 ___面向对象___ 相对的概念叫做 ___面向过程___ 。<br>
   > 后者考虑问题是通常把问题拆分成几个小问题，在编写程序中对应的行为一般有编写若干个函数。由于OI中一般只要考虑一个主问题即可，所以面向对象在OI中出现较多<br>
   > 前者则是将一个个功能封装进 _对象_ 中，其对应的行为以实现 _类(class)_ 为典型。这种程序设计的思维在 项目化编程 中有极大的优点——重用性、灵活性和扩展性 高
   在此处，我们将从[class](https://www.runoob.com/cplusplus/cpp-classes-objects.html)的声明、定义、使用来入手，切实的感受 ___面向对象___ 的代码风格
3. classの定义<br>
   [![菜鸟教程给出的定义结构](https://www.runoob.com/wp-content/uploads/2015/05/cpp-classes-objects-2020-12-10-11.png)](https://www.runoob.com/cplusplus/cpp-classes-objects.html)
   * 类 及 类名
     > 给类取名的时候，可以参照[struct](https://www.runoob.com/cplusplus/cpp-data-structures.html)，命名规则和变量一致
     > 类的名字以及成员变量 ___最好___ 有实际意义，例：
     > ```cpp
     > class student{
     >    private:
     >       string name;//人的名字
     >       int c,m,e;//C代表语文，M代表数学，E代表英语
     > };
     > ```
   * [访问修饰符](https://www.runoob.com/cplusplus/cpp-class-access-modifiers.html)<br>
        `本教程不涉及 继承 以及 protected 的使用，因为本教程用不到它们`
        - public
            > 公有成员在程序中类的外部是可访问的
            > public下的成员变量以及成员函数的使用与`struct`无异
        - private
            > 成员和类的默认访问修饰符是 private <br>
            > 私有成员变量或函数在类的外部是`不可访问`的，甚至是`不可查看`的。只有`类和友元函数`可以访问私有成员。
            > 例:
            > ```cpp
            > class Box {
            >    private:
            >       double width;
            >    public:
            >       double length;
            >       void setWidth( double wid );
            >       double getWidth( void );
            >}b;  //相当于换行写了   Box b;
            > ```
            > 在这个例子中，变量width的访问修饰符是private，因此`b.width`的写法是非法的<br>
            > 正确的做法是，通过`b.setwidth(double wid)`来设置`width`的值；
            > 通过`b.getWidth()`来获得`width`的值<br>
            > 类似这种 __在私有区域定义数据，在公有区域定义相关的函数，以便在类的外部也可以调用这些函数__ 的做法一般叫做 ___数据封装___ <br>这样能避免受到外界的干扰和误用，从而确保了安全<br>
            > 样例中的`length`就不符合数据封装的原则，不要这样写 ~~否则你有可能会被狠狠批斗的~~
5. [重载函数和重载运算符](https://www.runoob.com/cplusplus/cpp-overloading.html)
   - 重载函数
      > C++ 允许在同一作用域中的某个函数和运算符指定多个定义，分别称为函数重载和运算符重载。<br>
      > 在同一个作用域内，可以声明几个功能类似的同名函数，但是这些同名函数的**形式参数**（个数、类型或顺序）必须不同。<br>我们不能仅通过**返回类型**的不同来重载函数。
      > 重载函数可以为我们调用功能较相近的函数时提供便利,例:
      > ```cpp
      > // 哦对了，重载函数在class外也是可以使用的哦
      > void swap(int& a,int& b)      {int t=a;a=b;b=t;}
      > void swap(float& a,float& b)  {float t=a;a=b;b=t;}
      > void swap(bool& a,bool& b)    {bool t=b;a=b;b=t;}
      > // 以下是在类中使用的
      > class printer{
      >     public:
      >        print(int a)   {cout<<a;}
      >        print(float a)   {cout<<a;}
      >        print(string a)   {cout<<a;}
      > };
      > //错误示范
      > int f(void){void}
      > float f(void){void}
      > //主函数
      > signed main(){
      >     printer p;
      >     p.print(114514);
      >     p.print("\n1919810\n");
      >
      >     int a,b;
      >     cin>>a>>b;
      >     swap(a,b);
      >     cout<<a<<' '<<b<<endl;
      >     return 0;
      > }
      > ```
   - 重载运算符
      > 在c++中，运算符实际上也可以看作是一种函数，因此，就出现了**重载运算符**的用法<br>
      > 在这里我们介绍 [赋值运算符  = ](https://www.runoob.com/cplusplus/assignment-operators-overloading.html)<br>
      > 多说无益，直接上样例：
      > ```cpp
      > class node{  //平面直角坐标系中的一个点
      >     private:
      >        int x,y; //坐标
      >     public:
      >        void operator= (const node& n){  
      >           //此处const node& n 也可以写作node n
      >           //使用&是为了提高效率，使用const是为了防止n的值被这里的赋值函数更改
      >           x = n.x;    // 等效于 this->x = n.x;
      >           y = n.y;    // 等效于 this->y = n.y;
      >        }
      >        friend istream operator>>(istream& in,node& n){
      >           // 不要求掌握，看看就好
      >           in>>n.x>>n.y;
      >           return in;
      >        }
      > };
      > 
      > signed main(){
      >     node n;
      >     node m;
      >     cin >> n;
      >     m = n;
      >     // ...
      >     // 这段代码没有什么意义，只是为了说明重载运算符后类的运算就可以用符合我们原有习惯的写法来编写程序这一点而已
      >     return 0；
      >}
      > ```
      > 可以看出，使用重载运算符的写法非常符合我们对变量的编写习惯。<br>
      > 这使得我们在使用类时感到非常的舒适 XD<br>
      > 需要注意的是，所有的运算符函数都是放在 ___public___ 访问修饰符下的<br>(其中 流运算符 是以友元函数的形式)
      > 
6. [构造函数和析构函数](https://www.runoob.com/cplusplus/cpp-constructor-destructor.html)，[拷贝构造函数](https://www.runoob.com/cplusplus/cpp-copy-constructor.html)<br>
   > 这三个函数是类中非常特殊的函数。通过它们可以实现 **初始化新对象**、**释放对象占用内存**、**复制对象** 的作用<br>
   > 如果不编写这三个函数，编译器都会自动加入这几个函数。但是如果类中涉及到**指针**和**动态内存**时需要格外注意，此时必须人为的编写 *析构函数* 和 *拷贝构造函数*<br>
   > 切记，这三个函数都应放在 ***public*** 下
   - 构造函数
      > 类的构造函数会在**每次创建类的新对象时**执行。<br>构造函数的名称与类的名称是完全相同的，并且不会返回任何类型，也不会返回 void。<br>构造函数可用于为某些成员变量设置初始值。
   - 析构函数
      > 类的析构函数会在**每次删除所创建的对象时**执行。<br>析构函数的名称与类的名称是完全相同的，只是在前面加了个波浪号（~）作为前缀<br>析构函数有助于在跳出程序（比如关闭文件、释放内存等）前**释放资源**。<br>默认析构函数不会释放成员指针变量所指向的内存空间，如果要释放的话，还需要人为定义释放。<br>因此，当类中存在*指针变量*并且有*动态内存*分配时，最好有一个析构函数用来释放内存<br>另外，析构函数**不可以接受形参**，因此不存在析构函数的重载函数
   - 拷贝构造函数
      > 类的拷贝构造函数会在创建对象时，使用同一类中之前创建的对象来初始化新创建的对象。<br>
      > 拷贝构造函数一般有如下功能：
      > - 通过使用另一个同类型的对象来 ___初始化___ 新创建的对象。
      > - 复制对象并把它作为 ___函数参数___。
      > - 复制对象并把它作为 ___函数返回值___。
      >
      > 如果在类中没有定义拷贝构造函数，编译器会自行定义一个。<br>如果类带有*指针变量*，并有*动态内存*分配，则它必须有一个拷贝构造函数。

   样例：
   > ```cpp
   > class node{
   >     private:
   >        int *n;    
   >     public:
   >        node();                 //构造函数
   >        node(int sum);          //带参数的构造函数
   >        ~node();                //析构函数
   >        node(const node& obj);  //拷贝构造函数
   >        int value(){
   >           return *n;
   >        }
   > };
   > node::node(){                  //在类外定义函数时需要在函数名前加上“类名::”
   >     n = new int;                  //为指针分配内存
   >     *n = 0;
   > }
   > node::node(int sum){
   >     n = new int;
   >     *n = sum;
   > }
   > node::~node(){
   >     delete n;                     //释放指针内存
   > }
   > node::node(const node& obj){
   >     n = new int;
   >     *n = *obj.n;                  //拷贝值
   > }
   > int VALUE(node n){return n.value();} //拷贝构造函数的用法 II
   > node bigger_one(node a,node b){return a.value()>b.value() ? a : b ;}
   >     //三元运算符  ? :  。?前条件成立则返回 : 前的，否则返回 : 后的
   > signed main(){
   >     node n;
   >     //无参数的构造函数可以省略
   >     node m(4);                    
   >     //带参数的构造函数的调用需要在变量后加括号，就像函数一样
   >     node k(m);
   >     //拷贝构造函数的用法 I
   >     n = bigger_one(m,k);
   >     //拷贝构造函数用法   III
   >     n = bigger_one(m,4);
   >     //构造函数的另类用法，其中遇到数值4时会调用node(int num)来把4转化为node类型
   > }
   > ```
8. [头文件](https://zh.wikipedia.org/wiki/%E5%A4%B4%E6%96%87%E4%BB%B6)与注释，cpp与定义
   > 还记得前文提到过 class 有着较高 重用性，灵活性，拓展性 吗？<br>
   > 如果在每一个程序的头部复制大量的class的定义，那么这种灵活性就荡然无存了<br>
   > 因此，就不得不介绍头文件了


   > 一个头文件一般包含类、子程序、变量和其他标识符的前置声明<br>
   > 习惯上，*函数、类、枚举类、常量*的声明会放在头文件中，即`xxx.h`<br>
   > 而对应的*函数、类*的源码以及*注释*则会放在对应的源文件中，即`xxx.cpp`<br>
   > 值得注意的是，为了防止头文件被反复调用造成重复声明的错误，头文件应在首行加入
   > ```cpp
   > #pragma once
   > ```
   > 或者
   > ```cpp
   > // xxx.h
   > #ifndef XXX
   > #define XXX
   > //你的代码
   > #endif
   > ```
   > 多说无用，下面摆上样例<br><br>
   > 
   > [样例：实现高精度算法](https://blog.csdn.net/weixin_30500289/article/details/96110759)<br>
   > 样例的代码非常的长，但是使用时只需要：
   > ```cpp
   > #include "intx.h"
   > signed main(){
   >   //...
   >   return 0;
   > }
   > ```
   > 另外，vscode是支持[doxygen注释](https://www.cnblogs.com/schips/p/12200388.html)的<br>[Doxygen官方文档](https://doxygen.nl/manual/)<br>
   > 在头文件中使用doxygen注释，可以对声明的类，函数进行说明<br>
   > 鼠标在引用了对应头文件的文件中只需要悬停在函数/变量/类/命名空间/...上就可以快捷的获知该处的注释<br>
   > 样例:
   > ```cpp
   > // node.h
   > /**
   > * @class node
   > * @brief 表示一个平面直角坐标系中的一个点
   > ***/
   > class node{
   >     private:
   >        /**
   >         * @brief 表示坐标 \f$\left ( x,y \right )\f$
   >        ***/
   >        int x,y;
   >     public:
   >        /**
   >         * @brief 初始化
   >         * @param a 对应x坐标
   >         * @param b 对应y坐标
   >        ***/
   >        void set(int a,int b){
   >           x = a;
   >           y = b;
   >        }
   >        /**
   >         * @brief 计算距离
   >         * @param n 第二个坐标点
   >         * @return 两点距离的平方
   >        ***/
   >        float dist(node n){
   >           return (this->x - n.x)*(this->x - n.x) + (this->y - n.y)*(this->y - n.y);
   >        }
   > };
   > ```
   > 鼠标悬停效果图<br>
   ![node的样例](/image/01-8-e1.png)<br>
   ![set()的样例](/image/01-8-e2.png)<br>
   ![dist()的样例](/image/01-8-e3.png)<br>

### 02 主机(brain)与手柄(Controller)
1. 主机、手柄、电脑之间的硬件连接<br>
   ![连线图](/image/imageless_qwq_short.png)<br>
2. 创建新的VEX工程文件、文件标题规范、文件储存位置<br>
   > 从VEX插件中 顺次点击 `new project -> v5 -> c++ -> competition template -> 命名项目名字 -> create`，一个新的VEX工程文件就创建了
4. Brain.functions()
5. Controller.functions()

### 03 电机(motor)与运动
1. 声明、命名
2. 电机 与 手动控制程序
3. 监测电机
   * position()
   * resetposition()
   * temptrue()
   * ...

### 04 陀螺仪 与 自动转弯
1. 声明、命名
2. 初始化
3. 数据检测
   * heading()
4. 自动程序中的转弯问题
5. 画外吐槽

### 05 气泵
1. 定义、命名
2. 实物介绍
3. functions
   * set()
   * value()

### 06 视觉传感器
1. 定义、命名
2. 初始化
3. 颜色设置 和 识别机制的介绍
4. 返回值

### 07 *PID精确控制算法
1. 定义
2. 原理介绍
3. 使用方法
4. 优缺点

### 08 手动程序
1. 与操作手对接
2. 底盘方案
   * 左前进右旋转
   * 万向底盘
   * 无头模式

### 09 自动程序
1. 自动赛规则
2. 前进控制
3. 转弯控制
4. 完成自动赛任务
5. 多备案 + 耐心

### 10 规则类怪谈
1. 码风要求
2. 注释规范化
3. 请参与github的更新
