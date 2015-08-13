/* port from of */
//
//  flUtils.cpp
//  flTinyGLUtils
//
//  Created by Onishi Yoshito on 10/29/13.
//  Copyright (c) 2013 Onishi Yoshito. All rights reserved.
//

#include "flUtils.h"
#include "flCommon.h"
#include "flMath.h"

#ifdef TARGET_WIN32
#ifndef _MSC_VER
#include <unistd.h> // this if for MINGW / _getcwd
#include <sys/param.h> // for MAXPATHLEN
#endif
#endif

#if defined(TARGET_IOS) || defined(TARGET_OSX ) || defined(TARGET_LINUX)
#include <sys/time.h>
#include <cxxabi.h>
#endif

#ifdef TARGET_OSX
#ifndef TARGET_IOS
#include <mach-o/dyld.h>
#include <sys/param.h> // for MAXPATHLEN
#endif
#endif

#ifdef TARGET_WIN32
#include <mmsystem.h>
#ifdef _MSC_VER
#include <direct.h>
#endif

#endif

using namespace std;

FL_NAMESPACE_BEGIN

struct _handle {
    char* p;
    _handle(char* ptr) : p(ptr) {}
    ~_handle() { std::free(p); }
};

string demangle(const char* name)
{
    int status{-4};
    
    _handle result(abi::__cxa_demangle(name, nullptr, nullptr, &status));
    
    return (status==0) ? result.p : name;
}

void hsbToRgb(float hue, float saturation, float brightness, float* r, float* g, float* b)
{
	saturation = clamp(saturation, 0.f, 1.f);
	brightness = clamp(brightness, 0.f, 1.f);
	if(brightness == 0.f) { // black
        *r = *g = *b = 0.f;
	} else if(saturation == 0.f) { // grays
        *r = *g = *b = brightness;
	} else {
		float hueSix = hue * 6. / 1.f;
		float saturationNorm = saturation / 1.f;
		int hueSixCategory = (int) floorf(hueSix);
		float hueSixRemainder = hueSix - hueSixCategory;
		float pv = (1.f - saturationNorm) * brightness;
		float qv = (1.f - saturationNorm * hueSixRemainder) * brightness;
		float tv = (1.f - saturationNorm * (1.f - hueSixRemainder)) * brightness;
		switch(hueSixCategory) {
			case 0: case 6: // r
				*r = brightness;
				*g = tv;
				*b = pv;
				break;
			case 1: // g
				*r = qv;
				*g = brightness;
				*b = pv;
				break;
			case 2:
				*r = pv;
				*g = brightness;
				*b = tv;
				break;
			case 3: // b
				*r = pv;
				*g = qv;
				*b = brightness;
				break;
			case 4:
				*r = tv;
				*g = pv;
				*b = brightness;
				break;
			case 5: // back to r
				*r = brightness;
				*g = pv;
				*b = qv;
				break;
		}
	}
}

static unsigned long long startTime = GetSystemTime();   //  better at the first frame ?? (currently, there is some delay from static init, to running.
static unsigned long long startTimeMicros = GetSystemTimeMicros();

//--------------------------------------
unsigned long long GetElapsedTimeMillis(){
	return GetSystemTime() - startTime;
}

//--------------------------------------
unsigned long long GetElapsedTimeMicros(){
	return GetSystemTimeMicros() - startTimeMicros;
}

//--------------------------------------
float GetElapsedTimef(){
	return GetElapsedTimeMicros() / 1000000.0f;
}

//--------------------------------------
void ResetElapsedTimeCounter(){
	startTime = GetSystemTime();
	startTimeMicros = GetSystemTimeMicros();
}

//=======================================
// this is from freeglut, and used internally:
/* Platform-dependent time in milliseconds, as an unsigned 32-bit integer.
 * This value wraps every 49.7 days, but integer overflows cancel
 * when subtracting an initial start time, unless the total time exceeds
 * 32-bit, where the GLUT API return value is also overflowed.
 */
unsigned long long GetSystemTime( ) {
#ifndef TARGET_WIN32
    struct timeval now;
    gettimeofday( &now, NULL );
    return
    (unsigned long long) now.tv_usec/1000 +
    (unsigned long long) now.tv_sec*1000;
#else
#if defined(_WIN32_WCE)
    return GetTickCount();
#else
    return timeGetTime();
#endif
#endif
}

unsigned long long GetSystemTimeMicros( ) {
#ifndef TARGET_WIN32
    struct timeval now;
    gettimeofday( &now, NULL );
    return
    (unsigned long long) now.tv_usec +
    (unsigned long long) now.tv_sec*1000000;
#else
#if defined(_WIN32_WCE)
    return ((unsigned long long)GetTickCount()) * 1000;
#else
    return ((unsigned long long)timeGetTime()) * 1000;
#endif
#endif
}

//--------------------------------------------------
unsigned int GetUnixTime(){
	return (unsigned int)time(NULL);
}

