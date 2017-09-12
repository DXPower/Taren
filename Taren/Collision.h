#pragma once
#include <iostream>
#include <unordered_map>
#include <set>
#include "Vector2.h"
#include "Helpers.h"

using namespace std;

class Bucket;
class GameObject;

class Collision {
	public:
	static unordered_map<int, Bucket*> buckets;
	static int cellSizeX, cellSizeY, nX, nY;

	static void SetupBuckets(int sX, int sY, int cellSizeX, int cellSizeY);
	static void ClearBuckets();
	static void FillBuckets();
	static inline void CheckCollisions(set<Bucket*> &buckets);
};

class Collider {
	public:
	set<Bucket*> bucketsIn;

	GameObject* gameobject;

	Collider();
	Collider(GameObject* go);
	~Collider();

	bool GetCollisionEnabled();
	void SetCollisionEnabled(bool f);
	inline void Clear();
	inline void AddBucket(Vector2 pos);

	virtual void GetNearbyBoxes();
	virtual void CollisionEnter(Collider* c, SDL_Rect intersection);
	virtual void GameObjectSizeChanged(Vector2 size);

	virtual inline bool CheckCollision(Collider* c, SDL_Rect& intersection) {
		return false;
	}

	private:
	bool collisionEnabled = false;
};

class SquareCollider : public Collider {
	public:
	Rect boundingBox;

	SquareCollider(GameObject* gameobject);
	~SquareCollider() {};

	void GetNearbyBoxes() override;

	inline bool CheckCollision(Collider* c, SDL_Rect& intersection) override;
	void GameObjectSizeChanged(Vector2 size) override;

	//inline bool IsColliding(SquareCollider* s);
};

//template <class T : Collider>
//template <class T2 : Collider>
class CollisionChecker {
	public:
	static bool CheckCollision(SquareCollider* c1, SquareCollider* c2, SDL_Rect& intersection);
	static bool CheckCollision(Collider* c1, Collider* c2);
};

class Bucket {
	public:
	set<Collider*> objects;

	const Vector2 topLeft;
	const Vector2 bottomRight;

	const int id, x, y, sceneX, sceneY;

	Bucket(int id, int x, int y, int csX, int csY);
	~Bucket();

	inline void AddCollider(Collider* o);
	inline void Clear();
};


