#define BLYNK_TEMPLATE_ID "TMPL6l8l0Rp1Y"
#define BLYNK_TEMPLATE_NAME "MQ2"
#define BLYNK_AUTH_TOKEN "BIGPpTT1to-rCRLwEntgMoAcsyQFq4kL"

#include <WiFi.h>
#include <SPI.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
//#include <AceButton.h>
//using namespace ace_button;
#define BLYNK_PRINT Serial
BlynkTimer timer;
//---------------------------------------
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "LAPTOP-QGB1D019 6978";
char pass[] = "12345678";
//---------------------------------------
//----------CHÂN LED VÀ BUTTON-----------
WidgetLED led1(V1);       //LED BLYNK
WidgetLED led2(V3);
WidgetLED led3(V5);
WidgetLED led4(V7);
const int ledPin1 = 15;    //CHÂN LED
const int ledPin2 = 19;
const int ledPin3 = 5;
const int ledPin4 = 18;
const int btnPin1 = 27;   //CHÂN BUTTON
const int btnPin2 = 14;
const int btnPin3 = 26;
const int btnPin4 = 25;
int ledState1 = LOW;      //TRẠNG THÁI LED
int ledState2 = LOW;
int ledState3 = LOW;
int ledState4 = LOW;
int btnState1 = HIGH;     //TRẠNG THÁI BUTTON
int btnState2 = HIGH;
int btnState3 = HIGH;
int btnState4 = HIGH;
//---------CHÂN CẢM BIẾN ÁNH SÁNG--------
#define cbAS 36
#define led 4
int value;
//-----------CHÂN CẢM BIẾN KHÓI----------
#define MQ2 35
#define RED 32
#define BUZZER 33
int sensorValue = 0;
boolean state = false;
//---------------------------------------
BLYNK_CONNECTED() {
  Blynk.syncVirtual(V2);
  Blynk.syncVirtual(V4);
  Blynk.syncVirtual(V6);
  Blynk.syncVirtual(V8);
}
//---------------------------------------
BLYNK_WRITE(V2) {
  ledState1 = param.asInt();
  if(ledState1)
  {
    digitalWrite(ledPin1, ledState1);
    led1.on();
  }
  else{
    digitalWrite(ledPin1, ledState1);
    led1.off();
  }
}
BLYNK_WRITE(V4) {
  ledState2 = param.asInt();
  if(ledState2)
  {
    digitalWrite(ledPin2, ledState2);
    led2.on();
  }
  else{
    digitalWrite(ledPin2, ledState2);
    led2.off();
  }
}
BLYNK_WRITE(V6) {
  ledState3 = param.asInt();
  if(ledState3)
  {
    digitalWrite(ledPin3, ledState3);
    led3.on();
  }
  else{
    digitalWrite(ledPin3, ledState3);
    led3.off();
  }
}
BLYNK_WRITE(V8) {
  ledState4 = param.asInt();
  if(ledState4)
  {
    digitalWrite(ledPin4, ledState4);
    led4.on();
  }
  else{
    digitalWrite(ledPin4, ledState4);
    led4.off();
  }
}
//---------------------------------------
void setup(){
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  //
  pinMode(cbAS, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  //
  pinMode(RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(MQ2, INPUT);
  digitalWrite(RED, LOW);
  //
  pinMode(ledPin1, OUTPUT);
  pinMode(btnPin1, INPUT_PULLUP);
  digitalWrite(ledPin1, ledState1);
  pinMode(ledPin2, OUTPUT);
  pinMode(btnPin2, INPUT_PULLUP);
  digitalWrite(ledPin2, ledState2);
  pinMode(ledPin3, OUTPUT);
  pinMode(btnPin3, INPUT_PULLUP);
  digitalWrite(ledPin3, ledState3);
  pinMode(ledPin4, OUTPUT);
  pinMode(btnPin4, INPUT_PULLUP);
  digitalWrite(ledPin4, ledState4);
  //
  timer.setInterval(1000L, sendUptime);
}

//CODE CẢM BIẾN KHÓI - KHÍ GAS
void sendUptime()
{
  //--------------------------------------------------
  sensorValue = map(analogRead(MQ2), 0, 4095, 0, 100);
  int doc = analogRead(cbAS);
  value = 100 - map(doc,0, 4095, 0, 100);
  Blynk.virtualWrite(V0, sensorValue);
  Blynk.virtualWrite(V9, value);
  Serial.println(sensorValue);
  Serial.println(value);
  if (sensorValue > 20)
  {
    Blynk.logEvent("gas_alert","Gas Leakage Detected"); //
    digitalWrite(RED, HIGH);
    digitalWrite(BUZZER, HIGH);
  }
  else
  {
    digitalWrite(RED, LOW);
    digitalWrite(BUZZER, LOW);
  }
  //------------------------
  if (value <= 20)
  {
    digitalWrite(led, HIGH);
  } 
  else 
  {
    digitalWrite(led, LOW);
  }
  timer.setInterval(100L, checkPhysicalButton);
}
void loop()
{
  Blynk.run();
  timer.run();
}
void checkPhysicalButton()
{
  if (digitalRead(btnPin1) == LOW) {
    if (btnState1 != LOW) {
      led1.off();
      // Toggle LED state
      ledState1 = !ledState1;
      digitalWrite(ledPin1, ledState1);
      // Update Button Widget
      Blynk.virtualWrite(V2, ledState1);
      if(ledState1 == HIGH)
      {
        led1.on();
      }
      else{
        led1.off();
      }
    }
    btnState1 = LOW;
  } else {
    btnState1 = HIGH;
  }
  //-------------------------------
  if (digitalRead(btnPin2) == LOW) {
    if (btnState2 != LOW) {
      led2.off();
      // Toggle LED state
      ledState2 = !ledState2;
      digitalWrite(ledPin2, ledState2);
      // Update Button Widget
      Blynk.virtualWrite(V4, ledState2);
      if(ledState2 == HIGH)
      {
        led2.on();
      }
      else{
        led2.off();
      }
    }
    btnState2 = LOW;
  } else {
    btnState2 = HIGH;
  }
  //-------------------------------
  if (digitalRead(btnPin3) == LOW) {
    if (btnState3 != LOW) {
      led3.off();
      // Toggle LED state
      ledState3 = !ledState3;
      digitalWrite(ledPin3, ledState3);
      // Update Button Widget
      Blynk.virtualWrite(V6, ledState3);
      if(ledState3 == HIGH)
      {
        led3.on();
      }
      else{
        led3.off();
      }
    }
    btnState3 = LOW;
  } else {
    btnState3 = HIGH;
  }
  //-------------------------------
  if (digitalRead(btnPin4) == LOW) {
    if (btnState4 != LOW) {
      led4.off();

      // Toggle LED state
      ledState4 = !ledState4;
      digitalWrite(ledPin4, ledState4);

      // Update Button Widget
      Blynk.virtualWrite(V8, ledState4);

      if(ledState4 == HIGH)
      {
        led4.on();
      }
      else{
        led4.off();
      }
    }
    btnState4 = LOW;
  } else {
    btnState4 = HIGH;
  }
}
