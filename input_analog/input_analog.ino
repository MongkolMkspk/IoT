#include <stdio.h>
#define ANALOG_PIN A0
int analogValue =0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int temp ;
  char str[5];
  analogValue = analogRead(ANALOG_PIN);
  temp = analogValue *3.3 /1023*1000;
  sprintf(str,"%4d",temp);
  Serial.print("Analog input0 = ");
  if(str[0]==' ')Serial.print("0");
  else Serial.print(str[0]);
  Serial.print(".");
  if(str[1]==' ')Serial.print("0");
  else Serial.print(str[1]);
  if(str[2]==' ')Serial.print("0");
  else Serial.print(str[2]);
  Serial.print(str[3]);
  Serial.println(" Volt");
  /*analogValue = analogRead(ANALOG_PIN); 
  Serial.print("Analog input0 = ");
  Serial.println(analogValue);//can't use (" "+value)*/
  delay(500);
}
