## 信号槽

所谓信号槽，实际就是观察者模式。当某个事件发生之后，比如，按钮检测到自己被点击了一下，它就会发出一个信号（signal）。这种发出是没有目的的，类似广播。如果有对象对这个信号感兴趣，它就会使用连接（connect）函数，意思是，用自己的一个函数（成为槽（slot））来处理这个信号。也就是说，当信号发出时，被连接的槽函数会自动被回调。这就类似观察者模式：当发生了感兴趣的事件，某一个操作就会被自动触发。

```c++
// !!! Qt 5
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPushButton button("Quit");
    QObject::connect(&button, &QPushButton::clicked, &QApplication::quit);
    button.show();

    return app.exec();
}
```

在 Qt 5 中，`QObject::connect()`有五个重载：

```c++
QMetaObject::Connection connect(const QObject *, const char *,
                                const QObject *, const char *,
                                Qt::ConnectionType);

QMetaObject::Connection connect(const QObject *, const QMetaMethod &,
                                const QObject *, const QMetaMethod &,
                                Qt::ConnectionType);

QMetaObject::Connection connect(const QObject *, const char *,
                                const char *,
                                Qt::ConnectionType) const;

QMetaObject::Connection connect(const QObject *, PointerToMemberFunction,
                                const QObject *, PointerToMemberFunction,
                                Qt::ConnectionType)

QMetaObject::Connection connect(const QObject *, PointerToMemberFunction,
                                Functor);
```



connect()最常用的一般形式：

`connect(sender,signal,receiver,slot);`

这是我们最常用的形式。`connect()`一般会使用前面四个参数，第一个是发出信号的对象，第二个是发送对象发出的信号，第三个是接收信号的对象，第四个是接收对象在接收到信号之后所需要调用的函数。也就是说，当 sender 发出了 signal 信号之后，会自动调用 receiver 的 slot 函数。

这是最常用的形式，我们可以套用这个形式去分析上面给出的五个重载。第一个，sender 类型是`const QObject *`，signal 的类型是`const char *`，receiver 类型是`const QObject *`，slot 类型是`const char *`。这个函数将 signal 和 slot 作为字符串处理。第二个，sender 和 receiver 同样是`const QObject *`，但是 signal 和 slot 都是`const QMetaMethod &`。我们可以将每个函数看做是`QMetaMethod`的子类。因此，这种写法可以使用`QMetaMethod`进行类型比对。第三个，sender 同样是`const QObject *`，signal 和 slot 同样是`const char *`，但是却缺少了 receiver。这个函数其实是将 this 指针作为 receiver。第四个，sender 和 receiver 也都存在，都是`const QObject *`，但是 signal 和 slot 类型则是`PointerToMemberFunction`。看这个名字就应该知道，这是指向成员函数的指针。第五个，前面两个参数没有什么不同，最后一个参数是`Functor`类型。这个类型可以接受 static 函数、全局函数以及 Lambda 表达式。

由此我们可以看出，`connect()`函数，sender 和 receiver 没有什么区别，都是`QObject`指针；主要是 signal 和 slot 形式的区别。具体到我们的示例，我们的`connect()`函数显然是使用的第五个重载，最后一个参数是`QApplication`的 static 函数`quit()`。也就是说，当我们的 button 发出了`clicked()`信号时，会调用`QApplication`的`quit()`函数，使程序退出。



Qt 基础模块分为以下几个：

- **Qt Core**，提供核心的非 GUI 功能，所有模块都需要这个模块。这个模块的类包括了动画框架、定时器、各个容器类、时间日期类、事件、IO、JSON、插件机制、智能指针、图形（矩形、路径等）、线程、XML 等。所有这些类都可以通过 <QtCore> 头文件引入。
- **Qt Gui**，提供 GUI 程序的基本功能，包括与窗口系统的集成、事件处理、OpenGL 和 OpenGL ES 集成、2D 图像、字体、拖放等。这些类一般由 Qt 用户界面类内部使用，当然也可以用于访问底层的 OpenGL ES 图像 API。Qt Gui 模块提供的是所有图形用户界面程序都需要的通用功能。
- **Qt Multimedia**，提供视频、音频、收音机以及摄像头等功能。这些类可以通过 <QtMultimedia> 引入，而且需要在 pro 文件中添加 QT += multimedia。
- **Qt Network**，提供跨平台的网络功能。这些类可以通过 <QtNetwork> 引入，而且需要在 pro 文件中添加 QT += network。
- **Qt Qml**，提供供 QML（一种脚本语言，也提供 JavaScript 的交互机制） 使用的 C++ API。这些类可以通过 <QtQml> 引入，而且需要在 pro 文件中添加 QT += qml。
- **Qt Quick**，允许在 Qt/C++ 程序中嵌入 Qt Quick（一种基于 Qt 的高度动画的用户界面，适合于移动平台开发）。这些类可以通过 <QtQuick> 引入，而且需要在 pro 文件中添加 QT += quick。
- **Qt SQL**，允许使用 SQL 访问数据库。这些类可以通过 <QtSql> 引入，而且需要在 pro 文件中添加 QT += sql。
- **Qt Test**，提供 Qt 程序的单元测试功能。这些类可以通过 <QtTest> 引入，而且需要在 pro 文件中添加 QT += testlib。
- **Qt Webkit**，基于 WebKit2 的实现以及一套全新的 QML API（顺便说一下，Qt 4.8 附带的是 QtWebkit 2.2）。



