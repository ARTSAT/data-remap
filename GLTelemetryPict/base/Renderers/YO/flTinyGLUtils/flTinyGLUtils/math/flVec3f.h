/* port from oF */

#pragma once

#include <cmath>
#include <iostream>

#include "flMath.h"
#include "flCommon.h"
#include "flVec2f.h"
#include "flVec4f.h"

FL_NAMESPACE_BEGIN

class Vec2f;
class Vec4f;

class Vec3f {
public:
    float x,y,z;
    
    static const int DIM = 3;
    
    Vec3f(const Vec2f& vec);
    Vec3f(const Vec4f& vec);
    Vec3f( float _x=0.f, float _y=0.f, float _z=0.f );
    
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
    
    
    // Getters and Setters.
    //
    void set( float _x, float _y, float _z = 0 );
    void set( const Vec3f& vec );
    
    // Check similarity/equality.
    //
    bool operator==( const Vec3f& vec ) const;
    bool operator!=( const Vec3f& vec ) const;
    bool match( const Vec3f& vec, float tolerance=0.0001 ) const;
    /**
     * Checks if vectors look in the same direction.
     */
    bool isAligned( const Vec3f& vec, float tolerance=0.0001 ) const;
    bool align( const Vec3f& vec, float tolerance=0.0001 ) const;
    bool isAlignedRad( const Vec3f& vec, float tolerance=0.0001 ) const;
    bool alignRad( const Vec3f& vec, float tolerance=0.0001 ) const;
    
    
    // Operator overloading for Vec3f
    //
    Vec3f  operator+( const Vec3f& pnt ) const;
    Vec3f& operator+=( const Vec3f& pnt );
    Vec3f  operator-( const Vec3f& vec ) const;
    Vec3f& operator-=( const Vec3f& vec );
    Vec3f  operator*( const Vec3f& vec ) const;
    Vec3f& operator*=( const Vec3f& vec );
    Vec3f  operator/( const Vec3f& vec ) const;
    Vec3f& operator/=( const Vec3f& vec );
    Vec3f  operator-() const;
    
    //operator overloading for float
    //
    //    void 	  operator=( const float f);
    Vec3f  operator+( const float f ) const;
    Vec3f& operator+=( const float f );
    Vec3f  operator-( const float f ) const;
    Vec3f& operator-=( const float f );
    Vec3f  operator*( const float f ) const;
    Vec3f& operator*=( const float f );
    Vec3f  operator/( const float f ) const;
    Vec3f& operator/=( const float f );
    
    friend std::ostream& operator<<(std::ostream& os, const Vec3f& vec);
    friend std::istream& operator>>(std::istream& is, const Vec3f& vec);
    
