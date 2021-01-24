# Trip32
Tripmaster based on esp32, NEO6 GPS and HMC5883L (QMC5883L)

## Components
- ESP32 Dev Kit
- NEO6v2 GPS (To Do use NEO8)
- QMC5883L
- 6 Digit 7 Segment LCD Display HT1621
- 10K Resistors (x3)
- 3 Buttons


## Connections
- NEO6v2 GPS (To Do use NEO8)
  - RX -> TX0
  - TX -> RX0
- QMC5883L
  - SCL -> 22
  - SDA -> 21
- 6 Digit 7 Segment LCD Display HT1621 - 1
  - CS -> 19
  - WR -> 18
  - Data -> 5
- Button Up - 1
  - 3V
  - GRND -> 10K -> 15
- Button Down - 1
  - 3V
  - GRND -> 10K -> 4
- Button Menu - 1
  - 3V
  - GRND -> 10K -> 23
- 6 Digit 7 Segment LCD Display HT1621 - 2
  - CS -> 32
  - WR -> 33
  - Data -> 25
- Button Up - 2
  - 3V
  - GRND -> 10K -> 13
- Button Down - 2
  - 3V
  - GRND -> 10K -> 14
- Button Menu - 2
  - 3V
  - GRND -> 10K -> 34

## ESP32

|   |  INPUT | INPUT  |   |
|---|---|---|---|
|   | EN | 23  | Button 1 Menu  |
|   | VP  | 22  | QMC5883L - SCL   |
|   | VN  | 1-TX0  | GPS RX |
| Button 2 Menu  | 34  | 3-RX0  | GPS TX  |
|   | 35  | 21  | QMC5883L - SDA  |
| Display 2 - CS   | 32  | 19  |  Display 1 - CS |
| Display 2 - WR | 33  | 18  |  Display 1 - WR |
| Display 2 - Data  | 25  | 5  |  Display 1 - Data |
|   | 26  | 17-TX2  |   |
|   | 27  | 16-RX2  |   |
| Button 2 Down  | 14  | 4  | Button 1 Down  |
|   | 12  | 2  |   |
| Button 2 Up  | 13  | 15  | Button 1 Up  |
|   | GND  |  GND |   |
|   | VIN  |  3V3 |   |

## Libs

- HT1621 - Standar downloaded from arduino ide lib manager
- tinygps++ - download zip from https://github.com/mikalhart/TinyGPSPlus and install in arduino ide
- QMC5883LCompass - Standar downloaded from arduino ide lib manager
- Chrono.h - download zip from https://github.com/SofaPirate/Chrono and install in arduino ide

## Help

If sending to esp32 you get

'''
Serial port /dev/ttyUSB0
Connecting........_____.....__
'''

push boot buton on esp32

## Bugs

Compiling you get warning

'''
/home/ubuntu/Arduino/libraries/HT1621/src/HT1621.h:60:34: warning: ISO C++ forbids converting a string constant to 'char*' [-Wwrite-strings]
  void print(long num, char*flags="%6li", int precision = 0);
'''

## Debug

Monitor serial is configures on 115200 bauds