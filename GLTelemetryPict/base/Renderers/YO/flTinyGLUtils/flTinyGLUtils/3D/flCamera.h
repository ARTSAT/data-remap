#pragma once
#include "flNode.h"
#include "flVec2f.h"
#include "flVec3f.h"
#include "flMatrix4x4.h"
#include "flQuaternion.h"
#include "flRectangle.h"

namespace fl {

class Camera : public Node {
public:
	Camera();
	virtual ~Camera(){};
	
	// projection properties:
	void setFov(float f);
	void setNearClip(float f);
	void setFarClip(float f);
	void setLensOffset(const Vec2f & lensOffset);
	void setAspectRatio(float aspectRatio);
	void setForceAspectRatio(bool forceAspectRatio);

	float getFov() const { return fov; };
	float getNearClip() const { return nearClip; };
	float getFarClip() const { return farClip; };
	Vec2f getLensOffset() const { return lensOffset; };
	bool getForceAspectRatio() const {return forceAspectRatio;};
    float getAspectRatio() const {return aspectRatio; };
	void setupPerspective(bool vFlip = true, float fov = 60, float nearDist = 0, float farDist = 0, const Vec2f & lensOffset = Vec2f(0.0f, 0.0f));
	void setupOffAxisViewPortal(const Vec3f & topLeft, const Vec3f & bottomLeft, const Vec3f & bottomRight);
	
	void enableOrtho();
	void disableOrtho();
	bool getOrtho() const;
	
	float getImagePlaneDistance(Rectangle viewport = getViewport()) const;
	
	// set the matrices
	virtual void begin(Rectangle viewport = getViewport());
	virtual void end();
	
	// for hardcore peeps, access to the projection matrix
	Matrix4x4 getProjectionMatrix(Rectangle viewport = getViewport()) const;
	Matrix4x4 getModelViewMatrix() const;
	Matrix4x4 getModelViewProjectionMatrix(Rectangle viewport = getViewport()) const;
	
	// convert between spaces
	Vec3f worldToScreen(Vec3f WorldXYZ, Rectangle viewport = getViewport()) const;
	Vec3f screenToWorld(Vec3f ScreenXYZ, Rectangle viewport = getViewport()) const;
	Vec3f worldToCamera(Vec3f WorldXYZ, Rectangle viewport = getViewport()) const;
	Vec3f cameraToWorld(Vec3f CameraXYZ, Rectangle viewport = getViewport()) const;
	
	
protected:
    static Rectangle getViewport();
	void calcClipPlanes(Rectangle viewport);
    void pushView();
    void popView();
    
	int _savedViewport[4];
	bool isOrtho;
	float fov;
	float nearClip;
	float farClip;
	Vec2f lensOffset;
	bool forceAspectRatio;
	float aspectRatio; // only used when forceAspect=true, = w / h
	bool isActive;
};


}