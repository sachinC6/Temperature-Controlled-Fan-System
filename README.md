# Temperature-Controlled-Fan-System
An embedded system for automatic fan control based on temperature, developed by Sachin Chandra during NIELIT Calicut's 5-day Embedded for Beginners course (Batch-31), SMART LAB Project, C2S Program, MeitY.


# Temperature-Controlled Fan System

## Project Description
This embedded project automatically controls a fan's speed based on real-time temperature readings from a sensor. It uses PWM for variable fan speed (faster when hot) and LEDs to indicate status (red for hot, green for cool). The system demonstrates intelligent thermal management, ideal for electronics cooling in VLSI applications.

**Key Features**:
- Temperature polling via ADC (analog-to-digital conversion).
- Adaptive fan control using if-else logic and PWM.
- Status LEDs and optional buzzer for alerts.
- Data averaging with arrays for stable readings.

Developed by **Sachin Chandra**, 2nd-year B.Tech in Electronics Engineering (VLSI Design and Technology), during the 5-day "Embedded for Beginners" course offered by NIELIT Calicut and supported by the SMART LAB Project under the Chips to Start-Up (C2S) Program of MeitY, Govt of India (Batch-31).

## Course Attribution
Applies concepts from the syllabus:
- **Day 1-2**: C variables, datatypes, functions, control structures (if-else for thresholds, loops for polling).
- **Day 3**: Arrays for temperature history (averaging readings).
- **Day 4**: Embedded systems characteristics (real-time, resource-constrained), Embedded C vs. standard C, IDE flow.
- **Day 5**: STM32 Nucleo boards, GPIO/ADC drivers, SMART Lab for hardware access (NUCLEO G474).

## Hardware Requirements
- STM32 Nucleo G474 (Cortex M3-based).
- Temperature sensor (e.g., LM35 or DHT11 for ADC input).
- DC fan with motor driver (e.g., L298N for PWM control).
- LEDs (red, green) and 220Ω resistors.
- Buzzer (optional for high-temp alert).
- Jumper wires, breadboard.

## Software Requirements
- STM32CubeIDE (for ADC/PWM config and flashing).
- SMART Lab access for remote testing.

## Circuit Diagram
See `circuit_diagram.txt` for wiring. Key connections:
- LM35 sensor: VCC to 3.3V, GND to GND, OUT to PA0 (ADC input).
- Fan: Via L298N to PWM pin (e.g., TIM2_CH1 on PA5).
- LEDs: Red to PB0, Green to PB1 (GPIO outputs).

## Installation and Setup
1. Clone repo: `git clone https://github.com/yourusername/Temperature-Controlled-Fan-System.git`
2. Open `main.c` in STM32CubeIDE.
3. Configure ADC (PA0) and PWM (TIM2 on PA5) in the IDE's Pinout & Configuration tab.
4. Generate code, compile, and flash to Nucleo.
5. Test via SMART Lab.

## Usage
- Power on: System polls temp every second.
- If temp > 30°C: Fan high speed, red LED on.
- If temp < 20°C: Fan low/off, green LED on.
- Monitor via serial (add UART if needed).

## Demo
[Add video link: e.g., YouTube of fan speeding up with heat source.]

## Future Enhancements
- IoT integration for remote monitoring.
- VLSI simulation of ADC/PWM in Verilog.
- Multi-sensor averaging for accuracy.

## License
MIT License - Fork and contribute!

Developed by Sachin Chandra | NIELIT Calicut Batch-31 | SMART LAB Project, C2S Program, MeitY.
