/* port from oF */

/*
 *  flQuaternion.h
 *
 *  Created by Aaron Meyers on 6/22/09 -- modified by Arturo Castro, Zach Lieberman, Memo Akten
 *  based on code from OSG -
 *  see OSG license for more details:
 *  http://www.openscenegraph.org/projects/osg/wiki/Legal
 *
 */

#pragma once

#include <cmath>
#include <iostream>

#include "flVec4f.h"
#include "flCommon.h"

FL_NAMESPACE_BEGIN

class Matrix4x4;

class Quaternion {
public:
    //    float _v[4];
    Vec4f _v;
    
    inline Quaternion();
    inline Quaternion(float x, float y, float z, float w);
    inline Quaternion(const Vec4f& v);
    inline Quaternion(float angle, const Vec4f& axis);
    inline Quaternion(float angle1, const Vec4f& axis1, float angle2, const Vec4f& axis2, float angle3, const Vec4f& axis3);
    
    inline Quaternion& operator =(const Quaternion& q);
    inline bool operator ==(const Quaternion& q) const;
    inline bool operator !=(const Quaternion& q) const;
    //    inline bool operator <(const Quaternion& q) const;  // why?
    
    inline std::ostream& operator<<(std::ostream& os);
    inline std::istream& operator>>(std::istream& is);
    
    inline Vec4f asVec4() const;
    
    inline void set(float x, float y, float z, float w);
    inline void set(const Vec4f& v);
    
    void set(const Matrix4x4& matrix);
    void get(Matrix4x4& matrix) const;
    
    inline float& operator [](int i);
    inline float operator [](int i) const;
    
    inline float& x();
    inline float& y();
    inline float& z();
    inline float& w();
    
    inline float x() const;
    inline float y() const;
    inline float z() const;
    inline float w() const;
    
    // return true if the Quat represents a zero rotation, and therefore can be ignored in computations.
    inline bool zeroRotation() const;
    
    
    
    // BASIC ARITHMETIC METHODS
    // Implemented in terms of Vec4s. Some Vec4 operators, e.g.
    // operator* are not appropriate for quaternions (as
    // mathematical objects) so they are implemented differently.
    // Also define methods for conjugate and the multiplicative inverse.
    
    inline const Quaternion operator *(float rhs) const;                  // Multiply by scalar
    inline Quaternion& operator *=(float rhs);                            // Unary multiply by scalar
    inline const Quaternion operator*(const Quaternion& rhs) const;     // Binary multiply
    inline Quaternion& operator*=(const Quaternion& rhs);               // Unary multiply
    inline Quaternion operator /(float rhs) const;                        // Divide by scalar
    inline Quaternion& operator /=(float rhs);                            // Unary divide by scalar
    inline const Quaternion operator/(const Quaternion& denom) const;   // Binary divide
    inline Quaternion& operator/=(const Quaternion& denom);             // Unary divide
    inline const Quaternion operator +(const Quaternion& rhs) const;    // Binary addition
    inline Quaternion& operator +=(const Quaternion& rhs);              // Unary addition
    inline const Quaternion operator -(const Quaternion& rhs) const;    // Binary subtraction
    inline Quaternion& operator -=(const Quaternion& rhs);              // Unary subtraction
    inline const Quaternion operator -() const;                           // returns the negative of the quaternion. calls operator -() on the Vec4 */
    inline Vec4f operator*(const Vec4f& v) const;                       // Rotate a vector by this quaternion.
    
    
    // Length of the quaternion = sqrt(vec . vec)
    inline float length() const;
    
    // Length of the quaternion = vec . vec
    inline float length2() const;
    
    // Conjugate
    inline Quaternion conj() const;
    
    // Multiplicative inverse method: q^(-1) = q^*/(q.q^*)
    inline const Quaternion inverse() const;
    
    
    
    // METHODS RELATED TO ROTATIONS
    // Set a quaternion which will perform a rotation of an
    // angle around the axis given by the vector(x,y,z).
    // Should be written to also accept an angle and a Vec3?
    
    // Define Spherical Linear interpolation method also
    void makeRotate(float angle, float x, float y, float z);
    void makeRotate(float angle, const Vec4f& vec);
    void makeRotate(float angle1, const Vec4f& axis1, float angle2, const Vec4f& axis2, float angle3, const Vec4f& axis3);
    
    
    // Make a rotation Quat which will rotate vec1 to vec2.
    // Generally take a dot product to get the angle between these
    // and then use a cross product to get the rotation axis
    // Watch out for the two special cases when the vectors
    // are co-incident or opposite in direction.
    void makeRotate(const Vec4f& vec1, const Vec4f& vec2);
    
