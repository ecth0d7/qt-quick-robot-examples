# Qt 示例复现检查报告

检查日期：2026-09-22。检查基线：公开仓库提交 `6e5be42`。本次新增说明和测试没有修改两个示例的业务源码。

结论：两个示例在下述 Linux 环境中可从新下载的源码构建并运行，血量交互、通知、窗口缩放及 QML 资源更新验证通过。全新 Creator 配置暴露了额外的设计器模块识别问题；补充排查步骤后恢复了可视化编辑。这个结果不等于所有系统、Qt 版本、网络和显卡组合都已通过验证。

## 环境与方法

| 项目 | 实际环境 |
| --- | --- |
| 系统 | Ubuntu 22.04.5，x86_64 |
| Qt 开发库 | 官方桌面 Qt 6.11.1，gcc_64 |
| 编译器 / CMake | GCC 11.4.0 / CMake 3.22.1 |
| IDE | Qt Creator 19.0.2，中文界面 |
| 图形会话 | 独立 Xvfb X11 桌面，用于界面操作与截图 |
| 安装器 | Qt Online Installer 4.11.0 |
| 源码来源 | GitHub 新克隆；另行下载并解压 main 分支 ZIP |
| 清理范围 | 新源码副本、新构建目录、独立 Creator 用户配置 |

没有复用示例原有的构建产物或项目个人设置。Creator 的独立用户配置仍可发现机器上已经安装的 SDK，因此这不是空白操作系统上的首次安装测试。本次没有卸载并重新下载整套 Qt；在线安装全过程仍受账号、网络及仓库状态影响。

## 实测结果

| 检查 | 结果与证据 |
| --- | --- |
| Git 克隆、ZIP 解压 | 两种方式均获得完整源码；从不同副本分别构建示例 |
| Hello 全新配置与构建 | 成功生成并启动 hello_qt，启动日志无错误 |
| 机器人面板全新配置与构建 | 成功生成并启动 robot_panel，启动日志无错误 |
| 独立设计预览 | 用所选 Qt 的 qml 工具加载 DesignerPreview.qml 成功 |
| QML 静态检查 | 对面板 Form、行为组件和正式 main.qml 执行 qmllint，退出码 0 |
| 血量规则 | 初始值、正数受击、零与负数输入、int 极值、下限、恢复均通过 |
| 更新通知 | 值变化时通知；未变化时不重复通知，通过 |
| 实际按钮点击 | 使用 Qt Test 鼠标事件点击正式 QML 按钮；血量、文字、颜色、进度条同步，通过 |
| 零血量与恢复 | 零血量禁用受击，恢复后重新启用，通过 |
| 窗口缩放 | 400×300 与 900×600 下按钮仍在窗口内且可操作，通过 |
| 运行时 QML 警告 | 自动化交互期间未收到 QQmlEngine 警告 |
| 软件渲染 | 同一套交互测试以 QT_QUICK_BACKEND=software 运行，通过 |
| 只修改 QML 后重建 | radius 12→24；构建输出触发 AUTORCC、重新编译资源并链接；新窗口圆角像素变化符合预期 |
| 插件启用 | 全新配置中从“帮助 → 关于插件”启用 Qt Quick Designer 及其依赖，实际执行重启 |
| 设计器模块识别 | 首次出现 Controls/Layouts 找不到；重启后仍一度显示不完整，重置代码模型、等待扫描并重新进入设计后恢复 |
| 可视化写回源码 | 在恢复后的属性面板将 Radius 改为 24，保存后源码实际为 radius: 24 |
| 安装器镜像参数 | 本机安装器 --help 确认支持 --mirror；镜像服务范围另外对照中科大说明 |

测试程序位于 [tests](../tests/)，独立于两个示例工程，不增加示例自身的编译依赖。图形测试检查按钮、属性和窗口边界，不能代替所有主题、字体缩放和屏幕 DPI 的人工排版检查。

## 设计器问题的处理记录

实际复现的导入错误发生在编辑器/设计器中，完整 C++ 程序与静态预览可以正常运行。未据此认定 QtQuick.Controls 没有安装。

处理过程中确认了 `.qmlproject` 的桌面 Kit 和导入路径，重新启动 Creator，执行“工具 → QML/JS → 重置代码模型”，等待扫描完成，再切换编辑/设计模式。之后背景、控件和对象树恢复正常，并完成了属性修改验证。因为中间包含重启和重新扫描等步骤，这里不把某一个动作断言为唯一原因。

![重置代码模型入口](../images/11d-reset-qml-model.png)

![恢复后的可视化表单](../images/11e-designer-recovered.png)

