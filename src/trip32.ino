
#include <HT1621.h>
#include <HardwareSerial.h>
#include <TinyGPS++.h>
#include <QMC5883LCompass.h>
#include <Chrono.h> 

QMC5883LCompass compass;

Chrono myChrono; 

// GPS - INI
// NEO 6 TX - RX2
// NEO 6 RX - TX2
static const int RXPin = 16, TXPin = 17;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;
// The serial connection to the GPS device
HardwareSerial SerialGPS(1);

// GPS - FIN
HT1621 lcd;

const int ButtonUp = 15;
const int ButtonDown = 4;
const int ButtonMenu = 23;


double lastLat;
double lastLong;
bool lastLocOK = false;


int num_sat;
String heading;

void(*resetFunc)(void) = 0;

int menu = 1;
int menu_entries_qty = 5;

// menu = 1 - Speed
float speed_kmh = 0.0;

// menu = 2 - Trip
float trip = 0.0;

// menu = 3 - CAP
int cap;

// menu = 4 - Chrono
float chrono_elapsed;

// menu = 5 - AVG Speed
float avg_speed;

void setup()
{
  Serial.begin(115200);
  compass.init();
  pinMode(ButtonUp, INPUT);
  pinMode(ButtonDown, INPUT);
  pinMode(ButtonMenu, INPUT);
  // LCD Data D5 (5)
  // LCD wr D18 (18)
  // LCD cs D19 (19)
  lcd.begin(19, 18, 5); // (cs, wr, Data, backlight)
  lcd.backlight(); // turn on the backlight led
  lcd.clear(); // clear the screen

  // GPS - INI
    SerialGPS.begin(GPSBaud, SERIAL_8N1, RXPin, TXPin);

  Serial.println(F("TEST GPS Arduino Uno"));
  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
  // GPS - FIN
  lcd.print(999.9, 2);
  myChrono.restart();
}

void loop()
{
  inputButtons();
  getGPS(); // 1 Speed & 2 Trip
  getCAP(); // 3 CAP
  getChrono(); // 4 Chrono
  getAvgSpeed(); // 5 Avg Speed
  displayInfo();
  //debugInfo();
}

void inputButtons(){
    int Up_button_state = digitalRead(ButtonUp);
    if ( Up_button_state == HIGH )
    {
      switch (menu) {
        case 2:
          // 2 - Trip
          trip += 0.1;
          break;
        case 4:
          // 4 - Chrono
          break;
        default:
          break;
      }
    }
    int Down_button_state = digitalRead(ButtonDown);
    if ( Down_button_state == HIGH )
    {
      switch (menu) {
        case 2:
          // 2 - Trip
          trip -= 0.1;
          break;
        case 4:
          // 4 - Chrono
          break;
        default:
          break;
      }
    }
    int Menu_button_state = digitalRead(ButtonMenu);
    if ( Menu_button_state == HIGH )
    {
      menu += 1;
      if (menu > menu_entries_qty) {
        menu = 1;
      }
      lcd.print(menu * 1111, 1);
      delay(500);
      
    }
}

void displayInfo()
{
    switch (menu) {
      case 1:
        // 1 - Speed
        lcd.print(speed_kmh, 3);
        break;
      case 2:
        // 2 - Trip
        lcd.print(trip, 3);
        break;
      case 3:
        // 3 - CAP
        lcd.print(cap, 1);
        break;
      case 4:
        // 4 - Chrono
        lcd.print(chrono_elapsed, 3);
        break;
      case 5:
        // 5 - AVG Speed
        lcd.print(avg_speed, 3);
        break;
      default:
        break;
    }
}

void debugInfo()
{   
  
  Serial.print(F("Menu: "));
  Serial.print(menu);
  Serial.print(F("; 1 - Speed: "));
  Serial.print(speed_kmh);
  Serial.print(F("; 2 - Trip: "));
  Serial.print(trip);
  Serial.print(F("; 3 - CAP: "));
  Serial.print(cap);
  Serial.print(F("; 4 - Chrono: "));
  Serial.print(chrono_elapsed);
  Serial.print(F("; 5 - AVG Speed: "));
  Serial.print(avg_speed);
  Serial.println();
  
  Serial.print(F("Satelites: "));
  Serial.print(gps.satellites.value());
  Serial.print(F(" Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (SerialGPS.available())
      gps.encode(SerialGPS.read());
  } while (millis() - start < ms);
}

void getCAP()
{
  compass.read();
  cap = compass.getAzimuth();
}

void getChrono()
{
  // Chrono in min
  int ms = myChrono.elapsed();
  chrono_elapsed = ms/60000;
}


void getAvgSpeed()
{
  // Chrono in min
  avg_speed = trip / (chrono_elapsed/60);
}

void getGPS()
{
  num_sat = gps.satellites.value();

  // && gps.speed.valid() && (gps.speed.kmph() > MIN_SPEED)
  if (gps.location.isValid() == 1) {
    speed_kmh = gps.speed.kmph();
    if (lastLocOK) {
        trip += TinyGPSPlus::distanceBetween(gps.location.lat(),gps.location.lng(),lastLat,lastLong) / 1000.0;
    }
    lastLat = gps.location.lat();
    lastLong = gps.location.lng();
    lastLocOK = true;

  }

  smartDelay(100);

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    resetFunc();
    delay(1000);
  }
}
