#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <Arduino.h>

void EncoderCountRightA();
void EncoderCountLeftA();
void Left_Receive();
void Right_Receive();
void Distance_Measure();

void EnableMotorInterrupts();
void EnableIRInterrupts();
void EnableUltrasonicInterrupts();

#endif