    void makeRotate_original(const Vec4f& vec1, const Vec4f& vec2);
    
    // Return the angle and vector components represented by the quaternion.
    void getRotate(float&angle, float& x, float& y, float& z) const;
    void getRotate(float& angle, Vec4f& vec) const;
    
    // calculate and return the rotation as euler angles
    Vec4f getEuler() const;
    
    
    // Spherical Linear Interpolation.
    // As t goes from 0 to 1, the Quat object goes from "from" to "to".
    void slerp(float t, const Quaternion& from, const Quaternion& to);
    
    inline void normalize();
};


//----------------------------------------
Quaternion::Quaternion() {
    _v.set(0, 0, 0, 1);
}


//----------------------------------------
std::ostream& Quaternion::operator<<(std::ostream& os) {
    os << _v.x << ", " << _v.y << ", " << _v.z << ", " << _v.w;
    return os;
}


//----------------------------------------
std::istream& Quaternion::operator>>(std::istream& is) {
    is >> _v.x;
    is.ignore(2);
    is >> _v.y;
    is.ignore(2);
    is >> _v.z;
    is.ignore(2);
    is >> _v.w;
    return is;
}


//----------------------------------------
Quaternion::Quaternion(float x, float y, float z, float w) {
    _v.set(x, y, z, w);
}


//----------------------------------------
Quaternion::Quaternion(const Vec4f& v) {
    _v = v;
}


//----------------------------------------
Quaternion::Quaternion(float angle, const Vec4f& axis) {
    makeRotate(angle, axis);
}


//----------------------------------------
Quaternion::Quaternion(float angle1, const Vec4f& axis1, float angle2, const Vec4f& axis2, float angle3, const Vec4f& axis3) {
    makeRotate(angle1, axis1, angle2, axis2, angle3, axis3);
}


//----------------------------------------
Quaternion& Quaternion::operator =(const Quaternion& q) {
    _v = q._v;
    return *this;
}


//----------------------------------------
bool Quaternion::operator ==(const Quaternion& q) const {
    return _v == q._v;
}


//----------------------------------------
bool Quaternion::operator !=(const Quaternion& q) const {
    return _v != q._v;
}


//----------------------------------------
//bool Quaternion::operator <(const Quaternion& q) const {
//    if(_v.x < v._v.x) return true;
//    else if(_v.x > v._v.x) return false;
//    else if(_v.y < v._v.y) return true;
//    else if(_v.y > v._v.y) return false;
//    else if(_v.z < v._v.z) return true;
//    else if(_v.z > v._v.z) return false;
//    else return (_v.w < v._v.w);
//}



//----------------------------------------
Vec4f Quaternion::asVec4() const {
    return _v;
}

//----------------------------------------
void Quaternion::set(float x, float y, float z, float w) {
    _v.set(x, y, z, w);
}


//----------------------------------------
void Quaternion::set(const Vec4f& v) {
    _v = v;
}


//----------------------------------------
float& Quaternion::operator [](int i) {
    return _v[i];
}



//----------------------------------------
float Quaternion::operator [](int i) const {
    return _v[i];
}


//----------------------------------------
float& Quaternion::x() {
    return _v.x;
}


//----------------------------------------
float& Quaternion::y() {
    return _v.y;
}


//----------------------------------------
float& Quaternion::z() {
    return _v.z;
}


//----------------------------------------
float& Quaternion::w() {
    return _v.w;
}


//----------------------------------------
float Quaternion::x() const {
    return _v.x;
}


//----------------------------------------
float Quaternion::y() const {
    return _v.y;
}


//----------------------------------------
float Quaternion::z() const {
    return _v.z;
}


//----------------------------------------
float Quaternion::w() const {
    return _v.w;
}


//----------------------------------------
bool Quaternion::zeroRotation() const {
    return _v.x == 0.0 && _v.y == 0.0 && _v.z == 0.0 && _v.w == 1.0;
}



//----------------------------------------
const Quaternion Quaternion::operator *(float rhs) const {
    return Quaternion(_v.x*rhs, _v.y*rhs, _v.z*rhs, _v.w*rhs);
}


//----------------------------------------
Quaternion& Quaternion::operator *=(float rhs) {
    _v.x *= rhs;
    _v.y *= rhs;
    _v.z *= rhs;
    _v.w *= rhs;
    return *this; // enable nesting
}


