//
//  flArcball.cpp
//  flTinyGLUtils
//
//  Created by Onishi Yoshito on 11/6/13.
//  Copyright (c) 2013 Onishi Yoshito. All rights reserved.
//

#include "flArcball.h"
#include "flUtils.h"

FL_NAMESPACE_BEGIN

Arcball::Arcball()
{
    setNoConstraintAxis();
    mCurrentQuat = mInitialQuat = Quaternion();
}
Arcball::Arcball( const Vec2f &aScreenSize )
: mWindowSize( aScreenSize )
{
    setCenter( Vec2f( mWindowSize.x / 2.0f, mWindowSize.y / 2.0f ) );
    mRadius = std::min( (float)mWindowSize.x / 2, (float)mWindowSize.y / 2 );
    setNoConstraintAxis();
    mCurrentQuat = mInitialQuat = Quaternion();
}

void Arcball::mouseDown( const Vec2f &mousePos )
{
    mInitialMousePos = mousePos;
    mInitialQuat = mCurrentQuat;
}

void Arcball::mouseDrag( const Vec2f &mousePos )
{
    Vec3f from = mouseOnSphere( mInitialMousePos );
    Vec3f to = mouseOnSphere( mousePos );
    if( mUseConstraint ) {
        from = constrainToAxis( from, mConstraintAxis );
        to = constrainToAxis( to, mConstraintAxis );
    }
    Vec3f axis = from.getCrossed( to );
    mCurrentQuat = mInitialQuat * Quaternion( axis.x, axis.y, axis.z, from.dot( to ) );
    
    
    Quaternion quat( axis.x, axis.y, axis.z, from.dot( to ) );
    //        printf("%f, %f, %f, %f\n", quat.x(), quat.y(), quat.z(), quat.w());
    mCurrentQuat.normalize();
}


Vec3f Arcball::mouseOnSphere( const Vec2f &point ) {
    Vec3f result;
    
    result.x = ( point.x - mCenter.x ) / ( mRadius * 2 );
    result.y = ( point.y - mCenter.y ) / ( mRadius * 2 );
    result.z = 0.0f;
    
    float mag = result.lengthSquared();
    if( mag > 1.0f ) {
        result.normalize();
    }
    else {
        result.z = sqrtf( 1.0f - mag );
        result.normalize();
    }
    
    return result;
}

Vec3f Arcball::constrainToAxis( const Vec3f &loose, const Vec3f &axis )
{
    float norm;
    Vec3f onPlane = loose - axis * axis.dot( loose );
    norm = onPlane.lengthSquared();
    if( norm > 0.0f ) {
        if( onPlane.z < 0.0f )
            onPlane = -onPlane;
        return ( onPlane * ( 1.0f / sqrtf( norm ) ) );
    }
    
    if( axis.dot( Vec3f(0.f, 0.f, 1.f) ) < 0.0001f ) {
        onPlane = Vec3f(1.f, 0.f, 0.f);
    }
    else {
        onPlane = Vec3f( -axis.y, axis.x, 0.0f ).normalized();
    }
    
    return onPlane;
}



FL_NAMESPACE_END
