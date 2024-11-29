# Reverse-Parking-Sensor-System
This project implements a proximity sensor to assist when reversing a car. The system is developed on the LPC1769 (Rev C) board and uses multiple modules and peripherals to ensure efficient control and monitoring, providing real-time interaction with the user.

# LPC1769 Project: Control and Monitoring System

## Description
This project implements a control and monitoring system based on the **LPC1769 (Rev C)** board, using various peripherals to interact with the user, such as LEDs, a potentiometer, and a buzzer. The communication between the LPC1769 microcontroller and the computer is done via UART through a **PL2303** adapter.

## Hardware Requirements

### Base Board
- **LPC1769 (Rev C)**
- **Microcontroller**: ARM Cortex-M3 at 120 MHz
- **Flash Memory**: 512 KB
- **SRAM Memory**: 64 KB
- **GPIO Ports**: To interact with sensors, LEDs, buttons, etc.
- **Serial Communication (UART)**: For data transmission to the computer.

### Additional Components
- **UART Adapter (PL2303 or similar)**: For communication between the LPC1769 and the computer via USB.
- **Proximity Sensors**: Replaced by a potentiometer that provides continuous analog values.
- **LEDs**: Visual indicators to represent the system's status.
- **Buzzer**: To emit audible alerts.
- **LCD Display (optional)**: To show the system's status (e.g., sensor values).
- **Buttons/Switches**: To control the system modes.

### Connections and Wiring
- **USB Cable**: To connect the LPC1769 board to the computer.
- **Jumper Wires**: To connect additional peripherals (sensors, LEDs, buzzer).
- **Resistors**: To control current in some peripherals.

---

## Software Requirements

### Necessary Tools
- **MCUXpresso IDE**: To compile and load the code onto the LPC1769.
- **Python 3.x**: To run the graphical interface communicating via UART.
- **UART Drivers (PL2303)**: To ensure proper communication between the LPC1769 and the computer.
- **Visual Studio Code** (optional): To run the Python script.

---

## Installation and Setup

### Prerequisites
Before starting the compilation and programming, make sure you have installed and configured the following items:

1. **MCUXpresso IDE**: To compile and load the code.
2. **Python 3.x**: To run the UART interface.
3. **UART Drivers (PL2303)**: To ensure communication.
4. **Visual Studio Code** (optional): To run the Python script.

### Installation Steps

#### 1. Install MCUXpresso IDE
- Download and install **MCUXpresso IDE** from the [official NXP website](https://www.nxp.com/).
- During installation, select the default options.

#### 2. Install UART Drivers
- Install the appropriate drivers for the **PL2303** adapter.
- The drivers can be downloaded from the [official manufacturer’s website](http://www.prolific.com.tw/US/ShowProduct.aspx?p_id=225&pcid=41).
- Follow the installation instructions.

#### 3. Set Up the Environment in MCUXpresso IDE
- **Import Libraries**: Ensure that the necessary libraries for the LPC1769 are correctly imported into the IDE.
- **Import the Project**: Open MCUXpresso IDE and use the "Import Project" option to add the project.
- **Compile and Load the Project**: Follow the steps described in the **Compilation and Programming** section.

#### 4. UART Communication with Python

##### 4.1. Connect the UART Adapter
- Connect the **PL2303** adapter to the LPC1769 and the computer.
- Make sure to properly connect the **TX/RX** pins between the LPC1769 and the adapter.

##### 4.2. Verify the COM Port
- In the **Device Manager** in Windows, verify which COM port has been assigned to the UART adapter. This port will be used by the Python interface.

##### 4.3. Install UART Drivers
- Ensure that the drivers for the **PL2303** adapter are properly installed and that the UART port is recognized by the computer.

##### 4.4. Run the Interface in Python

- **Install Dependencies**: Make sure you have **Python 3.x** installed. Then, install the necessary dependencies by running:

  ```bash
  pip install pyserial customtkinter