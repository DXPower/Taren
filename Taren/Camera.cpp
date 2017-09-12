#pragma once
#include "Camera.h"
#include "GameObject.h"
#include "Application.h"

Camera::Camera() {}


Camera::~Camera() {}

const CameraTargetType Camera::GetTargetType() const {
	return targetType;
}

const Vector2 Camera::WorldToScreenPos(const Vector2& oPos) const {
	const Vector2* fPos = NULL;

	if (targetType == CameraTargetType::CAMERA_POSITION) {
		fPos = &position;
	} else if (targetType == CameraTargetType::CAMERA_FOLLOW) {
		fPos = gameobject->Position();
	}

	return Vector2(oPos.x - fPos->x + Application::SCREEN_WIDTH_HALF, oPos.y - fPos->y + Application::SCREEN_HEIGHT_HALF);
}

const Vector2 Camera::GetFocusPosition() const {
	if (targetType == CameraTargetType::CAMERA_POSITION) {
		return Vector2(position.x, position.y);
	} else if (targetType == CameraTargetType::CAMERA_FOLLOW) {
		Vector2* p = gameobject->Position();
		return Vector2(p->x, p->y);
	}
}

void Camera::SetTargetType(const CameraTargetType type) {
	targetType = type;
}

void Camera::SetFollowTarget(GameObject* g) {
	gameobject = g;
}

void Camera::SetTargetPosition(Vector2 v) {
	position = v;
}