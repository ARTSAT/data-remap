/* port from oF */

#include "flMath.h"
#include "float.h"
#include "flNoise.h"
#include "flVec3f.h"

#include <sys/time.h>

#ifndef TARGET_WIN32
#include <unistd.h>
#endif

using namespace fl;

//--------------------------------------------------
int fl::nextPow2(int a){
	// from nehe.gamedev.net lesson 43
	int rval=1;
	while(rval<a) rval<<=1;
	return rval;
}

void fl::seedRandom() {
    
    // good info here:
    // http://stackoverflow.com/questions/322938/recommended-way-to-initialize-srand
    
#ifdef TARGET_WIN32
    srand(GetTickCount());
#else
    // use XOR'd second, microsecond precision AND pid as seed
    struct timeval tv;
    gettimeofday(&tv, 0);
    long int n = (tv.tv_sec ^ tv.tv_usec) ^ getpid();
    srand((unsigned int)n);
#endif
}


//--------------------------------------------------
void fl::seedRandom(int val) {
	srand((unsigned int) val);
}

//--------------------------------------------------
float fl::random(float max) {
	return max * rand() / (RAND_MAX + 1.0f);
}

//--------------------------------------------------
float fl::random(float x, float y) {

	float high = 0;
	float low = 0;
	float randNum = 0;
	// if there is no range, return the value
	if (x == y) return x; 			// float == ?, wise? epsilon?
	high = MAX(x,y);
	low = MIN(x,y);
	randNum = low + ((high-low) * rand()/(RAND_MAX + 1.0));
	return randNum;
}

//--------------------------------------------------
float fl::randomf() {
	float randNum = 0;
	randNum = (rand()/(RAND_MAX + 1.0)) * 2.0 - 1.0;
	return randNum;
}

//--------------------------------------------------
float fl::randomuf() {
	float randNum = 0;
	randNum = rand()/(RAND_MAX + 1.0);
	return randNum;
}

Vec3f fl::randVec3f()
{
    const float phi = fl::random((float)M_PI * 2.0f);
    const float costheta = fl::random(-1.0f, 1.0f);
    
    const float rho = ::sqrt(1.0f - costheta * costheta);
    const float x = rho * ::cos(phi);
    const float y = rho * ::sin(phi);
    const float z = costheta;
    
    return Vec3f(x, y, z);
}

//---- new to 006
//from the forums http://www.openframeworks.cc/forum/viewtopic.php?t=1413

//--------------------------------------------------
float fl::normalize(float value, float min, float max){
	return clamp( (value - min) / (max - min), 0, 1);
}

