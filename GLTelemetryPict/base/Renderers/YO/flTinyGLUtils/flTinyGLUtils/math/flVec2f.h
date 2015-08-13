/* port from oF */

#pragma once

#include "flMath.h"
#include "flCommon.h"

FL_NAMESPACE_BEGIN

class Vec2f {
public:
    float x, y;
    
    static const int DIM = 2;
    
    Vec2f( float _x=0.f, float _y=0.f );
    
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
    void set( float _x, float _y );
    void set( const Vec2f& vec );
    
    // Check similarity/equality.
    //
    bool operator==( const Vec2f& vec ) const;
    bool operator!=( const Vec2f& vec ) const;
    bool match( const Vec2f& vec, float tolerance=0.0001 ) const;
    /**
     * Checks if vectors look in the same direction.
     * Tolerance is specified in degree.
     */
    bool isAligned( const Vec2f& vec, float tolerance=0.0001 ) const;
    bool isAlignedRad( const Vec2f& vec, float tolerance=0.0001 ) const;
    bool align( const Vec2f& vec, float tolerance=0.0001 ) const;
    bool alignRad( const Vec2f& vec, float tolerance=0.0001 ) const;
    
    
    // Overloading for any type to any type
    //
    Vec2f  operator+( const Vec2f& vec ) const;
    Vec2f& operator+=( const Vec2f& vec );
    Vec2f  operator-( const Vec2f& vec ) const;
    Vec2f& operator-=( const Vec2f& vec );
    Vec2f  operator*( const Vec2f& vec ) const;
    Vec2f& operator*=( const Vec2f& vec );
    Vec2f  operator/( const Vec2f& vec ) const;
    Vec2f& operator/=( const Vec2f& vec );
    
    
    //operator overloading for float
    //
    //    void 	  operator=( const float f);
    Vec2f  operator+( const float f ) const;
    Vec2f& operator+=( const float f );
    Vec2f  operator-( const float f ) const;
    Vec2f& operator-=( const float f );
    Vec2f  operator-() const;
    Vec2f  operator*( const float f ) const;
    Vec2f& operator*=( const float f );
    Vec2f  operator/( const float f ) const;
    Vec2f& operator/=( const float f );
    
    friend std::ostream& operator<<(std::ostream& os, const Vec2f& vec);
    friend std::istream& operator>>(std::istream& is, const Vec2f& vec);
    
    // Scaling
    //
    Vec2f  getScaled( const float length ) const;
    Vec2f& scale( const float length );
    
    
    // Rotation
    //
    Vec2f  getRotated( float angle ) const;
    Vec2f  getRotatedRad( float angle ) const;
    Vec2f& rotate( float angle );
    Vec2f& rotateRad( float angle );
    
    
    // Rotation - point around pivot
    //
    Vec2f  getRotated( float angle, const Vec2f& pivot ) const;
    Vec2f& rotate( float angle, const Vec2f& pivot );
    Vec2f  getRotatedRad( float angle, const Vec2f& pivot ) const;
    Vec2f& rotateRad( float angle, const Vec2f& pivot );
    
    
    // Map point to coordinate system defined by origin, vx, and vy.
    //
    Vec2f getMapped( const Vec2f& origin,
                    const Vec2f& vx,
                    const Vec2f& vy ) const;
    Vec2f& map( const Vec2f& origin,
               const Vec2f& vx, const Vec2f& vy );
    
    
    // Distance between two points.
    //
    float distance( const Vec2f& pnt) const;
    float squareDistance( const Vec2f& pnt ) const;
    
    
    // Linear interpolation.
    //
    //
    /**
     * p==0.0 results in this point, p==0.5 results in the
     * midpoint, and p==1.0 results in pnt being returned.
     */
    Vec2f   getInterpolated( const Vec2f& pnt, float p ) const;
    Vec2f&  interpolate( const Vec2f& pnt, float p );
    Vec2f   getMiddle( const Vec2f& pnt ) const;
    Vec2f&  middle( const Vec2f& pnt );
    Vec2f&  average( const Vec2f* points, int num );
    
    
    // Normalization
    //
    Vec2f  getNormalized() const;
    Vec2f& normalize();
    
    
    // Limit length.
    //
    Vec2f  getLimited(float max) const;
    Vec2f& limit(float max);
    
    
    // Perpendicular normalized vector.
    //
    Vec2f  getPerpendicular() const;
    Vec2f& perpendicular();
    
    
    // Length
    //
    float length() const;
    float squareLength() const;
    
    
    /**
     * Angle (deg) between two vectors.
     * This is a signed relative angle between -180 and 180.
     */
    float angle( const Vec2f& vec ) const;
    float angleRad( const Vec2f& vec ) const;
    
    
    /**
     * Dot Product.
     */
    float dot( const Vec2f& vec ) const;
    
    
    