    //Scale
    //
    Vec3f  getScaled( const float length ) const;
    Vec3f& scale( const float length );
    
    
    // Rotation
    //
    Vec3f  getRotated( float angle, const Vec3f& axis ) const;
    Vec3f  getRotatedRad( float angle, const Vec3f& axis ) const;
    Vec3f& rotate( float angle, const Vec3f& axis );
    Vec3f& rotateRad( float angle, const Vec3f& axis );
    Vec3f  getRotated(float ax, float ay, float az) const;
    Vec3f  getRotatedRad(float ax, float ay, float az) const;
    Vec3f& rotate(float ax, float ay, float az);
    Vec3f& rotateRad(float ax, float ay, float az);
    
    
    // Rotation - point around pivot
    //
    Vec3f   getRotated( float angle, const Vec3f& pivot, const Vec3f& axis ) const;
    Vec3f&  rotate( float angle, const Vec3f& pivot, const Vec3f& axis );
    Vec3f   getRotatedRad( float angle, const Vec3f& pivot, const Vec3f& axis ) const;
    Vec3f&  rotateRad( float angle, const Vec3f& pivot, const Vec3f& axis );
    
    
    // Map point to coordinate system defined by origin, vx, vy, and vz.
    //
    Vec3f getMapped( const Vec3f& origin,
                    const Vec3f& vx,
                    const Vec3f& vy,
                    const Vec3f& vz ) const;
    Vec3f& map( const Vec3f& origin,
               const Vec3f& vx,
               const Vec3f& vy,
               const Vec3f& vz );
    
    
    // Distance between two points.
    //
    float distance( const Vec3f& pnt) const;
    float squareDistance( const Vec3f& pnt ) const;
    
    
    // Linear interpolation.
    //
    /**
     * p==0.0 results in this point, p==0.5 results in the
     * midpoint, and p==1.0 results in pnt being returned.
     */
    Vec3f   getInterpolated( const Vec3f& pnt, float p ) const;
    Vec3f&  interpolate( const Vec3f& pnt, float p );
    Vec3f   getMiddle( const Vec3f& pnt ) const;
    Vec3f&  middle( const Vec3f& pnt );
    Vec3f&  average( const Vec3f* points, int num );
    
    
    // Normalization
    //
    Vec3f  getNormalized() const;
    Vec3f& normalize();
    
    
    // Limit length.
    //
    Vec3f  getLimited(float max) const;
    Vec3f& limit(float max);
    
    
    // Perpendicular vector.
    //
    Vec3f  getCrossed( const Vec3f& vec ) const;
    Vec3f& cross( const Vec3f& vec );
    /**
     * Normalized perpendicular.
     */
    Vec3f  getPerpendicular( const Vec3f& vec ) const;
    Vec3f& perpendicular( const Vec3f& vec );
    
    
    // Length
    //
    float length() const;
    float squareLength() const;
    /**
     * Angle (deg) between two vectors.
     * This is an unsigned relative angle from 0 to 180.
     * http://www.euclideanspace.com/maths/algebra/vectors/angleBetween/index.htm
     */
    float angle( const Vec3f& vec ) const;
    float angleRad( const Vec3f& vec ) const;
    
    
    // Dot Product
    //
    float dot( const Vec3f& vec ) const;
    
    
    
    //-----------------------------------------------
    // this methods are deprecated in 006 please use:
    
    // getScaled
    Vec3f rescaled( const float length ) const;
    
    // scale
    Vec3f& rescale( const float length );
    
    // getRotated
    Vec3f rotated( float angle, const Vec3f& axis ) const;
    
    // getRotated should this be const???
    Vec3f rotated(float ax, float ay, float az);
    
    // getNormalized
    Vec3f normalized() const;
    
    // getLimited
    Vec3f limited(float max) const;
    
    // getCrossed
    Vec3f crossed( const Vec3f& vec ) const;
    
    // getPerpendicular
    Vec3f perpendiculared( const Vec3f& vec ) const;
    
    // squareLength
    float lengthSquared() const;
    
    // use getMapped
    Vec3f  mapped( const Vec3f& origin,
                  const Vec3f& vx,
                  const Vec3f& vy,
                  const Vec3f& vz ) const;
    
    // use squareDistance
    float  distanceSquared( const Vec3f& pnt ) const;
    
    // use getInterpolated
    Vec3f 	interpolated( const Vec3f& pnt, float p ) const;
    
    // use getMiddle
    Vec3f 	middled( const Vec3f& pnt ) const;
    
    // use getRotated
    Vec3f 	rotated( float angle,
                    const Vec3f& pivot,
                    const Vec3f& axis ) const;
    
    // return all zero vector
    static Vec3f zero() { return Vec3f(0, 0, 0); }
    
    // return all one vector
    static Vec3f one() { return Vec3f(1, 1, 1); }
};




// Non-Member operators
//
//
Vec3f operator+( float f, const Vec3f& vec );
Vec3f operator-( float f, const Vec3f& vec );
Vec3f operator*( float f, const Vec3f& vec );
Vec3f operator/( float f, const Vec3f& vec );


/////////////////
// Implementation
/////////////////
inline Vec3f::Vec3f( float _x, float _y, float _z ):x(_x), y(_y), z(_z) {}


// Getters and Setters.
//
//
inline void Vec3f::set( float _x, float _y, float _z ) {
    x = _x;
    y = _y;
    z = _z;
}

inline void Vec3f::set( const Vec3f& vec ) {
    x = vec.x;
    y = vec.y;
    z = vec.z;
}


// Check similarity/equality.
//
//
inline bool Vec3f::operator==( const Vec3f& vec ) const {
    return (x == vec.x) && (y == vec.y) && (z == vec.z);
}

inline bool Vec3f::operator!=( const Vec3f& vec ) const {
    return (x != vec.x) || (y != vec.y) || (z != vec.z);
}

