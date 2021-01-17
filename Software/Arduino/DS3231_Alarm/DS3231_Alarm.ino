#include <RTClib.h>

RTC_DS3231 rtc;

#define CLOCK_INTERRUPT_PIN 2

void setup() {
  Serial.begin(9600);

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC!");
    Serial.flush();
    abort();
  }
  
  rtc.disable32K();

  pinMode(CLOCK_INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(CLOCK_INTERRUPT_PIN), onAlarm, FALLING);
 
  rtc.clearAlarm(1);
  rtc.clearAlarm(2);
  
  rtc.writeSqwPinMode(DS3231_OFF);
  rtc.disableAlarm(2);

  if (!rtc.setAlarm1(rtc.now() + TimeSpan(10),DS3231_A1_Second)) 
  {
    Serial.println("Error, alarm wasn't set!");
  } else 
  {
    Serial.println("Alarm will happen in 10 seconds!");
  }
}

void loop() {

  char date[10] = "hh:mm:ss";
  rtc.now().toString(date);
  Serial.print(date);

  Serial.print(" SQW: ");
  Serial.print(digitalRead(CLOCK_INTERRUPT_PIN));

  Serial.print(" Alarm1: ");
  Serial.print(rtc.alarmFired(1));
  Serial.println("");

  if (rtc.alarmFired(1)) {
    rtc.clearAlarm(1);
    
    //rtc.setAlarm1(rtc.now() + TimeSpan(4),DS3231_A1_Second);
    
    //rtc.disableAlarm(1);
    Serial.println("Alarm cleared");
    rtc.writeSqwPinMode(DS3231_SquareWave1Hz);
  }

  delay(1000);
}

void onAlarm() {
  Serial.println("Alarm occured!");
}
