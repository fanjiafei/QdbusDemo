# Qdbus总结

## 参考资料
- [Qt D-Bus官方文档](http://doc.qt.io/qt-5/qtdbus-index.html)
- [freedesktop D-Bus Tutorial](https://dbus.freedesktop.org/doc/dbus-tutorial.html)
- [QT中DBus的用法-CSDN](http://blog.csdn.net/imxiangzi/article/details/49699529/)
- [commonAPI教程](https://docs.projects.genivi.org/)
## 概述
> D-Bus is a system for interprocess communication (IPC). Architecturally, it has several layers:
> 
> - A library, libdbus, that allows two applications to connect to each other and exchange messages.
> 
> - A message bus daemon executable, built on libdbus, that multiple applications can connect to. The daemon can route messages from one application to zero or more other applications.
> 
> - Wrapper libraries or bindings based on particular application frameworks. For example, libdbus-glib and libdbus-qt. There are also bindings to languages such as Python. These wrapper libraries are the API most people should use, as they simplify the details of D-Bus programming. libdbus is intended to be a low-level backend for the higher level bindings. Much of the libdbus API is only useful for binding implementation.

D-Bus是一个消息总线系统，其功能已涵盖进程间通信的所有需求，并具备一些特殊的用途。D-Bus是三层架构的进程间通信系统，其中包括：

- 接口层：接口层由函数库libdbus提供，进程可通过该库使用D-Bus的能力。

- 总线层：总线层实际上是由D-Bus总线守护进程提供的。它在Linux系统启动时运行，负责进程间的消息路由和传递，其中包括Linux内核和Linux桌面环境的消息传递。

- 包装层：包装层一系列基于特定应用程序框架的Wrapper库。例如libdbus-glib 或libdbus-qt（即我们常说的gdbus和qdbus）。因为包装层简化了D-Bus编程，所以大多数时候我们使用包装层。

## 概念
### Service Names
> When communicating over a bus, applications obtain what is called a "service name": it is how that application chooses to be known by other applications on the same bus. The service names are brokered by the D-Bus bus daemon and are used to route messages from one application to another.

进程通过“Service name”进行总线通讯，由D-Bus总线守护进程通过使用“Service name”进行进程间的消息路由和传递。可以把这个类比成ip地址或者域名。
Service name的格式也非常像服务名，例如
**==org.freedesktop.DBus==**

### Object Paths
> Like network hosts, applications provide specific services to other applications by exporting objects. Those objects are hierarchically organised, much like the parent-child relationship that classes derived from QObject possess. One difference, however, is that there is the concept of "root object", that all objects have as ultimate parent.

对象路径

![image](http://doc.qt.io/qt-5/images/qurl-ftppath.png)

### Interfaces
> Interfaces are similar to C++ abstract classes and Java's interface keyword and declare the "contract" that is established between caller and callee. That is, they establish the names of the methods, signals and properties that are available as well as the behavior that is expected from either side when communication is established.

接口类似于C ++抽象类和Java的接口关键字，并声明在调用者和被调用者之间建立的“契约”。也就是说，他们建立了可用的方法，信号和属性的名称，以及建立通信时双方所期望的行为。
### Methods and Signals
> Each object has members; the two kinds of member are methods and signals. Methods are operations that can be invoked on an object, with optional input (aka arguments or "in parameters") and output (aka return values or "out parameters"). Signals are broadcasts from the object to any interested observers of the object; signals may contain a data payload.

方法是可以在对象上调用的操作，具有可选输入（又名参数或“输入参数”）和输出（又名返回值或“输出参数”）。

信号从对象广播到对象的任何感兴趣的观察者;信号也可以包含参数。

### exampple
新建一个D-Bus服务

```
//registe service
if(!connection.registerService("www.user.service.name")){
    qDebug()<<connection.lastError().message();
    exit(1);
}

//registe object
connection.registerObject("/user/service/path",&m_company,
                                  QDBusConnection::ExportAllContents);
```


服务名：www.user.service.name

路径：/user/service/path

```
Q_CLASSINFO("D-Bus Interface", "available.interface")
```

接口名为：available.interface
```
signals:
    void nameChangedSingal();
    void ageChangedSingal();
    void professionChangedSingal();
    void salaryChangedSingal();
    void recruitInfo(const QString& name ,const QString& result);

public slots:
    QString candidateName(QString name);
    int candidateAge(int age);
    QString candidateProfession(QString profession);
    double candidateExpectSalary(double salary);
```
method :
- QString candidateName(QString name);
- int candidateAge(int age);
- QString candidateProfession(QString profession);
- double candidateExpectSalary(double salary);

signal:
- void nameChangedSingal();
- void ageChangedSingal();
- void professionChangedSingal();
- void salaryChangedSingal();
- void recruitInfo(const QString& name ,const QString& result);

使用d-feet查看session总线消息

![image](http://www.fanjiafei.cn/wp-content/uploads/2018/02/D-Bus总线消息分析.png)

## QtDBus的使用
### 简介
> The Qt binding for libdbus, QtDBus, has been distributed with Qt since version 4.2. It is not documented here. See the [Qt documentation](http://qt-project.org/doc/qt-5/qtdbus-index.html) for details of how to use QtDBus.

在QT中的Dbus是使用的Dbus的包装层libdbus-qt。
要查看Dbus总线上的服务和对象可以借助==d-feet== 和==qdbusviewer==。
要发送信号可以使用dbus-send,要查看Dbus上的消息流可以使用dbus-monitor

QtDBus的使用方法有很多，我感觉功能最强大也相对比较好用的是==DBusProxy==方式。DBusProxy可以使访问更加方便，就像访问本地类成员变量的方式访问远程的method。下面就具体讲述如何使用DBusProxy进行。

在使用这个类的时候要使用两个工具

**qdbuscpp2xm**l和**qdbusxml2cpp**

使用qdbuscpp2xm根据头文件生成xml文件
```
qdbuscpp2xml –M –S hotel.h –o hotel.xml
```

利用qdbusxml2cpp根据xml文件生成客户端可调用的接口文件
```
qdbusxml2cpp hotel.xml –p hotelInterface
```
### 实例介绍
为了方便描述，设计一个Demo：**应聘者——公司（candidate——company）**

**candidate**通过D-Bus将应聘者的个人信息发送给company。包括姓名、年龄、薪水、职业。

**company**能够接收到candidate发送过来的应聘者信息，然后可以通过广播的方式广播出去，告诉应聘者录取结果。

#### Step1:服务端使用DBusProxy
1. 创建连接
```
QDBusConnection connection = QDBusConnection::sessionBus();
```

2. 注册服务
```
if(!connection.registerService("company.recruitment")){
    qDebug()<<connection.lastError().message();
    exit(1);
}

```

3. 注册对象
```
connection.registerObject("/company/path",&m_company,QDBusConnection::ExportAllContents);
```

在company类的头文件中申明 D-Bus Interface，编写相关method和signal
```
class company : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "company.interface")
public:
    explicit company();
    int getUsrAge();
    double getUsrSalary();
    QString getUsrName();
    QString gerUsrProfession();
    ~company();

signals:
    void nameChangedSingal();
    void ageChangedSingal();
    void professionChangedSingal();
    void salaryChangedSingal();
    void recruitInfo(const QString& name ,const QString& result);

public slots:
    QString candidateName(QString name);
    int candidateAge(int age);
    QString candidateProfession(QString profession);
    double candidateExpectSalary(double salary);

private:
    QString usr_name;
    int usr_age;
    QString usr_profession;
    double usr_salary;
};
```
#### Step2:生成Q-DBus文件
根据company.h生成dbus的xml文件
```
qdbuscpp2xml -M -S company.h -o company.xml
```
company.xml内容如下
```
<!DOCTYPE node PUBLIC "-//freedesktop//DTD D-BUS Object Introspection 1.0//EN" "http://www.freedesktop.org/standards/dbus/1.0/introspect.dtd">
<node>
  <interface name="company.interface">
    <signal name="nameChangedSingal">
    </signal>
    <signal name="ageChangedSingal">
    </signal>
    <signal name="professionChangedSingal">
    </signal>
    <signal name="salaryChangedSingal">
    </signal>
    <signal name="recruitInfo">
      <arg name="name" type="s" direction="out"/>
      <arg name="result" type="s" direction="out"/>
    </signal>
    <method name="candidateName">
      <arg type="s" direction="out"/>
      <arg name="name" type="s" direction="in"/>
    </method>
    <method name="candidateAge">
      <arg type="i" direction="out"/>
      <arg name="age" type="i" direction="in"/>
    </method>
    <method name="candidateProfession">
      <arg type="s" direction="out"/>
      <arg name="profession" type="s" direction="in"/>
    </method>
    <method name="candidateExpectSalary">
      <arg type="d" direction="out"/>
      <arg name="salary" type="d" direction="in"/>
    </method>
  </interface>
</node>
```
接着，根据company.xml生成客户端调用的Interface接口
```
qdbusxml2cpp company.xml -p companyInterface
```
会生成companyInterface.cpp和companyInterface.h接口文件

#### Step3:客户端使用DBusProxy
##### 调用method
1. 创建接口对象
```
company::interface m_company("company.recruitment","/company/path",
                                 QDBusConnection::sessionBus());
```
2. 调用对象的method方法
```
QDBusPendingReply<QString> reply = m_company.candidateName(name);
```
3. 等待完成（默认是异步调用）
```
reply.waitForFinished();
```
4. 如果method有返回值的话可以在reply中看到
```
if(reply.isValid()){
    qDebug()<<"candidate's name is "<<reply.value();
}
```
##### 监听signal
1. 创建接口对象
```
company::interface *p_company;//此处一定要是指针
p_company = new company::interface("company.recruitment","/company/path",QDBusConnection::sessionBus());
```
2. 绑定Interface的信号到本地的槽
```
connect(p_company,SIGNAL(recruitInfo(QString, QString)),this,SLOT(recruitInfoSlot(QString ,QString)));              
```              
#### Step4:Demo演示
- client端通过dbus的method方法调用Server端的函数
- client端通过监听dbus上的signal接收Server端发送来的广播消息。



