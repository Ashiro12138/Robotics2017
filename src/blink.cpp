
#include <Arduino.h>

#define LEG_BUILTIN 13

float t = 500.0;

void setup(){
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN,HIGH);
  delay(t);
  digitalWrite(LED_BUILTIN,LOW);
  delay(t);
  if(t==50.0){
    for (int i = 0; i < 15; i++) {
      digitalWrite(LED_BUILTIN,HIGH);
      delay(t);
      digitalWrite(LED_BUILTIN,LOW);
      delay(t);
    }
    t = 500.0;
  }else{
    t -= 50.0;
  }
}
