
//
//  flUtils.h
//  flTinyGLUtils
//
//  Created by Onishi Yoshito on 10/29/13.
//  Copyright (c) 2013 Onishi Yoshito. All rights reserved.
//

#ifndef __flTinyGLUtils__flUtils__
#define __flTinyGLUtils__flUtils__

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <bitset>

#include "flCommon.h"

FL_NAMESPACE_BEGIN

std::string demangle(const char* name);

template <class T> std::string getClassName(const T& t);
template <class T> std::string getClassName();

template<class T> void safeDelete(T* p);

void hsbToRgb(float hue, float saturation, float brightness, float* r, float* g, float* b);

int 	NextPow2(int input);

void	ResetElapsedTimeCounter();		// this happens on the first frame
float 	GetElapsedTimef();
unsigned long long GetElapsedTimeMillis();
unsigned long long GetElapsedTimeMicros();
int 	GetFrameNum();

int 	GetSeconds();
int 	GetMinutes();
int 	GetHours();

//number  seconds since 1970
unsigned int GetUnixTime();

unsigned long long GetSystemTime( );			// system time in milliseconds;
unsigned long long GetSystemTimeMicros( );			// system time in microseconds;

int     GetYear();
int     GetMonth();
int     GetDay();
int     GetWeekday();

template<class T>
void Randomize(std::vector<T>& values) {
    random_shuffle(values.begin(), values.end());
}

template<class T, class BoolFunction>
void Remove(std::vector<T>& values, BoolFunction shouldErase) {
    values.erase(remove_if(values.begin(), values.end(), shouldErase), values.end());
}

template<class T>
void Sort(std::vector<T>& values) {
    sort(values.begin(), values.end());
}
template<class T, class BoolFunction>
void Sort(std::vector<T>& values, BoolFunction compare) {
    sort(values.begin(), values.end(), compare);
}

template <class T>
unsigned int Find(const std::vector<T>& values, const T& target) {
    return distance(values.begin(), find(values.begin(), values.end(), target));
}

template <class T>
bool Contains(const std::vector<T>& values, const T& target) {
    return Find(values, target) != values.size();
}

template <class T>
std::string ToString(const T& value){
    std::ostringstream out;
    out << value;
    return out.str();
}

/// like sprintf "%4f" format, in this example precision=4
template <class T>
std::string ToString(const T& value, int precision){
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << value;
    return out.str();
}

/// like sprintf "% 4d" or "% 4f" format, in this example width=4, fill=' '
template <class T>
std::string ToString(const T& value, int width, char fill ){
    std::ostringstream out;
    out << std::fixed << std::setfill(fill) << std::setw(width) << value;
    return out.str();
}

/// like sprintf "%04.2d" or "%04.2f" format, in this example precision=2, width=4, fill='0'
template <class T>
std::string ToString(const T& value, int precision, int width, char fill ){
    std::ostringstream out;
    out << std::fixed << std::setfill(fill) << std::setw(width) << std::setprecision(precision) << value;
    return out.str();
}

template<class T>
std::string ToString(const std::vector<T>& values) {
    std::stringstream out;
    int n = values.size();
    out << "{";
    if(n > 0) {
        for(int i = 0; i < n - 1; i++) {
            out << values[i] << ", ";
        }
        out << values[n - 1];
    }
    out << "}";
    return out.str();
}

template<class T>
T FromString(const std::string & value){
    T data;
    std::stringstream ss;
    ss << value;
    ss >> data;
    return data;
}

template<>
std::string FromString(const std::string & value);

template<>
const char * FromString(const std::string & value);

int ToInt(const std::string& intString);
char ToChar(const std::string& charString);
float ToFloat(const std::string& floatString);
double ToDouble(const std::string& doubleString);

//--------------------------------------------------
std::string JoinString(std::vector <std::string> stringElements, const std::string & delimiter);
void StringReplace(std::string& input, std::string searchStr, std::string replaceStr);
bool IsStringInString(std::string haystack, std::string needle);
int StringTimesInString(std::string haystack, std::string needle);

std::string ToLower(const std::string & src);
std::string ToUpper(const std::string & src);

std::string VAArgsToString(const char * format, ...);
std::string VAArgsToString(const char * format, va_list args);

template <class T>
std::string getClassName(const T& t)
{
    return demangle(typeid(t).name());
}

template <class T>
std::string getClassName()
{
    return demangle(typeid(T).name());
}

template<class T> void safeDelete(T* p)
{
    delete p;
    p = nullptr;
}

FL_NAMESPACE_END

#endif /* defined(__flTinyGLUtils__flUtils__) */
