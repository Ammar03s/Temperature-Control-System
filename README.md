# Temperature Control System with IR Remote

This project is a temperature control system that uses an IR remote to set the temperature threshold at which a fan will be activated. It also displays the current temperature on an LCD screen and uses LEDs to indicate the temperature range.

## How to Use

1. Connect all the components as per the circuit diagram.
2. Upload the code to the Arduino board.
3. Use the IR remote to adjust the temperature threshold for the fan.
4. Observe the temperature on the LCD and the status of the LEDs.
5. The fan speed will adjust based on the temperature readings.


## Components

- Arduino Board
- IR Receiver
- LiquidCrystal LCD
- Temperature Sensor
- Red, Green, and Blue LEDs
- DC Motor (Fan)
- IR Remote
- Various resistors and connecting wires



## Code Explanation

### Libraries

The code includes two libraries:
- `IRremote.h` for handling IR remote functionality.
- `LiquidCrystal.h` for interfacing with the LCD Screen.

### Pin Definitions

- `RECV_PIN` is set to 4 for the IR receiver.
- `lcd` is configured with pins 13, 12, 11, 10, 9, 8 for the LCD.
- `tempIn` is set to A0 for the temperature sensor.
- `redLED`, `greenLED`, and `blueLED` are set to pins 7, 6, and 3 respectively for the LEDs.
- `MotorPin` is set to pin 5 for the motor (fan).

### Variables

- `motorSpeed`, `tempFan`, `results`, `RawValue`, `Voltage`, `tempC`, and `tempF` are used to handle the temperature and motor control logic.

### Setup Function

- Sets the pin modes for the motor and LEDs.
- Initializes the IR receiver and serial communication.
- Sets up the LCD.

### Loop Function

1. **Temperature Reading:**
   - Reads the temperature sensor value and converts it to Celsius and Fahrenheit.
   - Displays the temperature on the serial monitor and LCD.

2. **Motor Control:**
   - If the temperature exceeds the threshold (`tempFan`), the motor speed is set proportional to the temperature.
   - Otherwise, the motor is turned off.

3. **LED Indicators:**
   - Blue LED is on if the temperature is below 22°C.
   - Green LED is on if the temperature is between 22°C and 26°C.
   - Red LED is on if the temperature is above 26°C.

4. **IR Remote Control:**
   - The IR receiver decodes the remote signals.
   - Adjusts the `tempFan` threshold based on the remote input.
   - Displays the current fan activation threshold.

### IR Remote Codes

- `0xF708BF00`: Which is the Arrow pointing dowm, Decrease the `tempFan` threshold.
- `0xF50ABF00`: Which is the Arrow pointing up, Increase the `tempFan` threshold.



