#include <avr/sleep.h>//this AVR library contains the methods that controls the sleep modes
#define interruptPin 2

void setup() {
  Serial.begin(115200);//Start Serial Comunication
  pinMode(LED_BUILTIN, OUTPUT); //We use the led on pin 13 to indecate when Arduino is A sleep
  pinMode(interruptPin, INPUT_PULLUP); //Set pin d2 to input using the buildin pullup resistor
  digitalWrite(LED_BUILTIN, HIGH); //turning LED on
}

void loop() {
  Serial.println("Doing the things you know");//next line of code executed after the interrupt
  digitalWrite(LED_BUILTIN, HIGH); //turning LED on
  delay(5000);//wait 5 seconds before going to sleep
  Going_To_Sleep();
}

void Going_To_Sleep() {
  Serial.println("Sleeping now...");
  sleep_enable();//Enabling sleep mode
  attachInterrupt(0, wakeUp, LOW);//attaching a interrupt to pin d2
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);//Setting the sleep mode, in our case full sleep
  digitalWrite(LED_BUILTIN, LOW); //turning LED off
  delay(1000); //wait a second to allow the led to be turned off before going to sleep
  sleep_cpu();//activating sleep mode
}

void wakeUp() {
  //Serial.println("Waking up!");//Print message to serial monitor
  sleep_disable();//Disable sleep mode
  detachInterrupt(0); //Removes the interrupt from pin 2;
}
