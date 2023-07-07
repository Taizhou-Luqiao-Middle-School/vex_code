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
   > 手柄<br>
   > 场控<br>
   > 钢条<br>
   > 传感器<br>
   > 电机<br>
   > 气泵<br>
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
3. classの定义
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
   * 访问修饰符
   * (不涉及private)(red)
5. 重载函数
6. 构造函数，析构函数及拷贝构造函数
7. 数据封装
8. 头文件与注释，cpp与定义

### 02 主机(brain)与手柄(Controller)
1. 主机、手柄、电脑之间的硬件连接
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
