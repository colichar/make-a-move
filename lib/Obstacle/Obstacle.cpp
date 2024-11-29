#include "Obstacle.h"
#include "MsTimer2.h"
#include "KalmanFilter.h"
#include "Interrupts.h"

IR IR;
Ultrasonic Ultrasonic;
extern Balanced Balanced;
extern Mpu6050 Mpu6050;

void Ultrasonic::Pin_init()
{
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
}


char Ultrasonic ::measure_flag = 0;
unsigned long Ultrasonic ::measure_prev_time = 0;
double Ultrasonic ::distance_value;

void Function::Obstacle_Mode()
{
  IR.Send();
  Ultrasonic.Get_Distance();

  if (millis() - follow_prev_time >= 100)
  {
    follow_prev_time = millis();
    Balanced.Motion_Control(FORWARD);

    while (OBSTACLE_JUDAGEMENT)
    {
      Balanced.Motion_Control(STOP);

      if (millis() - Obstacle_time > 5000)
      { 
        Obstacle_time = millis();
        Back_time = millis();
        while (millis() - Back_time < 500)
        {
          Balanced.Motion_Control(BACK);
        }
      }

      Turning_Time = millis();
      while (millis() - Turning_Time < 750)
      {
        if (turn_flag)
        { turn_flag = 0;
          IR.Check();
        }
      }
      turn_flag = 1;


      Ultrasonic.Get_Distance();
    }

  }
    Obstacle_time = millis();
}

void IR::Pin_init()
{
  pinMode(LEFT_RECEIVE_PIN, INPUT_PULLUP);
  pinMode(RIGHT_RECEIVE_PIN, INPUT_PULLUP);
  pinMode(IR_SEND_PIN, OUTPUT);
  EnableIRInterrupts();   
}

void Ultrasonic::Get_Distance()
{
  if (millis() - get_distance_prev_time > 50)
  { 
    delayMicroseconds(1);
    get_distance_prev_time = millis();
    measure_flag = 0;
    EnableUltrasonicInterrupts();
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
  }
}

void IR::Check()
{
  int motion = left_is_obstacle + right_is_obstacle;
  switch (motion)
  {
    case Meet_OBSTACLE: Balanced.Motion_Control(LEFT);
      left_is_obstacle = 0; break;

    case FOLLOW_RIGHT:
      Balanced.Motion_Control(RIGHT);
      left_is_obstacle = 0; break;

    case FOLLOW_LEFT:
      Balanced.Motion_Control(LEFT);
      right_is_obstacle = 0; break;

    case FOLLOW_BACK:
      Balanced.Motion_Control(LEFT);
      right_is_obstacle = 0;
      left_is_obstacle = 0; break;
  }

}

void IR::Send()
{
  static unsigned long ir_send_time;

  if (millis() - ir_send_time > 15)
  {
    for (int i = 0; i < 39; i++)
    {
      digitalWrite(IR_SEND_PIN, LOW);
      delayMicroseconds(9);
      digitalWrite(IR_SEND_PIN, HIGH);
      delayMicroseconds(9);
    }
    ir_send_time = millis();
  }
}
