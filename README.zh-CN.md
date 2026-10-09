<p align="right">
  <a href="README.md"><img src="https://img.shields.io/badge/README-English-blue?style=for-the-badge" alt="Switch to English"></a>
</p>

![Windows Terminal 项目徽标](https://github.com/microsoft/terminal/assets/91625426/333ddc76-8ab2-4eb4-a8c0-4d7b953b1179)

[![Terminal 构建状态](https://dev.azure.com/shine-oss/terminal/_apis/build/status%2FTerminal%20CI?branchName=main)](https://dev.azure.com/shine-oss/terminal/_build/latest?definitionId=1&branchName=main)

# 欢迎来到 Windows Terminal、控制台与命令行仓库

> [!IMPORTANT]
> **本仓库是 Windows Terminal 的个人魔改分支。** 它跟随上游 `main` 分支，并在其之上加入了一批额外的功能与修复。
> 它会**与官方的 Windows Terminal 并存**安装，不会覆盖或替换官方版本，两者可以同时使用。
> 想快速了解改了什么，请看下面的[本版本有什么不同](#本版本有什么不同)；想直接装来用，请看[下载与安装](#下载与安装)，
> 到 Releases 页面下载现成的安装包即可。Click the **English** button at the top right to read this page in English.

<details>
  <summary><strong>目录</strong></summary>

- [本版本有什么不同](#本版本有什么不同)
- [下载与安装](#下载与安装)
- [Terminal 与控制台概览](#terminal-与控制台概览)
  - [Windows Terminal](#windows-terminal)
  - [Windows 控制台宿主](#windows-控制台宿主)
  - [共享组件](#共享组件)
  - [新版 Windows Terminal 是怎么做出来的](#新版-windows-terminal-是怎么做出来的)
- [相关资源](#相关资源)
- [常见问题](#常见问题)
  - [我编译并运行了新 Terminal，但它看起来还是老控制台的样子](#我编译并运行了新-terminal但它看起来还是老控制台的样子)
- [文档](#文档)
- [参与贡献](#参与贡献)
- [与团队沟通](#与团队沟通)
- [开发者指南](#开发者指南)
- [环境要求](#环境要求)
- [编译代码](#编译代码)
  - [在 PowerShell 中编译](#在-powershell-中编译)
  - [在 Cmd 中编译](#在-cmd-中编译)
- [运行与调试](#运行与调试)
  - [编码规范](#编码规范)
- [行为准则](#行为准则)

</details>

<br />

本仓库包含以下项目的源代码：

* [Windows Terminal](https://aka.ms/terminal)
* [Windows Terminal 预览版](https://aka.ms/terminal-preview)
* Windows 控制台宿主（`conhost.exe`）
* 两个项目之间共享的组件
* [ColorTool](./src/tools/ColorTool)
* [示例项目](./samples)，演示如何使用 Windows 控制台 API

相关仓库：

* [Windows Terminal 文档](https://learn.microsoft.com/windows/terminal)
  （[仓库：参与文档贡献](https://github.com/MicrosoftDocs/terminal)）
* [控制台 API 文档](https://github.com/MicrosoftDocs/Console-Docs)
* [Cascadia Code 字体](https://github.com/Microsoft/Cascadia-Code)

---

## 本版本有什么不同

本分支跟随上游 `main` 分支，并在其之上加入了一些额外的功能与修复。下面介绍的内容**都已经包含**在
[Releases 页面](../../releases) 发布的安装包里 —— 你不需要自己编译任何东西。

### 选项卡栏位置

选项卡栏不再固定在顶部。你可以把它移到窗口**底部**，或者移到**左侧**、**右侧** —— 放在侧面时
它会变成竖向列表，选项卡开得多的时候特别顺手。

**怎么用：** 打开 **设置** > **外观** > **选项卡栏位置**，选择 `顶部`、`底部`、`左侧（垂直）`
或 `右侧（垂直）`。在 `settings.json` 里这个选项叫 `tabPosition`。

另外还有一个 `toggleVerticalTabs` 动作，如果你更喜欢用快捷键，可以给它绑一个键，按一下就能在
横向和竖向之间切换（默认没有绑定任何按键）。

<!-- SCREENSHOT: 选项卡栏位置 -->
> _[截图位置：选项卡栏位置]_

### 窗口背景材质

窗口边框、选项卡栏和设置界面都可以使用 Mica、Mica Alt 或亚克力材质，让 Terminal 跟系统其他部分
融为一体，而不是贴在一块死板的纯色背景上。

**怎么用：** 打开 **设置** > **外观** > **应用程序背景材质**，挑一个样式即可。可选值有
`默认`、`纯色`、`Mica`、`Mica Alt`、`亚克力`、`亚克力（深色）`。
在 `settings.json` 里这个选项叫 `applicationBackgroundMaterial`。

> 这个设置只作用于窗口、选项卡栏和设置界面，不会改变终端内容区。如果你希望终端内容也跟着
> 窗口材质走，把配置文件的「终端背景材质」设为「使用窗口材质」即可
> （对应 `backgroundMaterial` 的 `useWindowMaterial`）。

<!-- SCREENSHOT: 窗口背景材质 -->
> _[截图位置：窗口背景材质]_

### 透明窗口不再残留字影

以前开着透明度或亚克力的时候，滚动和切换会在屏幕上留下淡淡的「幽灵字符」和残影，现在这个问题
已经修掉了。同一轮修复还处理了：非标准缩放比例下文字位置错乱、滚动时残留字符，以及滚动边距在
分页之间、主缓冲区与备用缓冲区之间互相串味的问题。

<!-- SCREENSHOT: 修复前后对比 -->
> _[截图位置：修复前后对比]_

### 中文与符号对齐更准

私有使用区（PUA）的字符现在一律按窄字符处理，不再受「模糊宽度」策略影响。这样中文和制表符、
符号混排时，列就能对齐了。

### 支持从右往左的文字

阿拉伯语、希伯来语等从右往左书写的文字现在能正确整形显示，方向混排的行也会在正确的词和语种
边界处断开。

### 选项卡拖动开关

**设置** > **交互** > **通过拖动重新排列或拖出选项卡** 控制选项卡能否用鼠标拖动来重排，
或者拖出来变成一个新窗口。当 Terminal 以管理员身份或另一个用户身份运行时，这个开关会自动关闭，
并给出原因说明 —— 那种情况下拖动选项卡会让窗口崩溃。此时仍然可以用「移动选项卡」相关的动作。

<!-- SCREENSHOT: 选项卡拖动设置 -->
> _[截图位置：选项卡拖动设置]_

### 设置界面翻页更顺滑

在设置界面里翻页不再卡顿。内置的页面切换动画被换成了简单的淡入效果，即使新页面还在加载，
动画也依然流畅。

### 每个新会话都有真彩色

新开的会话会自动带上 `COLORTERM=truecolor` 环境变量，因此会读取它的工具 —— `ls`、`bat`
以及大量其他命令行程序 —— 都能输出完整的 24 位真彩色。

### 中文界面补齐

设置界面里缺失的简体中文翻译已经补上，失效的条目被清理掉，还修复了一处可能导致设置页崩溃的
遗留文案键。

---

## 下载与安装

这个版本**只有一条安装路径**：到 [Releases 页面](../../releases) 下载压缩包，从压缩包里安装。
它没有上架微软应用商店，也不在 winget、Chocolatey、Scoop 里 —— 那些装的是微软的官方版本，
不是这个。

1. 打开[最新版本](../../releases/latest)，在 **Assets** 里下载
   `WindowsTerminal-Dev-<版本>-x64.zip`。
2. 解压到任意位置。
3. 在 PowerShell 中进入解压出来的目录，运行 `.\Add-AppDevPackage.ps1`。
   它会依次完成：信任证书 → 安装框架依赖 → 安装主程序。

如果 PowerShell 不允许运行脚本，先为当前会话放开限制：

```powershell
Set-ExecutionPolicy -Scope Process Bypass
```

### 手动安装

如果你更想一步步自己来，顺序很重要 —— 框架依赖必须先装好：

1. 信任证书：右键点击 `.cer` 文件，选择 **安装证书**，选择 **本地计算机**，然后选
   **将所有的证书都放入下列存储** > **浏览** > **受信任人**。
2. 安装依赖：`Add-AppxPackage .\Dependencies\x64\Microsoft.UI.Xaml.2.8.appx`
   （系统已有 Microsoft.UI.Xaml 2.8 可跳过）。
3. 安装主程序：`Add-AppxPackage .\CascadiaPackage_<版本>_x64.msixbundle`

> [!IMPORTANT]
> **这个版本会与官方的 Windows Terminal 并存安装，不会覆盖或替换它。** 两者可以同时安装、
> 同时使用，设置也各自独立、互不影响。在开始菜单里它叫 **Terminal Dev**，图标右下角带一个
> 绿色的 **DEV** 角标，一眼就能区分。想卸载时，到 **设置** > **应用** > **已安装的应用** 里
> 删除即可，官方版本不受影响。

> [!NOTE]
> 这个包使用的是自行签名的测试证书，而不是微软商店的证书，所以证书那一步是必须的。
> 只有在你能够接受信任一张由打包机器自行生成的证书时，才建议安装。

---

## Terminal 与控制台概览

在深入代码之前，请先花几分钟看一下下面的概览：

### Windows Terminal

Windows Terminal 是一款全新的、现代化的、功能丰富且高效的终端应用，面向命令行用户。它包含了
Windows 命令行社区最常被要求的大量功能，例如选项卡、富文本、国际化、可配置性、主题与样式等等。

Terminal 还需要满足我们的各项目标和指标，以确保它始终保持快速高效，不会占用大量内存或电量。

### Windows 控制台宿主

Windows 控制台宿主 `conhost.exe` 是 Windows 最早的命令行体验。它还承载着 Windows 的命令行
基础设施，以及 Windows 控制台 API 服务器、输入引擎、渲染引擎、用户偏好设置等。本仓库中的
控制台宿主代码，正是 Windows 自带的 `conhost.exe` 的实际构建来源。

自 2014 年接手 Windows 命令行以来，团队为控制台添加了多项新功能，包括背景透明、按行选择、
对 [ANSI / 虚拟终端序列](https://en.wikipedia.org/wiki/ANSI_escape_code) 的支持、
[24 位色彩](https://devblogs.microsoft.com/commandline/24-bit-color-in-the-windows-console/)、
[伪控制台（"ConPTY"）](https://devblogs.microsoft.com/commandline/windows-command-line-introducing-the-windows-pseudo-console-conpty/)
等等。

不过，由于 Windows 控制台的首要目标是保持向后兼容，我们一直无法加入社区（以及团队）多年来
想要的许多功能，包括选项卡、Unicode 文本和表情符号。

正是这些限制促使我们创造了新的 Windows Terminal。

> 如果你想进一步了解命令行（尤其是 Windows 命令行）的演进历程，可以阅读命令行团队博客上的
> [这一系列配套文章](https://devblogs.microsoft.com/commandline/windows-command-line-backgrounder/)。

### 共享组件

在改造 Windows 控制台的过程中，我们对它的代码库做了大幅现代化：把逻辑实体清晰地拆分为模块和
类，引入了一些关键的扩展点，用更安全、更高效的
[STL 容器](https://docs.microsoft.com/en-us/cpp/standard-library/stl-containers?view=vs-2022)
替换了若干陈旧的自家集合与容器，并通过微软的
[Windows 实现库（WIL）](https://github.com/Microsoft/wil) 让代码更简单、更安全。

这次改造让控制台的若干关键组件可以被 Windows 上的任何终端实现复用，包括全新的基于 DirectWrite
的文本排版与渲染引擎、能够同时存储 UTF-16 和 UTF-8 的文本缓冲区、VT 解析器/发射器等等。

### 新版 Windows Terminal 是怎么做出来的

在开始规划新的 Windows Terminal 应用时，我们探索并评估了多种方案和技术栈。最终我们认为，
继续投入 C++ 代码库最能达成我们的目标 —— 这样可以让我们在上述已现代化的组件基础上，
同时服务于现有的控制台和新的 Terminal。此外我们还意识到，这使我们能够把 Terminal 的核心
本身构建成一个可复用的 UI 控件，供其他人集成进自己的应用。

这项工作的成果就在本仓库中，并以 Windows Terminal 应用的形式发布 —— 对本分支而言，就是
[本仓库 Releases 页面](../../releases) 上的安装包。

---

## 相关资源

想进一步了解 Windows Terminal，下面这些资源可能会有用：

* [命令行博客](https://devblogs.microsoft.com/commandline)
* [命令行背景知识系列博客](https://devblogs.microsoft.com/commandline/windows-command-line-backgrounder/)
* Windows Terminal 发布：[Terminal 宣传视频](https://www.youtube.com/watch?v=8gw0rXPMMPE&list=PLEHMQNlPj-Jzh9DkNpqipDGCZZuOwrQwR&index=2&t=0s)
* Windows Terminal 发布：[Build 2019 会议](https://www.youtube.com/watch?v=KMudkRcwjCw)
* Run As Radio：[第 645 期 - Richard Turner 谈 Windows Terminal](https://www.runasradio.com/Shows/Show/645)
* Azure DevOps Podcast：[第 54 期 - Kayla Cinnamon 与 Rich Turner 谈 Windows Terminal 上的 DevOps](http://azuredevopspodcast.clear-measure.com/kayla-cinnamon-and-rich-turner-on-devops-on-the-windows-terminal-team-episode-54)
* Microsoft Ignite 2019 会议：[现代 Windows 命令行：Windows Terminal - BRK3321](https://myignite.techcommunity.microsoft.com/sessions/81329?source=sessions)

---

## 常见问题

### 我编译并运行了新 Terminal，但它看起来还是老控制台的样子

原因：你在 Visual Studio 里启动的解决方案不对。

解决办法：确认你在 Visual Studio 里编译并部署的是 `CascadiaPackage` 项目。

> [!NOTE]
> `OpenConsole.exe` 只是一个本地编译出来的 `conhost.exe`，也就是承载 Windows 命令行基础设施的
> 经典 Windows 控制台。Windows Terminal 通过
> [ConPty](https://devblogs.microsoft.com/commandline/windows-command-line-introducing-the-windows-pseudo-console-conpty/)
> 使用 OpenConsole 来连接命令行应用并与它们通信。

---

## 文档

所有项目文档都位于 [aka.ms/terminal-docs](https://aka.ms/terminal-docs)。
如果你想参与文档贡献，请在
[Windows Terminal 文档仓库](https://github.com/MicrosoftDocs/terminal) 提交拉取请求。

---

## 参与贡献

我们非常期待与你 —— 我们出色的社区 —— 一起协作，共同构建并改进 Windows Terminal！

***在开始开发某个功能或修复之前***，请先阅读并遵循我们的
[贡献者指南](./CONTRIBUTING.md)，以避免做无用功或重复劳动。

## 与团队沟通

与团队沟通最方便的方式是通过 GitHub issues。

欢迎提交新的 issue、功能请求和建议，但**请务必先搜索是否已有相似的、打开或已关闭的 issue。**

如果你有觉得还不值得开 issue 的问题想咨询，可以通过 Twitter 联系我们：

* Christopher Nguyen，产品经理：[@nguyen_dows](https://twitter.com/nguyen_dows)
* Dustin Howett，工程负责人：[@dhowett](https://twitter.com/DHowett)
* Mike Griese，高级开发者：[@zadjii@mastodon.social](https://mastodon.social/@zadjii)
* Carlos Zamora，开发者：[@cazamor_msft](https://twitter.com/cazamor_msft)
* Pankaj Bhojwani，开发者
* Leonard Hecker，开发者：[@LeonardHecker](https://twitter.com/LeonardHecker)

## 开发者指南

## 环境要求

你可以通过以下两种方式之一来配置编译 Terminal 的环境：

### 使用 WinGet 配置文件

克隆仓库之后，你可以使用
[WinGet 配置文件](https://learn.microsoft.com/en-us/windows/package-manager/configuration/#use-a-winget-configuration-file-to-configure-your-machine)
来配置环境。[默认配置文件](.config/configuration.winget) 会安装 Visual Studio 2026 Community
以及其余所需的工具。[.config](.config) 目录下还提供了另外两个变体，分别对应 Visual Studio 2026
的企业版和专业版。运行默认配置文件时，你可以在资源管理器中双击该文件，或者执行下面的命令：

```powershell
winget configure .config\configuration.winget
```

### 手动配置

* 运行 Windows Terminal 需要 Windows 10 2004（内部版本 >= 10.0.19041.0）或更高版本
* 要在本地安装并运行 Windows Terminal，必须在 Windows 设置应用中
  [开启开发人员模式](https://learn.microsoft.com/windows/uwp/get-started/enable-your-device-for-development)
* 必须安装 [PowerShell 7 或更高版本](https://github.com/PowerShell/PowerShell/releases/latest)
* 必须安装 [Windows 11 (10.0.26100) SDK](https://developer.microsoft.com/windows/downloads/windows-sdk/)，版本不低于 10.0.26100.8249
* 必须安装 [VS 2026](https://visualstudio.microsoft.com/downloads/) 18.6 或更高版本
* 必须通过 VS 安装程序安装以下工作负载。注意：打开解决方案时会
  [提示自动安装缺失的组件](https://devblogs.microsoft.com/setup/configure-visual-studio-across-your-organization-with-vsconfig/)：
  * 使用 C++ 的桌面开发
  * WinUI 应用开发
* 必须安装 [.NET Framework 4.7.2 目标包](https://learn.microsoft.com/dotnet/framework/install/guide-for-developers#to-install-the-net-framework-developer-pack-or-targeting-pack) 才能编译测试项目

## 编译代码

`OpenConsole.slnx` 可以在 Visual Studio 中编译，也可以通过 **/tools** 目录下的一组便捷脚本
和工具在命令行中编译：

### 在 PowerShell 中编译

```powershell
Import-Module .\tools\OpenConsole.psm1
Set-MsBuildDevEnvironment
Invoke-OpenConsoleBuild
```

### 在 Cmd 中编译

```shell
.\tools\razzle.cmd
bcz
```

## 运行与调试

要在 VS 中调试 Windows Terminal，请在解决方案资源管理器中右键点击 `CascadiaPackage` 并进入
属性。在「调试」菜单中，把「应用程序进程」和「后台任务进程」都改成「仅限本机」。

之后就可以按 <kbd>F5</kbd> 编译并调试 Terminal 项目了。请确保选择 "x64" 或 "x86" 平台 ——
Terminal 无法以 "Any CPU" 编译（因为 Terminal 是 C++ 应用，不是 C# 应用）。

> 你不能通过直接运行 WindowsTerminal.exe 来启动 Terminal。具体原因请见
> [#926](https://github.com/microsoft/terminal/issues/926)、
> [#4043](https://github.com/microsoft/terminal/issues/4043)

### 编码规范

请阅读下面这些关于编码实践的简短文档。

> 如果你发现这些文档缺少某些内容，欢迎为仓库中任意位置的文档文件做贡献（或者新写一些！）

随着我们不断了解「怎样才能让人成为项目的有效贡献者」，这些文档也在持续完善中。

* [代码风格](./doc/STYLE.md)
* [代码组织](./doc/ORGANIZATION.md)
* [遗留代码库中的异常](./doc/EXCEPTIONS.md)
* [在 WIL 中与 Windows 打交道的实用智能指针与宏](./doc/WIL.md)

---

## 行为准则

本项目采用了[微软开源行为准则][conduct-code]。
更多信息请参见[行为准则常见问题][conduct-FAQ]，或通过 [opencode@microsoft.com][conduct-email]
联系我们。

[conduct-code]: https://opensource.microsoft.com/codeofconduct/
[conduct-FAQ]: https://opensource.microsoft.com/codeofconduct/faq/
[conduct-email]: mailto:opencode@microsoft.com
