#define PIN_LED 7

unsigned int toggle, x;

void setup() {
  pinMode(PIN_LED,OUTPUT);
  Serial.begin(115200);
  while(!Serial){
    ;
  }
  toggle=1;
  delay(1000);
  for(x=0; x<6;x++){
  digitalWrite(PIN_LED, 0);
  delay (200);
  digitalWrite(PIN_LED, 1);
  delay (200);
  }

  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
