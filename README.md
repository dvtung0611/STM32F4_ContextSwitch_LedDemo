# STM32F4 Bare-Metal Mini RTOS (LED Demo)

## Overview

This project is a **bare-metal implementation of a simple preemptive scheduler (mini RTOS)** on the STM32F407 (ARM Cortex-M4), developed **without using HAL, CMSIS-RTOS, or any high-level libraries**.

The system demonstrates **multi-tasking using SysTick and PendSV**, where multiple independent tasks run concurrently with different execution periods.

> Goal: Understand deeply how an RTOS works internally — from **CPU startup sequence, stack management, exception handling, to context switching**.

---

## Key Features

* Fully **bare-metal implementation** (direct register manipulation, no HAL/CMSIS abstraction layer)
* Custom **startup code & linker script**
* **Preemptive multitasking** using:
  * SysTick (time base - 1ms tick)
  * PendSV (context switching)
* Manual **context switching mechanism**:
  * Save/restore CPU registers (R0–R12, LR, PC, xPSR)
* Separation of **MSP (kernel) and PSP (tasks)**
* Basic **round-robin scheduler**
* Task delay mechanism using **tick counter**
* Fault handling enabled:
  * HardFault, BusFault, UsageFault, MemManage

---

## System Architecture

### Scheduler Flow
```mermaid
graph LR
    A["SysTick Interrupt (1ms)"] --> B["Increment Global Tick"]
    B --> C["Check Blocked Tasks and Unblock Ready Tasks"]
    C --> D["Trigger PendSV"]
    D --> E["Context Switch"]
    E --> F["Next Task Executes"]
    
    classDef gray fill:#2ecc71,stroke:#27ae60,stroke-width:2px,color:#fff
    classDef green fill:#3498db,stroke:#2980b9,stroke-width:2px,color:#fff
    classDef blue fill:#9b59b6,stroke:#8e44ad,stroke-width:2px,color:#fff
    classDef purple fill:#34495e,stroke:#2c3e50,stroke-width:2px,color:#fff
    
    class A gray
    class B,C,D green
    class E blue
    class F purple
```

---

## Task Configuration

The system runs 4 independent tasks controlling 4 LEDs on the STM32F4 Discovery board:

| Task   | LED Color | Period  |
| ------ | --------- | ------- |
| Task 1 | Green     | 1000 ms |
| Task 2 | Orange    | 500 ms  |
| Task 3 | Blue      | 250 ms  |
| Task 4 | Red       | 125 ms  |

Each task operates independently using a delay mechanism based on system ticks.

---

## Hardware & Tools

### Hardware

* STM32F4 Discovery (STM32F407VG)

### Software / Toolchain

* GNU Arm Embedded Toolchain (`arm-none-eabi-gcc`)
* OpenOCD (flashing & debugging)
* GDB (debugging)
* Makefile (build system)
* VSCode (development)
* STM32CubeIDE (for easier exploration)

---

## Startup Flow

1. MCU Reset
2. Load initial stack pointer (MSP)
3. Copy `.data` from Flash → SRAM
4. Zero initialize `.bss`
5. Initialize system
6. Jump to `main()`

---

## Context Switching Mechanism

* **SysTick** triggers every 1ms → updates system tick
* When a task needs switching:

  * **PendSV is triggered**
  * CPU automatically saves part of context
  * Remaining registers are saved manually
* Scheduler selects next task
* Context of next task is restored
* Execution resumes

---

## Core Concepts Covered

This project demonstrates deep understanding of:

### ARM Cortex-M Architecture

* Thread mode vs Handler mode
* Privileged vs Unprivileged execution
* MSP vs PSP stack usage
* Exception entry/exit behavior

### CPU & Memory

* Register set (R0–R12, LR, PC, xPSR)
* Memory map of STM32F407
* Stack types and stack frame

### Interrupt & Exception Handling

* NVIC configuration
* SysTick & PendSV usage
* Fault handling mechanisms

### Bare-Metal Development

* Writing Makefile from scratch
* GCC compilation & linking process
* Custom linker script
* Flashing using OpenOCD + GDB

---

## Demo

Each LED toggles at a different frequency, demonstrating independent task execution:

* Green → 1s
* Orange → 500ms
* Blue → 250ms
* Red → 125ms

Demo (click to the picture):

[![Watch the demo](https://img.youtube.com/vi/Vvbdrus1IEg/0.jpg)](https://youtu.be/Vvbdrus1IEg)

---

## Notes

* This project is for **educational purposes**
* Code is written with focus on **understanding low-level behavior**, not production optimization
* Naming/style may not follow strict industry conventions

---

## Learning Outcome

After completing this project, I achieved:

* Deep understanding of **RTOS internals**
* Ability to write **bare-metal firmware from scratch**
* Strong grasp of **ARM Cortex-M architecture**
* Experience building **toolchain & debugging environment manually**
