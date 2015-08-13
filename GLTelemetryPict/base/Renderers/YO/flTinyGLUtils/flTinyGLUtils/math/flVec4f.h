/* port from oF */

#pragma once

#include <iostream>
#include <cmath>

#include "flCommon.h"

FL_NAMESPACE_BEGIN

class Vec2f;
class Vec3f;

class Vec4f {
public:
    float x, y, z, w;
    
    static const int DIM = 4;
    
    Vec4f(const Vec2f& vec);
    Vec4f(const Vec3f& vec);
    Vec4f( float _x=0.f, float _y=0.f, float _z=0.f, float _w=0.f );
    
    // Getters and Setters.
    //
    void set( float _x, float _y, float _z, float _w );
    void set( const Vec4f& vec );
    
    float * getPtr() {
        return (float*)&x;
    }
    const float * getPtr() const {
        return (const float *)&x;
    }
    
    float& operator[]( int n ){
        return getPtr()[n];
    }
    
    float operator[]( int n ) const {
        return getPtr()[n];
    }
    
    // Check similarity/equality.
    //
    bool operator==( const Vec4f& vec ) const;
    bool operator!=( const Vec4f& vec ) const;
    bool match( const Vec4f& vec, float tolerance=0.0001) const;
    
    
    // Additions and Subtractions.
    //
    Vec4f  operator+( const Vec4f& vec ) const;
    Vec4f& operator+=( const Vec4f& vec );
    Vec4f  operator-( const float f ) const;
    Vec4f& operator-=( const float f );
    Vec4f  operator-( const Vec4f& vec ) const;
    Vec4f& operator-=( const Vec4f& vec );
    Vec4f  operator+( const float f ) const;
    Vec4f& operator+=( const float f );
    Vec4f  operator-() const;
    
    
    // Scalings
    //
    Vec4f  operator*( const Vec4f& vec ) const;
    Vec4f& operator*=( const Vec4f& vec );
    Vec4f  operator*( const float f ) const;
    Vec4f& operator*=( const float f );
    Vec4f  operator/( const Vec4f& vec ) const;
    Vec4f& operator/=( const Vec4f& vec );
    Vec4f  operator/( const float f ) const;
    Vec4f& operator/=( const float f );
    
    friend std::ostream& operator<<(std::ostream& os, const Vec4f& vec);
    friend std::istream& operator>>(std::istream& is, const Vec4f& vec);
    
    
    Vec4f  getScaled( const float length ) const;
    Vec4f& scale( const float length );
    
    
    // Distance between two points.
    //
    float distance( const Vec4f& pnt) const;
    float squareDistance( const Vec4f& pnt ) const;
    
    
    // Linear interpolation.
    //
    /**
     * p==0.0 results in this point, p==0.5 results in the
     * midpoint, and p==1.0 results in pnt being returned.
     */
    Vec4f   getInterpolated( const Vec4f& pnt, float p ) const;
    Vec4f&  interpolate( const Vec4f& pnt, float p );
    Vec4f   getMiddle( const Vec4f& pnt ) const;
    Vec4f&  middle( const Vec4f& pnt );
    Vec4f&  average( const Vec4f* points, int num );
    
    
    // Normalization
    //
    Vec4f  getNormalized() const;
    Vec4f& normalize();
    
    
    // Limit length.
    //
    Vec4f  getLimited(float max) const;
    Vec4f& limit(float max);
    
    
    // Length
    //
    float length() const;
    float squareLength() const;
    /**
     * Dot Product.
     */
    float dot( const Vec4f& vec ) const;
    
    //cross
    Vec4f crossed( const Vec4f& vec ) const;
    Vec4f getCrossed( const Vec4f& vec ) const;
    Vec4f& cross( const Vec4f& vec );
    
    
    //---------------------------------------
    // this methods are deprecated in 006 please use:
    
    // getScaled
    Vec4f rescaled( const float length ) const;
    
    // scale
    Vec4f& rescale( const float length );
    
    // getNormalized
    Vec4f normalized() const;
    
    // getLimited
    Vec4f limited(float max) const;
    
    // squareLength
    float lengthSquared() const;
    
