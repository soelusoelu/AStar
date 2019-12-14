#include "Camera.h"
#include "../System/Game.h"

Camera::Camera() :
    mCameraPosition(Vector3::zero),
    mLookAt(Vector3::forward),
    mUp(Vector3::up),
    mPlayerPosition(mCameraPosition),
    mView(Matrix4::identity),
    mProj(Matrix4::identity) {
    mView = Matrix4::createLookAt(mCameraPosition, mLookAt, mUp);
    mProj = Matrix4::createPerspectiveFOV(
        45.f,
        static_cast<float>(Game::WINDOW_WIDTH),
        static_cast<float>(Game::WINDOW_HEIGHT),
        0.1f,
        1000.f
    );
}

Camera::~Camera() = default;

void Camera::update() {
    mCameraPosition.z += 0.01f;
    mView = Matrix4::createLookAt(mCameraPosition, mLookAt, mUp);
}

Vector3 Camera::getPosition() {
    return mCameraPosition;
}

Matrix4 Camera::getView() {
    return mView;
}

Matrix4 Camera::getProjection() {
    return mProj;
}
