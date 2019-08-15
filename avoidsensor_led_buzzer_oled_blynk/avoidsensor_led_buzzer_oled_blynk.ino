/*---------------------KRENOVATOR---------------------
  LIVE MOVEMENT ALERT

  The sensor use is avoidance sensor; as for this
  project, the sensor is used to detect any object
  infront of it. The code is to read the sensor
  behavior. The LED is used as a trigger component
  for the presence or absence of any object and buzzer
  will produce sound when a object is near. OLED
  display is to monitor the result on display live.

  Get the code at github
  https://github.com/MZulsyahmi/live-movement-monitoring-using-blynk.git
  
  by M.Zulsyahmi @krenovator
  August 2019
 */
 
/*the library for OLED display*/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//initialize for pin used
int avoidpin = D4;  //KY-032 avoidance sensor

int ledR = D8;      //red LED
int ledG = D7;      //green LED

int buzzer = D3;    //buzzer

#define OLED_RESET LED_BUILTIN
Adafruit_SSD1306 display(OLED_RESET);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourNetworkName";
char pass[] = "Password";

WidgetLED red(V1);
WidgetLED green(V2);

void setup() {
  display.clearDisplay();
  
  Serial.begin(115200);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  
  //declaration for the pin
  pinMode(avoidpin, INPUT);

  pinMode(ledR,OUTPUT);
  pinMode(ledG,OUTPUT);
  pinMode(buzzer,OUTPUT);

  Blynk.begin(auth, ssid, pass);
  
  // Clear the buffer/display
  display.clearDisplay();
}

void loop() {
  int Sensor = digitalRead(avoidpin);

  //condition used: if...else condition
  //HIGH = 1 or ON      LOW = 0 or OFF
  if(Sensor == LOW){
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.print("OBJECT");
    
    digitalWrite(ledR, HIGH);
    digitalWrite(ledG, LOW);
    digitalWrite(buzzer,HIGH);
    
    red.on();
    green.off();

    Blynk.email("YourEmail", "EmailSubject", "MessageYouWantToSend");
  }
  else{
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.setTextSize(3);
    display.print("No Object");
    
    digitalWrite(ledR, LOW);
    digitalWrite(ledG, HIGH);
    digitalWrite(buzzer,LOW);
    
    red.off();
    green.on();
  }
  delay(2000);
  display.clearDisplay();
  Blynk.run();
}