    //---------------------------------------------------
    // this methods are deprecated in 006 please use:
    
    // getScaled
    Vec2f rescaled( const float length ) const;
    
    // scale
    Vec2f& rescale( const float length );
    
    // getRotated
    Vec2f rotated( float angle ) const;
    
    // getNormalized
    Vec2f normalized() const;
    
    // getLimited
    Vec2f limited(float max) const;
    
    // getPerpendicular
    Vec2f perpendiculared() const;
    
    // squareLength
    float lengthSquared() const;
    
    // getInterpolated
    Vec2f interpolated( const Vec2f& pnt, float p ) const;
    
    // getMiddled
    Vec2f middled( const Vec2f& pnt ) const;
    
    // getMapped
    Vec2f mapped( const Vec2f& origin, const Vec2f& vx, const Vec2f& vy ) const;
    
    // squareDistance
    float distanceSquared( const Vec2f& pnt ) const;
    
    // use getRotated
    Vec2f rotated( float angle, const Vec2f& pivot ) const;
    
    // return all zero vector
    static Vec2f zero() { return Vec2f(0, 0); }
    
    // return all one vector
    static Vec2f one() { return Vec2f(1, 1); }
};





// Non-Member operators
//
Vec2f operator+( float f, const Vec2f& vec );
Vec2f operator-( float f, const Vec2f& vec );
Vec2f operator*( float f, const Vec2f& vec );
Vec2f operator/( float f, const Vec2f& vec );







/////////////////
// Implementation
/////////////////


inline Vec2f::Vec2f( float _x, float _y ):x(_x), y(_y) {}


// Getters and Setters.
//
//
inline void Vec2f::set( float _x, float _y ) {
    x = _x;
    y = _y;
}

inline void Vec2f::set( const Vec2f& vec ) {
    x = vec.x;
    y = vec.y;
}


// Check similarity/equality.
//
//
inline bool Vec2f::operator==( const Vec2f& vec ) const {
    return (x == vec.x) && (y == vec.y);
}

inline bool Vec2f::operator!=( const Vec2f& vec ) const {
    return (x != vec.x) || (y != vec.y);
}

inline bool Vec2f::match( const Vec2f& vec, float tolerance ) const {
    return (fabs(x - vec.x) < tolerance)
    && (fabs(y - vec.y) < tolerance);
}

/**
 * Checks if vectors look in the same direction.
 * Tolerance is specified in degree.
 */
inline bool Vec2f::isAligned( const Vec2f& vec, float tolerance ) const {
    return  fabs( this->angle( vec ) ) < tolerance;
}
inline bool Vec2f::align( const Vec2f& vec, float tolerance ) const {
    return isAligned( vec, tolerance );
}

inline bool Vec2f::isAlignedRad( const Vec2f& vec, float tolerance ) const {
    return  fabs( this->angleRad( vec ) ) < tolerance;
}
inline bool Vec2f::alignRad( const Vec2f& vec, float tolerance ) const {
    return isAlignedRad( vec, tolerance );
}


// Overloading for any type to any type
//
//

inline Vec2f Vec2f::operator+( const Vec2f& vec ) const {
    return Vec2f( x+vec.x, y+vec.y);
}

inline Vec2f& Vec2f::operator+=( const Vec2f& vec ) {
    x += vec.x;
    y += vec.y;
    return *this;
}

inline Vec2f Vec2f::operator-( const Vec2f& vec ) const {
    return Vec2f(x-vec.x, y-vec.y);
}