inline bool Vec3f::match( const Vec3f& vec, float tolerance ) const{
    return (fabs(x - vec.x) < tolerance)
    && (fabs(y - vec.y) < tolerance)
    && (fabs(z - vec.z) < tolerance);
}

/**
 * Checks if vectors look in the same direction.
 */
inline bool Vec3f::isAligned( const Vec3f& vec, float tolerance ) const {
    float angle = this->angle( vec );
    return  angle < tolerance;
}
inline bool Vec3f::align( const Vec3f& vec, float tolerance ) const {
    return isAligned( vec, tolerance );
}

inline bool Vec3f::isAlignedRad( const Vec3f& vec, float tolerance ) const {
    float angle = this->angleRad( vec );
    return  angle < tolerance;
}
inline bool Vec3f::alignRad( const Vec3f& vec, float tolerance ) const {
    return isAlignedRad( vec, tolerance );
}


// Operator overloading for Vec3f
//
//

inline std::ostream& operator<<(std::ostream& os, const Vec3f& vec) {
    os << vec.x << ", " << vec.y << ", " << vec.z;
    return os;
}

inline std::istream& operator>>(std::istream& is, Vec3f& vec) {
    is >> vec.x;
    is.ignore(2);
    is >> vec.y;
    is.ignore(2);
    is >> vec.z;
    return is;
}

inline Vec3f Vec3f::operator+( const Vec3f& pnt ) const {
    return Vec3f( x+pnt.x, y+pnt.y, z+pnt.z );
}

inline Vec3f& Vec3f::operator+=( const Vec3f& pnt ) {
    x+=pnt.x;
    y+=pnt.y;
    z+=pnt.z;
    return *this;
}

inline Vec3f Vec3f::operator-( const Vec3f& vec ) const {
    return Vec3f( x-vec.x, y-vec.y, z-vec.z );
}

inline Vec3f& Vec3f::operator-=( const Vec3f& vec ) {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}

inline Vec3f Vec3f::operator*( const Vec3f& vec ) const {
    return Vec3f( x*vec.x, y*vec.y, z*vec.z );
}

inline Vec3f& Vec3f::operator*=( const Vec3f& vec ) {
    x*=vec.x;
    y*=vec.y;
    z*=vec.z;
    return *this;
}

inline Vec3f Vec3f::operator/( const Vec3f& vec ) const {
    return Vec3f( vec.x!=0 ? x/vec.x : x , vec.y!=0 ? y/vec.y : y, vec.z!=0 ? z/vec.z : z );
}

inline Vec3f& Vec3f::operator/=( const Vec3f& vec ) {
    vec.x!=0 ? x/=vec.x : x;
    vec.y!=0 ? y/=vec.y : y;
    vec.z!=0 ? z/=vec.z : z;
    return *this;
}

inline Vec3f Vec3f::operator-() const {
    return Vec3f( -x, -y, -z );
}


//operator overloading for float
//
//
//inline void Vec3f::operator=( const float f){
//	x = f;
//	y = f;
//	z = f;
//}

inline Vec3f Vec3f::operator+( const float f ) const {
    return Vec3f( x+f, y+f, z+f);
}

inline Vec3f& Vec3f::operator+=( const float f ) {
    x += f;
    y += f;
    z += f;
    return *this;
}

inline Vec3f Vec3f::operator-( const float f ) const {
    return Vec3f( x-f, y-f, z-f);
}

inline Vec3f& Vec3f::operator-=( const float f ) {
    x -= f;
    y -= f;
    z -= f;
    return *this;
}

inline Vec3f Vec3f::operator*( const float f ) const {
    return Vec3f( x*f, y*f, z*f );
}

inline Vec3f& Vec3f::operator*=( const float f ) {
    x*=f;
    y*=f;
    z*=f;
    return *this;
}

inline Vec3f Vec3f::operator/( const float f ) const {
    if(f == 0) return Vec3f( x, y, z);
    
    return Vec3f( x/f, y/f, z/f );
}

inline Vec3f& Vec3f::operator/=( const float f ) {
    if(f == 0) return *this;
    
    x/=f;
    y/=f;
    z/=f;
    return *this;
}


