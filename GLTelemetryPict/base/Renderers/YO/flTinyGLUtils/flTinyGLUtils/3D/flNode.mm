#include "flNode.h"
#include "flQuaternion.h"
#include "flMatrix4x4.h"
#include "flVec3f.h"
#include "flVec4f.h"
//#include "flTools.h"

using namespace fl;

Node::Node() : 
	parent(NULL) {
	setPosition(Vec3f(0, 0, 0));
	setOrientation(Vec3f(0, 0, 0));
	setScale(1);
}

//----------------------------------------
void Node::setParent(Node& parent) {
	this->parent = &parent;
}

//----------------------------------------
void Node::clearParent() {
	this->parent = NULL;
}

//----------------------------------------
Node* Node::getParent() const {
	return parent;
}

//----------------------------------------
void Node::setTransformMatrix(const Matrix4x4 &m44) {
	localTransformMatrix = m44;

	Quaternion so;
    fl::Vec4f v(position.x, position.y, position.z, 0.0);
    fl::Vec4f s(scale.x, scale.y, scale.z, 0.0);
	localTransformMatrix.decompose(v, orientation, s, so);
	
	onPositionChanged();
	onOrientationChanged();
	onScaleChanged();
}

//----------------------------------------
void Node::setPosition(float px, float py, float pz) {
	setPosition(Vec3f(px, py, pz));
}

//----------------------------------------
void Node::setPosition(const Vec3f& p) {
	position = p;
	localTransformMatrix.setTranslation(position);
	onPositionChanged();
}

//----------------------------------------
void Node::setGlobalPosition(float px, float py, float pz) {
	setGlobalPosition(Vec3f(px, py, pz));
}

//----------------------------------------
void Node::setGlobalPosition(const Vec3f& p) {
	if(parent == NULL) {
		setPosition(p);
	} else {
		setPosition(p * Matrix4x4::getInverseOf(parent->getGlobalTransformMatrix()));
	}
}

//----------------------------------------
Vec3f Node::getPosition() const {
	return position;
}

//----------------------------------------
float Node::getX() const {
	return position.x;
}

//----------------------------------------
float Node::getY() const {
	return position.y;
}

//----------------------------------------
float Node::getZ() const {
	return position.z;
}

//----------------------------------------
void Node::setOrientation(const Quaternion& q) {
	orientation = q;
	createMatrix();
	onOrientationChanged();
}

//----------------------------------------
void Node::setOrientation(const Vec3f& eulerAngles) {
	setOrientation(Quaternion(eulerAngles.y, Vec3f(0, 1, 0), eulerAngles.x, Vec3f(1, 0, 0), eulerAngles.z, Vec3f(0, 0, 1)));
}

//----------------------------------------
void Node::setGlobalOrientation(const Quaternion& q) {
	if(parent == NULL) {
		setOrientation(q);
	} else {
		Matrix4x4 invParent(Matrix4x4::getInverseOf(parent->getGlobalTransformMatrix()));
		Matrix4x4 m44(Matrix4x4(q) * invParent);
		setOrientation(m44.getRotate());
	}
}

//----------------------------------------
Quaternion Node::getOrientationQuat() const {
	return orientation;
}

//----------------------------------------
Vec3f Node::getOrientationEuler() const {
    return orientation.getEuler();
}

//----------------------------------------
void Node::setScale(float s) {
	setScale(s, s, s);
}

//----------------------------------------
void Node::setScale(float sx, float sy, float sz) {
	setScale(Vec3f(sx, sy, sz));
}

//----------------------------------------
void Node::setScale(const Vec3f& s) {
	this->scale = s;
	createMatrix();
	onScaleChanged();
}

//----------------------------------------
Vec3f Node::getScale() const {
	return scale;
}

//----------------------------------------
void Node::move(float x, float y, float z) {
	move(Vec3f(x, y, z));
}

//----------------------------------------
void Node::move(const Vec3f& offset) {
	position += offset;
	localTransformMatrix.setTranslation(position);
	onPositionChanged();
}

//----------------------------------------
void Node::truck(float amount) {
	move(getXAxis() * amount);
}

//----------------------------------------
void Node::boom(float amount) {
	move(getYAxis() * amount);
}

//----------------------------------------
void Node::dolly(float amount) {
	move(getZAxis() * amount);
}

//----------------------------------------
void Node::tilt(float degrees) {
	rotate(degrees, getXAxis());
}

//----------------------------------------
void Node::pan(float degrees) {
	rotate(degrees, getYAxis());
}

//----------------------------------------
void Node::roll(float degrees) {
	rotate(degrees, getZAxis());
}

//----------------------------------------
void Node::rotate(const Quaternion& q) {
	orientation *= q;
	createMatrix();
}

//----------------------------------------
void Node::rotate(float degrees, const Vec3f& v) {
	rotate(Quaternion(degrees, v));
}

//----------------------------------------
void Node::rotate(float degrees, float vx, float vy, float vz) {
	rotate(Quaternion(degrees, Vec3f(vx, vy, vz)));
}

