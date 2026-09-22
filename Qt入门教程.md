# Qt 入门：从认识 Qt 到机器人状态面板

本文介绍 Qt 的用途、下载安装、项目运行和可视化编辑，再通过两个独立小工程说明 QML 与 C++ 之间的数据交互。

示例使用本地模拟的机器人血量，无需机器人或服务器。第 5、6 章包含全部源码，源码获取方式见第 3 章，下载后可直接打开工程。

> 文中的截图位置预留待补充。图片可放在本文同级的 `images/` 目录，并使用相对路径引用。安装器和 IDE 的菜单文字可能随版本、语言变化，以实际界面为准。

## 1. Qt 是什么，可以用来做什么

### 1.1 从一个日常软件理解 Qt

一个机器人状态软件通常需要窗口、按钮、血量条、地图，还要接收数据、响应点击、保存配置。Qt 提供实现这些功能的库和工具，让开发者能够在已有基础上编写应用程序。

**Qt 是一个跨平台的应用程序开发框架。** 它提供界面、网络、数据处理等能力，可用于桌面、移动和嵌入式应用。跨平台通常意味着复用大量源码，并针对各平台分别构建和适配。[Qt 官方：Qt 简介](https://doc.qt.io/qt-6/qt-intro.html)

在本例中，C++ 负责血量数据和变化规则，QML 负责描述面板的外观和交互。

### 1.2 能做哪些程序

| 应用场景 | 具体例子 | 可以在 Qt 中做的工作 |
| --- | --- | --- |
| 机器人上位机 | 查看机器人状态、显示传感器数据 | 界面展示、输入操作、数据通信 |
| 工业监控 | 温度、压力、设备报警面板 | 实时显示、参数设置、告警提示 |
| 桌面工具 | 配置编辑器、数据查看器 | 表单、文件操作、列表与图形展示 |
| 嵌入式屏幕 | 仪器或设备上的触摸操作界面 | 按钮、状态显示、交互动画 |

这些是应用设计示例。真正接入设备时，还需要实现对应的通信协议和业务逻辑。下面通过示例说明界面与数据之间的联系。

> **截图位 01｜成品效果预览：** 机器人血量面板的运行效果，标出标题、血量、进度条和按钮。

### 1.3 Qt、Qt Creator 和 QML 分别是什么

| 名称 | 是什么 | 用途 |
| --- | --- | --- |
| Qt | 应用开发框架 | 提供程序需要的库与能力 |
| Qt Creator | 集成开发环境（IDE） | 打开工程、编辑、构建、运行和调试 |
| C++ | 编程语言 | 实现血量、受击和恢复的规则 |
| QML | 描述对象、属性和界面的语言 | 写面板布局、文字和交互 |
| Qt Quick | QML 界面技术 | 构建示例的窗口内容 |
| Qt Quick Controls | 常用控件库 | 提供 `Button`、`Label`、`ProgressBar` |
| Qt Quick Designer | Creator 中的 QML 可视化编辑工具 | 选择控件、修改外观和布局 |
| Qt Design Studio | 面向界面设计的独立工具 | 编辑和预览 QML 界面，可作为设计工具选择 |
| CMake | 构建配置工具 | 告诉编译工具要编译哪些文件、链接哪些库 |
| 编译器 | 把 C++ 源码编译成程序的工具 | Linux 常见 GCC，Windows 可用 MinGW 或 MSVC |

使用 Qt Creator 构建程序时，还需要安装 Qt 开发库和匹配的编译工具链，并确认它们已被正确识别。

### 1.4 示例采用的界面技术

Qt 有不同的界面开发方式。本文使用 **Qt Quick + QML**，适合以面板、状态展示和交互为主的练习。

| 文件 | 用途 |
| --- | --- |
| `.cpp` / `.h` | C++ 实现与声明 |
| `.qml` | 窗口、组件、绑定和交互 |
| `.ui.qml` | 供可视化设计工具编辑的 QML 表单 |
| `.qmlproject` | 设计预览的工程入口 |
| `CMakeLists.txt` | 完整 C++ 应用的工程入口 |
| `.qrc` | 要随程序构建的资源清单 |

如果看到 `QWidget`、`QMainWindow` 和 XML `.ui` 文件，那是 Qt Widgets 的界面路线。本文中的项目采用上表所列的文件类型。

## 2. 下载与安装 Qt 开发环境

### 2.1 安装前先确定三件事

确认自己的操作系统、处理器架构，以及准备安装的 Qt 版本。示例代码要求 **Qt 6.5 或更新版本、C++17、CMake 3.21 或更新版本**；现有示例已在 Linux、Qt 6.11.1、GCC 环境验证。

选择满足示例要求的 Qt 6 桌面版本及匹配工具链。具体可安装版本以在线安装器显示为准，不必为了入门同时安装多个版本。

Qt 安装位置可按本机情况选择，示例没有写死 Qt 的安装路径。

### 2.2 从官网下载在线安装器

1. 打开 [Qt 官方开源下载入口](https://www.qt.io/development/download-qt-installer-oss)。下面以该入口的在线安装流程为例。
2. 选择与电脑操作系统和架构相匹配的安装器，例如 Windows x64 或 Linux x64。
3. 下载 **Qt Online Installer**。这是用于选择并下载 Qt 组件的安装程序。
4. 按官网提示注册或登录 Qt Account，并完成邮箱验证。[Qt 官方下载与账号步骤](https://www.qt.io/development/download-qt-installer-oss)

> **截图位 02｜下载页面：** 标出系统与架构选择、在线安装器下载按钮。
>
> **截图位 03｜账号与安装器欢迎页：** 展示登录入口，截图中不要包含账号密码等个人信息。

### 2.3 使用镜像启动安装器

下载 Qt 组件较慢时，可在启动在线安装器时加入 `--mirror` 参数，指定中国科学技术大学镜像。下面的命令仍然打开图形安装界面，后续照常登录和选择组件；实际下载速度取决于网络和镜像状态。[中科大镜像使用说明](https://mirrors.ustc.edu.cn/help/qtproject.html)

**Windows（PowerShell）：** 将下载的安装器重命名为 `qt-online-installer.exe`，在文件所在文件夹打开 PowerShell，执行：

```powershell
.\qt-online-installer.exe --mirror https://mirrors.ustc.edu.cn/qtproject
```

也可以保留原文件名，将命令中的 `qt-online-installer.exe` 替换为实际名称。要使用镜像参数，应通过上述命令启动；直接双击文件不会带上这次指定的参数。

**Linux：** 可以将下载的 `.run` 文件重命名为 `qt-online-installer.run`，在该文件所在目录打开终端执行：

```bash
chmod +x ./qt-online-installer.run
./qt-online-installer.run --mirror https://mirrors.ustc.edu.cn/qtproject
```

第一条命令赋予执行权限，第二条带镜像参数启动安装器。这里的 `./` 表示当前目录；文件名应与实际保存的文件一致。

`--mirror` 后填写镜像的 Qt 根地址，使用上面的 `https://mirrors.ustc.edu.cn/qtproject` 即可，不要追加 `/online/qtsdkrepository/...`。此参数用于开源组件的元数据与下载源，账号登录仍按安装器提示进行。[Qt 官方：指定镜像](https://doc.qt.io/qt-6/get-and-install-qt-cli.html#selecting-mirror-for-opensource)

若镜像暂时不可用，退出安装器，去掉 `--mirror` 及其后的地址重新启动，恢复默认下载方式。

> **截图位 03A｜带镜像启动：** 展示终端中的完整命令，以及启动后的安装器窗口。

Linux 的编译器等开发工具一般由系统提供。Ubuntu / Debian 系统可先安装基础构建工具；以下是该类系统的安装命令，不用于 Windows：

```bash
sudo apt update
sudo apt install build-essential gdb cmake ninja-build libgl1-mesa-dev
```

这是基础工具和 OpenGL 开发依赖，具体系统可能还需补充图形运行库。遇到缺库提示时，按所选 Qt 版本与发行版的要求补齐。[Qt 官方：Linux 开发环境](https://doc.qt.io/qt-6/linux.html)

### 2.4 选择安装位置和组件

登录后，按安装器提示选择安装目录。初学时保留合适的默认目录即可，并记下位置，后续查找维护工具时会用到。

选择 **Desktop / 桌面开发**。如果需要逐项选组件，进入 **Custom Installation / 自定义安装**。安装器的分组名可能变化，下表按“要装什么”进行核对。[Qt 官方：在线安装流程](https://doc.qt.io/qt-6/qt-online-installation.html)

| 项目 | 如何选择 | 为什么需要 |
| --- | --- | --- |
| Qt 6 桌面开发库 | 选择所需 Qt 6 版本对应的桌面包 | 提供 Core、Gui、Qml、Quick、Quick Controls 等能力 |
| Qt Creator | 安装 | 编辑、构建、运行完整工程 |
| 编译器或工具链 | 与 Qt 桌面包匹配 | 编译 C++ |
| CMake、Ninja 等构建工具 | 确认可用，可使用安装器提供的版本 | 配置工程并执行构建 |
| Qt 文档和示例 | 可选 | 查阅文档与示例 |
| Qt Design Studio | 可选，按可视化编辑需要安装 | 独立进行可视化设计 |

Qt Quick 等能力可能已经包含在所选桌面 Qt 包中，不一定各有一个同名复选框。关键是后续能找到示例所需模块。

**Windows：** 如果采用 MinGW，选择对应的 Qt MinGW 桌面包及匹配的 MinGW 编译工具；如果采用 MSVC，则安装对应的 Visual Studio C++ 工具链并选择 Qt MSVC 包。编译器和 Qt 包要匹配。[Qt 官方：Windows 工具链支持](https://doc.qt.io/qt-6/windows.html)

**Linux：** 通常选择对应架构的 GCC 桌面包，并使用系统安装的 GCC。不要选择交叉编译到另一种设备的套件作为当前桌面 Kit。

> **截图位 04｜安装位置：** 标出安装目录，路径按本机情况选择。
>
> **截图位 05｜组件选择：** 标出一个 Qt 6 桌面包、Qt Creator、匹配工具链和构建工具。Windows、Linux 可以分别补图。

按提示阅读安装条款、确认选择并等待安装完成。首次安装需要联网下载组件。

### 2.5 安装后先检查 Kit

打开 **Qt Creator**，进入设置或首选项中的 **Kits / 构建套件**。不同版本可能从“工具 → 选项”或“Preferences”进入。

Kit 可以理解成“这次用哪套工具来构建程序”。核对下面几项：

| 检查项 | 应当看到什么 |
| --- | --- |
| Qt 版本 | 刚安装的桌面 Qt 6 |
| C++ 编译器 | 与 Qt 包匹配的 GCC、MinGW 或 MSVC |
| CMake | 已检测到的 CMake 工具 |
| 调试器 | 适用于所选工具链的调试工具 |
| Kit 状态 | 没有阻止构建的错误提示 |

Qt Creator 的工程配置依赖 Kit；打开工程时也可以进入 Kit 设置检查。具体设置入口参见 [Qt 官方：打开和配置工程](https://doc.qt.io/qtcreator/creator-project-opening.html)。

> **截图位 06｜Kit 检查：** 标出 Qt 版本、编译器、CMake 和 Kit 状态。

如果漏装了组件，打开 Qt 安装目录中的 **Maintenance Tool / 维护工具**，添加或移除对应组件即可。[Qt 官方：维护已安装组件](https://doc.qt.io/qt-6/qt-online-installation.html)

后续补装或更新组件时，也可给维护工具传入同样的镜像参数。在 Qt 安装目录中打开终端，按实际文件名执行；下面以 `MaintenanceTool` 为例：

Windows（PowerShell）：

```powershell
.\MaintenanceTool.exe --mirror https://mirrors.ustc.edu.cn/qtproject
```

Linux：

```bash
./MaintenanceTool --mirror https://mirrors.ustc.edu.cn/qtproject
```

维护工具同样支持 `--mirror`；需要镜像时，在启动命令中明确传入该参数。[Qt 官方：安装器与维护工具的镜像参数](https://doc.qt.io/qt-6/get-and-install-qt-cli.html#selecting-mirror-for-opensource)

**检查结果：** 能启动 Creator，并找到可用于桌面 C++ 工程的 Qt 6 Kit。随后通过小工程验证环境。

## 3. 获取源码并打开项目

### 3.1 从 GitHub 获取源码

源码仓库：[ecth0d7/qt-quick-robot-examples](https://github.com/ecth0d7/qt-quick-robot-examples)。

[下载 ZIP 压缩包](https://github.com/ecth0d7/qt-quick-robot-examples/archive/refs/heads/main.zip)，或按下面的步骤操作。

仓库包含两个独立示例和本文，按下面任一种方式下载即可。

**方式一：下载 ZIP**

1. 打开上面的 GitHub 仓库地址。
2. 点击 **Code → Download ZIP**。
3. 解压压缩包，进入解压后的仓库根目录，不要直接在压缩包内打开工程。

**方式二：使用 Git**

已安装 Git 时，在准备保存源码的目录打开终端，执行：

```bash
git clone https://github.com/ecth0d7/qt-quick-robot-examples.git
cd qt-quick-robot-examples
```

目录结构如下：

```text
qt-quick-robot-examples/
├── README.md
├── Qt入门教程.md
└── qt_classroom/
    ├── 01_hello/
    │   ├── CMakeLists.txt
    │   ├── main.cpp
    │   ├── main.qml
    │   └── resources.qrc
    └── 02_robot_panel/
        ├── CMakeLists.txt
        ├── RobotState.h
        ├── RobotState.cpp
        ├── main.cpp
        ├── main.qml
        ├── RobotPanel.qml
        ├── RobotPanelForm.ui.qml
        ├── resources.qrc
        ├── DesignerPreview.qml
        └── RobotPanel.qmlproject
```

文中的工程路径均相对于仓库根目录；第 5、6 章源码标题中的 `01_hello/` 和 `02_robot_panel/` 相对于 `qt_classroom/`。后面的完整构建命令从仓库根目录执行，第 2 章安装器命令则在安装器所在目录执行。

通过 ZIP 下载时，目录名可能带有 `-main` 后缀；进入实际解压目录即可，内部相对路径不变。只复制单个 `.qml` 文件无法获得完整 C++ 工程，应下载整个仓库。

> **截图位 06A｜获取源码：** 展示 GitHub 仓库中的 Code 菜单和 Download ZIP 入口。

### 3.2 打开完整工程

1. 启动 Qt Creator。
2. 在欢迎页或“文件”菜单选择 **Open Project / 打开项目**，部分版本显示“打开文件或项目”。
3. 进入 `qt_classroom/01_hello/`，选择 **`CMakeLists.txt`**。
4. 在配置页面选择上一章准备好的桌面 Qt 6 Kit，使用 Debug 配置。
5. 确认构建目录，点击 **Configure Project / 配置项目**，等待 CMake 完成。

这里要打开工程配置文件，单独打开 `main.cpp` 只能编辑代码，不能代替完整的构建配置。[Qt 官方：打开项目](https://doc.qt.io/qtcreator/creator-project-opening.html)

> **截图位 07｜打开工程：** 标出选中的 `01_hello/CMakeLists.txt`。
>
> **截图位 08｜首次配置：** 标出 Kit、Debug、构建目录和配置按钮。

### 3.3 认识 Creator 的几个区域

| 区域 | 用来做什么 |
| --- | --- |
| 项目文件树 | 找到 C++、QML 和工程配置文件 |
| 中央编辑区 | 阅读和修改当前文件 |
| Projects / 项目设置 | 检查构建与运行配置 |
| Build / 构建操作 | 根据源码生成程序 |
| Run / 运行操作 | 启动当前选择的程序 |
| Compile Output / 编译输出 | 查看配置、编译和链接过程 |
| Application Output / 应用程序输出 | 查看程序运行日志 |
| Issues / 问题 | 集中查看错误和警告 |

> **截图位 09｜Creator 主界面：** 用编号标出文件树、编辑区、构建、运行和输出区域。

### 3.4 构建并运行

先执行“构建”，成功后执行“运行”。预期看到深色窗口和 `Hello RoboMaster!`。

第一次先不修改代码。能成功运行，说明 Qt 库、编译器和工程配置已经基本配合起来。若失败，先从问题面板和编译输出找到第一条有效错误。

> **截图位 10｜首次运行结果：** 展示 Hello 窗口，并标注当前运行目标为 `hello_qt`。

**检查结果：** 工程配置成功，运行后显示 Hello 窗口。

## 4. 如何可视化编辑界面

本章先体验设计工具。使用已经提供好的工程二，不需要立即理解它的 C++ 代码。

### 4.1 选对入口

| 目的 | 打开什么 |
| --- | --- |
| 构建并运行完整机器人面板 | `qt_classroom/02_robot_panel/CMakeLists.txt` |
| 打开界面设计工程 | `qt_classroom/02_robot_panel/RobotPanel.qmlproject` |
| 修改面板外观 | 设计工程中的 `RobotPanelForm.ui.qml` |

在 Qt Creator 的 Qt Quick Designer，或 Qt Design Studio 中打开设计工程，再选择 `RobotPanelForm.ui.qml` 进入 **Design / 设计** 模式。`.ui.qml` 用于支持可视化编辑的表单。[Qt 官方：UI 文件](https://doc.qt.io/qtcreator/creator-quick-ui-forms.html)

如果 Creator 中没有设计视图，检查插件或扩展列表中的 Qt Quick Designer 是否启用；按工具提示重启。若当前安装包没有该功能，可使用 Qt Design Studio 打开相同的 `.qmlproject`。

> **截图位 11｜设计入口：** 展示 `RobotPanel.qmlproject`、选中的 `.ui.qml` 文件，以及设计模式入口。

### 4.2 认识设计视图

| 区域 | 操作方式 |
| --- | --- |
| Navigator / 对象树 | 选择窗口中的矩形、文字和按钮 |
| 2D / 画布 | 查看布局和选中控件 |
| Properties / 属性 | 修改文字、颜色、圆角、尺寸等 |
| Components / 组件库 | 查找并添加可用控件 |

可以在对象树或画布选中组件，再修改属性面板中的值。遇到不容易点选的内部控件，优先使用对象树。[Qt 官方：创建和编辑组件实例](https://doc.qt.io/qtcreator/quick-component-instances.html)

> **截图位 12｜设计视图总览：** 标出对象树、画布、属性面板和组件库。

### 4.3 不写代码，先改一次外观

1. 在对象树选择表单根 `Rectangle`。
2. 在属性面板找到 `radius`，把圆角从 `12` 改为 `24`。
3. 保存，观察画布变化。
4. 切到代码视图，找到 `radius: 24`，确认设计操作已经写入源码。
5. 打开或切回 `02_robot_panel/CMakeLists.txt` 对应的完整工程，构建并运行 `robot_panel`。

预期结果：设计视图和正式程序都显示新的圆角。第一次先改圆角、颜色、字体或间距；面板实际宽度由外层窗口布局决定，改默认 `width` 未必能看出变化。

> **截图位 13｜修改属性：** 标出选中的根对象和 `radius` 输入框。
>
> **截图位 14｜结果对照：** 展示保存后的设计画布、对应属性代码以及正式运行效果。

### 4.4 只看正在修改的面板

这个小工程只有一个面板，打开 `RobotPanelForm.ui.qml` 就能专注编辑它。以后界面变多时，也可以单独打开目标表单，或使用专门的预览入口，不必把整个应用的所有界面都放在同一个画布上编辑。

### 4.5 分清设计预览和正式程序

| 项目 | 设计预览 | 正式运行 |
| --- | --- | --- |
| 入口 | `DesignerPreview.qml` | C++ 加载 `main.qml` |
| 界面 | `RobotPanelForm` | 行为组件使用同一份 Form |
| 血量来源 | 预览文件写入的 350 | C++ 对象初始为 500 |
| 按钮 | 展示外观，没有业务点击逻辑 | 可以受击和恢复 |
| 后端 | 不需要 C++ 对象 | 需要 C++ 对象 |

直接在设计器打开表单时可能看到默认 500；运行专用预览文件时显示 350。这些预览数字用来帮助排版，不会修改正式后端数据。

本例的完整应用把 QML 放入 `.qrc` 资源中。修改后要 **保存 → 关闭旧程序 → 构建 → 重新运行**。如果同时打开多个工程，检查当前活动工程和运行目标，确保运行的是 `robot_panel`。

**检查结果：** 保存并构建后，正式程序显示修改后的外观。

到这里，安装和工具操作已经完成。下面从最小工程开始解释代码，再逐步学习属性绑定、C++ 数据和内存管理。

## 5. 示例一：第一个窗口的完整源码

工程入口：[01_hello/CMakeLists.txt](qt_classroom/01_hello/CMakeLists.txt)。仓库中已包含这四个文件；下面列出完整内容，方便对照阅读。

```text
01_hello/
├── CMakeLists.txt
├── main.cpp
├── main.qml
└── resources.qrc
```

### `01_hello/CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.21)
project(hello_qt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2)
qt_standard_project_setup()
set(CMAKE_AUTORCC ON)

qt_add_executable(hello_qt main.cpp resources.qrc)
target_link_libraries(hello_qt PRIVATE
    Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::QuickControls2)
```

### `01_hello/main.cpp`

```cpp
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QUrl>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return 1;
    return app.exec();
}
```

### `01_hello/main.qml`

```qml
import QtQuick
import QtQuick.Controls

ApplicationWindow {
    width: 480
    height: 300
    visible: true
    title: "Hello Qt"
    color: "#101b2a"

    Label {
        anchors.centerIn: parent
        text: "Hello RoboMaster!"
        color: "white"
        font.pixelSize: 28
    }
}
```

### `01_hello/resources.qrc`

```xml
<RCC>
    <qresource prefix="/">
        <file>main.qml</file>
    </qresource>
</RCC>
```

### 5.1 用 Qt Creator 运行

1. 打开 `qt_classroom/01_hello/CMakeLists.txt`。
2. 选择桌面 Qt Kit 和 Debug 配置，等待 CMake 配置完成。
3. 执行“构建”，然后“运行”。
4. 查看“应用程序输出”和“Issues/问题”，记录第一条有效错误。

预期结果：一个深色窗口，中间显示 `Hello RoboMaster!`。

### 5.2 终端构建方式

以下命令从仓库根目录执行。Linux 下运行路径如下；Windows 可使用 Qt Creator 运行配置。

前提：终端的 CMake 查找环境已经能够找到所安装的 Qt。Qt Creator 选过 Kit，不代表外部终端也自动取得同样的环境。

```bash
cd qt_classroom/01_hello
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j 4
./build/hello_qt
```

若提示找不到 Qt6，可先在 Creator 中按 5.1 操作。也可以把对应 Qt 的 `bin` 目录加入终端的 PATH，再在工程目录使用它提供的配置工具：

```bash
qt-cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j 4
./build/hello_qt
```

Qt 的安装位置按本机环境配置。若切换 Qt 版本或编译器，使用新的构建目录，例如把上述命令中的 `build` 全部改成 `build-new`。

### 5.3 逐步解释启动过程

| 语句或文件 | 作用 |
| --- | --- |
| `QGuiApplication app(...)` | 建立 GUI 应用环境 |
| `QQmlApplicationEngine engine` | 创建 QML 引擎 |
| `engine.load(...)` | 加载界面，并创建 QML 对象 |
| `rootObjects().isEmpty()` | 检查是否成功创建根对象 |
| `app.exec()` | 进入事件循环，处理输入、计时器等事件 |
| `resources.qrc` | 把 `main.qml` 纳入资源构建 |

`qrc:/main.qml` 是 Qt 资源 URL，不是电脑根目录的文件路径。这里界面随程序构建；保存 QML 后，要重新构建并重新运行。

CMake 中，`find_package` 查找 Qt，`qt_add_executable` 声明要生成的程序，`target_link_libraries` 指定依赖。`qt_standard_project_setup()` 开启包括 AUTOMOC 在内的常用设置；`CMAKE_AUTORCC` 让构建处理 `.qrc` 清单。

### 5.4 修改窗口标题与文字

修改窗口标题和问候文字，然后构建并运行。确认修改的源码文件、构建目录和实际运行的程序路径。

**预期结果：** 新启动的窗口显示修改后的标题和文字。

## 6. 示例二：机器人状态面板的完整源码

这个工程独立于工程一，可以直接打开运行。它加入 C++ 状态对象和可视化表单，没有网络、插件动态库或大型工程依赖。

工程入口：[02_robot_panel/CMakeLists.txt](qt_classroom/02_robot_panel/CMakeLists.txt)。仓库中已包含这十个文件，下面给出完整内容，不需要从其他项目补代码。

```text
02_robot_panel/
├── CMakeLists.txt
├── RobotState.h              声明血量属性、操作和通知
├── RobotState.cpp            血量规则的实现
├── main.cpp                  创建后端并交给 QML
├── main.qml                  正式窗口
├── RobotPanelForm.ui.qml     外观与布局
├── RobotPanel.qml            数据绑定与点击处理
├── resources.qrc             正式界面的资源清单
├── DesignerPreview.qml       静态设计预览
└── RobotPanel.qmlproject     设计工具入口
```

### `02_robot_panel/CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.21)
project(robot_panel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2)
qt_standard_project_setup()
set(CMAKE_AUTORCC ON)

qt_add_executable(robot_panel
    main.cpp
    RobotState.h
    RobotState.cpp
    resources.qrc
)
target_link_libraries(robot_panel PRIVATE
    Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::QuickControls2)
```

### `02_robot_panel/RobotState.h`

```cpp
#pragma once

#include <QObject>

class RobotState final : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int health READ health NOTIFY healthChanged)
    Q_PROPERTY(int maxHealth READ maxHealth CONSTANT)

public:
    explicit RobotState(QObject *parent = nullptr);

    int health() const;
    int maxHealth() const;
    Q_INVOKABLE void damage(int amount);
    Q_INVOKABLE void reset();

signals:
    void healthChanged();

private:
    void setHealth(int value);
    int m_health = 500;
};
```

### `02_robot_panel/RobotState.cpp`

```cpp
#include "RobotState.h"
#include <algorithm>

RobotState::RobotState(QObject *parent) : QObject(parent) {}

int RobotState::health() const
{
    return m_health;
}

int RobotState::maxHealth() const
{
    return 500;
}

void RobotState::damage(int amount)
{
    if (amount <= 0)
        return;
    setHealth(m_health - std::min(amount, m_health));
}

void RobotState::reset()
{
    setHealth(maxHealth());
}

void RobotState::setHealth(int value)
{
    const int next = std::clamp(value, 0, maxHealth());
    if (m_health == next)
        return;
    m_health = next;
    emit healthChanged();
}
```

### `02_robot_panel/main.cpp`

```cpp
#include "RobotState.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QUrl>
#include <QVariant>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    RobotState robot; // 先创建后端，保证它比 QML 引擎更晚销毁。
    QQmlApplicationEngine engine;
    engine.setInitialProperties({{"backend", QVariant::fromValue(&robot)}});
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return 1;
    return app.exec();
}
```

### `02_robot_panel/main.qml`

```qml
import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: window
    required property var backend
    width: 560
    height: 340
    minimumWidth: 400
    minimumHeight: 300
    visible: true
    title: "机器人状态面板"
    color: "#101b2a"

    RobotPanel {
        anchors.fill: parent
        anchors.margins: 24
        backend: window.backend
    }
}
```

### `02_robot_panel/RobotPanelForm.ui.qml`

```qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    width: 512
    height: 292
    radius: 12
    color: "#1c3046"

    property int health: 500
    property int maxHealth: 500
    property alias damageButton: damageButton
    property alias resetButton: resetButton

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 16

        Label {
            text: "RED 1 · 步兵"
            color: "white"
            font.pixelSize: 24
        }
        Label {
            text: "血量：" + root.health + " / " + root.maxHealth
            color: root.health < 150 ? "#ff8c7a" : "#d9e7f5"
            font.pixelSize: 20
        }
        ProgressBar {
            Layout.fillWidth: true
            from: 0
            to: root.maxHealth
            value: root.health
        }
        RowLayout {
            Button {
                id: damageButton
                text: "模拟受击 -50"
                enabled: root.health > 0
            }
            Button {
                id: resetButton
                text: "恢复"
            }
        }
        Item {
            Layout.fillHeight: true
        }
    }
}
```

### `02_robot_panel/RobotPanel.qml`

```qml
import QtQuick

RobotPanelForm {
    id: panel
    required property var backend
    health: panel.backend.health
    maxHealth: panel.backend.maxHealth

    Connections {
        target: panel.damageButton
        function onClicked() {
            panel.backend.damage(50);
        }
    }
    Connections {
        target: panel.resetButton
        function onClicked() {
            panel.backend.reset();
        }
    }
}
```

### `02_robot_panel/resources.qrc`

```xml
<RCC>
    <qresource prefix="/">
        <file>main.qml</file>
        <file>RobotPanel.qml</file>
        <file>RobotPanelForm.ui.qml</file>
    </qresource>
</RCC>
```

### `02_robot_panel/DesignerPreview.qml`

```qml
import QtQuick
import QtQuick.Controls

ApplicationWindow {
    width: 560
    height: 340
    visible: true
    title: "设计预览：静态示例数据"
    color: "#101b2a"

    RobotPanelForm {
        anchors.fill: parent
        anchors.margins: 24
        health: 350
        maxHealth: 500
    }
}
```

### `02_robot_panel/RobotPanel.qmlproject`

```qml
import QmlProject 1.1

Project {
    mainFile: "DesignerPreview.qml"
    mainUiFile: "RobotPanelForm.ui.qml"
    QmlFiles { directory: "." }
    qt6Project: true
}
```

### 6.1 构建与运行

在 Qt Creator 中打开 `qt_classroom/02_robot_panel/CMakeLists.txt`，选择桌面 Kit，构建并运行 `robot_panel`。

也可在已经配置 Qt 查找环境的终端中，从仓库根目录执行：

```bash
cd qt_classroom/02_robot_panel
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j 4
./build/robot_panel
```

与工程一相同，需要时可用 `qt-cmake` 替代第一条配置命令中的 `cmake`。

**预期结果：** 初始血量为 500；每次受击减少 50；低于 150 时文字变色；最低为 0，受击按钮随后禁用；点击恢复后回到 500。

## 7. 一次点击如何更新界面

一次受击操作的数据流如下，对应源码见上一章。

```mermaid
flowchart LR
    A[点击受击按钮] --> B[RobotPanel.qml 的 Connections]
    B --> C[调用 RobotState.damage]
    C --> D[更新 m_health]
    D --> E[发出 healthChanged]
    E --> F[重新读取绑定的 health]
    F --> G[文字和进度条更新]
```

### 7.1 QML 属性与绑定

表单中的 `property int health: 500` 定义可变化的属性；`value: root.health` 让进度条依赖这个属性。属性变化时，绑定表达式会重新计算。[Qt 官方：属性绑定](https://doc.qt.io/qt-6/qtqml-syntax-propertybinding.html)

`id: root` 在当前组件作用域内标识对象；它不是全局变量。`root.health < 150 ? ... : ...` 是根据血量选择颜色的条件表达式。

本例由 C++ 对象管理血量数据。因此点击时调用 `backend.damage(50)`，由 C++ 修改血量。不要改成 `panel.health = 100`：这会覆盖 `health: panel.backend.health` 的绑定，界面可能不再跟随后端。

点击受击按钮后，文字和进度条随血量变化自动更新，无需分别编写刷新代码。

### 7.2 `Q_PROPERTY` 与更新通知

`Q_PROPERTY(int health READ health NOTIFY healthChanged)` 把 C++ 的血量公开为 Qt 属性。`READ` 指定读取函数，`NOTIFY` 指定变化通知。`maxHealth` 使用 `CONSTANT`，表示该属性在对象生命周期内不变化。

`Q_INVOKABLE` 允许 QML 调用 `damage()` 和 `reset()`。`Q_OBJECT` 配合构建时生成的元对象代码支持这些机制。[Qt 官方：暴露 C++ 属性与方法](https://doc.qt.io/qt-6/qtqml-cppintegration-exposecppattributes.html)

`setHealth()` 先限制范围，再判断值是否真的改变，最后修改成员并发出 `healthChanged()`。这样既维护状态规则，也避免无意义的重复通知。

**验证更新通知：** 临时注释 `emit healthChanged()`，构建运行，观察点击后界面不刷新。用 C++ 断点查看 `m_health`，确认“数据没变化”和“界面没收到通知”是两个问题。验证完成后恢复该行。

### 7.3 C++ 对象怎样到达 QML

`main.cpp` 中的 `engine.setInitialProperties(...)` 在加载根对象前提供 `backend`。`main.qml` 使用 `required property var backend` 接收它，再传给 `RobotPanel`。

`required` 要求创建组件时提供该属性。正式窗口必须由带后端的 C++ 程序加载，单独运行它可能因缺少 `backend` 失败；设计预览有自己的入口。

### 7.4 表单与行为为什么分开

| 文件 | 放什么 | 本例内容 |
| --- | --- | --- |
| `RobotPanelForm.ui.qml` | 外观、布局、显示属性 | 文字、颜色、进度条、按钮 |
| `RobotPanel.qml` | 绑定和交互 | 连接点击信号，调用后端 |
| `RobotState.cpp` | 数据规则 | 血量范围、受击、恢复 |

表单通过 `property alias damageButton: damageButton` 暴露内部按钮，包装器再用 `Connections` 处理它的点击信号。别名让外部能够访问按钮，但不需要知道其内部布局。

`.ui.qml` 有设计工具的语法限制，应保留声明式表单；函数、点击处理和计时器等逻辑放到普通 QML 或 C++ 中。[Qt 官方：UI 文件约束](https://doc.qt.io/qtcreator/creator-quick-ui-forms.html)

### 7.5 布局怎样适应窗口

`ColumnLayout` 负责纵向排列，`RowLayout` 负责横向排列。外层布局用 `anchors.fill` 占据面板内部空间；布局管理的子控件用 `Layout.fillWidth`、`Layout.fillHeight` 等属性安排尺寸。

同一个由 Layout 管理的子控件，不要又用 anchors 强行控制其几何尺寸。需要建议尺寸时使用 `Layout.preferredWidth`、`Layout.preferredHeight`。[Qt 官方：布局说明](https://doc.qt.io/qt-6/qtquicklayouts-overview.html)

## 8. 内存与线程管理

### 8.1 对象寿命与所有权

工程二的 `robot` 和 `engine` 都是局部对象。`robot` 先构造，`engine` 后构造；退出时顺序相反，所以 QML 引擎结束后，后端才释放。传入 `&robot` 是让 QML 使用现有对象，不要求在这里动态分配一份新对象。

QObject 还支持父子所有权：父对象销毁时会销毁其子对象。对需要动态创建的 QObject，可以明确交给父对象管理。[Qt 官方：对象树与所有权](https://doc.qt.io/qt-6/objecttrees.html)

| 情况 | 建议 |
| --- | --- |
| 能直接放在作用域或类成员中的数据 | 优先值语义，随作用域或所属对象释放 |
| 独占的非 QObject 动态资源 | 使用 RAII 或 `std::unique_ptr` |
| 由 QObject 父对象管理的堆对象 | 不再让另一个独立拥有者重复负责释放 |
| 只借用的对象指针 | 确保对象寿命覆盖使用期 |

本例通过局部对象管理生命周期，无需额外使用 `new`。设计对象关系时，应明确创建者、拥有者和使用者。

### 8.2 不阻塞事件循环

本例受击操作很短，直接在主线程完成即可。以后接入网络、图像或 AI 时，不要在按钮回调中执行长期等待或耗时推理。

GUI 操作留在主线程；耗时任务采用异步方式或工作线程，完成后再交付结果。QObject 的线程归属和事件循环需要配合。[Qt 官方：线程与 QObject](https://doc.qt.io/qt-6/threads-qobject.html)

`QTimer` 不会自动创建工作线程；把耗时推理放进主线程的定时回调仍然会卡住界面。后台任务退出时要先停止任务并等待线程结束，再释放被使用的对象。

## 9. 从小工程理解模块化

本例划分出三种职责：状态规则、界面行为、界面外观。它们可以分别阅读和修改，但**本例没有实现动态插件系统**。

接入设备时，可以按照下面的关系组织数据流：

```text
设备或模拟数据 → 数据解析 → 状态对象或列表模型 → QML 界面
```

如果机器人数量增加，可用 `ListView` / `GridView` 与模型配合，让一份 delegate 模板显示多条记录。C++ 列表通常采用 `QAbstractListModel`：已有记录变化要发 `dataChanged`；插入、删除记录分别配对使用 begin/end 通知。[Qt 官方：QAbstractListModel](https://doc.qt.io/qt-6/qabstractlistmodel.html)

后续实现插件时，需要明确数据接口、启动和停止方法、所有权、线程以及缓存上限。把文件分成几个文件夹只是代码组织的起点，不能自动获得插件隔离和生命周期管理。

## 10. 常见问题与调试方法

| 现象 | 优先检查 |
| --- | --- |
| CMake 找不到 Qt6 | Creator 的 Kit 是否正确；外部终端是否配置了对应 Qt |
| 找不到 QtQuick 或 Controls | 是否安装对应模块，是否混用了另一套 Qt 环境 |
| 改界面没有效果 | 是否保存、重新构建并运行正确的可执行文件 |
| 新增 QML 组件后找不到类型 | 文件名是否正确；本例的 `.qrc` 是否加入了新文件 |
| 设计视图报错 | 是否把函数或点击处理写进 `.ui.qml` |
| required 属性未提供 | 是否误把正式 `main.qml` 当成无后端预览入口 |
| 血量变量变了，界面不更新 | 是否发出 `healthChanged`；是否覆盖了原绑定 |
| 布局异常 | 是否让 Layout 与 anchors 同时控制同一个子控件 |
| Q_OBJECT 相关链接错误 | 类文件是否加入目标、AUTOMOC 是否开启，同时检查函数是否有定义 |
| 窗口卡住 | 是否在主线程阻塞等待或执行长循环 |

**断点调试：** 在 `RobotState::damage()` 设置断点，以 Debug 启动，点击受击，查看 `amount` 和 `m_health`，再单步进入 `setHealth()`。观察先修改成员、再发出通知的执行顺序。

临时日志可以使用 C++ 的 `qDebug()`（需包含 `<QDebug>`），或普通 QML 事件处理中的 `console.log(...)`。先记录状态变化，避免高频刷屏。

## 11. 扩展练习与常见问答

### 扩展练习

1. 把每次受击改为 25，并同步按钮文字。说明两个修改分别在哪个文件。
2. 把低血量阈值改成最大血量的 30%，用比例表达式实现。
3. 把最大血量改成 800，确保初始值、恢复值和预览示例也合理；注意当前代码中初始值与 `maxHealth()` 分别在哪里定义。
4. 新增“治疗 +50”功能：在 C++ 中增加可调用方法，经过 `setHealth()` 限制上限；表单增加按钮和别名，行为文件连接信号。

完成后检查血量上下限、按钮行为、文字、进度条和窗口缩放，不只确认“能编译”。

### 常见问答

| 问题 | 说明 |
| --- | --- |
| 为什么 `.qmlproject` 能预览，但按钮不改血量？ | 本例预览只加载 Form，未创建 C++ 后端与行为包装器 |
| 为什么不用手动更新文字和进度条？ | 它们通过属性绑定依赖同一份血量 |
| 普通 C++ 成员为什么不能直接被 QML 读取？ | 本例通过 Qt 元对象和 `Q_PROPERTY` 公开接口 |
| 注释通知信号后发生了什么？ | 成员仍可变化，但绑定不知道需要重新读取 |
| 保存 Form 后，正式程序为何还要构建？ | 本例通过 `.qrc` 将界面纳入构建资源 |
| 为什么先创建 robot，再创建 engine？ | 确保 QML 使用后端期间后端仍然存活 |

完整示例源码分别保存在 [01_hello](qt_classroom/01_hello/) 和 [02_robot_panel](qt_classroom/02_robot_panel/) 目录中。