//Scale
//
//
inline Vec3f Vec3f::rescaled( const float length ) const {
    return getScaled(length);
}
inline Vec3f Vec3f::getScaled( const float length ) const {
    float l = (float)sqrt(x*x + y*y + z*z);
    if( l > 0 )
        return Vec3f( (x/l)*length, (y/l)*length, (z/l)*length );
    else
        return Vec3f();
}
inline Vec3f& Vec3f::rescale( const float length ) {
    return scale(length);
}
inline Vec3f& Vec3f::scale( const float length ) {
    float l = (float)sqrt(x*x + y*y + z*z);
    if (l > 0) {
        x = (x/l)*length;
        y = (y/l)*length;
        z = (z/l)*length;
    }
    return *this;
}



// Rotation
//
//
inline Vec3f Vec3f::rotated( float angle, const Vec3f& axis ) const {
    return getRotated(angle, axis);
}
inline Vec3f Vec3f::getRotated( float angle, const Vec3f& axis ) const {
    Vec3f ax = axis.normalized();
    float a = (float)(angle*DEG_TO_RAD);
    float sina = sin( a );
    float cosa = cos( a );
    float cosb = 1.0f - cosa;
    
    return Vec3f( x*(ax.x*ax.x*cosb + cosa)
                 + y*(ax.x*ax.y*cosb - ax.z*sina)
                 + z*(ax.x*ax.z*cosb + ax.y*sina),
                 x*(ax.y*ax.x*cosb + ax.z*sina)
                 + y*(ax.y*ax.y*cosb + cosa)
                 + z*(ax.y*ax.z*cosb - ax.x*sina),
                 x*(ax.z*ax.x*cosb - ax.y*sina)
                 + y*(ax.z*ax.y*cosb + ax.x*sina)
                 + z*(ax.z*ax.z*cosb + cosa) );
}

inline Vec3f Vec3f::getRotatedRad( float angle, const Vec3f& axis ) const {
    Vec3f ax = axis.normalized();
    float a = angle;
    float sina = sin( a );
    float cosa = cos( a );
    float cosb = 1.0f - cosa;
    
    return Vec3f( x*(ax.x*ax.x*cosb + cosa)
                 + y*(ax.x*ax.y*cosb - ax.z*sina)
                 + z*(ax.x*ax.z*cosb + ax.y*sina),
                 x*(ax.y*ax.x*cosb + ax.z*sina)
                 + y*(ax.y*ax.y*cosb + cosa)
                 + z*(ax.y*ax.z*cosb - ax.x*sina),
                 x*(ax.z*ax.x*cosb - ax.y*sina)
                 + y*(ax.z*ax.y*cosb + ax.x*sina)
                 + z*(ax.z*ax.z*cosb + cosa) );
}

inline Vec3f& Vec3f::rotate( float angle, const Vec3f& axis ) {
    Vec3f ax = axis.normalized();
    float a = (float)(angle*DEG_TO_RAD);
    float sina = sin( a );
    float cosa = cos( a );
    float cosb = 1.0f - cosa;
    
    float nx = x*(ax.x*ax.x*cosb + cosa)
    + y*(ax.x*ax.y*cosb - ax.z*sina)
    + z*(ax.x*ax.z*cosb + ax.y*sina);
    float ny = x*(ax.y*ax.x*cosb + ax.z*sina)
    + y*(ax.y*ax.y*cosb + cosa)
    + z*(ax.y*ax.z*cosb - ax.x*sina);
    float nz = x*(ax.z*ax.x*cosb - ax.y*sina)
    + y*(ax.z*ax.y*cosb + ax.x*sina)
    + z*(ax.z*ax.z*cosb + cosa);
    x = nx; y = ny; z = nz;
    return *this;
}


inline Vec3f& Vec3f::rotateRad(float angle, const Vec3f& axis ) {
    Vec3f ax = axis.normalized();
    float a = angle;
    float sina = sin( a );
    float cosa = cos( a );
    float cosb = 1.0f - cosa;
    
    float nx = x*(ax.x*ax.x*cosb + cosa)
    + y*(ax.x*ax.y*cosb - ax.z*sina)
    + z*(ax.x*ax.z*cosb + ax.y*sina);
    float ny = x*(ax.y*ax.x*cosb + ax.z*sina)
    + y*(ax.y*ax.y*cosb + cosa)
    + z*(ax.y*ax.z*cosb - ax.x*sina);
    float nz = x*(ax.z*ax.x*cosb - ax.y*sina)
    + y*(ax.z*ax.y*cosb + ax.x*sina)
    + z*(ax.z*ax.z*cosb + cosa);
    x = nx; y = ny; z = nz;
    return *this;
}

