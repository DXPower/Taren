#pragma once
#include "Vector2.h"

class GameObject;

enum CameraTargetType {
	CAMERA_FOLLOW,
	CAMERA_POSITION
};

class Camera {
	public:

	Camera();
	~Camera();

	const CameraTargetType GetTargetType() const;
	const Vector2 WorldToScreenPos(const Vector2& pos) const;
	const Vector2 GetFocusPosition() const;
	void SetTargetType(const CameraTargetType type);
	void SetFollowTarget(GameObject* g);
	void SetTargetPosition(Vector2 v);

	private:
	CameraTargetType targetType = CameraTargetType::CAMERA_FOLLOW;

	GameObject* gameobject = NULL;

	Vector2 position = Vector2::zero;
};