Qt 官方提供了针对模块识别错误的 [代码模型重置说明](https://doc.qt.io/qtcreator/creator-reference-js-and-qml-error-codes.html#resetting-the-code-model)。如果模块文件实际缺失，应修复安装；如果实际错误是图形上下文创建失败，应检查渲染环境，不能混用这几类问题的解决方法。

设计器为组件库生成缩略图时，也可能尝试加载需要 backend 的 RobotPanel.qml，从而记录后端缺失信息。应先核对报错文件：本例编辑对象是 RobotPanelForm.ui.qml，静态预览入口是 DesignerPreview.qml，正式 main.qml 需要 C++ 注入 backend。不能通过删除正式窗口的 required 属性来掩盖入口用错的问题。

## 如何重复运行自动化检查

使用与示例相同的桌面 Qt，并确保其中包含 Qt Test。下面是 Linux 命令；在仓库根目录打开终端，先让 PATH 能找到该 Qt 的 `qt-cmake`。如果有多套 Qt，先用 `command -v qt-cmake` 核对来源。

```bash
qt-cmake -S tests -B build-tests -DCMAKE_BUILD_TYPE=Debug
cmake --build build-tests -j 4
ctest --test-dir build-tests --output-on-failure
```

测试会打开窗口，必须在可用的图形会话中执行。无显示服务的 Linux CI 可自行准备 Xvfb，再通过 `xvfb-run -a ctest --test-dir build-tests --output-on-failure` 运行。软件渲染复查：

```bash
QT_QUICK_BACKEND=software ctest --test-dir build-tests --output-on-failure
```

本次两种模式均为 `1/1` 个 CTest 测试通过；该测试内部包含血量规则和真实窗口交互两组检查。使用 EXAMPLE_ROOT 配置项可以指定另一份下载的示例目录，本次测试实际指向独立解压的 ZIP 源码。

手动验证 QML 重建时，修改表单圆角、保存、关闭旧程序、重新构建并运行，确认画面变化。完成后可将圆角改回仓库默认值 12。

## 相关帖子与官方说明交叉核对

帖子用于收集实际出现过的故障现象；旧帖涉及的 Qt 5、旧 Creator 或其他系统命令没有直接复制到教程中。

| 问题线索 | 对照依据及本文处理 |
| --- | --- |
| [Qt Creator 6.0.1 的 Design 视图不可用](https://forum.qt.io/topic/133310/qt-creator-6-0-1-design-view-not-working) | 对照 [官方插件启用流程](https://doc.qt.io/qtcreator/creator-how-to-enable-plugins.html)，并在本机 19.0.2 实际验证搜索、启用依赖、重启和打开表单 |
| [远程 Linux 构建后无法显示窗口](https://forum.qt.io/topic/163436/compile-and-build-project-on-remote-machine) | 帖中显示连接和 xcb 提示同时出现；教程分别说明显示服务与缺失动态库，依据 [官方 XCB 依赖表](https://doc.qt.io/qt-6/linux-requirements.html) 定位 |
| 本次实测 QML module not found | 对照 [官方模块识别与重置说明](https://doc.qt.io/qtcreator/creator-reference-js-and-qml-error-codes.html#resetting-the-code-model)，新增第 4.1.3 节操作截图 |
| 安装镜像范围与旧版本 | 依据 [中科大 Qt 镜像说明](https://mirrors.ustc.edu.cn/help/qtproject.html)，明确镜像根地址、维护版本范围和默认源回退 |
| 只装 IDE、工具链不匹配 | 依据 [官方 Kit 配置](https://doc.qt.io/qtcreator/creator-targets.html) 和 [编译器说明](https://doc.qt.io/qtcreator/creator-tool-chains.html)，增加手动注册和匹配检查 |
| Windows 双击 exe 缺 DLL | 依据 [官方部署说明](https://doc.qt.io/qt-6/windows-deployment.html)，区分开发环境运行和程序部署 |

## 尚未覆盖的范围

- Windows / MSVC / MinGW、macOS、ARM、Qt 6.5 及其他 Qt 版本：本次没有对应实机验证。文中的最低版本要求来自工程配置，不能等同于完整兼容性测试矩阵。
- Qt Design Studio：作为官方支持的编辑入口说明，未在本次环境独立安装和走完操作流程。
- 从卸载开始重新下载、登录、安装全部 Qt 组件：未执行；此前安装截图中也有明确注明来源的官方参考图，不能据此声称完整安装验证。
- 镜像速度与可用性、不同显卡驱动、桌面协议、字体与高 DPI：不能由当前 Xvfb 环境推断全部通过。

本次未发现需要修改示例业务源码的问题；新增的是可重复测试、工具配置排查与验证边界说明。
