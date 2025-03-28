#include "CollisionManager.h"
#include "ServiceLocator.h"
#include "Engine/Engine.h"
#include "Objects/Object.h"
#include "Objects/Components/Components.h"
#include <box2d/box2d.h>
CollisionManager::CollisionManager()
	:	objects(nullptr),
	worldId(nullptr)
{}

void CollisionManager::Start()
{
	objects = &sl::GetEngine().objects;
	worldId = &sl::GetWorldId();
	b2World_SetHitEventThreshold(*worldId, 3); // set the hit threshold to be at least 3 m/s to count as a hit
}

void CollisionManager::UpdateCollisions() // updates the necessary components when collisions are detected
{
	b2ContactEvents contactEvents = b2World_GetContactEvents(*worldId);
	for (int i = 0; i < contactEvents.hitCount; ++i)
	{
		const b2ContactHitEvent& hitEvent = contactEvents.hitEvents[i];
		for (auto& obj : *objects) {
			RectRigidbody* rectBodyPtr = nullptr;
			CircleRigidbody* circleBodyPtr = nullptr;
			if(obj->HasComponent(RECT_RIGIDBODY)) rectBodyPtr = (RectRigidbody*)obj->GetComponent(RECT_RIGIDBODY);
			if(obj->HasComponent(CIRCLE_RIGIDBODY)) circleBodyPtr = (CircleRigidbody*)obj->GetComponent(CIRCLE_RIGIDBODY);
			if (rectBodyPtr) {
				if (rectBodyPtr->GetBodyId().index1 == hitEvent.shapeIdA.index1 || rectBodyPtr->GetBodyId().index1 == hitEvent.shapeIdB.index1) {
					if (obj->HasComponent(DESTRUCTIBLE_ITEM)) {
						DestructibleItem* destructible = (DestructibleItem*)obj->GetComponent(DESTRUCTIBLE_ITEM);
						destructible->DamageWithSpeed(hitEvent.approachSpeed);
					}
				}
			}
			if (circleBodyPtr) {
				if (circleBodyPtr->GetBodyId().index1 == hitEvent.shapeIdA.index1 || circleBodyPtr->GetBodyId().index1 == hitEvent.shapeIdB.index1) {
					if (obj->HasComponent(DESTRUCTIBLE_ITEM)) {
						DestructibleItem* destructible = (DestructibleItem*)obj->GetComponent(DESTRUCTIBLE_ITEM);
						destructible->DamageWithSpeed(hitEvent.approachSpeed);
					}
				}
			}
		}
	}
}

bool CollisionManager::IsBodyAsleep(b2BodyId id)
{
	float yVelocityThreshold = 0.1f;
	b2Vec2 velocity = b2Body_GetLinearVelocity(id);
	if (velocity.y > yVelocityThreshold) {
		return false;
	}
	return true;
}

bool CollisionManager::AllBodiesAsleep()
{
	// Returns true if no bodies awake or the bodies awake move very little
	if (b2World_GetAwakeBodyCount(*worldId) == 0) return true;
	std::vector<b2BodyId> bodies;
	for (auto& obj : *objects) {
		if (obj->HasComponent(RECT_RIGIDBODY)) bodies.push_back(((RectRigidbody*)obj->GetComponent(RECT_RIGIDBODY))->GetBodyId());
		if (obj->HasComponent(CIRCLE_RIGIDBODY)) bodies.push_back(((CircleRigidbody*)obj->GetComponent(CIRCLE_RIGIDBODY))->GetBodyId());
	}
	for (auto& body : bodies) {
		float yVelocityThreshold = 0.1f;
		b2Vec2 velocity = b2Body_GetLinearVelocity(body);
		if (velocity.y > yVelocityThreshold) {
			return false;
		}
	}
	return true;
}