    // use squareDistance
    float  distanceSquared( const Vec4f& pnt ) const;
    
    // use getInterpolated
    Vec4f 	interpolated( const Vec4f& pnt, float p ) const;
    
    // use getMiddle
    Vec4f 	middled( const Vec4f& pnt ) const;
    
    // return all zero vector
    static Vec4f zero() { return Vec4f(0, 0, 0, 0); }
    
    // return all one vector
    static Vec4f one() { return Vec4f(1, 1, 1, 1); }
    
};

// Non-Member operators
//
//
Vec4f operator+( float f, const Vec4f& vec );
Vec4f operator-( float f, const Vec4f& vec );
Vec4f operator*( float f, const Vec4f& vec );
Vec4f operator/( float f, const Vec4f& vec );







/////////////////
// Implementation
/////////////////

inline Vec4f::Vec4f( float _x,
                    float _y,
                    float _z,
                    float _w ):x(_x), y(_y), z(_z), w(_w) {}

// Getters and Setters.
//
//
inline void Vec4f::set( float _x, float _y, float _z, float _w ) {
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

inline void Vec4f::set( const Vec4f& vec ) {
    x = vec.x;
    y = vec.y;
    z = vec.z;
    w = vec.w;
}


// Check similarity/equality.
//
//
inline bool Vec4f::operator==( const Vec4f& vec ) const {
    return (x == vec.x) && (y == vec.y) && (z == vec.z) && (w == vec.w);
}

inline bool Vec4f::operator!=( const Vec4f& vec ) const {
    return (x != vec.x) || (y != vec.y) || (z != vec.z) || (w != vec.w);
}

inline bool Vec4f::match( const Vec4f& vec, float tolerance) const {
    return (std::fabs(x - vec.x) < tolerance)
    && (std::fabs(y - vec.y) < tolerance)
    && (std::fabs(z - vec.z) < tolerance)
    && (std::fabs(w - vec.w) < tolerance);
}




// Additions and Subtractions.
//
//
inline Vec4f Vec4f::operator+( const Vec4f& vec ) const {
    return Vec4f( x+vec.x, y+vec.y, z+vec.z, w+vec.w);
}

inline Vec4f& Vec4f::operator+=( const Vec4f& vec ) {
    x += vec.x;
    y += vec.y;
    z += vec.z;
    w += vec.w;
    return *this;
}

inline Vec4f Vec4f::operator-( const float f ) const {
    return Vec4f( x-f, y-f, z-f, w-f );
}

inline Vec4f& Vec4f::operator-=( const float f ) {
    x -= f;
    y -= f;
    z -= f;
    w -= f;
    return *this;
}

inline Vec4f Vec4f::operator-( const Vec4f& vec ) const {
    return Vec4f( x-vec.x, y-vec.y, z-vec.z, w-vec.w );
}

inline Vec4f& Vec4f::operator-=( const Vec4f& vec ) {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    w -= vec.w;
    return *this;
}

inline Vec4f Vec4f::operator+( const float f ) const {
    return Vec4f( x+f, y+f, z+f, w+f );
}

inline Vec4f& Vec4f::operator+=( const float f ) {
    x += f;
    y += f;
    z += f;
    w += f;
    return *this;
}

inline Vec4f Vec4f::operator-() const {
    return Vec4f( -x, -y, -z, -w );
}


// Scalings
//
//
inline Vec4f Vec4f::operator*( const Vec4f& vec ) const {
    return Vec4f( x*vec.x, y*vec.y, z*vec.z, w*vec.w );
}

inline Vec4f& Vec4f::operator*=( const Vec4f& vec ) {
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
    w *= vec.w;
    return *this;
}

inline Vec4f Vec4f::operator*( const float f ) const {
    return Vec4f( x*f, y*f, z*f, w*f );
}

inline Vec4f& Vec4f::operator*=( const float f ) {
    x *= f;
    y *= f;
    z *= f;
    w *= f;
    return *this;
}

inline Vec4f Vec4f::operator/( const Vec4f& vec ) const {
    return Vec4f( vec.x!=0 ? x/vec.x : x , vec.y!=0 ? y/vec.y : y, vec.z!=0 ? z/vec.z : z, vec.w!=0 ? w/vec.w : w  );
}

inline Vec4f& Vec4f::operator/=( const Vec4f& vec ) {
    vec.x!=0 ? x/=vec.x : x;
    vec.y!=0 ? y/=vec.y : y;
    vec.z!=0 ? z/=vec.z : z;
    vec.w!=0 ? w/=vec.w : w;
    return *this;
}

inline Vec4f Vec4f::operator/( const float f ) const {
    if(f == 0) return Vec4f(x, y, z, w);
    
    return Vec4f( x/f, y/f, z/f, w/f );
}

inline Vec4f& Vec4f::operator/=( const float f ) {
    if(f == 0)return *this;
    
    x /= f;
    y /= f;
    z /= f;
    w /= f;
    return *this;
}


inline std::ostream& operator<<(std::ostream& os, const Vec4f& vec) {
    os << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w;
    return os;
}

inline std::istream& operator>>(std::istream& is, Vec4f& vec) {
    is >> vec.x;
    is.ignore(2);
    is >> vec.y;
    is.ignore(2);
    is >> vec.z;
    is.ignore(2);
    is >> vec.w;
    return is;
}


inline Vec4f Vec4f::rescaled( const float length ) const {
    return getScaled(length);
}

inline Vec4f Vec4f::getScaled( const float length ) const {
    float l = (float)sqrt(x*x + y*y + z*z + w*w);
    if( l > 0 )
        return Vec4f( (x/l)*length, (y/l)*length,
                     (z/l)*length, (w/l)*length );
    else
        return Vec4f();
}

inline Vec4f& Vec4f::rescale( const float length ) {
    return scale(length);
}

inline Vec4f& Vec4f::scale( const float length ) {
    float l = (float)sqrt(x*x + y*y + z*z + w*w);
    if (l > 0) {
        x = (x/l)*length;
        y = (y/l)*length;
        z = (z/l)*length;
        w = (w/l)*length;
    }
    return *this;
}



// Distance between two points.
//
//
inline float Vec4f::distance( const Vec4f& pnt) const {
    float vx = x-pnt.x;
    float vy = y-pnt.y;
    float vz = z-pnt.z;
    float vw = w-pnt.w;
    return (float)sqrt( vx*vx + vy*vy + vz*vz + vw*vw );
}

inline float Vec4f::distanceSquared( const Vec4f& pnt ) const {
    return squareDistance(pnt);
}

inline float Vec4f::squareDistance( const Vec4f& pnt ) const {
    float vx = x-pnt.x;
    float vy = y-pnt.y;
    float vz = z-pnt.z;
    float vw = w-pnt.w;
    return vx*vx + vy*vy + vz*vz + vw*vw;
}



// Linear interpolation.
//
//
/**
 * p==0.0 results in this point, p==0.5 results in the
 * midpoint, and p==1.0 results in pnt being returned.
 */
inline Vec4f Vec4f::interpolated( const Vec4f& pnt, float p ) const{
    return getInterpolated(pnt,p);
}

inline Vec4f Vec4f::getInterpolated( const Vec4f& pnt, float p ) const {
    return Vec4f( x*(1-p) + pnt.x*p,
                 y*(1-p) + pnt.y*p,
                 z*(1-p) + pnt.z*p,
                 w*(1-p) + pnt.w*p );
}

inline Vec4f& Vec4f::interpolate( const Vec4f& pnt, float p ) {
    x = x*(1-p) + pnt.x*p;
    y = y*(1-p) + pnt.y*p;
    z = z*(1-p) + pnt.z*p;
    w = w*(1-p) + pnt.w*p;
    return *this;
}

inline Vec4f Vec4f::middled( const Vec4f& pnt ) const {
    return getMiddle(pnt);
}

inline Vec4f Vec4f::getMiddle( const Vec4f& pnt ) const {
    return Vec4f( (x+pnt.x)/2.0f, (y+pnt.y)/2.0f,
                 (z+pnt.z)/2.0f, (w+pnt.w)/2.0f );
}

inline Vec4f& Vec4f::middle( const Vec4f& pnt ) {
    x = (x+pnt.x)/2.0f;
    y = (y+pnt.y)/2.0f;
    z = (z+pnt.z)/2.0f;
    w = (w+pnt.w)/2.0f;
    return *this;
}


// Average (centroid) among points.
// (Addition is sometimes useful for calculating averages too)
//
//
inline Vec4f& Vec4f::average( const Vec4f* points, int num ) {
    x = 0.f;
    y = 0.f;
    z = 0.f;
    w = 0.f;
    for( int i=0; i<num; i++) {
        x += points[i].x;
        y += points[i].y;
        z += points[i].z;
        w += points[i].w;
    }
    x /= num;
    y /= num;
    z /= num;
    w /= num;
    return *this;
}



// Normalization
//
//
inline Vec4f Vec4f::normalized() const {
    return getNormalized();
}

inline Vec4f Vec4f::getNormalized() const {
    float length = (float)sqrt(x*x + y*y + z*z + w*w);
    if( length > 0 ) {
        return Vec4f( x/length, y/length, z/length, w/length );
    } else {
        return Vec4f();
    }
}

inline Vec4f& Vec4f::normalize() {
    float lenght = (float)sqrt(x*x + y*y + z*z + w*w);
    if( lenght > 0 ) {
        x /= lenght;
        y /= lenght;
        z /= lenght;
        w /= lenght;
    }
    return *this;
}



// Limit length.
//
//
inline Vec4f Vec4f::limited(float max) const {
    return getLimited(max);
}

inline Vec4f Vec4f::getLimited(float max) const {
    Vec4f limited;
    float lengthSquared = (x*x + y*y + z*z + w*w);
    if( lengthSquared > max*max && lengthSquared > 0 ) {
        float ratio = max/(float)sqrt(lengthSquared);
        limited.set( x*ratio, y*ratio, z*ratio, w*ratio );
    } else {
        limited.set(x,y,z,w);
    }
    return limited;
}

inline Vec4f& Vec4f::limit(float max) {
    float lengthSquared = (x*x + y*y + z*z + w*w);
    if( lengthSquared > max*max && lengthSquared > 0 ) {
        float ratio = max/(float)sqrt(lengthSquared);
        x *= ratio;
        y *= ratio;
        z *= ratio;
        w *= ratio;
    }
    return *this;
}



// Length
//
//
inline float Vec4f::length() const {
    return (float)sqrt( x*x + y*y + z*z + w*w );
}

inline float Vec4f::lengthSquared() const {
    return squareLength();
}

inline float Vec4f::squareLength() const {
    return (float)(x*x + y*y + z*z + w*w);
}



/**
 * Dot Product.
 */
inline float Vec4f::dot( const Vec4f& vec ) const {
    return x*vec.x + y*vec.y + z*vec.z + w*vec.w;
}


//cross

inline Vec4f Vec4f::crossed( const Vec4f& vec ) const {
    return getCrossed(vec);
}
inline Vec4f Vec4f::getCrossed( const Vec4f& vec ) const {
    return Vec4f( y*vec.z - z*vec.y,
                 z*vec.x - x*vec.z,
                 x*vec.y - y*vec.x );
}

inline Vec4f& Vec4f::cross( const Vec4f& vec ) {
    float _x = y*vec.z - z*vec.y;
    float _y = z*vec.x - x*vec.z;
    z = x*vec.y - y*vec.x;
    x = _x;
    y = _y;
    return *this;
}



// Non-Member operators
//
//
inline Vec4f operator+( float f, const Vec4f& vec ) {
    return Vec4f( f+vec.x, f+vec.y, f+vec.z, f+vec.w );
}

inline Vec4f operator-( float f, const Vec4f& vec ) {
    return Vec4f( f-vec.x, f-vec.y, f-vec.z, f-vec.w );
}

inline Vec4f operator*( float f, const Vec4f& vec ) {
    return Vec4f( f*vec.x, f*vec.y, f*vec.z, f*vec.w );
}

inline Vec4f operator/( float f, const Vec4f& vec ) {
    return Vec4f( f/vec.x, f/vec.y, f/vec.z, f/vec.w);
}

FL_NAMESPACE_END