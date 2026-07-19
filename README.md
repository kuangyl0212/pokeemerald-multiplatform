# pokeemerald-multiplatform

An experimental Windows, Linux, and Android port of the [Pokemon Emerald decompilation](https://github.com/pret/pokeemerald).

The project runs the decompiled game code directly. It is not a bundled GBA emulator and does not include a commercial ROM.

> This fork adds a **Simplified Chinese (zh-CN) localization** on top of the multiplatform port. See [中文汉化](#中文汉化) below for details.

## Platform Status

| Platform | Status | Output |
| --- | --- | --- |
| Windows | Working through the SDL2 backend | `pokeemerald.exe` |
| Linux | Working native 32-bit SDL2 build | `pokeemerald` |
| Android | Working experimental ARMv7 SDL2 build | `android/app/build/outputs/apk/debug/app-debug.apk` |
| GBA ROM | Upstream target | `pokeemerald.gba` |

## Port Changes

- Repaired the portable MP2K/M4A music player and sound mixer build.
- Added SDL2 float audio output at 42060 Hz.
- Sanitized invalid floating-point samples independently in the M4A and CGB audio paths, eliminating loud buzzing without discarding valid audio.
- Added output headroom and clipping protection.
- Fixed structure and pointer conversions required by the portable audio engine.
- Fixed portable BIOS, DMA, flash-save, trainer-card, and sound-related compilation errors.
- Added working save-file access through `pokeemerald.sav`.
- Added a Wine launcher for the Windows build.
- Added native 32-bit Linux compilation and SDL2 linkage.
- Added aspect-ratio-preserving 3:2 rendering with independently scaled background artwork and a transparent frame.
- Added persistent display settings with automatic support for additional numbered background images.
- Added an experimental Android SDL2/Gradle project and an ARMv7 cross-compilation pipeline.
- Added Android rendering, frame pacing, audio output, writable save storage, and lifecycle handling.
- Added an Android-native labeled multitouch overlay and SDL game-controller input.
- Added launcher icons on Android and an embedded multi-resolution icon on Windows.

## Controls

| GBA control | Keyboard |
| --- | --- |
| A | `Z` |
| B | `X` |
| Start | `Enter` |
| Select | `Backslash` |
| L | `A` |
| R | `S` |
| D-pad | Arrow keys |
| Fast-forward | `Space` |
| Pause | `Ctrl+P` |
| Soft reset | `Ctrl+R` |

Windows XInput controllers are supported by the SDL2 backend. Android supports SDL-compatible gamepads, including D-pad and left analog-stick movement. Native Linux currently uses keyboard input.

## Windows Build

The Windows target uses the 32-bit MinGW toolchain, SDL2, and ImageMagick. ImageMagick converts the PNG border assets to alpha-preserving BMP files supported by the Windows SDL2 build:

```sh
make -f Makefile_pc -j4
```

Place `SDL2.dll` beside `pokeemerald.exe`. On Linux, the Windows build can be launched through Wine with:

```sh
./launch.sh
```

## Linux Build

The game data contains 32-bit pointers, so the native Linux target must currently be built as a 32-bit executable. Install a multilib C toolchain plus 32-bit SDL2 and SDL2_image development files, then run:

```sh
make -f Makefile_pc linux -j4
./pokeemerald
```

Linux objects are kept separately under `build/linux`, so they do not interfere with the Windows build.

The resulting executable is `pokeemerald` in the repository root.

## Display Settings

The in-game Options menu includes a `DISPLAY` page. Settings apply immediately and are written to `pokeemerald.cfg`; Android stores the same config in the app's private storage.

Desktop builds support fullscreen, window size, integer scaling, VSync, border frame visibility, background selection, and volume. Android supports border frame visibility, background selection, and volume.

## Border Artwork

Windows, Linux, and Android use the same border assets from the repository root:

- `Border.png` is the transparent frame fitted around the centered 3:2 gameplay viewport.
- `BG.png` is the default background and scales independently to fill the complete output.
- `BG1.png`, `BG2.png`, and subsequent sequentially numbered files add selectable backgrounds after the default `BG` entry.

The background selector order is `BG`, `BG 1`, `BG 2`, and so on, followed by `OFF` for a plain black background. Numbered files must be contiguous; for example, `BG2.png` is only detected when `BG1.png` is also present.

Backgrounds and the frame should use a 1280x720 canvas. Keep the frame opening centered at the same location and dimensions as `Border.png` so it remains aligned at different output aspect ratios.

## Saving

Save data is read from and written to:

```text
pokeemerald.sav
```

Keep this file if you clean or move the build.

## Android Build

The Android project targets API 36 and `armeabi-v7a`. The 32-bit ABI is required by the game's current pointer layout. Android SDK 36, NDK `26.3.11579264`, CMake 3.22.1, and a compatible JDK are required.

Initialize SDL2 and apply the Android lifecycle patch once after cloning:

```sh
git submodule update --init --recursive
git -C android/SDL2 apply ../patches/sdl2-android-lifecycle.patch
```

Set `JAVA_HOME` and `ANDROID_HOME`, then build with SDL2's Gradle wrapper:

```sh
android/SDL2/android-project/gradlew -p android :app:assembleDebug
```

Install the debug APK on a connected device with:

```sh
adb install -r android/app/build/outputs/apk/debug/app-debug.apk
```

Android saves are stored in the app's writable private storage. Windows and Linux continue to use `pokeemerald.sav` in the working directory.

Android includes a labeled multitouch overlay for the D-pad, A, B, Start, Select, L, and R.

## Upstream Project

This repository is a fork of [gradenGnostic/pokeemerald-multiplatform](https://github.com/gradenGnostic/pokeemerald-multiplatform), which is itself based on the Pokémon Emerald decompilation. The upstream decompilation project builds the following ROM:

- `pokeemerald.gba`
- SHA-1: `f3ae088181bf583e55daf962a92bb46f4f1d07b7`

See [INSTALL.md](INSTALL.md) for the original decompilation setup and [pret.github.io](https://pret.github.io/) for other pret projects.

## 中文汉化

本 fork 在多平台移植基础上新增了简体中文（zh-CN）汉化，主要工作包括：

- **字体系统**：基于 [Fusion Pixel Font 12px zh_hans](https://github.com/TakWolf/fusion-pixel-font) 生成 12×12 中文点阵字体，覆盖 GB2312 字符集；对缺失字符使用系统字体（如 SimSun）回退。中文字形添加 1px 右下阴影以匹配英文字体风格，垂直基线对齐英文。
- **字符编码**：使用 GB2312 编码，通过 `{CHN}` 控制码（0x80 前缀 + 2 字节 GB2312）切换中文渲染模式。`charmap.txt` 中定义了字符映射。
- **字符串处理**：在 `string_util.c`、`text.c`、`braille.c`、`battle_message.c` 等文件的多个字符串函数中添加 0x80 转义序列处理，避免 GB2312 字节被误判为控制码。
- **已汉化内容**：地图名、招式描述、道具描述、特性名称与描述、性格名称、训练家职业名称、对手呼叫信息、对战金字塔楼层名、PC 相关文本等共 1200+ 条字符串。
- **构建工具**：`tools/generate_chinese_font.py` 生成中文字体文件，`tools/translate_map_names.py` 翻译地图名，`tools/fix_all_quotes.py` 转换引号，`tools/check_gb2312.py` 校验 GB2312 合规性。

### 已知限制

- Battle Frontier 训练家名受 `PLAYER_NAME_LENGTH+1=8` 字节限制，无法完整汉化（仅容纳 1 个中文字）。
- 部分内容（如 Easy Chat 词汇、部分 NPC 对话）尚未汉化。

### 构建说明

Windows 构建使用 `Makefile_pc`，构建前需将 `SDL2.dll` 放置在可执行文件旁。汉化字体文件 `chinese.latfont` 会在构建时自动生成。

```sh
make -f Makefile_pc -j4
```

## Legal

Pokémon and Pokémon Emerald are trademarks of Nintendo, Creatures Inc., and GAME FREAK inc. This is an unofficial fan project and is not affiliated with or endorsed by those companies.

The scoped license in [LICENSE](LICENSE) applies only to original multiplatform-port modifications and Simplified Chinese localization modifications contributed through this fork. It does not relicense upstream code, third-party components, or copyrighted game assets. No game ROM, copyrighted asset, or derivative of the Pokémon Emerald ROM is distributed with this repository.
