#include "Camera.h"

// initialize
Camera::Camera() : mDirty(true), mTilt(0.0f), mYaw(0.0f)
{
	// set vectors
	mPosition = Vec3(0.0f, 0.0f, 0.0f);
	mRight = Vec3(1.0f, 0.0f, 0.0f);
	mUp = Vec3(0.0f, 1.0f, 0.0f);
	mForward = Vec3(0.0f, 0.0f, 1.0f);
}

// position the camera and let it look at the given point
void Camera::LookAt(Vec3 eye, Vec3 at, Vec3 up)
{
	// recalculate
	mDirty = true;

	// forward vector
	mForward = (at - eye);
	mForward.Norm();

	// right vector
	mRight = up.Cross(mForward);
	mRight.Norm();

	// up vector
	mUp = mForward.Cross(mRight);
	mUp.Norm();

	// set position
	mPosition = eye;

	// set tilt and yaw
	mTilt = asinf(-mForward.y) * RAD2DEG;
	mYaw = atan2f(mForward.x, mForward.z) * RAD2DEG;
}

// Create perspective projection matrix
void Camera::Perspective(float fov, float aspect, float near, float far)
{
	mProjection = Mat4::CreatePerspective(fov, aspect, near, far);
}

// create orthographics projection matrix
void Camera::Orthographic(float near, float far)
{
	mProjection = Mat4::CreateOrthographic(0.0f, 1.0f, 1.0f, 0.0f, near, far);
}

// create orthographics2D projection matrix
void Camera::Orthographic2D(int width, int height)
{
	mProjection = Mat4::CreateOrthographic2D(width, height, 0.0f, 1.0f);
}

void Camera::Strafe(float value)
{
	mDirty = true;
	mPosition += mRight * value;
}

void Camera::Move(float value)
{
	mDirty = true;
	mPosition += mForward * value;
}

void Camera::Rotate(float x, float y, float z)
{
	// tell the class to recreate the view matrix
	mDirty = true;

	mTilt += x;
	mYaw += y;

	// clamp pitch
	if (mTilt < -89.0f)
	{
		x = x - (89.0f + mTilt);
		mTilt = -89.0f;
	}
	else if (mTilt > 89.0f)
	{
		x = x + (89.0f - mTilt);
		mTilt = 89.0f;
	}

	//pitch rotation
	if(x != 0)	
	{
		Mat4 pitchRot = Mat4::RotationAxis(mRight, x);

		mUp = pitchRot * mUp;
		mUp.Norm();
		mForward = pitchRot * mForward;
		mForward.Norm();
	}

	//clamp yaw
	if (mYaw < 0)
	{
		mYaw = 359 + mYaw;
	}
	else if (mYaw > 359)
	{
		mYaw = mYaw - 359;
	}

	// yaw rotation
	if(y != 0)
	{
		Mat4 yawRot = Mat4::RotationY(y);

		mRight = yawRot * mRight;
		mRight.Norm();
		mUp = yawRot * mUp;
		mUp.Norm();
		mForward = yawRot * mForward;
		mForward.Norm();
	}
}

Mat4 Camera::GetView() 
{ 
	// return the view matrix if nothing has changed
	if(!mDirty)
		return mView;

	// regenerate the orientation
	mForward.Norm();

	mUp = mForward.Cross(mRight);
	mUp.Norm();

	mRight = mUp.Cross(mForward);
	mRight.Norm();

	// create the view matrix
	mView.m11 = mRight.x;
	mView.m21 = mRight.y;
	mView.m31 = mRight.z;

	mView.m12 = mUp.x;
	mView.m22 = mUp.y;
	mView.m32 = mUp.z;

	mView.m13 = mForward.x;
	mView.m23 = mForward.y;
	mView.m33 = mForward.z;

	mView.m41 = -(mRight * mPosition);
	mView.m42 = -(mUp * mPosition);
	mView.m43 = -(mForward * mPosition);

	mView.m14 = 0.0f;
	mView.m24 = 0.0f;
	mView.m34 = 0.0f;
	mView.m44 = 1.0f;

	mDirty = false;
	return mView;
}

Mat4 Camera::GetWorld()
{
	Mat4 world;

	world.m11 = mRight.x;
	world.m12 = mRight.y;
	world.m13 = mRight.z;

	world.m21 = mUp.x;
	world.m22 = mUp.y;
	world.m23 = mUp.z;

	world.m31 = mForward.x;
	world.m32 = mForward.y;
	mView.m33 = mForward.z;

	world.SetPosition(this->mPosition);

	return world;
}

void Camera::ExtractFrustum()
{

}