// const???
inline Vec3f Vec3f::rotated(float ax, float ay, float az) {
    return getRotated(ax,ay,az);
}

inline Vec3f Vec3f::getRotated(float ax, float ay, float az) const {
    float a = (float)cos(DEG_TO_RAD*(ax));
    float b = (float)sin(DEG_TO_RAD*(ax));
    float c = (float)cos(DEG_TO_RAD*(ay));
    float d = (float)sin(DEG_TO_RAD*(ay));
    float e = (float)cos(DEG_TO_RAD*(az));
    float f = (float)sin(DEG_TO_RAD*(az));
    
    float nx = c * e * x - c * f * y + d * z;
    float ny = (a * f + b * d * e) * x + (a * e - b * d * f) * y - b * c * z;
    float nz = (b * f - a * d * e) * x + (a * d * f + b * e) * y + a * c * z;
    
    return Vec3f( nx, ny, nz );
}

inline Vec3f Vec3f::getRotatedRad(float ax, float ay, float az) const {
    float a = cos(ax);
    float b = sin(ax);
    float c = cos(ay);
    float d = sin(ay);
    float e = cos(az);
    float f = sin(az);
    
    float nx = c * e * x - c * f * y + d * z;
    float ny = (a * f + b * d * e) * x + (a * e - b * d * f) * y - b * c * z;
    float nz = (b * f - a * d * e) * x + (a * d * f + b * e) * y + a * c * z;
    
    return Vec3f( nx, ny, nz );
}


inline Vec3f& Vec3f::rotate(float ax, float ay, float az) {
    float a = (float)cos(DEG_TO_RAD*(ax));
    float b = (float)sin(DEG_TO_RAD*(ax));
    float c = (float)cos(DEG_TO_RAD*(ay));
    float d = (float)sin(DEG_TO_RAD*(ay));
    float e = (float)cos(DEG_TO_RAD*(az));
    float f = (float)sin(DEG_TO_RAD*(az));
    
    float nx = c * e * x - c * f * y + d * z;
    float ny = (a * f + b * d * e) * x + (a * e - b * d * f) * y - b * c * z;
    float nz = (b * f - a * d * e) * x + (a * d * f + b * e) * y + a * c * z;
    
    x = nx; y = ny; z = nz;
    return *this;
}


inline Vec3f& Vec3f::rotateRad(float ax, float ay, float az) {
    float a = cos(ax);
    float b = sin(ax);
    float c = cos(ay);
    float d = sin(ay);
    float e = cos(az);
    float f = sin(az);
    
    float nx = c * e * x - c * f * y + d * z;
    float ny = (a * f + b * d * e) * x + (a * e - b * d * f) * y - b * c * z;
    float nz = (b * f - a * d * e) * x + (a * d * f + b * e) * y + a * c * z;
    
    x = nx; y = ny; z = nz;
    return *this;
}


// Rotate point by angle (deg) around line defined by pivot and axis.
//
//
inline Vec3f Vec3f::rotated( float angle,
                            const Vec3f& pivot,
                            const Vec3f& axis ) const{
    return getRotated(angle, pivot, axis);
}

inline Vec3f Vec3f::getRotated( float angle,
                               const Vec3f& pivot,
                               const Vec3f& axis ) const
{
    Vec3f ax = axis.normalized();
    float tx = x - pivot.x;
    float ty = y - pivot.y;
    float tz = z - pivot.z;
    
    float a = (float)(angle*DEG_TO_RAD);
    float sina = sin( a );
    float cosa = cos( a );
    float cosb = 1.0f - cosa;
    
    float xrot = tx*(ax.x*ax.x*cosb + cosa)
    + ty*(ax.x*ax.y*cosb - ax.z*sina)
    + tz*(ax.x*ax.z*cosb + ax.y*sina);
    float yrot = tx*(ax.y*ax.x*cosb + ax.z*sina)
    + ty*(ax.y*ax.y*cosb + cosa)
    + tz*(ax.y*ax.z*cosb - ax.x*sina);
    float zrot = tx*(ax.z*ax.x*cosb - ax.y*sina)
    + ty*(ax.z*ax.y*cosb + ax.x*sina)
    + tz*(ax.z*ax.z*cosb + cosa);
    
    
    return Vec3f( xrot+pivot.x, yrot+pivot.y, zrot+pivot.z );
}