//----------------------------------------
const Quaternion Quaternion::operator*(const Quaternion& rhs) const {
    return Quaternion(rhs._v.w*_v.x + rhs._v.x*_v.w + rhs._v.y*_v.z - rhs._v.z*_v.y,
                      rhs._v.w*_v.y - rhs._v.x*_v.z + rhs._v.y*_v.w + rhs._v.z*_v.x,
                      rhs._v.w*_v.z + rhs._v.x*_v.y - rhs._v.y*_v.x + rhs._v.z*_v.w,
                      rhs._v.w*_v.w - rhs._v.x*_v.x - rhs._v.y*_v.y - rhs._v.z*_v.z);
}


//----------------------------------------
Quaternion& Quaternion::operator*=(const Quaternion& rhs) {
    float x = rhs._v.w * _v.x + rhs._v.x * _v.w + rhs._v.y * _v.z - rhs._v.z * _v.y;
    float y = rhs._v.w * _v.y - rhs._v.x * _v.z + rhs._v.y * _v.w + rhs._v.z * _v.x;
    float z = rhs._v.w * _v.z + rhs._v.x * _v.y - rhs._v.y * _v.x + rhs._v.z * _v.w;
    _v.w = rhs._v.w * _v.w - rhs._v.x * _v.x - rhs._v.y * _v.y - rhs._v.z * _v.z;
    
    _v.z = z;
    _v.y = y;
    _v.x = x;
    
    return (*this); // enable nesting
}


//----------------------------------------
Quaternion Quaternion::operator /(float rhs) const {
    float div = 1.0 / rhs;
    return Quaternion(_v.x*div, _v.y*div, _v.z*div, _v.w*div);
}


//----------------------------------------
Quaternion& Quaternion::operator /=(float rhs) {
    float div = 1.0 / rhs;
    _v.x *= div;
    _v.y *= div;
    _v.z *= div;
    _v.w *= div;
    return *this;
}


//----------------------------------------
const Quaternion Quaternion::operator/(const Quaternion& denom) const {
    return ((*this) * denom.inverse());
}


//----------------------------------------
Quaternion& Quaternion::operator/=(const Quaternion& denom) {
    (*this) = (*this) * denom.inverse();
    return (*this); // enable nesting
}


//----------------------------------------
const Quaternion Quaternion::operator +(const Quaternion& rhs) const {
    return Quaternion(_v.x + rhs._v.x, _v.y + rhs._v.y,
                      _v.z + rhs._v.z, _v.w + rhs._v.w);
}


//----------------------------------------
Quaternion& Quaternion::operator +=(const Quaternion& rhs) {
    _v.x += rhs._v.x;
    _v.y += rhs._v.y;
    _v.z += rhs._v.z;
    _v.w += rhs._v.w;
    return *this; // enable nesting
}


//----------------------------------------
const Quaternion Quaternion::operator -(const Quaternion& rhs) const {
    return Quaternion(_v.x - rhs._v.x, _v.y - rhs._v.y,
                      _v.z - rhs._v.z, _v.w - rhs._v.w);
}


//----------------------------------------
Quaternion& Quaternion::operator -=(const Quaternion& rhs) {
    _v.x -= rhs._v.x;
    _v.y -= rhs._v.y;
    _v.z -= rhs._v.z;
    _v.w -= rhs._v.w;
    return *this; // enable nesting
}


//----------------------------------------
const Quaternion Quaternion::operator -() const {
    return Quaternion(-_v.x, -_v.y, -_v.z, -_v.w);
}


//----------------------------------------
float Quaternion::length() const {
    return sqrt(_v.x*_v.x + _v.y*_v.y + _v.z*_v.z + _v.w*_v.w);
}


//----------------------------------------
float Quaternion::length2() const {
    return _v.x*_v.x + _v.y*_v.y + _v.z*_v.z + _v.w*_v.w;
}


//----------------------------------------
Quaternion Quaternion::conj() const {
    return Quaternion(-_v.x, -_v.y, -_v.z, _v.w);
}


//----------------------------------------
const Quaternion Quaternion::inverse() const {
    return conj() / length2();
}



//----------------------------------------
Vec4f Quaternion::operator*(const Vec4f& v) const {
    // nVidia SDK implementation
    Vec4f uv, uuv;
    Vec4f qvec(_v.x, _v.y, _v.z);
    uv = qvec.getCrossed(v);    //uv = qvec ^ v;
    uuv = qvec.getCrossed(uv);    //uuv = qvec ^ uv;
    uv *= (2.0f * _v.w);
    uuv *= 2.0f;
    return v + uv + uuv;
}

void Quaternion::normalize(){
    float len = _v.w*_v.w + _v.x*_v.x + _v.y*_v.y + _v.z*_v.z;
    float factor = 1.0f / sqrt(len);
    _v.x *= factor;
    _v.y *= factor;
    _v.z *= factor;
    _v.w *= factor;
}

FL_NAMESPACE_END