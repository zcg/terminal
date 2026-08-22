# AGENTS.md

Windows Terminal + the Windows console host (`conhost.exe`) — the
`microsoft/terminal` codebase. Pure Windows, C++ (C++/WinRT + WIL), built with
MSBuild. No CMake, no Linux. Source under `src/`; solution is `OpenConsole.slnx`.

## Building

Prereqs (README + `doc/building.md`): VS 2026 (18.6+), Windows 11 SDK
10.0.26100.8249+, PowerShell 7+. Configs `Debug`/`Release`/`AuditMode`;
platforms `x64`/`x86`/`arm64` — never `AnyCPU`. Binaries land in
`bin\<platform>\<config>\`.

PowerShell:

```powershell
Import-Module .\tools\OpenConsole.psm1
Set-MsBuildDevEnvironment   # sets up VS dev shell + $env:Platform
Invoke-OpenConsoleBuild     # nuget restore + msbuild; extra args pass to msbuild
```

Cmd:

```
.\tools\razzle.cmd
bcz           # clean+build Debug by default; `bcz rel` for Release
```

To build the Terminal package only (slow, produces an msix):
`Invoke-OpenConsoleBuild /t:Terminal\CascadiaPackage` (or `bx` after razzle).
In VS, set `CascadiaPackage` as the startup project to run/debug the Terminal —
`OpenConsole.exe` is the conhost clone and is *not* the Terminal app.

## Tests (TAEF)

All tests use TAEF (`te.exe` from the `Microsoft.Taef` NuGet package), not the
VS test runner. Test binaries and their suite names are listed in `tools/tests.xml`.

- `Invoke-OpenConsoleTests` — runs all unit tests by default.
  `-Test <name>` selects one suite (`host`, `terminal`, `terminalApp`,
  `unitSettingsModel`, ...); `-TaefArgs` passes through to `te.exe`.
  ft/uia suites spawn their own windows and may move the mouse.
- Run one test by name:

  ```
  te.exe bin\x64\Debug\Conhost.Unit.Tests.dll /name:*BufferTests*
  ```

  `te.exe` is at `packages\Microsoft.Taef.*\build\Binaries\x64\te.exe` (also
  `%TAEF%` after `razzle.cmd`). Add `/waitForDebugger` to attach a debugger.
- Wrappers: `runut.cmd`, `runft.cmd`, `runuia.cmd`, `testcon.cmd`.

## Formatting (CI-enforced)

`runformat.cmd` / `Invoke-CodeFormat` — clang-format on all C++ plus XamlStyler
on `.xaml` (`runxamlformat.cmd` for XAML only). Run before any PR; CI rejects
unformatted code. `.clang-format` is at the repo root.

## Architecture

Two products share a common core:

- **Windows Terminal** — `src/cascadia`
- **Console host (conhost)** — `src/host` (this source also ships inside Windows)

Dependency chain (each layer consumes the one below):

```
TerminalConnection (backends: ConptyConnection, etc.)
  → TerminalSettings (settings abstraction, JSON model)
  → TerminalCore (the Terminal class: buffer, color table, VT, input — UI-agnostic)
  → TerminalControl (WinUI TermControl, DX/atlas renderer, input translation)
  → TerminalApp (tabs/panes, settings UI, action handling — C++/WinRT)
  → WindowsTerminal (EXE: Win32 window + XAML islands)
  → CascadiaPackage (msix packaging)
```

VT support: `src/terminal/parser` (characters → verbs) and `src/terminal/adapter`
(verbs → console API). Rendering: `src/renderer` (base + engines: gdi, atlas, dx).
Shared utilities: `src/til` (feature flags, text/color/geometry, etc.), `src/types`,
`src/inc` (cross-cutting headers).

Conventions: unit tests in `ut_*` dirs, feature tests in `ft_*`, project outputs
grouped in `dll`/`exe`/`lib` subdirs, interfaces under `inc`.

Feature flags: declared in `src/features.xml`, consumed as `Feature_X::IsEnabled()`.
New features must be gated with a flag and use `alwaysDisabledReleaseTokens` unless
shipped (see `doc/feature_flags.md`).

### Coding guidance

Modern C++ per C++ Core Guidelines; WIL smart pointers/result macros for Win32/NT
APIs; prefer HRESULT/exceptions over NTSTATUS; in `TerminalApp` be deliberate
about C++/WinRT strong/weak references. See `doc/STYLE.md`, `doc/WIL.md`.

## Local notes

- This checkout tracks upstream `main`, but the working tree often carries
  in-progress local modifications — run `git status`/`git diff` before assuming
  files match upstream.
- A `.codegraph/` index exists; use `codegraph explore`/`codegraph node` for
  symbol-level code search.
- `custom.props` and `.wt.json` at the root are local config, not upstream files.
