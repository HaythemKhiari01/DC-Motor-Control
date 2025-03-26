# DC Motor Control with STM32F407

## Overview
This project implements a **PWM-based DC motor control system** using an STM32F407 microcontroller. It configures GPIO, timers, and the floating-point unit (FPU) while providing system call and memory management functions. The PWM output on PA2 controls the motor speed.

## Features
- **PWM speed control** using **TIM2_CH3 (PA2)**.
- **Timer-based delay** using **TIM4**.
- **FPU activation** for floating-point calculations.
- **System calls and memory management implementations**.

## Project Structure
```
dc_motor_control/
├── .settings/           # Eclipse project settings
├── Inc/                 # Header files
├── Src/                 # Source files
│   ├── main.c           # Main application logic
│   ├── fpu.c            # Floating Point Unit (FPU) setup
│   ├── syscalls.c       # System calls for newlib
│   ├── sysmem.c         # Memory management implementation
├── Startup/             # Startup files for STM32F4
├── STM32F407VGTx_FLASH.ld  # Linker script for Flash
├── STM32F407VGTx_RAM.ld    # Linker script for RAM
```

## Requirements
- **STM32F407 Discovery Board**
- **STM32CubeIDE**
- **GCC ARM Toolchain**
- **Motor Driver (e.g., L298N, DRV8833)**
- **DC Motor**

## Installation & Compilation
1. Clone this repository:
   ```bash
   git clone https://github.com/HaythemKhiari/DC-Motor-Control.git
   ```
2. Open the project in **STM32CubeIDE**.
3. Build and flash the firmware to the STM32F407 board.

## Usage
The application controls the speed of a **DC motor** using PWM:
1. **Initializes GPIOA and TIM2**.
2. **Generates a PWM signal** with a frequency of **1 kHz**.
3. **Modifies the PWM duty cycle** periodically to adjust motor speed:
   - **20% duty cycle** (low speed)
   - **50% duty cycle** (medium speed)
   - **90% duty cycle** (high speed)

## Code Explanation
### `main.c`
- Initializes GPIO and TIM2 for **PWM-based motor control**.
- Uses TIM4 for time delay.
- Runs an infinite loop adjusting the PWM duty cycle to change motor speed.

### `fpu.c`
- Enables the Floating Point Unit (FPU) for ARM Cortex-M4.

### `syscalls.c`
- Implements system calls for **newlib**, supporting basic I/O functions.

### `sysmem.c`
- Implements `_sbrk()` for dynamic memory allocation.

## Future Improvements
- Implement **bidirectional motor control** using **H-Bridge**.
- Add **speed feedback** using an **encoder**.
- Optimize **power consumption**.

## License
This project is provided AS-IS under the **STMicroelectronics License**.

---
*Developed using STM32CubeIDE & STM32F4 HAL Libraries.*

