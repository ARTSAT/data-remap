#include "flCamera.h"

using namespace fl;

//----------------------------------------
Camera::Camera() :
isOrtho(false),
fov(60),
nearClip(0),
farClip(0),
lensOffset(0.0f, 0.0f),
forceAspectRatio(false),
isActive(false)
{
}

//----------------------------------------
void Camera::setFov(float f) {
	fov = f;
}

//----------------------------------------
void Camera::setNearClip(float f) {
	nearClip = f;
}

//----------------------------------------
void Camera::setFarClip(float f) {
	farClip = f;
}

//----------------------------------------
void Camera::setLensOffset(const Vec2f & lensOffset){
	this->lensOffset = lensOffset;
}

//----------------------------------------
void Camera::setAspectRatio(float aspectRatio){
	this->aspectRatio = aspectRatio;
	setForceAspectRatio(true);
}

//----------------------------------------
void Camera::setForceAspectRatio(bool forceAspectRatio){
	this->forceAspectRatio = forceAspectRatio;
}

//----------------------------------------
void Camera::setupPerspective(bool vFlip, float fov, float nearDist, float farDist, const Vec2f & lensOffset){
	float viewW = getViewport().w;
	float viewH = getViewport().h;

	float eyeX = viewW / 2;
	float eyeY = viewH / 2;
	float halfFov = PI * fov / 360;
	float theTan = tanf(halfFov);
	float dist = eyeY / theTan;

	if(nearDist == 0) nearDist = dist / 10.0f;
	if(farDist == 0) farDist = dist * 10.0f;

	setFov(fov);
	setNearClip(nearDist);
	setFarClip(farDist);
	setLensOffset(lensOffset);
	setForceAspectRatio(false);

	setPosition(eyeX,eyeY,dist);
	lookAt(Vec3f(eyeX,eyeY,0),Vec3f(0,1,0));


	if(vFlip){
		setScale(1,-1,1);
	}
}

//----------------------------------------
void Camera::setupOffAxisViewPortal(const Vec3f & topLeft, const Vec3f & bottomLeft, const Vec3f & bottomRight){
	Vec3f bottomEdge = bottomRight - bottomLeft; // plane x axis
	Vec3f leftEdge = topLeft - bottomLeft; // plane y axis
	Vec3f bottomEdgeNorm = bottomEdge.normalized();
	Vec3f leftEdgeNorm = leftEdge.normalized();
	Vec3f bottomLeftToCam = this->getPosition() - bottomLeft;
	
	Vec3f cameraLookVector = leftEdgeNorm.getCrossed(bottomEdgeNorm);
	
	Vec3f cameraUpVector = bottomEdgeNorm.getCrossed(cameraLookVector);
	
	this->lookAt(cameraLookVector + this->getPosition(), cameraUpVector);

	//lensoffset
	Vec2f lensOffset;
	lensOffset.x = -bottomLeftToCam.dot(bottomEdgeNorm) * 2.0f / bottomEdge.length() + 1.0f;
	lensOffset.y = -bottomLeftToCam.dot(leftEdgeNorm) * 2.0f / leftEdge.length() + 1.0f;
	setLensOffset(lensOffset);
	setAspectRatio( bottomEdge.length() / leftEdge.length() );
	float distanceAlongOpticalAxis = abs(bottomLeftToCam.dot(cameraLookVector));
	setFov(2.0f * RAD_TO_DEG * atan( (leftEdge.length() / 2.0f) / distanceAlongOpticalAxis));
}

//----------------------------------------
void Camera::enableOrtho() {
	isOrtho = true;
}

//----------------------------------------
void Camera::disableOrtho() {
	isOrtho = false;
}

//----------------------------------------
bool Camera::getOrtho() const {
	return isOrtho;
}

//----------------------------------------
float Camera::getImagePlaneDistance(Rectangle viewport) const {
	return viewport.h / (2.0f * tanf(PI * fov / 360.0f));
}

//----------------------------------------
void Camera::begin(Rectangle viewport) {
	if(!isActive) pushView();
	isActive = true;

//	ofSetCoordHandedness(OF_RIGHT_HANDED);

	// autocalculate near/far clip planes if not set by user
	calcClipPlanes(viewport);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glLoadMatrixf( this->getProjectionMatrix(viewport).getPtr() );

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf( Matrix4x4::getInverseOf(getGlobalTransformMatrix()).getPtr() );
    glViewport(viewport.x, viewport.y, viewport.w, viewport.h);
}

