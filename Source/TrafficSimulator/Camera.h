#ifndef CAMERA_H_
#define CAMERA_H_

#include "Math/WildMath.h"
using namespace wmath;

// Handles the camera through which we see the world
// standard uses FPS fly style movement
class Camera
{
public:
	Camera();

	// adjusters
	void LookAt(Vec3 eye, Vec3 at, Vec3 Up);
	void Perspective(float fov, float aspect, float near, float far);
	void Orthographic(float near, float far);
	void Orthographic2D(int width, int height);

	// transformations
	void Strafe(float value);
	void Move(float value);
	void Rotate(float x, float y, float z);

	// getters
	Mat4 GetView();
	Mat4 GetWorld();
	Mat4 GetProjection() { return mProjection; }

private:
	void ExtractFrustum();

protected:
	Vec3 mPosition;
	Vec3 mForward;
	Vec3 mRight;
	Vec3 mUp;

	Mat4 mView;
	Mat4 mProjection;
	bool mDirty;

	// for FPS style camera
	float mTilt;
	float mYaw;
};

#endif
