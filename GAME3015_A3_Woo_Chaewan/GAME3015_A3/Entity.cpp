#include "Entity.hpp"

Entity::Entity(Game* game) : SceneNode(game), mVelocity(0, 0)
{
}

Entity::~Entity()
{
}

void Entity::setVelocity(XMFLOAT2 velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

XMFLOAT2 Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::accelerate(XMFLOAT2 velocity)
{
	mVelocity.x += velocity.x;
	mVelocity.y += velocity.y;
}

void Entity::accelerate(float vx, float vy)
{
	mVelocity.x += vx;
	mVelocity.y += vy;
}

void Entity::updateCurrent(const GameTimer& gt) 
{
	XMFLOAT2 mV;
	mV.x = mVelocity.x * gt.DeltaTime();
	mV.y = mVelocity.y * gt.DeltaTime();

	move(mV.x, 0, mV.y);	// y and z swapped, because the game is 2D

	mVelocity.x = 0.f;
	mVelocity.y = 0.f;

	renderer->World = getWorldTransform();
	renderer->NumFramesDirty++;
}