// if begin(); pushes first, then we need an end to pop
//----------------------------------------
void Camera::end() {
	if (isActive)
	{
		popView();
		isActive = false;
	}
}
//----------------------------------------
Matrix4x4 Camera::getProjectionMatrix(Rectangle viewport) const {
	if(isOrtho) {
		Matrix4x4 ortho;
		ortho.makeOrthoMatrix(0, viewport.w, 0, viewport.h, nearClip, farClip);
		return ortho;
	}else{
		float aspect = forceAspectRatio ? aspectRatio : viewport.w/viewport.h;
		Matrix4x4 matProjection;
		matProjection.makePerspectiveMatrix(fov, aspect, nearClip, farClip);
		matProjection.translate(-lensOffset.x, -lensOffset.y, 0);
		return matProjection;
	}
}
//----------------------------------------
Matrix4x4 Camera::getModelViewMatrix() const {
	Matrix4x4 matModelView;
	matModelView.makeInvertOf(getGlobalTransformMatrix());
	return matModelView;
}
//----------------------------------------
Matrix4x4 Camera::getModelViewProjectionMatrix(Rectangle viewport) const {
	return getModelViewMatrix() * getProjectionMatrix(viewport);
}
//----------------------------------------
Vec3f Camera::worldToScreen(Vec3f WorldXYZ, Rectangle viewport) const {

	Vec3f CameraXYZ = WorldXYZ * getModelViewProjectionMatrix(viewport);
	Vec3f ScreenXYZ;

	ScreenXYZ.x = (CameraXYZ.x + 1.0f) / 2.0f * viewport.w + viewport.x;
	ScreenXYZ.y = (1.0f - CameraXYZ.y) / 2.0f * viewport.h + viewport.y;

	ScreenXYZ.z = CameraXYZ.z;

	return ScreenXYZ;

}
//----------------------------------------
Vec3f Camera::screenToWorld(Vec3f ScreenXYZ, Rectangle viewport) const {

	//convert from screen to camera
	Vec3f CameraXYZ;
	CameraXYZ.x = 2.0f * (ScreenXYZ.x - viewport.x) / viewport.w - 1.0f;
	CameraXYZ.y = 1.0f - 2.0f *(ScreenXYZ.y - viewport.y) / viewport.h;
	CameraXYZ.z = ScreenXYZ.z;

	//get inverse camera matrix
	Matrix4x4 inverseCamera;
	inverseCamera.makeInvertOf(getModelViewProjectionMatrix(viewport));

	//convert camera to world
	return CameraXYZ * inverseCamera;

}
//----------------------------------------
Vec3f Camera::worldToCamera(Vec3f WorldXYZ, Rectangle viewport) const {
	return WorldXYZ * getModelViewProjectionMatrix(viewport);
}
//----------------------------------------
Vec3f Camera::cameraToWorld(Vec3f CameraXYZ, Rectangle viewport) const {

	Matrix4x4 inverseCamera;
	inverseCamera.makeInvertOf(getModelViewProjectionMatrix(viewport));

	return CameraXYZ * inverseCamera;
}
//----------------------------------------
void Camera::calcClipPlanes(Rectangle viewport)
{
	// autocalculate near/far clip planes if not set by user
	if(nearClip == 0 || farClip == 0) {
		float dist = getImagePlaneDistance(viewport);
		nearClip = (nearClip == 0) ? dist / 100.0f : nearClip;
		farClip = (farClip == 0) ? dist * 10.0f : farClip;
	}
}

//----------------------------------------
Rectangle Camera::getViewport()
{
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    Rectangle r;
    r.x = viewport[0];
    r.y = viewport[1];
    r.w = viewport[2];
    r.h = viewport[3];
    return r;
}

void Camera::pushView()
{
    glGetIntegerv(GL_VIEWPORT, _savedViewport);
}

void Camera::popView()
{
    glViewport(_savedViewport[0], _savedViewport[1], _savedViewport[2], _savedViewport[3]);
}