inline Vec2f& Vec2f::operator-=( const Vec2f& vec ) {
    x -= vec.x;
    y -= vec.y;
    return *this;
}

inline Vec2f Vec2f::operator*( const Vec2f& vec ) const {
    return Vec2f(x*vec.x, y*vec.y);
}

inline Vec2f& Vec2f::operator*=( const Vec2f& vec ) {
    x*=vec.x;
    y*=vec.y;
    return *this;
}

inline Vec2f Vec2f::operator/( const Vec2f& vec ) const {
    return Vec2f( vec.x!=0 ? x/vec.x : x , vec.y!=0 ? y/vec.y : y);
}

inline Vec2f& Vec2f::operator/=( const Vec2f& vec ) {
    vec.x!=0 ? x/=vec.x : x;
    vec.y!=0 ? y/=vec.y : y;
    return *this;
}

inline std::ostream& operator<<(std::ostream& os, const Vec2f& vec) {
    os << vec.x << ", " << vec.y;
    return os;
}

inline std::istream& operator>>(std::istream& is, Vec2f& vec) {
    is >> vec.x;
    is.ignore(2);
    is >> vec.y;
    return is;
}

//operator overloading for float
//
//
//inline void Vec2f::operator=( const float f){
//	x = f;
//	y = f;
//}

inline Vec2f Vec2f::operator+( const float f ) const {
    return Vec2f( x+f, y+f);
}

inline Vec2f& Vec2f::operator+=( const float f ) {
    x += f;
    y += f;
    return *this;
}

inline Vec2f Vec2f::operator-( const float f ) const {
    return Vec2f( x-f, y-f);
}

inline Vec2f& Vec2f::operator-=( const float f ) {
    x -= f;
    y -= f;
    return *this;
}

inline Vec2f Vec2f::operator-() const {
    return Vec2f(-x, -y);
}

inline Vec2f Vec2f::operator*( const float f ) const {
    return Vec2f(x*f, y*f);
}

inline Vec2f& Vec2f::operator*=( const float f ) {
    x*=f;
    y*=f;
    return *this;
}

inline Vec2f Vec2f::operator/( const float f ) const {
    if(f == 0) return Vec2f(x, y);
    
    return Vec2f(x/f, y/f);
}

inline Vec2f& Vec2f::operator/=( const float f ) {
    if(f == 0) return *this;
    
    x/=f;
    y/=f;
    return *this;
}

inline Vec2f Vec2f::rescaled( const float length ) const {
    return getScaled(length);
}

inline Vec2f Vec2f::getScaled( const float length ) const {
    float l = (float)sqrt(x*x + y*y);
    if( l > 0 )
        return Vec2f( (x/l)*length, (y/l)*length );
    else
        return Vec2f();
}

inline Vec2f& Vec2f::rescale( const float length ){
    return scale(length);
}

inline Vec2f& Vec2f::scale( const float length ) {
    float l = (float)sqrt(x*x + y*y);
    if (l > 0) {
        x = (x/l)*length;
        y = (y/l)*length;
    }
    return *this;
}



// Rotation
//
//
inline Vec2f Vec2f::rotated( float angle ) const {
    return getRotated(angle);
}

inline Vec2f Vec2f::getRotated( float angle ) const {
    float a = (float)(angle*DEG_TO_RAD);
    return Vec2f( x*cos(a) - y*sin(a),
                 x*sin(a) + y*cos(a) );
}

inline Vec2f Vec2f::getRotatedRad( float angle ) const {
    float a = angle;
    return Vec2f( x*cos(a) - y*sin(a),
                 x*sin(a) + y*cos(a) );
}

inline Vec2f& Vec2f::rotate( float angle ) {
    float a = (float)(angle * DEG_TO_RAD);
    float xrot = x*cos(a) - y*sin(a);
    y = x*sin(a) + y*cos(a);
    x = xrot;
    return *this;
}

inline Vec2f& Vec2f::rotateRad( float angle ) {
    float a = angle;
    float xrot = x*cos(a) - y*sin(a);
    y = x*sin(a) + y*cos(a);
    x = xrot;
    return *this;
}



// Rotate point by angle (deg) around pivot point.
//
//

