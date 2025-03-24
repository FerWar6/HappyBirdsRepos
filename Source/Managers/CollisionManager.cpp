#include "CollisionManager.h"
#include "ServiceLocator.h"
#include "Engine/Engine.h"
#include "Objects/Object.h"
#include "box2d/box2d.h"
#include "Objects/Components/Components.h"
CollisionManager::CollisionManager()
	:	objects(nullptr),
	worldId(nullptr)
{}

void CollisionManager::Start()
{
	objects = &sl::GetEngine().objects;
	worldId = &sl::GetWorldId();
}

void CollisionManager::UpdateCollisions()
{
	for (auto& obj : *objects) {
		obj->Update();
	}

	b2ContactEvents contactEvents = b2World_GetContactEvents(*worldId);

	if (contactEvents.hitCount > 0)
	{
		for (int i = 0; i < contactEvents.hitCount; ++i)
		{
			const b2ContactHitEvent& hitEvent = contactEvents.hitEvents[i];
			for (auto& obj : *objects) {
				RectRigidbody* bodyPtr = (RectRigidbody*)obj->GetComponent(RECT_RIGIDBODY);
				if (bodyPtr) {
					if (bodyPtr->bodyId.index1 == hitEvent.shapeIdA.index1 || bodyPtr->bodyId.index1 == hitEvent.shapeIdB.index1) {
						if (obj->HasComponent(DESTRUCTIBLE_ITEM)) {
							DestructibleItem* destructible = (DestructibleItem*)obj->GetComponent(DESTRUCTIBLE_ITEM);
							destructible->DamageWithSpeed(hitEvent.approachSpeed);
						}
					}
					//std::cout << "bodyId index: " << bodyPtr->bodyId.index1 << "\n";
				}
				//std::cout << "hitEvent shapeA: " << hitEvent.shapeIdA.index1 << "\n";
				//std::cout << "hitEvent shapeB: " << hitEvent.shapeIdB.index1 << "\n";
			}
			std::cout << " Point: (" << hitEvent.point.x << ", " << hitEvent.point.y << ")"
				<< " Normal: (" << hitEvent.normal.x << ", " << hitEvent.normal.y << ")"
				<< " Speed: " << hitEvent.approachSpeed << " m/s\n";
		}
	}
}