Qt 扩展模块则有更多的选择：

- **Qt 3D**，提供声明式语法，在 Qt 程序中可以简单地嵌入 3D 图像。Qt 3D 为 Qt Quick 添加了 3D 内容渲染。Qt 3D 提供了 QML 和 C++ 两套 API，用于开发 3D 程序。
- **Qt Bluetooth**，提供用于访问蓝牙无线设备的 C++ 和 QML API。
- **Qt Contacts**，用于访问地址簿或者联系人数据库的 C++ 和 QML API。
- **Qt Concurrent**，封装了底层线程技术的类库，方便开发多线程程序。
- **Qt D-Bus**，这是一个仅供 Unix 平台使用的类库，用于利用 D-Bus 协议进行进程间交互。
- **Qt Graphical Effects**，提供一系列用于实现图像特效的类，比如模糊、锐化等。
- **Qt Image Formats**，支持图片格式的一系列插件，包括 TIFF、MNG、TGA 和 WBMP。
- **Qt JS Backend**，该模块没有公开的 API，是 V8 JavaScript 引擎的一个移植。这个模块仅供 QtQml 模块内部使用。
- **Qt Location**，提供定位机制、地图和导航技术、位置搜索等功能的 QML 和 C++ API。
- **Qt OpenGL**，方便在 Qt 应用程序中使用 OpenGL。该模块仅仅为了程序从 Qt 4 移植到 Qt 5 的方便才保留下来，如果你需要在新的 Qt 5 程序中使用 OpenGL 相关技术，需要使用的是 QtGui 模块中的 QOpenGL。
- **Qt Organizer**，使用 QML 和 C++ API 访问组织事件（organizer event）。organizer API 是 Personal Information Management API 的一部分，用于访问 Calendar 信息。通过 Organizer API 可以实现：从日历数据库访问日历时间、导入 iCalendar 事件或者将自己的事件导出到 iCalendar。
- **Qt Print Support**，提供对打印功能的支持。
- **Qt Publish and Subscribe**，为应用程序提供对项目值的读取、导航、订阅等的功能。
- **Qt Quick 1**，从 Qt 4 移植过来的 QtDeclarative 模块，用于提供与 Qt 4 的兼容。如果你需要开发新的程序，需要使用 QtQuick 模块。
- **Qt Script**，提供脚本化机制。这也是为提供与 Qt 4 的兼容性，如果要使用脚本化支持，请使用 QtQml 模块的 QJS* 类。
- **Qt Script Tools**，为使用了 Qt Script 模块的应用程序提供的额外的组件。
- **Qt Sensors**，提供访问各类传感器的 QML 和 C++ 接口。
- **Qt Service Framework**，提供客户端发现其他设备的服务。Qt Service Framework 为在不同平台上发现、实现和访问服务定义了一套统一的机制。
- **Qt SVG**，提供渲染和创建 SVG 文件的功能。
- **Qt System Info**，提供一套 API，用于发现系统相关的信息，比如电池使用量、锁屏、硬件特性等。
- **Qt Tools**，提供了 Qt 开发的方便工具，包括 Qt CLucene、Qt Designer、Qt Help 以及 Qt UI Tools 。
- **Qt Versit**，提供了对 Versit API 的支持。Versit API 是 Personal Information Management API 的一部分，用于 QContacts 和 vCard 以及 QOrganizerItems 和 iCalendar 之间的相互转换。
- **Qt Wayland**，仅用于 Linux 平台，用于替代 QWS，包括 Qt Compositor API（server）和 Wayland 平台插件（clients）。
- **Qt WebKit**，从 Qt 4 移植来的基于 WebKit1 和 QWidget 的 API。
- **Qt Widgets**，使用 C++ 扩展的 Qt Gui 模块，提供了一些界面组件，比如按钮、单选框等。
- **Qt XML**，SAX 和 DOM 的 C++ 实现。该模块已经废除，请使用 QXmlStreamReader/Writer。
- **Qt XML Patterns**，提供对 XPath、XQuery、XSLT 和 XML Schema 验证的支持。

