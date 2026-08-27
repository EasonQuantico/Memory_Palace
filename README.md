# 🎹 Memory Palace — STM32 电子琴

> 一个基于 STM32F103 的多功能电子琴项目，**Memory Palace（记忆宫殿）** 是它的 GitHub 仓库名。

[![STM32](https://img.shields.io/badge/MCU-STM32F103-blue.svg)](https://www.st.com/)
[![Keil](https://img.shields.io/badge/IDE-Keil%20MDK-green.svg)](https://www.keil.com/)
[![Standard](https://img.shields.io/badge/Lib-STM32F10x_StdPeriph_V3.5.0-orange.svg)](https://www.st.com/en/embedded-software/stsw-stm32054.html)
[![License](https://img.shields.io/badge/license-MIT-lightgrey.svg)](LICENSE)

---

## 📖 项目简介

本项目使用 **STM32F103 + 无源蜂鸣器** 实现一台可弹奏、可录放、可自动演奏的电子琴。三大功能模块：

| 模块 | 功能 | 备注 |
| :--- | :--- | :--- |
| 🎵 **按键发声** | 15 个矩阵按键实时弹奏 | 音域覆盖 **3 个八度 × 12 个半音 = 36 音** |
| 🎤 **手动录放** | 录入并回放自定义旋律 | 缓冲区 **24 个音符**，超出自动丢弃最早音符 |
| 🎼 **自动演奏** | 内置三首示范曲 | 《小星星》《K歌之王》《富士山下》 |

---

## ✨ 功能详解

### 1️⃣ 按键发声（基础）

- **硬件**：15 个按键（PB0 ~ PB15）外加一个 PA0 复用键
- **音域**：3 个八度 × 12 个半音（C3 ~ B5）
- **发声原理**：定时器 TIM1 输出 PWM → 蜂鸣器
- **去抖**：GPIO 外部中断 + 软件延时双重消抖

### 2️⃣ 手动录入（进阶）

- 通过功能键切换"录入模式"
- 按下音符键自动记录**音高 + 时长**
- 缓冲区满 24 个音符后停止录入并自动播放
- 可播放自己录入的旋律

### 3️⃣ 自动演奏（进阶）

| 曲名 | 风格 |
| :--- | :--- |
| 🎵 小星星（Twinkle Twinkle Little Star） | 入门 |
| 🎵 K歌之王（陈奕迅） | 流行 |
| 🎵 富士山下（陈奕迅） | 粤语 |

> 修改 `main.c` 中的 `song_tone[]` / `song_time[]` / `song_note[]` 数组即可录入新曲。

---

## 🔧 硬件清单

| 器件 | 型号 / 规格 | 数量 | 作用 |
| :--- | :--- | :---: | :--- |
| 主控 MCU | STM32F103C8T6 | 1 | 核心控制 |
| 蜂鸣器 | 有源 / 无源蜂鸣器 5V | 1 | 发声 |
| OLED 屏 | 0.96 寸 I2C OLED（SSD1306） | 1 | 状态显示 |
| 按键 | 6×6×5 mm 微型轻触按键 | 16 | 输入 |
| LED | 5 mm 红/绿/蓝 | 3 | 指示 |
| 数码管 | 共阴极七段数码管 | 2 | 显示（可选） |
| 电阻 / 排阻 | 10 kΩ 上拉、限流电阻 | 若干 | 配线 |

> 完整原理图与 PCB 文件位于 `hardware/` 目录。

---

## 📂 目录结构

```
Memory_Palace/
├── user/                       # 用户应用层
│   ├── main.c                  # 主程序（电子琴核心逻辑）
│   ├── stm32f10x_conf.h        # 库配置文件
│   └── stm32f10x_it.c          # 中断服务程序
├── hardware/                   # 硬件驱动层
│   ├── Key.c / Key.h           # 按键扫描
│   ├── LED.c / LED.h           # LED 控制
│   ├── OLED.c / OLED.h         # OLED 显示
│   └── shumaguan.c / .h        # 数码管驱动
├── system/                     # 系统通用层
│   └── Delay.c / Delay.h       # 延时函数
├── library/                    # STM32 标准外设库（已精简）
│   └── stm32f10x_*.c / .h      # 仅保留项目用到的外设
├── starup/                     # 启动文件
│   ├── startup_stm32f10x_*.s   # 各容量型号启动文件
│   ├── core_cm3.c / .h         # Cortex-M3 内核
│   └── system_stm32f10x.c / .h # 系统初始化
├── 01.c                        # 早期 LED 按键实验（保留作参考）
└── README.md                   # 本文件
```

> ⚠️ **注意**：Keil 工程文件（`*.eprj`、`*.uvprojx`）以及编译产物（`DebugConfig/`、`Listings/`、`Objects/`、各种 `.o` / `.crf`）已通过 `.gitignore` 屏蔽，不会进入版本库。如需重建工程，请使用 Keil MDK 新建工程并按上述目录添加源文件。

---

## 🚀 快速上手

### 环境要求

| 工具 | 版本 |
| :--- | :--- |
| Keil MDK-ARM | 5.x 及以上 |
| STM32 标准外设库 | V3.5.0（已包含在 `library/`） |
| 烧录器 | ST-Link V2 / J-Link / 串口 ISP |

### 编译步骤

1. **新建 Keil 工程**
   - `Project → New uVision Project`
   - 选择芯片 `STM32F103C8`
   - 勾选 CMSIS Core + Device Startup

2. **添加源文件**
   - 把 `user/`、`hardware/`、`system/`、`library/`、`starup/` 添加到 Source Group
   - 添加编译宏 `USE_STDPERIPH_DRIVER`

3. **配置头文件路径**
   - `Options for Target → C51 / C++ → Include Paths` 添加：
     ```
     .\user
     .\hardware
     .\system
     .\library
     .\library\inc
     .\starup
     ```

4. **编译**
   - `F7` 一键编译，生成 `.hex` 文件

5. **烧录**
   - ST-Link / J-Link / FlyMcu 均可

---

## 🎮 操作说明

| 操作 | 功能 |
| :--- | :--- |
| **短按音符键** | 立即发声 |
| **功能键 1** | 切换工作模式（弹奏 / 录入 / 播放） |
| **功能键 2** | 确认 / 删除 / 切换曲目 |
| **长按** | 复位 / 切换八度 |

详细按键定义见 `user/main.c` 顶部注释。

---

## 📜 License

本项目以 **MIT License** 开源 — 详见 [LICENSE](LICENSE) 文件。

STM32 标准外设库 V3.5.0 版权归 STMicroelectronics 所有，使用请遵守其原始许可。

---

## 👤 作者

**EasonQuantico**

- GitHub: [@EasonQuantico](https://github.com/EasonQuantico)
- 项目主页: [Memory_Palace](https://github.com/EasonQuantico/Memory_Palace)

如果这个项目对你有帮助，欢迎 ⭐ Star！
