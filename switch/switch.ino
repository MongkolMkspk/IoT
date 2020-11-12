#define sw1 D4
#define sw2 D5
#define led1 D6
#define led2 D7
int st_sw1 = 0;
int st_sw2 = 0;
int st_1 = 0;
int st_2 = 0;
int last_st_sw1 = 1;
int last_st_sw2 = 1;
void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(sw1, INPUT);
  pinMode(sw2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  st_sw1 = digitalRead(sw1);
  if ((st_sw1 == 0) && (last_st_sw1 == 1)) {
    st_1 = ~st_1;
    digitalWrite(led1, st_1);
    delay(250);
  }
  last_st_sw1 = st_sw1;

  st_sw2 = digitalRead(sw2);
  if ((st_sw2 == 1) && (last_st_sw2 == 0)) {
    st_2 = ~st_2;
    digitalWrite(led2, st_2);
    delay(250);
  }
  last_st_sw2 = st_sw2;
}
