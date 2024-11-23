#include <Wire.h>
#include <MPU6050.h>
#include <PID_v1.h>
#include "IMUUtils.h"

// MPU6050 instance
MPU6050 mpu;

// PID parameters
double setpoint = 0;    // Desired tilt angle (upright position)
double input = 0;       // Current tilt angle
double output = 0;      // PID output for motor control
double Kp = 2.0, Ki = 0.5, Kd = 1.0; // PID coefficients

// PID controller instance
PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

// Motor control pins
#define MOTOR_LEFT_PWM 5
#define MOTOR_RIGHT_PWM 6
#define MOTOR_LEFT_DIR 7
#define MOTOR_RIGHT_DIR 8

void controlMotors(double pidOutput) {
    if (pidOutput > 0) {
        // Move forward
        analogWrite(MOTOR_LEFT_PWM, pidOutput);
        analogWrite(MOTOR_RIGHT_PWM, pidOutput);
        digitalWrite(MOTOR_LEFT_DIR, HIGH);
        digitalWrite(MOTOR_RIGHT_DIR, HIGH);
    } else {
        // Move backward
        pidOutput = -pidOutput; // Make the value positive
        analogWrite(MOTOR_LEFT_PWM, pidOutput);
        analogWrite(MOTOR_RIGHT_PWM, pidOutput);
        digitalWrite(MOTOR_LEFT_DIR, LOW);
        digitalWrite(MOTOR_RIGHT_DIR, LOW);
    }
}

void setup() {
    // Initialize serial communication
    Serial.begin(9600);

    // Initialize I2C communication and MPU6050
    Wire.begin();
    mpu.initialize();
    if (!mpu.testConnection()) {
        Serial.println("MPU6050 connection failed!");
        while (1);
    }

    // Initialize PID controller
    myPID.SetMode(AUTOMATIC);
    myPID.SetOutputLimits(-255, 255); // Output range for PWM

    // Configure motor control pins
    pinMode(MOTOR_LEFT_PWM, OUTPUT);
    pinMode(MOTOR_RIGHT_PWM, OUTPUT);
    pinMode(MOTOR_LEFT_DIR, OUTPUT);
    pinMode(MOTOR_RIGHT_DIR, OUTPUT);
}

void loop() {
    int16_t ax, ay, az, gx, gy, gz;

    // Get motion data from MPU6050
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // Calculate tilt angle
    input = IMUUtils::getTiltAngle(ax, az);

    // Compute PID output
    myPID.Compute();

    // Apply PID output to motors
    controlMotors(output);

    // Debugging: Print the angle and PID output
    Serial.print("Tilt Angle: ");
    Serial.print(input);
    Serial.print(" | PID Output: ");
    Serial.println(output);

    delay(10);
}