// This method is deprecated in 006 please use getRotated instead
inline Vec2f Vec2f::rotated( float angle, const Vec2f& pivot ) const {
    return getRotated(angle, pivot);
}

inline Vec2f Vec2f::getRotated( float angle, const Vec2f& pivot ) const {
    float a = (float)(angle * DEG_TO_RAD);
    return Vec2f( ((x-pivot.x)*cos(a) - (y-pivot.y)*sin(a)) + pivot.x,
                 ((x-pivot.x)*sin(a) + (y-pivot.y)*cos(a)) + pivot.y );
}

inline Vec2f& Vec2f::rotate( float angle, const Vec2f& pivot ) {
    float a = (float)(angle * DEG_TO_RAD);
    float xrot = ((x-pivot.x)*cos(a) - (y-pivot.y)*sin(a)) + pivot.x;
    y = ((x-pivot.x)*sin(a) + (y-pivot.y)*cos(a)) + pivot.y;
    x = xrot;
    return *this;
}

inline Vec2f Vec2f::getRotatedRad( float angle, const Vec2f& pivot ) const {
    float a = angle;
    return Vec2f( ((x-pivot.x)*cos(a) - (y-pivot.y)*sin(a)) + pivot.x,
                 ((x-pivot.x)*sin(a) + (y-pivot.y)*cos(a)) + pivot.y );
}

inline Vec2f& Vec2f::rotateRad( float angle, const Vec2f& pivot ) {
    float a = angle;
    float xrot = ((x-pivot.x)*cos(a) - (y-pivot.y)*sin(a)) + pivot.x;
    y = ((x-pivot.x)*sin(a) + (y-pivot.y)*cos(a)) + pivot.y;
    x = xrot;
    return *this;
}



// Map point to coordinate system defined by origin, vx, and vy.
//
//

// This method is deprecated in 006 please use getMapped instead
inline Vec2f Vec2f::mapped( const Vec2f& origin,
                           const Vec2f& vx,
                           const Vec2f& vy ) const{
    return getMapped(origin, vx, vy);
}

inline Vec2f Vec2f::getMapped( const Vec2f& origin,
                              const Vec2f& vx,
                              const Vec2f& vy ) const
{
    return Vec2f( origin.x + x*vx.x + y*vy.x,
                 origin.y + x*vx.y + y*vy.y );
}

inline Vec2f& Vec2f::map( const Vec2f& origin,
                         const Vec2f& vx, const Vec2f& vy )
{
    float xmap = origin.x + x*vx.x + y*vy.x;
    y = origin.y + x*vx.y + y*vy.y;
    x = xmap;
    return *this;
}


// Distance between two points.
//
//
inline float Vec2f::distance( const Vec2f& pnt) const {
    float vx = x-pnt.x;
    float vy = y-pnt.y;
    return (float)sqrt(vx*vx + vy*vy);
}

//this method is deprecated in 006 please use squareDistance
inline float Vec2f::distanceSquared( const Vec2f& pnt ) const {
    return squareDistance(pnt);
}

inline float Vec2f::squareDistance( const Vec2f& pnt ) const {
    float vx = x-pnt.x;
    float vy = y-pnt.y;
    return vx*vx + vy*vy;
}



// Linear interpolation.
//
//
/**
 * p==0.0 results in this point, p==0.5 results in the
 * midpoint, and p==1.0 results in pnt being returned.
 */

// this method is deprecated in 006 please use getInterpolated
inline Vec2f Vec2f::interpolated( const Vec2f& pnt, float p ) const{
    return getInterpolated(pnt, p);
}

inline Vec2f Vec2f::getInterpolated( const Vec2f& pnt, float p ) const {
    return Vec2f( x*(1-p) + pnt.x*p, y*(1-p) + pnt.y*p );
}

inline Vec2f& Vec2f::interpolate( const Vec2f& pnt, float p ) {
    x = x*(1-p) + pnt.x*p;
    y = y*(1-p) + pnt.y*p;
    return *this;
}

// this method is deprecated in 006 please use getMiddle
inline Vec2f Vec2f::middled( const Vec2f& pnt ) const{
    return getMiddle(pnt);
}

