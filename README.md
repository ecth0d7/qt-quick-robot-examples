# Qt Quick 机器人状态示例

两个独立的 Qt 6 / C++17 小工程，展示窗口启动、QML 可视化表单、C++ 属性绑定和按钮交互。

[阅读完整 Qt 入门教程](Qt入门教程.md) · [下载源码 ZIP](https://github.com/ecth0d7/qt-quick-robot-examples/archive/refs/heads/main.zip)

```bash
git clone https://github.com/ecth0d7/qt-quick-robot-examples.git
cd qt-quick-robot-examples
```

## 示例

| 工程 | 内容 | 打开入口 |
| --- | --- | --- |
| Hello Qt | 最小窗口、QML 加载、Qt 资源 | [CMakeLists.txt](qt_classroom/01_hello/CMakeLists.txt) |
| 机器人状态面板 | 模拟受击与恢复、属性通知、表单与行为分离 | [CMakeLists.txt](qt_classroom/02_robot_panel/CMakeLists.txt) |

血量由本地模拟产生，无需机器人、网络服务或其他业务工程。

![机器人状态面板运行效果](images/01-robot-panel.png)

教程包含下载安装、Kit 配置、打开工程、可视化编辑及运行结果截图。

## 开发环境

- Qt 6.5 或更新版本，包含 Core、Gui、Qml、Quick、QuickControls2。
- 支持 C++17 的编译器。
- CMake 3.21 或更新版本。
- Qt Creator；可视化编辑使用 Qt Quick Designer 或 Qt Design Studio。

已在 Ubuntu 22.04.5 / Qt 6.11.1 / GCC 11.4 中使用新下载源码完成构建、按钮交互、缩放与 QML 重建验证。详见 [复现检查报告及测试命令](docs/REPRODUCIBILITY.md)；Windows 等其他环境尚未实机覆盖。

## 打开与运行

在 Qt Creator 中打开任一示例的 `CMakeLists.txt`，选择与 Qt 库匹配的桌面 Kit，然后构建并运行。

Linux 终端中，从仓库根目录执行以下命令。前提是 CMake 已能找到所安装的 Qt；也可使用对应 Qt 提供的 `qt-cmake` 替代第一条命令中的 `cmake`。

```bash
cmake -S qt_classroom/01_hello -B build-hello -DCMAKE_BUILD_TYPE=Debug
cmake --build build-hello -j 4
./build-hello/hello_qt
```

机器人状态面板：

```bash
cmake -S qt_classroom/02_robot_panel -B build-panel -DCMAKE_BUILD_TYPE=Debug
cmake --build build-panel -j 4
./build-panel/robot_panel
```

## 可视化编辑

打开 [RobotPanel.qmlproject](qt_classroom/02_robot_panel/RobotPanel.qmlproject)，在设计模式编辑 [RobotPanelForm.ui.qml](qt_classroom/02_robot_panel/RobotPanelForm.ui.qml)。

如果 Design 为灰色或报模块找不到，按 [教程第 4.1 节](Qt入门教程.md#41-选对入口) 检查当前文件、插件、Kit，并在需要时重置 QML 代码模型。

`DesignerPreview.qml` 使用静态数据；完整应用由 C++ 提供血量并处理操作。两条路径使用同一份表单。修改界面后保存，再构建并重启完整应用。

## 文件职责

- `RobotState.h/.cpp`：血量状态、受击和恢复规则、变化通知。
- `RobotPanelForm.ui.qml`：外观与布局。
- `RobotPanel.qml`：属性绑定和点击行为。
- `main.cpp`：创建后端并注入 QML。
- `resources.qrc`：正式程序使用的界面资源。

源码中没有固定的 Qt 安装路径。构建产物与个人 IDE 设置不纳入仓库。