//----------------------------------------
void Node::rotateAround(const Quaternion& q, const Vec3f& point) {
	//	ofLog(OF_LOG_VERBOSE, "Node::rotateAround(const Quaternion& q, const Vec3f& point) not implemented yet");
	//	Matrix4x4 m = getLocalTransformMatrix();
	//	m.setTranslation(point);
	//	m.rotate(q);
	
	setGlobalPosition((getGlobalPosition() - point)* q + point); 
	
//	onOrientationChanged();
	onPositionChanged();
}

//----------------------------------------
void Node::rotateAround(float degrees, const Vec3f& axis, const Vec3f& point) {
	rotateAround(Quaternion(degrees, axis), point);
}

//----------------------------------------
void Node::lookAt(const Vec3f& lookAtPosition, Vec3f upVector) {
	if(parent) upVector = upVector * Matrix4x4::getInverseOf(parent->getGlobalTransformMatrix());	
	Vec3f zaxis = (getGlobalPosition() - lookAtPosition).normalized();	
	if (zaxis.length() > 0) {
		Vec3f xaxis = upVector.getCrossed(zaxis).normalized();	
		Vec3f yaxis = zaxis.getCrossed(xaxis);
		
		Matrix4x4 m;
		m._mat[0].set(xaxis.x, xaxis.y, xaxis.z, 0);
		m._mat[1].set(yaxis.x, yaxis.y, yaxis.z, 0);
		m._mat[2].set(zaxis.x, zaxis.y, zaxis.z, 0);
		
		setGlobalOrientation(m.getRotate());
	}
}

//----------------------------------------
void Node::lookAt(const Node& lookAtNode, const Vec3f& upVector) {
	lookAt(lookAtNode.getGlobalPosition(), upVector);
}

//----------------------------------------
Vec3f Node::getXAxis() const {
	return axis[0];
}

//----------------------------------------
Vec3f Node::getYAxis() const {
	return axis[1];
}

//----------------------------------------
Vec3f Node::getZAxis() const {
	return axis[2];
}

//----------------------------------------
Vec3f Node::getSideDir() const {
	return getXAxis();
}

//----------------------------------------
Vec3f Node::getLookAtDir() const {
	return -getZAxis();
}

//----------------------------------------
Vec3f Node::getUpDir() const {
	return getYAxis();
}

//----------------------------------------
float Node::getPitch() const {
	return getOrientationEuler().x;
}

//----------------------------------------
float Node::getHeading() const {
	return getOrientationEuler().y;
}

//----------------------------------------
float Node::getRoll() const {
	return getOrientationEuler().z;
}

//----------------------------------------
const Matrix4x4& Node::getLocalTransformMatrix() const {
	return localTransformMatrix;
}

//----------------------------------------
Matrix4x4 Node::getGlobalTransformMatrix() const {
	if(parent) return getLocalTransformMatrix() * parent->getGlobalTransformMatrix();
	else return getLocalTransformMatrix();
}

//----------------------------------------
Vec3f Node::getGlobalPosition() const {
	return getGlobalTransformMatrix().getTranslation();
}

//----------------------------------------
Quaternion Node::getGlobalOrientation() const {
	return getGlobalTransformMatrix().getRotate();
}

//----------------------------------------
Vec3f Node::getGlobalScale() const {
	if(parent) return getScale()*parent->getGlobalScale();
	else return getScale();
}

//----------------------------------------
void Node::orbit(float longitude, float latitude, float radius, const Vec3f& centerPoint) {
	Matrix4x4 m;

	// find position
	Vec3f p(0, 0, radius);
	p.rotate(clamp(latitude, -89, 89), Vec3f(1, 0, 0));
	p.rotate(longitude, Vec3f(0, 1, 0));
	p += centerPoint;
	setPosition(p);
	
	lookAt(centerPoint);//, v - centerPoint);
}

//----------------------------------------
void Node::orbit(float longitude, float latitude, float radius, Node& centerNode) {
	orbit(longitude, latitude, radius, centerNode.getGlobalPosition());
}

//----------------------------------------
void Node::resetTransform() {
	setPosition(Vec3f());
	setOrientation(Vec3f());
}

//----------------------------------------
void Node::draw() {
	transformGL();
	customDraw();
	restoreTransformGL();
}

//----------------------------------------
void Node::transformGL() const {
	glPushMatrix();
	glMultMatrixf( getGlobalTransformMatrix().getPtr() );
}

//----------------------------------------
void Node::restoreTransformGL() const {
	glPopMatrix();
}

//----------------------------------------
void Node::createMatrix() {
	//if(isMatrixDirty) {
	//	isMatrixDirty = false;
	localTransformMatrix.makeScaleMatrix(scale);
	localTransformMatrix.rotate(orientation);
	localTransformMatrix.setTranslation(position);
	
	if(scale[0]>0) axis[0] = getLocalTransformMatrix().getRowAsVec3f(0)/scale[0];
	if(scale[1]>0) axis[1] = getLocalTransformMatrix().getRowAsVec3f(1)/scale[1];
	if(scale[2]>0) axis[2] = getLocalTransformMatrix().getRowAsVec3f(2)/scale[2];
}


