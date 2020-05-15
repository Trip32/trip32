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
- 6 Digit 7 Segment LCD Display HT1621
  - CS -> 19
  - WR -> 18
  - Data -> 5
- Button Up
  - 3V
  - GRND -> 10K -> 15
- Button Down
  - 3V
  - GRND -> 10K -> 4
- Button Menu
  - 3V
  - GRND -> 10K -> 23