inline Vec3f Vec3f::getRotatedRad( float angle,
                                  const Vec3f& pivot,
                                  const Vec3f& axis ) const
{
    Vec3f ax = axis.normalized();
    float tx = x - pivot.x;
    float ty = y - pivot.y;
    float tz = z - pivot.z;
    
    float a = angle;
    float sina = sin( a );
    float cosa = cos( a );
    float cosb = 1.0f - cosa;
    
    float xrot = tx*(ax.x*ax.x*cosb + cosa)
    + ty*(ax.x*ax.y*cosb - ax.z*sina)
    + tz*(ax.x*ax.z*cosb + ax.y*sina);
    float yrot = tx*(ax.y*ax.x*cosb + ax.z*sina)
    + ty*(ax.y*ax.y*cosb + cosa)
    + tz*(ax.y*ax.z*cosb - ax.x*sina);
    float zrot = tx*(ax.z*ax.x*cosb - ax.y*sina)
    + ty*(ax.z*ax.y*cosb + ax.x*sina)
    + tz*(ax.z*ax.z*cosb + cosa);
    
    
    return Vec3f( xrot+pivot.x, yrot+pivot.y, zrot+pivot.z );
}


inline Vec3f& Vec3f::rotate( float angle,
                            const Vec3f& pivot,
                            const Vec3f& axis )
{
    Vec3f ax = axis.normalized();
    x -= pivot.x;
    y -= pivot.y;
    z -= pivot.z;
    
    float a = (float)(angle*DEG_TO_RAD);
    float sina = sin( a );
    float cosa = cos( a );
    float cosb = 1.0f - cosa;
    
    float xrot = x*(ax.x*ax.x*cosb + cosa)
    + y*(ax.x*ax.y*cosb - ax.z*sina)
    + z*(ax.x*ax.z*cosb + ax.y*sina);
    float yrot = x*(ax.y*ax.x*cosb + ax.z*sina)
    + y*(ax.y*ax.y*cosb + cosa)
    + z*(ax.y*ax.z*cosb - ax.x*sina);
    float zrot = x*(ax.z*ax.x*cosb - ax.y*sina)
    + y*(ax.z*ax.y*cosb + ax.x*sina)
    + z*(ax.z*ax.z*cosb + cosa);
    
    x = xrot + pivot.x;
    y = yrot + pivot.y;
    z = zrot + pivot.z;
    
    return *this;
}


inline Vec3f& Vec3f::rotateRad( float angle,
                               const Vec3f& pivot,
                               const Vec3f& axis )
{
    Vec3f ax = axis.normalized();
    x -= pivot.x;
    y -= pivot.y;
    z -= pivot.z;
    
    float a = angle;
    float sina = sin( a );
    float cosa = cos( a );
    float cosb = 1.0f - cosa;
    
    float xrot = x*(ax.x*ax.x*cosb + cosa)
    + y*(ax.x*ax.y*cosb - ax.z*sina)
    + z*(ax.x*ax.z*cosb + ax.y*sina);
    float yrot = x*(ax.y*ax.x*cosb + ax.z*sina)
    + y*(ax.y*ax.y*cosb + cosa)
    + z*(ax.y*ax.z*cosb - ax.x*sina);
    float zrot = x*(ax.z*ax.x*cosb - ax.y*sina)
    + y*(ax.z*ax.y*cosb + ax.x*sina)
    + z*(ax.z*ax.z*cosb + cosa);
    
    x = xrot + pivot.x;
    y = yrot + pivot.y;
    z = zrot + pivot.z;
    
    return *this;
}




// Map point to coordinate system defined by origin, vx, vy, and vz.
//
//
inline Vec3f Vec3f::mapped( const Vec3f& origin,
                           const Vec3f& vx,
                           const Vec3f& vy,
                           const Vec3f& vz ) const{
    return getMapped(origin, vx, vy, vz);
}

