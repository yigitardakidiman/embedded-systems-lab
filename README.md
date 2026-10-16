# ⚡ Multi-Architecture Embedded Systems Engineering Lab

[![C/C++](https://img.shields.io/badge/Language-C%20%2F%20C%2B%2B%20%2F%20Verilog-00599C?logo=c%2B%2B&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Toolchain](https://img.shields.io/badge/IDE-VS%20Code%20%2B%20PlatformIO-orange?logo=visualstudiocode&logoColor=white)](https://code.visualstudio.com/)
[![Architectures](https://img.shields.io/badge/Architectures-ARM%20%7C%20RISC--V%20%7C%20Xtensa%20%7C%20MSP430%20%7C%20AVR%20%7C%20FPGA-blueviolet)](#-target-platforms--architecture-matrix)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

> A rigorous, hands-on embedded systems laboratory and portfolio covering **12 development boards** across **6 distinct processor architectures**, spanning **144 progressive projects**—from register-level bare-metal bring-up to real-time operating systems (RTOS), DSP/signal analysis, embedded Linux kernel drivers, and FPGA hardware synthesis.

---

## 🧭 Overview & Motivation

Embedded systems engineering requires mastering low-level software abstractions across diverse silicon targets. This monorepo documents my structured progression through the embedded engineering spectrum:

*   **Layer 1 (Bare-Metal & Silicon Architecture):** Clock tree configuration, vector tables, register manipulation, SysTick, and hardware interrupt controllers (NVIC).
*   **Layer 2 (On-Chip Peripheral Engines & DMA):** Hardware Timers, PWM generation, Input Capture, multi-channel ADC/DAC, and DMA controller architectures.
*   **Layer 3 (Advanced Systems & Concurrency):** Preemptive RTOS (FreeRTOS/ThreadX), CMSIS-DSP real-time signal processing, wireless protocol stacks (BLE 5.0, ESP-NOW), Embedded Linux device drivers, and digital logic synthesis (Verilog on FPGA).

---

## 🔬 Target Platforms & Architecture Matrix

| Target Platform | Core / Architecture | Max Clock | Memory (Flash / RAM) | Primary Focus in this Repo |
| :--- | :--- | :--- | :--- | :--- |
| **ST NUCLEO-H723ZG** | ARM Cortex-M7 (w/ DP-FPU) | 550 MHz | 1 MB / 564 KB | CMSIS-DSP, Fast Fourier Transform (FFT), Cache Coherency, Advanced DMA |
| **ST NUCLEO-U575ZI-Q** | ARM Cortex-M33 (TrustZone) | 160 MHz | 2 MB / 786 KB | Ultra-Low-Power (STOP2), LPBAM Autonomous DMA, Memory Security |
| **ST P-NUCLEO-WB55** | Dual-Core: Cortex-M4 + M0+ | 64 / 32 MHz | 1 MB / 256 KB | Inter-Core IPC (HSEM/IPCC), BLE 5.0 Stack, IEEE 802.15.4 MAC |
| **TI EK-TM4C123GXL** | ARM Cortex-M4F | 80 MHz | 256 KB / 32 KB | Bit-Banding, Motion Control PWM, Custom Preemptive RTOS Kernel |
| **Raspberry Pi Pico 2 W** | Dual Cortex-M33 / Dual RISC-V | 150 MHz | 4 MB / 520 KB | Programmable I/O (PIO), Architecture Benchmarking, Multi-Core FIFO |
| **ESP-WROOM-32** | Dual-Core Xtensa LX6 | 240 MHz | 4 MB / 520 KB | Dual-Core FreeRTOS Concurrency, Non-blocking Sockets, BLE/Wi-Fi |
| **ESP32-C3 Super Mini** | Single-Core 32-bit RISC-V | 160 MHz | 4 MB / 400 KB | RISC-V CSR Profiling, Active-Low GPIO, ESP-NOW Low-Latency Telemetry |
| **TI MSP430F5529 LP** | 16-bit MSP430X RISC | 25 MHz | 128 KB / 10 KB | Full-Speed USB 2.0 (HID/CDC), Hardware Multiplier (MPY32), Unified Clock |
| **TI MSP-EXP430G2** | 16-bit MSP430 RISC | 16 MHz | 16 KB / **512 B** | Extreme Resource Constraint Optimization, Register-level LPM4 Sleep |
| **CRIUS AIOP PRO** | 8-bit AVR (ATmega2560) | 16 MHz | 256 KB / 8 KB | 8-bit Register Bare-Metal, Multi-Channel Hardware Timers, Cascaded PID |
| **Raspberry Pi Zero W** | ARM1176JZF-S (Embedded Linux) | 1.0 GHz | 512 MB | Linux Kernel Modules (LKM), sysfs, `libgpiod`, Multi-Threaded POSIX |
| **Tang Nano 9K** | Gowin GW1NR-9 FPGA | 27 MHz OSC | 8,640 LUT4 | Verilog RTL, Finite State Machines (FSM), Soft-Core RISC-V SoC |

---

## 📁 Repository Organization

```text
embedded-systems-lab/
├── docs/                             # Hardware schematics, architecture notes, register cheat sheets
│
├── 01-esp32-wroom/                   # Xtensa Dual-Core FreeRTOS & IoT Projects
├── 02-esp32-c3-riscv/                # RISC-V 32-bit Architecture & Mini Nodes
├── 03-rpi-pico2w/                    # RP2350 PIO State Machines & Dual-Core SDK
├── 04-stm32-h723-cortex-m7/          # 550 MHz CMSIS-DSP & Real-Time Signal Processing
├── 05-stm32-u575-cortex-m33/         # Autonomous LPBAM & TrustZone Security
├── 06-stm32-wb55-dual-core/          # BLE 5.0 Custom Services & IEEE 802.15.4 MAC
├── 07-msp430g2-baremetal/            # 512-Byte RAM Extreme Optimization & Bare-Metal
├── 08-msp430f5529-usb/               # On-Chip Full-Speed USB (HID/CDC) & DMA
├── 09-tm4c123-tiva-c/                # Motion Control PWM & Custom Preemptive Scheduler
├── 10-crius-atmega2560/              # 8-bit AVR Bare-Metal & Cascaded PID Loops
├── 11-rpi-zero-w-linux/              # Embedded Linux, Character Drivers, & Kernel Modules
└── 12-tang-nano-9k-fpga/             # Verilog HDL Digital Logic & Soft RISC-V SoC
```

---

## 🚀 3-Tier Architecture Roadmap (144 Projects Total)

Each of the 12 target boards contains **12 dedicated projects** designed to progressively climb the embedded hierarchy:

```mermaid
flowchart TD
    Tier1["🟢 Tier 1: Hardware Bring-Up & Bare-Metal Fundamentals\n(Toolchain verification, Clock Tree, GPIO, Vector Table, Polling vs Interrupts, Timers)"]
    Tier2["🟡 Tier 2: Peripheral Engines, DMA & Protocols\n(Hardware PWM, Input Capture, Multi-Channel ADC/DAC, DMA Transfers, Power Modes)"]
    Tier3["🔴 Tier 3: Advanced Systems & Real-Time Architecture\n(RTOS Kernels, CMSIS-DSP, TrustZone, BLE Stacks, Linux Kernel Modules, FPGA RTL)"]

    Tier1 --> Tier2 --> Tier3
```

### Key Architectural Highlights Across the Platforms

1.  **512-Byte RAM Extreme Optimization (`07-msp430g2-baremetal`):**
    Developing bare-metal applications with extreme memory constraints, avoiding heap allocation entirely, and utilizing fixed-point math and register-level bit-masking in LPM4 deep sleep.
2.  **Autonomous LPBAM Background Processing (`05-stm32-u575-cortex-m33`):**
    Configuring LPTIM, LPDMA, and low-power peripherals to acquire and buffer data autonomously in STOP2 sleep mode without CPU intervention.
3.  **Real-Time Signal Processing via CMSIS-DSP (`04-stm32-h723-cortex-m7`):**
    Timer-triggered ADC sampling, DMA buffer ping-ponging, and real-time Fast Fourier Transform (FFT) computations using the Cortex-M7 double-precision hardware FPU.
4.  **Hardware State Machines with PIO (`03-rpi-pico2w`):**
    Writing custom Programmable I/O (PIO) assembly state machines running at 150 MHz to offload timing-critical protocol handling completely from the CPU cores.
5.  **Bare-Metal Preemptive Task Switcher (`09-tm4c123-tiva-c`):**
    Building a custom round-robin preemptive scheduler from scratch using the ARM Cortex-M PendSV exception and assembly stack frame manipulation (`R4-R11`, `PSP`).
6.  **Soft-Core RISC-V SoC Synthesis (`12-tang-nano-9k-fpga`):**
    Synthesizing a 32-bit `PicoRV32` RISC-V core into the FPGA fabric, wiring memory-mapped hardware peripheral blocks in Verilog, and executing compiled C binaries.

---

## 🛠️ Toolchain & Development Environment

*   **Primary IDE:** Visual Studio Code
*   **Build Systems & Frameworks:**
    *   [PlatformIO Core](https://platformio.org/) (for ESP32, RP2350, AVR, MSP430)
    *   [STM32CubeIDE / STM32CubeCLT](https://www.st.com/) + `STM32_Programmer_CLI` (for STM32 H7/U5/WB)
    *   [Gowin EDA](https://www.gowinsemi.com/) + [openFPGALoader](https://github.com/trabucayre/openFPGALoader) (for Tang Nano 9K)
*   **Compilers:** `arm-none-eabi-gcc`, `riscv32-esp-elf-gcc`, `msp430-elf-gcc`, `avr-gcc`

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
