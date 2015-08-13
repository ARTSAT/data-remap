//
//  flArcball.h
//  flTinyGLUtils
//
//  Created by Onishi Yoshito on 11/6/13.
//  Copyright (c) 2013 Onishi Yoshito. All rights reserved.
//

#ifndef __flTinyGLUtils__flArcball__
#define __flTinyGLUtils__flArcball__

#include "flCommon.h"
#include "flVec2f.h"
#include "flVec3f.h"
#include "flQuaternion.h"

FL_NAMESPACE_BEGIN

class Arcball {
public:
    Arcball();
    Arcball(const Vec2f &aScreenSize);
	
    void mouseDown(const Vec2f &mousePos);
    void mouseDrag(const Vec2f &mousePos);
	
	void resetQuat() { mCurrentQuat = mInitialQuat = Quaternion(); }
	Quaternion getQuat() { return mCurrentQuat; }
	void setQuat(const Quaternion &quat) { mCurrentQuat = quat; }
	
	void setWindowSize(const Vec2f &aWindowSize) { mWindowSize = aWindowSize; }
	void setCenter(const Vec2f &aCenter) { mCenter = aCenter; }
	Vec2f getCenter() const { return mCenter; }
	void setRadius(float aRadius) { mRadius = aRadius; }
	float getRadius() const { return mRadius; }
	void setConstraintAxis(const Vec3f &aConstraintAxis) { mConstraintAxis = aConstraintAxis; mUseConstraint = true; }
	void setNoConstraintAxis() { mUseConstraint = false; }
	bool isUsingConstraint() const { return mUseConstraint; }
	Vec3f getConstraintAxis() const { return mConstraintAxis; }
	
    Vec3f mouseOnSphere(const Vec2f &point);
	
private:
	// Force sphere point to be perpendicular to axis
    Vec3f constrainToAxis(const Vec3f &loose, const Vec3f &axis);
	
	Vec2f		mWindowSize;
	Vec2f		mInitialMousePos;
	Vec2f		mCenter;
	Quaternion  mCurrentQuat, mInitialQuat;
	float		mRadius;
	Vec3f		mConstraintAxis;
	bool		mUseConstraint;
};

FL_NAMESPACE_END

#endif /* defined(__flTinyGLUtils__flArcball__) */