//check for division by zero???
//--------------------------------------------------
float fl::map(float value, float inputMin, float inputMax, float outputMin, float outputMax, bool clamp) {

	if (fabs(inputMin - inputMax) < FLT_EPSILON){
		return outputMin;
	} else {
		float outVal = ((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin);
	
		if( clamp ){
			if(outputMax < outputMin){
				if( outVal < outputMax )outVal = outputMax;
				else if( outVal > outputMin )outVal = outputMin;
			}else{
				if( outVal > outputMax )outVal = outputMax;
				else if( outVal < outputMin )outVal = outputMin;
			}
		}
		return outVal;
	}

}

//--------------------------------------------------
float fl::dist(float x1, float y1, float x2, float y2) {
	return sqrt(double((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

//--------------------------------------------------
float fl::distSquared(float x1, float y1, float x2, float y2) {
	return ( (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) );
}

//--------------------------------------------------
float fl::clamp(float value, float min, float max) {
	return value < min ? min : value > max ? max : value;
}

// return sign  the number
//--------------------------------------------------
int fl::sign(float n) {
	if( n > 0 ) return 1;
	else if(n < 0) return -1;
	else return 0;
}

//--------------------------------------------------
bool fl::inRange(float t, float min, float max) {
	return t>=min && t<=max;
}

//--------------------------------------------------
float fl::radToDeg(float radians) {
	return radians * RAD_TO_DEG;
}

//--------------------------------------------------
float fl::degToRad(float degrees) {
    return degrees * DEG_TO_RAD;
}

//--------------------------------------------------
float fl::lerp(float start, float stop, float amt) {
	return start + (stop-start) * amt;
}

//--------------------------------------------------
float fl::wrapRadians(float angle, float from, float to){
	while (angle > to ) angle -= TWO_PI;
	while (angle < from ) angle += TWO_PI;
	return angle;
}


float fl::wrapDegrees(float angle, float from, float to){
	while (angle > to ) angle-=360;
	while (angle < from ) angle+=360;
	return angle;

}

//--------------------------------------------------
float fl::lerpDegrees(float currentAngle, float targetAngle, float pct) {
    return currentAngle + angleDifferenceDegrees(currentAngle,targetAngle) * pct;
}

//--------------------------------------------------
float fl::lerpRadians(float currentAngle, float targetAngle, float pct) {
	return currentAngle + angleDifferenceRadians(currentAngle,targetAngle) * pct;
}

//--------------------------------------------------
float fl::noise(float x){
	return _slang_library_noise1(x)*0.5f + 0.5f;
}

//--------------------------------------------------
float fl::noise(float x, float y){
	return _slang_library_noise2(x,y)*0.5f + 0.5f;
}

//--------------------------------------------------
float fl::noise(float x, float y, float z){
	return _slang_library_noise3(x,y,z)*0.5f + 0.5f;
}

//--------------------------------------------------
float fl::noise(float x, float y, float z, float w){
	return _slang_library_noise4(x,y,z,w)*0.5f + 0.5f;
}

//--------------------------------------------------
float fl::signedNoise(float x){
	return _slang_library_noise1(x);
}

//--------------------------------------------------
float fl::signedNoise(float x, float y){
	return _slang_library_noise2(x,y);
}

//--------------------------------------------------
float fl::signedNoise(float x, float y, float z){
	return _slang_library_noise3(x,y,z);
}

//--------------------------------------------------
float fl::signedNoise(float x, float y, float z, float w){
	return _slang_library_noise4(x,y,z,w);
}


//--------------------------------------------------
bool fl::lineSegmentIntersection(Vec4f line1Start, Vec4f line1End, Vec4f line2Start, Vec4f line2End, Vec4f & intersection){
	Vec4f diffLA, diffLB;
	float compareA, compareB;
	diffLA = line1End - line1Start;
	diffLB = line2End - line2Start;
	compareA = diffLA.x*line1Start.y - diffLA.y*line1Start.x;
	compareB = diffLB.x*line2Start.y - diffLB.y*line2Start.x;
	if (
		(
			( ( diffLA.x*line2Start.y - diffLA.y*line2Start.x ) < compareA ) ^
			( ( diffLA.x*line2End.y - diffLA.y*line2End.x ) < compareA )
		)
		&&
		(
			( ( diffLB.x*line1Start.y - diffLB.y*line1Start.x ) < compareB ) ^
			( ( diffLB.x*line1End.y - diffLB.y*line1End.x) < compareB )
		)
	)
	{
		float lDetDivInv = 1 / ((diffLA.x*diffLB.y) - (diffLA.y*diffLB.x));
		intersection.x =  -((diffLA.x*compareB) - (compareA*diffLB.x)) * lDetDivInv ;
		intersection.y =  -((diffLA.y*compareB) - (compareA*diffLB.y)) * lDetDivInv ;

		return true;
	}

	return false;
}

//--------------------------------------------------
Vec4f fl::bezierVec4f( Vec4f a, Vec4f b, Vec4f c, Vec4f d, float t){
    float tp = 1.0 - t;
    return a*tp*tp*tp + b*3*t*tp*tp + c*3*t*t*tp + d*t*t*t;
}

//--------------------------------------------------
Vec4f fl::curveVec4f( Vec4f a, Vec4f b, Vec4f c, Vec4f d, float t){
    Vec4f pt;
    float t2 = t * t;
    float t3 = t2 * t;
    pt.x = 0.5f * ( ( 2.0f * b.x ) +
                   ( -a.x + c.x ) * t +
                   ( 2.0f * a.x - 5.0f * b.x + 4 * c.x - d.x ) * t2 +
                   ( -a.x + 3.0f * b.x - 3.0f * c.x + d.x ) * t3 );
    pt.y = 0.5f * ( ( 2.0f * b.y ) +
                   ( -a.y + c.y ) * t +
                   ( 2.0f * a.y - 5.0f * b.y + 4 * c.y - d.y ) * t2 +
                   ( -a.y + 3.0f * b.y - 3.0f * c.y + d.y ) * t3 );
    return pt;
}

//--------------------------------------------------
Vec4f fl::bezierTangent( Vec4f a, Vec4f b, Vec4f c, Vec4f d, float t){
    return (d-a-c*3+b*3)*(t*t)*3 + (a+c-b*2)*t*6 - a*3+b*3;
}

//--------------------------------------------------
Vec4f fl::curveTangent( Vec4f a, Vec4f b, Vec4f c, Vec4f d, float t){
    Vec4f v0 = ( c - a )*0.5;
    Vec4f v1 = ( d - b )*0.5;
    return ( b*2 -c*2 + v0 + v1)*(3*t*t) + ( c*3 - b*3 - v1 - v0*2 )*( 2*t) + v0;

}

//--------------------------------------------------
float fl::angleDifferenceDegrees(float currentAngle, float targetAngle) {
	return wrapDegrees(targetAngle - currentAngle);
}

//--------------------------------------------------
float fl::angleDifferenceRadians(float currentAngle, float targetAngle) {
	return  wrapRadians(targetAngle - currentAngle);
}
