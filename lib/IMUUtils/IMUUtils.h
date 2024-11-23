#ifndef IMU_UTILS_H
#define IMU_UTILS_H

#include <Wire.h>
#include <MPU6050.h>

class IMUUtils {
public:
    static float getTiltAngle(int16_t ax, int16_t az);
};

#endif // IMU_UTILS_H
