#include "Interrupts.h"
#include "Motor.h"
#include "Follow.h"
#include "EnableInterrupt.h"
#include "MsTimer2.h"

unsigned long Motor::encoder_count_right_a;
unsigned long Motor::encoder_count_left_a;

//Getting Right Wheel Speed.
void EncoderCountRightA()
{
  Motor::encoder_count_right_a++;
}
//Getting Left Wheel Speed.
void EncoderCountLeftA()
{
  Motor::encoder_count_left_a++;
}



unsigned char IR::left_receive_flag;
unsigned char IR::right_receive_flag;
int IR::left_is_obstacle;
int IR::right_is_obstacle;
unsigned int IR::left_count;
unsigned int IR::right_count;


void IR::Left_Receive()
{ 
   left_is_obstacle=1;
}

void IR::Right_Receive()
{ 
   right_is_obstacle=2;
}


void Ultrasonic::Distance_Measure()
{
  if (measure_flag == 0)
  {
    measure_prev_time = micros();
    enableInterrupt(ECHO_PIN, Distance_Measure, FALLING);
    measure_flag = 1;
  }
  else if (measure_flag == 1)
  {
    distance_value = (micros() - measure_prev_time) * 0.017; //340.29 m/s / 2 -> (340.29*100 cm) /(1000*1000 us) / 2 = 0.0170145
    measure_flag = 2;//Serial.println(distance_value);
  }
}

// Initialize all interrupts her
void EnableMotorInterrupts() {
  // Motor encoder interrupts
  enableInterrupt(ENCODER_LEFT_A_PIN, EncoderCountLeftA, CHANGE);
  enableInterrupt(ENCODER_RIGHT_A_PIN, EncoderCountRightA, CHANGE);
}

void EnableIRInterrupts() {
  // IR interrupts
  enableInterrupt(LEFT_RECEIVE_PIN, IR::Left_Receive, FALLING);
  enableInterrupt(RIGHT_RECEIVE_PIN, IR::Right_Receive, FALLING);
}

void EnableUltrasonicInterrupts() {
    enableInterrupt(ECHO_PIN, Ultrasonic::Distance_Measure, RISING);
}