#ifndef _MATH_UTIL_H_
#define _MATH_UTIL_H_

#include <cmath>

#ifndef M_PI
 #define M_PI 3.14159265358979323846
#endif

#define DEG2RAD(angle) angle * ((float)M_PI/180.f)
#define RAD2DEG(angle) angle * (180.0f/(float)M_PI)

#endif
