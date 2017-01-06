#pragma once

#pragma once

#include <math.h>
#define PI 3.14159265358979323846264338327950288419716939937510
#define DegToRad(deg) (deg * PI / 180)
#define RadToDeg(rad) (rad * 180 / PI)
#define Clamp(value, min, max) ((value < min ? min : value) > max ? max : value)