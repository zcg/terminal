<p align="right">
  <a href="README.zh-CN.md"><img src="https://img.shields.io/badge/README-%E4%B8%AD%E6%96%87-red?style=for-the-badge" alt="切换到中文"></a>
</p>

![Windows Terminal project logos and branding image](https://github.com/microsoft/terminal/assets/91625426/333ddc76-8ab2-4eb4-a8c0-4d7b953b1179)

[![Terminal Build Status](https://dev.azure.com/shine-oss/terminal/_apis/build/status%2FTerminal%20CI?branchName=main)](https://dev.azure.com/shine-oss/terminal/_build/latest?definitionId=1&branchName=main)

# Welcome to the Windows Terminal, Console and Command-Line repo

> [!IMPORTANT]
> **This is a personal fork of Windows Terminal.** It follows the upstream
> `main` branch and adds a set of extra features and fixes on top of it. It
> installs **alongside** the official Windows Terminal rather than replacing it,
> so you can keep both. See
> [What's different in this build](#whats-different-in-this-build) for a
> plain-language tour, or jump straight to
> [Download and install](#download-and-install) to grab a ready-made installer
> from the Releases page. 中文说明请点右上角的 **中文** 按钮。

<details>
  <summary><strong>Table of Contents</strong></summary>

- [What's different in this build](#whats-different-in-this-build)
- [Download and install](#download-and-install)
- [Terminal \& Console Overview](#terminal--console-overview)
  - [Windows Terminal](#windows-terminal)
  - [The Windows Console Host](#the-windows-console-host)
  - [Shared Components](#shared-components)
  - [Creating the new Windows Terminal](#creating-the-new-windows-terminal)
- [Resources](#resources)
- [FAQ](#faq)
  - [I built and ran the new Terminal, but it looks just like the old console](#i-built-and-ran-the-new-terminal-but-it-looks-just-like-the-old-console)
- [Documentation](#documentation)
- [Contributing](#contributing)
- [Communicating with the Team](#communicating-with-the-team)
- [Developer Guidance](#developer-guidance)
- [Prerequisites](#prerequisites)
- [Building the Code](#building-the-code)
  - [Building in PowerShell](#building-in-powershell)
  - [Building in Cmd](#building-in-cmd)
- [Running \& Debugging](#running--debugging)
  - [Coding Guidance](#coding-guidance)
- [Code of Conduct](#code-of-conduct)

</details>

<br />

This repository contains the source code for:

* [Windows Terminal](https://aka.ms/terminal)
* [Windows Terminal Preview](https://aka.ms/terminal-preview)
* The Windows console host (`conhost.exe`)
* Components shared between the two projects
* [ColorTool](./src/tools/ColorTool)
* [Sample projects](./samples)
  that show how to consume the Windows Console APIs

Related repositories include:

* [Windows Terminal Documentation](https://learn.microsoft.com/windows/terminal)
  ([Repo: Contribute to the docs](https://github.com/MicrosoftDocs/terminal))
* [Console API Documentation](https://github.com/MicrosoftDocs/Console-Docs)
* [Cascadia Code Font](https://github.com/Microsoft/Cascadia-Code)

---

## What's different in this build

This fork tracks the upstream `main` branch and adds a handful of extra features
and fixes on top of it. Everything described below is **already included** in the
packages published on the [Releases page](../../releases) — you do not need to
build anything yourself.

### Tab bar position

The tab strip is no longer stuck at the top. You can move it to the **bottom** of
the window, or to the **left** or **right** side, where it turns into a vertical
list — much easier to scan when you have a lot of tabs open.

**How to use it:** open **Settings** > **Appearance** > **Tab bar position** and
pick `Top`, `Bottom`, `Left (vertical)` or `Right (vertical)`. The same option is
called `tabPosition` in `settings.json`.

There is also a `toggleVerticalTabs` action if you would rather use a shortcut:
bind it to a key of your choice and press it to flip between the horizontal and
vertical layouts. It has no default shortcut.

<!-- SCREENSHOT: tab bar position -->
> _[Screenshot: tab bar position]_

### Window background material

The window frame, the tab row and the settings pages can use Mica, Mica Alt or
acrylic, so Terminal blends in with the rest of Windows instead of sitting on a
flat block of colour.

**How to use it:** open **Settings** > **Appearance** > **Application background
material** and pick a style. The choices are `Default`, `Solid`, `Mica`,
`Mica Alt`, `Acrylic` and `Acrylic Dark`. The same option is called
`applicationBackgroundMaterial` in `settings.json`.

<!-- SCREENSHOT: window background material -->
> _[Screenshot: window background material]_

### No more ghost characters in transparent windows

With transparency or acrylic turned on, scrolling and switching used to leave
faint leftover characters and smears behind. That is fixed. The same round of
work also took care of text that landed in the wrong place at non-standard
display scaling, leftovers while scrolling, and scroll margins leaking between
pages and between the main and alternate screen buffers.

<!-- SCREENSHOT: before / after ghosting -->
> _[Screenshot: before and after]_

### Better Chinese and symbol alignment

Characters from the Private Use Area are now treated as narrow no matter which
ambiguous-width policy is selected, so lines that mix Chinese with box-drawing
characters and symbols line up properly.

### Right-to-left text

Arabic, Hebrew and other right-to-left scripts are shaped correctly, and
mixed-direction lines are broken at proper word and script boundaries.

### Drag tabs on or off

**Settings** > **Interaction** > **Reorder and tear out tabs by dragging**
controls whether tabs can be dragged to reorder them, or pulled out into a new
window. When Terminal is running as administrator or as another user, the switch
is turned off automatically and a note explains why — dragging tabs in that
situation would crash the window. The "move tab" actions still work.

<!-- SCREENSHOT: tab drag setting -->
> _[Screenshot: tab drag setting]_

### Smoother settings pages

Moving between pages in the settings UI no longer stutters. The built-in page
transition was replaced with a simple fade, which stays smooth even while the
next page is still being put together.

### True colour in every new session

New sessions start with `COLORTERM=truecolor` in their environment, so tools that
look for it — `ls`, `bat` and plenty of other command-line programs — produce
full 24-bit colour output.

### Filled-in Chinese UI

Missing Simplified Chinese strings in the settings UI were filled in, dead
entries were removed, and a leftover text key that could crash a settings page
was fixed.

---

## Download and install

There is exactly one way to get this build: download the archive from the
[Releases page](../../releases) and install it from there. It is not published to
the Microsoft Store, and it is not in winget, Chocolatey or Scoop — those install
the official Microsoft build, not this one.

1. Open the [latest release](../../releases/latest) and, under **Assets**,
   download `WindowsTerminal-Dev-<version>-x64.zip`.
2. Unzip it anywhere you like.
3. In PowerShell, from inside the extracted folder, run `.\Add-AppDevPackage.ps1`.
   It trusts the certificate, installs the framework dependency and installs the
   app itself, in that order.

If PowerShell refuses to run the script, allow it for the current session first:

```powershell
Set-ExecutionPolicy -Scope Process Bypass
```

### Installing by hand

If you would rather do each step yourself, the order matters — the framework
dependency has to be in place before the app:

1. Trust the certificate: right-click the `.cer` file, choose **Install
   Certificate**, select **Local Machine**, then **Place all certificates in the
   following store** > **Browse** > **Trusted People**.
2. Install the dependency:
   `Add-AppxPackage .\Dependencies\x64\Microsoft.UI.Xaml.2.8.appx`
   (skip this if your system already has Microsoft.UI.Xaml 2.8).
3. Install the app:
   `Add-AppxPackage .\CascadiaPackage_<version>_x64.msixbundle`

> [!IMPORTANT]
> **This build installs alongside the official Windows Terminal — it does not
> replace it.** Both can be installed and used at the same time, and they keep
> separate settings. In the Start menu this one is called **Terminal Dev**, and
> its icon has a green **DEV** badge in the corner, so the two are easy to tell
> apart. Uninstall it at any time from **Settings** > **Apps** >
> **Installed apps** — the official build stays where it is.

> [!NOTE]
> The package is signed with a self-signed test certificate rather than a
> Microsoft Store certificate, which is why the certificate step is needed. Only
> install it if you are comfortable trusting a certificate that was generated on
> the machine that built the package.

---

## Terminal & Console Overview

Please take a few minutes to review the overview below before diving into the
code:

### Windows Terminal

Windows Terminal is a new, modern, feature-rich, productive terminal application
for command-line users. It includes many of the features most frequently
requested by the Windows command-line community including support for tabs, rich
text, globalization, configurability, theming & styling, and more.

The Terminal will also need to meet our goals and measures to ensure it remains
fast and efficient, and doesn't consume vast amounts of memory or power.

### The Windows Console Host

The Windows Console host, `conhost.exe`, is Windows' original command-line user
experience. It also hosts Windows' command-line infrastructure and the Windows
Console API server, input engine, rendering engine, user preferences, etc. The
console host code in this repository is the actual source from which the
`conhost.exe` in Windows itself is built.

Since taking ownership of the Windows command-line in 2014, the team added
several new features to the Console, including background transparency,
line-based selection, support for [ANSI / Virtual Terminal
sequences](https://en.wikipedia.org/wiki/ANSI_escape_code), [24-bit
color](https://devblogs.microsoft.com/commandline/24-bit-color-in-the-windows-console/),
a [Pseudoconsole
("ConPTY")](https://devblogs.microsoft.com/commandline/windows-command-line-introducing-the-windows-pseudo-console-conpty/),
and more.

However, because Windows Console's primary goal is to maintain backward
compatibility, we have been unable to add many of the features the community
(and the team) have been wanting for the last several years including tabs,
unicode text, and emoji.

These limitations led us to create the new Windows Terminal.

> You can read more about the evolution of the command-line in general, and the
> Windows command-line specifically in [this accompanying series of blog
> posts](https://devblogs.microsoft.com/commandline/windows-command-line-backgrounder/)
> on the Command-Line team's blog.

### Shared Components

While overhauling Windows Console, we modernized its codebase considerably,
cleanly separating logical entities into modules and classes, introduced some
key extensibility points, replaced several old, home-grown collections and
containers with safer, more efficient [STL
containers](https://docs.microsoft.com/en-us/cpp/standard-library/stl-containers?view=vs-2022),
and made the code simpler and safer by using Microsoft's [Windows Implementation
Libraries - WIL](https://github.com/Microsoft/wil).

This overhaul resulted in several of Console's key components being available
for re-use in any terminal implementation on Windows. These components include a
new DirectWrite-based text layout and rendering engine, a text buffer capable of
storing both UTF-16 and UTF-8, a VT parser/emitter, and more.

### Creating the new Windows Terminal

When we started planning the new Windows Terminal application, we explored and
evaluated several approaches and technology stacks. We ultimately decided that
our goals would be best met by continuing our investment in our C++ codebase,
which would allow us to reuse several of the aforementioned modernized
components in both the existing Console and the new Terminal. Further, we
realized that this would allow us to build much of the Terminal's core itself as
a reusable UI control that others can incorporate into their own applications.

The result of this work is contained within this repo and is published as the
Windows Terminal application. For this fork, that means the packages on
[this repository's releases page](../../releases).

---

## Resources

For more information about Windows Terminal, you may find some of these
resources useful and interesting:

* [Command-Line Blog](https://devblogs.microsoft.com/commandline)
* [Command-Line Backgrounder Blog
  Series](https://devblogs.microsoft.com/commandline/windows-command-line-backgrounder/)
* Windows Terminal Launch: [Terminal "Sizzle
  Video"](https://www.youtube.com/watch?v=8gw0rXPMMPE&list=PLEHMQNlPj-Jzh9DkNpqipDGCZZuOwrQwR&index=2&t=0s)
* Windows Terminal Launch: [Build 2019
  Session](https://www.youtube.com/watch?v=KMudkRcwjCw)
* Run As Radio: [Show 645 - Windows Terminal with Richard
  Turner](https://www.runasradio.com/Shows/Show/645)
* Azure DevOps Podcast: [Episode 54 - Kayla Cinnamon and Rich Turner on DevOps
  on the Windows
  Terminal](http://azuredevopspodcast.clear-measure.com/kayla-cinnamon-and-rich-turner-on-devops-on-the-windows-terminal-team-episode-54)
* Microsoft Ignite 2019 Session: [The Modern Windows Command Line: Windows
  Terminal -
  BRK3321](https://myignite.techcommunity.microsoft.com/sessions/81329?source=sessions)

---

## FAQ

### I built and ran the new Terminal, but it looks just like the old console

Cause: You're launching the incorrect solution in Visual Studio.

Solution: Make sure you're building & deploying the `CascadiaPackage` project in
Visual Studio.

> [!NOTE]
> `OpenConsole.exe` is just a locally-built `conhost.exe`, the classic
> Windows Console that hosts Windows' command-line infrastructure. OpenConsole
> is used by Windows Terminal to connect to and communicate with command-line
> applications (via
> [ConPty](https://devblogs.microsoft.com/commandline/windows-command-line-introducing-the-windows-pseudo-console-conpty/)).

---

## Documentation

All project documentation is located at [aka.ms/terminal-docs](https://aka.ms/terminal-docs). If you would like
to contribute to the documentation, please submit a pull request on the [Windows
Terminal Documentation repo](https://github.com/MicrosoftDocs/terminal).

---

## Contributing

We are excited to work alongside you, our amazing community, to build and
enhance Windows Terminal\!

***BEFORE you start work on a feature/fix***, please read & follow our
[Contributor's
Guide](./CONTRIBUTING.md) to
help avoid any wasted or duplicate effort.

## Communicating with the Team

The easiest way to communicate with the team is via GitHub issues.

Please file new issues, feature requests and suggestions, but **DO search for
similar open/closed preexisting issues before creating a new issue.**

If you would like to ask a question that you feel doesn't warrant an issue
(yet), please reach out to us via Twitter:

* Christopher Nguyen, Product Manager:
  [@nguyen_dows](https://twitter.com/nguyen_dows)
* Dustin Howett, Engineering Lead: [@dhowett](https://twitter.com/DHowett)
* Mike Griese, Senior Developer: [@zadjii@mastodon.social](https://mastodon.social/@zadjii)
* Carlos Zamora, Developer: [@cazamor_msft](https://twitter.com/cazamor_msft)
* Pankaj Bhojwani, Developer
* Leonard Hecker, Developer: [@LeonardHecker](https://twitter.com/LeonardHecker)

## Developer Guidance

## Prerequisites

You can configure your environment to build Terminal in one of two ways:

### Using WinGet configuration file

After cloning the repository, you can use a [WinGet configuration file](https://learn.microsoft.com/en-us/windows/package-manager/configuration/#use-a-winget-configuration-file-to-configure-your-machine)
to set up your environment. The [default configuration file](.config/configuration.winget) installs Visual Studio 2026 Community & rest of the required tools. There are two other variants of the configuration file available in the [.config](.config) directory for Enterprise & Professional editions of Visual Studio 2026. To run the default configuration file, you can either double-click the file from explorer or run the following command:

```powershell
winget configure .config\configuration.winget
```

### Manual configuration

* You must be running Windows 10 2004 (build >= 10.0.19041.0) or later to run
  Windows Terminal
* You must [enable Developer Mode in the Windows Settings
  app](https://learn.microsoft.com/windows/uwp/get-started/enable-your-device-for-development)
  to locally install and run Windows Terminal
* You must have [PowerShell 7 or later](https://github.com/PowerShell/PowerShell/releases/latest) installed
* You must have the [Windows 11 (10.0.26100) SDK](https://developer.microsoft.com/windows/downloads/windows-sdk/) installed at version 10.0.26100.8249 or greater.
* You must have at least [VS 2026](https://visualstudio.microsoft.com/downloads/) version 18.6 installed
* You must install the following Workloads via the VS Installer. Note: Opening
  the solution will [prompt you to install missing components automatically](https://devblogs.microsoft.com/setup/configure-visual-studio-across-your-organization-with-vsconfig/):
  * Desktop Development with C++
  * WinUI application development
* You must install the [.NET Framework 4.7.2 Targeting Pack](https://learn.microsoft.com/dotnet/framework/install/guide-for-developers#to-install-the-net-framework-developer-pack-or-targeting-pack) to build test projects

## Building the Code

OpenConsole.slnx may be built from within Visual Studio or from the command-line
using a set of convenience scripts & tools in the **/tools** directory:

### Building in PowerShell

```powershell
Import-Module .\tools\OpenConsole.psm1
Set-MsBuildDevEnvironment
Invoke-OpenConsoleBuild
```

### Building in Cmd

```shell
.\tools\razzle.cmd
bcz
```

## Running & Debugging

To debug the Windows Terminal in VS, right click on `CascadiaPackage` (in the
Solution Explorer) and go to properties. In the Debug menu, change "Application
process" and "Background task process" to "Native Only".

You should then be able to build & debug the Terminal project by hitting
<kbd>F5</kbd>. Make sure to select either the "x64" or the "x86" platform - the
Terminal doesn't build for "Any Cpu" (because the Terminal is a C++ application,
not a C# one).

> 👉 You will _not_ be able to launch the Terminal directly by running the
> WindowsTerminal.exe. For more details on why, see
> [#926](https://github.com/microsoft/terminal/issues/926),
> [#4043](https://github.com/microsoft/terminal/issues/4043)

### Coding Guidance

Please review these brief docs below about our coding practices.

> 👉 If you find something missing from these docs, feel free to contribute to
> any of our documentation files anywhere in the repository (or write some new
> ones!)

This is a work in progress as we learn what we'll need to provide people in
order to be effective contributors to our project.

* [Coding Style](./doc/STYLE.md)
* [Code Organization](./doc/ORGANIZATION.md)
* [Exceptions in our legacy codebase](./doc/EXCEPTIONS.md)
* [Helpful smart pointers and macros for interfacing with Windows in WIL](./doc/WIL.md)

---

## Code of Conduct

This project has adopted the [Microsoft Open Source Code of
Conduct][conduct-code]. For more information see the [Code of Conduct
FAQ][conduct-FAQ] or contact [opencode@microsoft.com][conduct-email] with any
additional questions or comments.

[conduct-code]: https://opensource.microsoft.com/codeofconduct/
[conduct-FAQ]: https://opensource.microsoft.com/codeofconduct/faq/
[conduct-email]: mailto:opencode@microsoft.com
