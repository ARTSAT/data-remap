/* port from oF */

#ifndef PI
#define PI       (3.14159265358979323846)
#endif

#ifndef TWO_PI
#define TWO_PI   (6.28318530717958647693)
#endif

#ifndef M_TWO_PI
#define M_TWO_PI   (6.28318530717958647693)
#endif

#ifndef FOUR_PI
#define FOUR_PI (12.56637061435917295385)
#endif

#ifndef HALF_PI
#define HALF_PI  (1.57079632679489661923)
#endif

#ifndef DEG_TO_RAD
#define DEG_TO_RAD (PI/180.0)
#endif

#ifndef RAD_TO_DEG
#define RAD_TO_DEG (180.0/PI)
#endif

#ifndef MIN
#define MIN(x,y) (((x) < (y)) ? (x) : (y))
#endif

#ifndef MAX
#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#endif

#ifndef CLAMP
#define CLAMP(val,min,max) (MAX(MIN(val,max),min))
#endif

#ifndef ABS
#define ABS(x) (((x) < 0) ? -(x) : (x))
#endif


// notes:
// -----------------------------------------------------------
// for fast things look here: http://musicdsp.org/archive.php?classid=5#115
// -----------------------------------------------------------
// the random () calls are based on misconceptions described here:
// http://www.azillionmonkeys.com/qed/random.html
// (Bad advice from C.L.C. FAQ)
// we should correct this --
// -----------------------------------------------------------

#pragma once

#include <vector>

#include "flVec4f.h"
#include "flCommon.h"

FL_NAMESPACE_BEGIN

int 		nextPow2 ( int a );
void        seedRandom();
void 		seedRandom(int val);
float       random(float max);                  // random (0 - max)
float 		random(float val0, float val1);		// random (x - y)
float 		randomf();							// random (-1 - 1)
float 		randomuf();							// random (0 - 1)
Vec3f       randVec3f();

float		normalize(float value, float min, float max);
float		map(float value,
                float inputMin,
                float inputMax,
                float outputMin,
                float outputMax,
                bool clamp = false);
float		clamp(float value, float min, float max);
float		lerp(float start, float stop, float amt);
float		dist(float x1, float y1, float x2, float y2);
float		distSquared(float x1, float y1, float x2, float y2);
int			sign(float n);
bool		inRange(float t, float min, float max);

float		radToDeg(float radians);
float		degToRad(float degrees);
float 		lerpDegrees(float currentAngle, float targetAngle, float pct);
float 		lerpRadians(float currentAngle, float targetAngle, float pct);
float 		angleDifferenceDegrees(float currentAngle, float targetAngle);
float 		angleDifferenceRadians(float currentAngle, float targetAngle);
float 		angleSumRadians(float currentAngle, float targetAngle);
float		wrapRadians(float angle, float from = -PI, float to=+PI);
float		wrapDegrees(float angle, float from = -180, float to=+180);

//returns noise in 0.0 to 1.0 range
float		noise(float x);
float		noise(float x, float y);
float		noise(float x, float y, float z);
float		noise(float x, float y, float z, float w);

//returns noise in -1.0 to 1.0 range
float		signedNoise(float x);
float		signedNoise(float x, float y);
float		signedNoise(float x, float y, float z);
float		signedNoise(float x, float y, float z, float w);

bool 		lineSegmentIntersection(Vec4f line1Start,
                                    Vec4f line1End,
                                    Vec4f line2Start,
                                    Vec4f line2End,
                                    Vec4f & intersection);

Vec4f 	bezierVec4f( Vec4f a, Vec4f b, Vec4f c, Vec4f d, float t);
Vec4f 	curveVec4f( Vec4f a, Vec4f b, Vec4f c, Vec4f d, float t);
Vec4f 	bezierTangent( Vec4f a, Vec4f b, Vec4f c, Vec4f d, float t);
Vec4f 	curveTangent( Vec4f a, Vec4f b, Vec4f c, Vec4f d, float t);

template<class T>
T lerp(T x0, T x1, float t)
{
    return x0*t + x1*(1.f-t);
}

FL_NAMESPACE_END