inline Vec3f Vec3f::getMapped( const Vec3f& origin,
                              const Vec3f& vx,
                              const Vec3f& vy,
                              const Vec3f& vz ) const
{
    return Vec3f( origin.x + x*vx.x + y*vy.x + z*vz.x,
                 origin.y + x*vx.y + y*vy.y + z*vz.y,
                 origin.z + x*vx.z + y*vy.z + z*vz.z );
}

inline Vec3f& Vec3f::map( const Vec3f& origin,
                         const Vec3f& vx,
                         const Vec3f& vy,
                         const Vec3f& vz )
{
    float xmap = origin.x + x*vx.x + y*vy.x + z*vz.x;
    float ymap =  origin.y + x*vx.y + y*vy.y + z*vz.y;
    z = origin.z + x*vx.z + y*vy.z + z*vz.z;
    x = xmap;
    y = ymap;
    return *this;
}


// Distance between two points.
//
//
inline float Vec3f::distance( const Vec3f& pnt) const {
    float vx = x-pnt.x;
    float vy = y-pnt.y;
    float vz = z-pnt.z;
    return (float)sqrt(vx*vx + vy*vy + vz*vz);
}

inline float  Vec3f::distanceSquared( const Vec3f& pnt ) const{
    return squareDistance(pnt);
}

inline float  Vec3f::squareDistance( const Vec3f& pnt ) const {
    float vx = x-pnt.x;
    float vy = y-pnt.y;
    float vz = z-pnt.z;
    return vx*vx + vy*vy + vz*vz;
}



// Linear interpolation.
//
//
/**
 * p==0.0 results in this point, p==0.5 results in the
 * midpoint, and p==1.0 results in pnt being returned.
 */

inline Vec3f Vec3f::interpolated( const Vec3f& pnt, float p ) const {
    return getInterpolated(pnt,p);
}

inline Vec3f Vec3f::getInterpolated( const Vec3f& pnt, float p ) const {
    return Vec3f( x*(1-p) + pnt.x*p,
                 y*(1-p) + pnt.y*p,
                 z*(1-p) + pnt.z*p );
}

inline Vec3f& Vec3f::interpolate( const Vec3f& pnt, float p ) {
    x = x*(1-p) + pnt.x*p;
    y = y*(1-p) + pnt.y*p;
    z = z*(1-p) + pnt.z*p;
    return *this;
}


inline Vec3f Vec3f::middled( const Vec3f& pnt ) const {
    return getMiddle(pnt);
}

inline Vec3f Vec3f::getMiddle( const Vec3f& pnt ) const {
    return Vec3f( (x+pnt.x)/2.0f, (y+pnt.y)/2.0f, (z+pnt.z)/2.0f );
}

inline Vec3f& Vec3f::middle( const Vec3f& pnt ) {
    x = (x+pnt.x)/2.0f;
    y = (y+pnt.y)/2.0f;
    z = (z+pnt.z)/2.0f;
    return *this;
}


// Average (centroid) among points.
// Addition is sometimes useful for calculating averages too.
//
//
inline Vec3f& Vec3f::average( const Vec3f* points, int num ) {
    x = 0.f;
    y = 0.f;
    z = 0.f;
    for( int i=0; i<num; i++) {
        x += points[i].x;
        y += points[i].y;
        z += points[i].z;
    }
    x /= num;
    y /= num;
    z /= num;
    return *this;
}



// Normalization
//
//
inline Vec3f Vec3f::normalized() const {
    return getNormalized();
}

inline Vec3f Vec3f::getNormalized() const {
    float length = (float)sqrt(x*x + y*y + z*z);
    if( length > 0 ) {
        return Vec3f( x/length, y/length, z/length );
    } else {
        return Vec3f();
    }
}

inline Vec3f& Vec3f::normalize() {
    float length = (float)sqrt(x*x + y*y + z*z);
    if( length > 0 ) {
        x /= length;
        y /= length;
        z /= length;
    }
    return *this;
}



// Limit length.
//
//

inline Vec3f Vec3f::limited(float max) const {
    return getLimited(max);
}

