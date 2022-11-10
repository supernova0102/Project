 #include <Servo.h>

// Arduino pin assignment
#define PIN_LED 9
#define PIN_POTENTIOMETER 0 // Potentiometer at Pin A3

// Add IR Sensor Definition Here !!!
#define PIN_SERVO 10
#define _DIST_MIN 100     // minimum distance to be measured (unit: mm)
#define _DIST_MAX 250 
#define _DUTY_MIN 550  // servo full clock-wise position (0 degree)
#define _DUTY_NEU 1475 // servo neutral position (90 degree)
#define _DUTY_MAX 2400 // servo full counter-clockwise position (180 degree)

#define LOOP_INTERVAL 20   // Loop Interval (unit: msec)
#define _EMA_ALPHA 0.2 

float dist_prev = _DIST_MAX;        // Distance last-measured
float dist_ema;       
Servo myservo;
unsigned long last_loop_time;   // unit: msec

void setup()
{
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);
  pinMode(PIN_LED,OUTPUT);
  Serial.begin(1000000);
}

void loop()
{
  unsigned long time_curr = millis();
  int a_value, duty;
  int dist;
  a_value = analogRead(PIN_POTENTIOMETER);
  // wait until next event time
  if (time_curr < (last_loop_time + LOOP_INTERVAL))
    return;
  last_loop_time += LOOP_INTERVAL;
  
  // Modify the below line to implement the EMA equation
  dist = (6762.0/(a_value-9)-4.0)*10.0- 65.0;
  
  
  
  
  if (dist < _DIST_MIN) {
    dist= dist_prev;
    digitalWrite(PIN_LED, 0);// Set Lower Value
         // LED OFF
  } else if (dist> _DIST_MAX) {
    dist = dist_prev; 
    digitalWrite(PIN_LED, 0);// Set Higher Value
           // LED OFF
  } else {    // In desired Range
         // LED ON      
    dist_prev = dist;
    digitalWrite(PIN_LED, 1);
  }
  // Remove Next line !!!
  // Read IR Sensor value !!!
  // Convert IR sensor value into distance !!!
  // we need distance range filter here !!!
  // we need EMA filter here !!!

  dist_ema = _EMA_ALPHA*dist +(1-_EMA_ALPHA)*dist_ema;
  
  // map distance into duty
 if(dist_ema <= 100){
  duty = _DUTY_MIN;
    myservo.writeMicroseconds(duty);
//    digitalWrite(PIN_LED, 1);
}else if(dist_ema > 100 && dist_ema< 250){
  duty = _DUTY_MIN + (dist_ema-100)/150*1850;
  myservo.writeMicroseconds(duty);
//  digitalWrite(PIN_LED, 0);
    }else if(dist_ema >= 250){
    duty = _DUTY_MAX;
    myservo.writeMicroseconds(duty);
//    digitalWrite(PIN_LED, 1);
}

 
  last_loop_time += LOOP_INTERVAL;
  // print IR sensor value, distnace, duty !!!
  Serial.print("Min:"); Serial.print(_DIST_MIN);
  Serial.print(", IR:"); Serial.print(a_value);
  Serial.print(", dist:"); Serial.print(dist);
  Serial.print(", ema:"); Serial.print(dist_ema);
  Serial.print(", Servo:"); Serial.print(duty);
  Serial.print(",Max:"); Serial.print(_DIST_MAX);
  Serial.println("");
}
