void setup() {
  // put your setup code here, to run once:
  pinMode(16,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(2,OUTPUT);
  boolean a=true;
}

void loop() {
  // put your main code here, to run repeatedly:
  static int i=1;
  if(i>3){
    i=1;
  }
  else if(i%2==0){
    digitalWrite(14,HIGH);//red
    digitalWrite(16,LOW);//green
    digitalWrite(2,LOW);//yellow
  }
  else if(i%3==0){
    digitalWrite(14,LOW);
    digitalWrite(16,LOW);
    digitalWrite(2,HIGH);
  }
  else{
    digitalWrite(14,LOW);
    digitalWrite(16,HIGH);
    digitalWrite(2,LOW);
  }
  i+=1;
  delay(1000);
  
}