inline Vec3f Vec3f::getLimited(float max) const {
    Vec3f limited;
    float lengthSquared = (x*x + y*y + z*z);
    if( lengthSquared > max*max && lengthSquared > 0 ) {
        float ratio = max/(float)sqrt(lengthSquared);
        limited.set( x*ratio, y*ratio, z*ratio);
    } else {
        limited.set(x,y,z);
    }
    return limited;
}

inline Vec3f& Vec3f::limit(float max) {
    float lengthSquared = (x*x + y*y + z*z);
    if( lengthSquared > max*max && lengthSquared > 0 ) {
        float ratio = max/(float)sqrt(lengthSquared);
        x *= ratio;
        y *= ratio;
        z *= ratio;
    }
    return *this;
}


// Perpendicular vector.
//
//
inline Vec3f Vec3f::crossed( const Vec3f& vec ) const {
    return getCrossed(vec);
}
inline Vec3f Vec3f::getCrossed( const Vec3f& vec ) const {
    return Vec3f( y*vec.z - z*vec.y,
                 z*vec.x - x*vec.z,
                 x*vec.y - y*vec.x );
}

inline Vec3f& Vec3f::cross( const Vec3f& vec ) {
    float _x = y*vec.z - z*vec.y;
    float _y = z*vec.x - x*vec.z;
    z = x*vec.y - y*vec.x;
    x = _x;
    y = _y;
    return *this;
}

/**
 * Normalized perpendicular.
 */
inline Vec3f Vec3f::perpendiculared( const Vec3f& vec ) const {
    return getPerpendicular(vec);
}

inline Vec3f Vec3f::getPerpendicular( const Vec3f& vec ) const {
    float crossX = y*vec.z - z*vec.y;
    float crossY = z*vec.x - x*vec.z;
    float crossZ = x*vec.y - y*vec.x;
    
    float length = (float)sqrt(crossX*crossX +
                               crossY*crossY +
                               crossZ*crossZ);
    
    if( length > 0 )
        return Vec3f( crossX/length, crossY/length, crossZ/length );
    else
        return Vec3f();
}

inline Vec3f& Vec3f::perpendicular( const Vec3f& vec ) {
    float crossX = y*vec.z - z*vec.y;
    float crossY = z*vec.x - x*vec.z;
    float crossZ = x*vec.y - y*vec.x;
    
    float length = (float)sqrt(crossX*crossX +
                               crossY*crossY +
                               crossZ*crossZ);
    
    if( length > 0 ) {
        x = crossX/length;
        y = crossY/length;
        z = crossZ/length;
    } else {
        x = 0.f;
        y = 0.f;
        z = 0.f;
    }
    
    return *this;
}


// Length
//
//
inline float Vec3f::length() const {
    return (float)sqrt( x*x + y*y + z*z );
}

inline float Vec3f::lengthSquared() const {
    return squareLength();
}

inline float Vec3f::squareLength() const {
    return (float)(x*x + y*y + z*z);
}



/**
 * Angle (deg) between two vectors.
 * This is an unsigned relative angle from 0 to 180.
 * http://www.euclideanspace.com/maths/algebra/vectors/angleBetween/index.htm
 */
inline float Vec3f::angle( const Vec3f& vec ) const {
    Vec3f n1 = this->normalized();
    Vec3f n2 = vec.normalized();
    return (float)(acos( n1.dot(n2) )*RAD_TO_DEG);
}

inline float Vec3f::angleRad( const Vec3f& vec ) const {
    Vec3f n1 = this->normalized();
    Vec3f n2 = vec.normalized();
    return (float)acos( n1.dot(n2) );
}



/**
 * Dot Product.
 */
inline float Vec3f::dot( const Vec3f& vec ) const {
    return x*vec.x + y*vec.y + z*vec.z;
}





// Non-Member operators
//
//
inline Vec3f operator+( float f, const Vec3f& vec ) {
    return Vec3f( f+vec.x, f+vec.y, f+vec.z );
}

inline Vec3f operator-( float f, const Vec3f& vec ) {
    return Vec3f( f-vec.x, f-vec.y, f-vec.z );
}

inline Vec3f operator*( float f, const Vec3f& vec ) {
    return Vec3f( f*vec.x, f*vec.y, f*vec.z );
}

inline Vec3f operator/( float f, const Vec3f& vec ) {
    return Vec3f( f/vec.x, f/vec.y, f/vec.z);
}

FL_NAMESPACE_END