inline Vec2f Vec2f::getMiddle( const Vec2f& pnt ) const {
    return Vec2f( (x+pnt.x)/2.0f, (y+pnt.y)/2.0f );
}

inline Vec2f& Vec2f::middle( const Vec2f& pnt ) {
    x = (x+pnt.x)/2.0f;
    y = (y+pnt.y)/2.0f;
    return *this;
}



// Average (centroid) among points.
// Addition is sometimes useful for calculating averages too.
//
//
inline Vec2f& Vec2f::average( const Vec2f* points, int num ) {
    x = 0.f;
    y = 0.f;
    for( int i=0; i<num; i++) {
        x += points[i].x;
        y += points[i].y;
    }
    x /= num;
    y /= num;
    return *this;
}



// Normalization
//
//
inline Vec2f Vec2f::normalized() const {
    return getNormalized();
}

inline Vec2f Vec2f::getNormalized() const {
    float length = (float)sqrt(x*x + y*y);
    if( length > 0 ) {
        return Vec2f( x/length, y/length );
    } else {
        return Vec2f();
    }
}

inline Vec2f& Vec2f::normalize() {
    float length = (float)sqrt(x*x + y*y);
    if( length > 0 ) {
        x /= length;
        y /= length;
    }
    return *this;
}



// Limit length.
//
//
inline Vec2f Vec2f::limited(float max) const{
    return getLimited(max);
}

inline Vec2f Vec2f::getLimited(float max) const {
    Vec2f limited;
    float lengthSquared = (x*x + y*y);
    if( lengthSquared > max*max && lengthSquared > 0 ) {
        float ratio = max/(float)sqrt(lengthSquared);
        limited.set( x*ratio, y*ratio);
    } else {
        limited.set(x,y);
    }
    return limited;
}

inline Vec2f& Vec2f::limit(float max) {
    float lengthSquared = (x*x + y*y);
    if( lengthSquared > max*max && lengthSquared > 0 ) {
        float ratio = max/(float)sqrt(lengthSquared);
        x *= ratio;
        y *= ratio;
    }
    return *this;
}



// Perpendicular normalized vector.
//
//
inline Vec2f Vec2f::perpendiculared() const {
    return getPerpendicular();
}

inline Vec2f Vec2f::getPerpendicular() const {
    float length = (float)sqrt( x*x + y*y );
    if( length > 0 )
        return Vec2f( -(y/length), x/length );
    else
        return Vec2f();
}

inline Vec2f& Vec2f::perpendicular() {
    float length = (float)sqrt( x*x + y*y );
    if( length > 0 ) {
        float _x = x;
        x = -(y/length);
        y = _x/length;
    }
    return *this;
}


// Length
//
//
inline float Vec2f::length() const {
    return (float)sqrt( x*x + y*y );
}

inline float Vec2f::lengthSquared() const {
    return squareLength();
}

inline float Vec2f::squareLength() const {
    return (float)(x*x + y*y);
}



/**
 * Angle (deg) between two vectors.
 * This is a signed relative angle between -180 and 180.
 */
inline float Vec2f::angle( const Vec2f& vec ) const {
    return (float)(atan2( x*vec.y-y*vec.x, x*vec.x + y*vec.y )*RAD_TO_DEG);
}

/**
 * Angle (deg) between two vectors.
 * This is a signed relative angle between -180 and 180.
 */
inline float Vec2f::angleRad( const Vec2f& vec ) const {
    return atan2( x*vec.y-y*vec.x, x*vec.x + y*vec.y );
}


/**
 * Dot Product.
 */
inline float Vec2f::dot( const Vec2f& vec ) const {
    return x*vec.x + y*vec.y;
}







// Non-Member operators
//
//
inline Vec2f operator+( float f, const Vec2f& vec ) {
    return Vec2f( f+vec.x, f+vec.y);
}

inline Vec2f operator-( float f, const Vec2f& vec ) {
    return Vec2f( f-vec.x, f-vec.y);
}

inline Vec2f operator*( float f, const Vec2f& vec ) {
    return Vec2f( f*vec.x, f*vec.y);
}

inline Vec2f operator/( float f, const Vec2f& vec ) {
    return Vec2f( f/vec.x, f/vec.y);
}

FL_NAMESPACE_END