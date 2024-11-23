#include "IMUUtils.h"
#include <math.h> // For atan2 and PI

float IMUUtils::getTiltAngle(int16_t ax, int16_t az) {
    return atan2(ax, az) * 180 / M_PI;
}