//--------------------------------------------------
int GetSeconds(){
	time_t 	curr;
	tm 		local;
	time(&curr);
	local	=*(localtime(&curr));
	return local.tm_sec;
}

//--------------------------------------------------
int GetMinutes(){
	time_t 	curr;
	tm 		local;
	time(&curr);
	local	=*(localtime(&curr));
	return local.tm_min;
}

//--------------------------------------------------
int GetHours(){
	time_t 	curr;
	tm 		local;
	time(&curr);
	local	=*(localtime(&curr));
	return local.tm_hour;
}

//--------------------------------------------------
int GetYear(){
    time_t    curr;
    tm       local;
    time(&curr);
    local   =*(localtime(&curr));
    int year = local.tm_year + 1900;
    return year;
}

//--------------------------------------------------
int GetMonth(){
    time_t    curr;
    tm       local;
    time(&curr);
    local   =*(localtime(&curr));
    int month = local.tm_mon + 1;
    return month;
}

//--------------------------------------------------
int GetDay(){
    time_t    curr;
    tm       local;
    time(&curr);
    local   =*(localtime(&curr));
    return local.tm_mday;
}

//--------------------------------------------------
int GetWeekday(){
    time_t    curr;
    tm       local;
    time(&curr);
    local   =*(localtime(&curr));
    return local.tm_wday;
}
//----------------------------------------
template<>
string FromString(const string & value){
	return value;
}

//----------------------------------------
template<>
const char * FromString(const string & value){
	return value.c_str();
}

//----------------------------------------
int ToInt(const string& intString) {
	int x = 0;
	istringstream cur(intString);
	cur >> x;
	return x;
}

//----------------------------------------
float ToFloat(const string& floatString) {
	float x = 0;
	istringstream cur(floatString);
	cur >> x;
	return x;
}

//----------------------------------------
double ToDouble(const string& doubleString) {
	double x = 0;
	istringstream cur(doubleString);
	cur >> x;
	return x;
}
//----------------------------------------
char ToChar(const string& charString) {
	char x = '\0';
	istringstream cur(charString);
	cur >> x;
	return x;
}

//--------------------------------------------------
string JoinString(vector <string> stringElements, const string & delimiter){
	string resultString = "";
	int numElements = (int)stringElements.size();
    
	for(int k = 0; k < numElements; k++){
		if( k < numElements-1 ){
			resultString += stringElements[k] + delimiter;
		} else {
			resultString += stringElements[k];
		}
	}
    
	return resultString;
}

//--------------------------------------------------
void StringReplace(string& input, string searchStr, string replaceStr){
	size_t uPos = 0;
	size_t uFindLen = searchStr.length();
	size_t uReplaceLen = replaceStr.length();
    
	if( uFindLen == 0 ){
		return;
	}
    
	for( ;(uPos = input.find( searchStr, uPos )) != std::string::npos; ){
		input.replace( uPos, uFindLen, replaceStr );
		uPos += uReplaceLen;
	}
}

//--------------------------------------------------
bool IsStringInString(string haystack, string needle){
	return ( strstr(haystack.c_str(), needle.c_str() ) != NULL );
}

int StringTimesInString(string haystack, string needle){
	const size_t step = needle.size();
    
	size_t count(0);
	size_t pos(0) ;
    
	while( (pos=haystack.find(needle, pos)) != std::string::npos) {
		pos +=step;
		++count ;
	}
    
	return (int)count;
}

//--------------------------------------------------
string ToLower(const string & src){
	string dst(src);
	transform(src.begin(),src.end(),dst.begin(),::tolower);
	return dst;
}

//--------------------------------------------------
string ToUpper(const string & src){
	string dst(src);
	transform(src.begin(),src.end(),dst.begin(),::toupper);
	return dst;
}

//--------------------------------------------------
string VAArgsToString(const char * format, ...){
	// variadic args to string:
	// http://www.codeproject.com/KB/string/string_format.aspx
	static char aux_buffer[10000];
	string retStr("");
	if (NULL != format){
        
		va_list marker;
        
		// initialize variable arguments
		va_start(marker, format);
        
		// Get formatted string length adding one for NULL
		size_t len = vsprintf(aux_buffer, format, marker) + 1;
        
		// Reset variable arguments
		va_end(marker);
        
		if (len > 0)
		{
			va_list args;
            
			// initialize variable arguments
			va_start(args, format);
            
			// Create a char vector to hold the formatted string.
			vector<char> buffer(len, '\0');
			vsprintf(&buffer[0], format, args);
			retStr = &buffer[0];
			va_end(args);
		}
        
	}
	return retStr;
}

string VAArgsToString(const char * format, va_list args){
	// variadic args to string:
	// http://www.codeproject.com/KB/string/string_format.aspx
	char aux_buffer[10000];
	string retStr("");
	if (NULL != format){
        
		// Get formatted string length adding one for NULL
		vsprintf(aux_buffer, format, args);
		retStr = aux_buffer;
        
	}
	return retStr;
}

FL_NAMESPACE_END