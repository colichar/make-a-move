#include "Motor.h"
#include "EnableInterrupt.h"



void Motor::Encoder_init()
{
  enableInterrupt(ENCODER_LEFT_A_PIN, EncoderCountLeftA, CHANGE);
  enableInterrupt(ENCODER_RIGHT_A_PIN, EncoderCountRightA, CHANGE);
}

unsigned long Motor::encoder_count_right_a;
//Getting right wheel speed.
static void Motor::EncoderCountRightA()
{
  Motor::encoder_count_right_a++;
}


unsigned long Motor::encoder_count_left_a;
//Getting left wheel speed.
static void Motor::EncoderCountLeftA()
{
  Motor::encoder_count_left_a++;
}
