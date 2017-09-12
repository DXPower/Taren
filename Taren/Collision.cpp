#include <math.h>
#include "Collision.h"
#include "Game.h"
#include "GameObject.h"

unordered_map<int, Bucket*> Collision::buckets;
int Collision::cellSizeX, Collision::cellSizeY, Collision::nX, Collision::nY;

Bucket::Bucket(int id, int x, int y, int csX, int csY) : id(id), x(x), y(y), topLeft(Vector2(x * csX, y * csY)), bottomRight(Vector2((x + 1) * csX, (y + 1) * csY)), sceneX(x * csX), sceneY(y * csY) {
	
}

void Bucket::AddCollider(Collider* o) {
	objects.insert(o);
}

void Bucket::Clear() {
	objects.clear();
}

Collider::Collider() {}

Collider::Collider(GameObject* gameobject) : gameobject(gameobject) {
	//GetNearbyBoxes();
}

Collider::~Collider() {
	set<Bucket*>::iterator bit;

	for (bit = bucketsIn.begin(); bit != bucketsIn.end(); bit++) {
		(*bit)->objects.erase(this);
	}
}

void Collider::SetCollisionEnabled(bool f) {
	collisionEnabled = f;
}

bool Collider::GetCollisionEnabled() {
	return collisionEnabled;
}

void Collision::FillBuckets() {
	for (Collider* o : Game::colliders) {
		o->GetNearbyBoxes();
	}
}

void Collision::ClearBuckets() {
	for (pair<int, Bucket*> p : buckets) {
		p.second->Clear();
	}

	for (Collider* o : Game::colliders) {
		o->Clear();
	}
}

void Collision::SetupBuckets(int sX, int sY, int csX, int csY) {
	int nX = (int) floorf(sX / csX), nY = (int) floorf(sY / csY), id = 0;

	Collision::nX = nX;
	Collision::nY = nY;
	Collision::cellSizeX = csX;
	Collision::cellSizeY = csY;

	for (int y = 0; y < nY; y++) {
		for (int x = 0; x < nX; x++) {
			buckets[id] = new Bucket(id, x, y, csX, csY);
			id++;
		}
	}
}


void Collision::CheckCollisions(set<Bucket*> &buckets) {
	set<Collider*> colliders;

	for (Bucket* b : buckets) {
		for (Collider* c : b->objects) {
			if (colliders.find(c) == colliders.end()) {
				colliders.insert(c);
			}
		}
	}

	if (colliders.size() <= 1) return;

	set<Collider*>::iterator head;
	set<Collider*>::iterator compare;

	int c = 1;

	

	for (head = colliders.begin(); head != colliders.end(); ++head) {
		for (compare = next(colliders.begin(), c); compare != colliders.end(); ++compare) {
			SDL_Rect intersection;
			Game::collisionsChecksPerSec++;
			if ((*head)->CheckCollision(*compare, intersection)) {
				(*head)->CollisionEnter(*compare, intersection);
				(*compare)->CollisionEnter(*head, intersection);
			}
		}

		c++;
	}
}

void Collider::Clear() {
	for (Bucket* b : bucketsIn) {
		b->objects.erase(this);
	}

	bucketsIn.clear();
}

void Collider::GetNearbyBoxes() {}

void Collider::AddBucket(Vector2 pos) {
	int x = floorf(pos.x / Collision::cellSizeX);
	int y = floorf(pos.y / Collision::cellSizeY);

	if (x >= Collision::nX || x < 0 || y >= Collision::nY || y < 0) {
		return;
	}

	int i = y * Collision::nX + x;
	Bucket* bucket = Collision::buckets[i];

	if (bucketsIn.find(bucket) == bucketsIn.end()) {
		Bucket* bucket = Collision::buckets[i];

		bucketsIn.insert(bucket);
		bucket->objects.insert(this);
	}
}

SquareCollider::SquareCollider(GameObject* gameobject) : Collider(gameobject) {
	GetNearbyBoxes();
};


//bool SquareCollider::IsColliding(SquareCollider* c) {
//	SDL_Rect rect;
//	return SDL_IntersectRect(&boundingBox.ToSDL(), &c->boundingBox.ToSDL(), &rect);
//}

void SquareCollider::GetNearbyBoxes() {
	Clear();
	Vector2 size = gameobject->GetSize();
	
	boundingBox.x = gameobject->Position()->x;
	boundingBox.y = gameobject->Position()->y;
	boundingBox.w = size.x;
	boundingBox.h = size.y;

	if (size.x > Collision::cellSizeX || size.y > Collision::cellSizeY) {
		// We add and not index * width for performance reasons.
		for (int x = boundingBox.x; x < boundingBox.x + size.x + Collision::cellSizeX / 2; x += Collision::cellSizeX) {
			for (int y = boundingBox.y; y < boundingBox.y + size.y + Collision::cellSizeY / 2; y += Collision::cellSizeY) {
				AddBucket(Vector2(x, y));
			}
		}
	} else {
		Vector2 min = Vector2(boundingBox.x, boundingBox.y);
		Vector2 max = Vector2(boundingBox.x + boundingBox.w, boundingBox.y + boundingBox.h);

		AddBucket(min);
		AddBucket(Vector2(min.x, max.y));
		AddBucket(Vector2(max.x, min.y));
		AddBucket(max);
	}

	Collision::CheckCollisions(bucketsIn);
}

void Collider::CollisionEnter(Collider* c, SDL_Rect intersection) {
	gameobject->CollisionEnter(c, intersection);
}

bool SquareCollider::CheckCollision(Collider* c, SDL_Rect& intersection) {
	if (SquareCollider* col = dynamic_cast<SquareCollider*>(c)) {
		return CollisionChecker::CheckCollision(this, col, intersection);
	} else {
		return false;
	}
}

bool CollisionChecker::CheckCollision(Collider* c1, Collider* c2) {
	return false;
}

bool CollisionChecker::CheckCollision(SquareCollider* c1, SquareCollider* c2, SDL_Rect& intersection) {
	const Vector2* v1 = c1->gameobject->GetVelocity();
	const Vector2* v2 = c2->gameobject->GetVelocity();
	Rect r1 = {c1->boundingBox.x + v1->x, c1->boundingBox.y + v1->y, c1->boundingBox.w, c1->boundingBox.h}; // Extrapolating for velocity
	Rect r2 = {c2->boundingBox.x + v2->x, c2->boundingBox.y + v2->y, c2->boundingBox.w, c2->boundingBox.h};

	if (SDL_IntersectRect(&r1.ToSDL(), &r2.ToSDL(), &intersection)) {
		return true;
	} else {
		return false;
	}
}

void Collider::GameObjectSizeChanged(Vector2 size) {}

void SquareCollider::GameObjectSizeChanged(Vector2 size) {
	boundingBox.w = size.x;
	boundingBox.h = size.y;
	GetNearbyBoxes();
}