# 课程安排

### 00 序言
1. 前言
2. 语言基础说明<br>
   VEX程序可以支持C++和python，但是在这里只涉及C++<br>
   如果有python基础而没有C++基础，建议访问[菜鸟教程](https://www.runoob.com/cplusplus/cpp-tutorial.html)来学习语法知识<br>
   如果编程基础近似为0而对编程有兴趣的同学，建议先在[洛谷题单](https://www.luogu.com.cn/training/list)完成入门系列之后再来看VEX的教程
4. 编译环境
   支持VEX程序的软件有 [vscode](https://code.visualstudio.com/sha/download?build=stable&os=win32-x64-user) 、VEXcode pro v5等，本教程只介绍vscode的使用<br>
   点击此处的链接可以下载到vscode的安装包<br>
   打开vscode之后，需要下载拓展 chinese , c/c++ , VEX Robotics<br>
   > 如果有兴趣可以追加拓展 Better C++ Syntax 、 C/C++ Compile Run 、 Dracula Official等 <br>
   另外，为了防患于未然，下载一个git和及时把代码上传到github是相当的有必要的（我才不会告诉你我有一次文件损坏了只好从头重写呢）<br>
   下载git只需要跟着vscode的窗口一通按就好了，如何使用请看网上的[教程](https://www.runoob.com/git/git-tutorial.html)<br>
   可以点击`打开文件夹`来开始你的代码
6. 硬件条件
7. VEX社区

### 01 面向对象
1. 面向对象思维的介绍及引入
2. 访问修饰符
3. 重载函数
4. 构造函数，析构函数及拷贝构造函数
5. 数据封装
6. 头文件与注释，cpp与定义

### 02 主机(brain)与手柄(Controller)
1. 主机、手柄、电脑之间的硬件连接
2. 创建新的VEX工程文件、文件标题规范、文件储存位置
   从VEX插件中 顺次点击 `new project -> v5 -> c++ -> competition template -> 命名项目名字 -> create`，一个新的VEX工程文件就创建了
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
