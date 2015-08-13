#pragma once

#include "flVec3f.h"
#include "flQuaternion.h"
#include "flMatrix4x4.h"
#include "flMath.h"

namespace fl {
    
    class Node {
    public:
        Node();
        virtual ~Node() {}
        
        void setParent(Node& parent);
        void clearParent();
        Node* getParent() const;
        
        
        //----------------------------------------
        // Get transformations
        
        Vec3f getPosition() const;
        float getX() const;
        float getY() const;
        float getZ() const;
        
        Vec3f getXAxis() const;
        Vec3f getYAxis() const;
        Vec3f getZAxis() const;
        
        Vec3f getSideDir() const;		// x axis
        Vec3f getLookAtDir()const;	// -z axis
        Vec3f getUpDir() const;		// y axis
        
        float getPitch() const;
        float getHeading() const;
        float getRoll() const;
        
        Quaternion getOrientationQuat() const;
        Vec3f getOrientationEuler() const;
        Vec3f getScale() const;
        
        const Matrix4x4& getLocalTransformMatrix() const;
        
        // TODO: optimize and cache these
        // (parent would need to know about its children so it can inform them
        // to update their global matrices if it itself transforms)
        Matrix4x4 getGlobalTransformMatrix() const;
        Vec3f getGlobalPosition() const;
        Quaternion getGlobalOrientation() const;
        Vec3f getGlobalScale() const;
        
        
        
        // Set Transformations
        
        // directly set transformation matrix
        void setTransformMatrix(const Matrix4x4 &m44);
        
        // position
        void setPosition(float px, float py, float pz);
        void setPosition(const Vec3f& p);
        
        void setGlobalPosition(float px, float py, float pz);
        void setGlobalPosition(const Vec3f& p);
        
        
        // orientation
        void setOrientation(const Quaternion& q);			// set as quaternion
        void setOrientation(const Vec3f& eulerAngles);	// or euler can be useful, but prepare for gimbal lock
        //	void setOrientation(const ofMatrix3x3& orientation);// or set as m33 if you have transformation matrix
        
        void setGlobalOrientation(const Quaternion& q);
        
        
        // scale set and get
        void setScale(float s);
        void setScale(float sx, float sy, float sz);
        void setScale(const Vec3f& s);
        
        
        // helpful move methods
        void move(float x, float y, float z);			// move by arbitrary amount
        void move(const Vec3f& offset);				// move by arbitrary amount
        void truck(float amount);						// move sideways (in local x axis)
        void boom(float amount);						// move up+down (in local y axis)
        void dolly(float amount);						// move forward+backward (in local z axis)
        
        
        // helpful rotation methods
        void tilt(float degrees);						// tilt up+down (around local x axis)
        void pan(float degrees);						// rotate left+right (around local y axis)
        void roll(float degrees);						// roll left+right (around local z axis)
        void rotate(const Quaternion& q);				// rotate by quaternion
        void rotate(float degrees, const Vec3f& v);	// rotate around arbitrary axis by angle
        void rotate(float degrees, float vx, float vy, float vz);
        
        void rotateAround(const Quaternion& q, const Vec3f& point);	// rotate by quaternion around point
        void rotateAround(float degrees, const Vec3f& axis, const Vec3f& point);	// rotate around arbitrary axis by angle around point
        
        // orient node to look at position (-ve z axis pointing to node)
        void lookAt(const Vec3f& lookAtPosition, Vec3f upVector = Vec3f(0, 1, 0));
        void lookAt(const Node& lookAtNode, const Vec3f& upVector = Vec3f(0, 1, 0));
        
        
        // orbit object around target at radius
        void orbit(float longitude, float latitude, float radius, const Vec3f& centerPoint = Vec3f(0, 0, 0));
        void orbit(float longitude, float latitude, float radius, Node& centerNode);
        
        
        // set opengl's modelview matrix to this nodes transform
        // if you want to draw something at the position+orientation+scale of this node...
        // ...call Node::transform(); write your draw code, and Node::restoreTransform();
        // OR A simpler way is to extend Node and override Node::customDraw();
        void transformGL() const;
        void restoreTransformGL() const;
        
        
        // resets this node's transformation
        void resetTransform();
        
        
        // if you extend Node and wish to change the way it draws, extend this
        virtual void customDraw() {}
        
        
        // draw function. do NOT override this
        // transforms the node to its position+orientation+scale
        // and calls the virtual 'customDraw' method above which you CAN override
        void draw();
        
    protected:
        Node *parent;
        
        void createMatrix();
        
        
        // classes extending Node can override these methods to get notified 
        virtual void onPositionChanged() {}
        virtual void onOrientationChanged() {}
        virtual void onScaleChanged() {}
        
    private:
        Vec3f position;
        Quaternion orientation;
        Vec3f scale;
        
        Vec3f axis[3];
        
        Matrix4x4 localTransformMatrix;
        //	Matrix4x4 globalTransformMatrix;
    };
    
}