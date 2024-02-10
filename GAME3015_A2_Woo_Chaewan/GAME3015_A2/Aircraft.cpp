#include "Aircraft.hpp"
#include "Game.hpp"
#include "Missile.h"
#include "World.hpp"

Aircraft::Aircraft(Type type, Game* game) : Entity(game)
	, mType(type)
{
	switch (type)
	{
	case (Eagle):
		mSprite = "Eagle";
		break;
	case (Raptor):
		mSprite = "Raptor";
		break;
	default:
		mSprite = "Eagle";
		break;
	}
}

Aircraft::~Aircraft()
{
}

void Aircraft::updateCurrent(const GameTimer& gt)
{
	switch (mType)
	{
	case (Eagle):	// eagle boundary
		if (mWorldPosition.x >= 2.9f)
		{
			mWorldPosition.x = 2.9f;
		}
		else if (mWorldPosition.x <= -2.9f)
		{
			mWorldPosition.x = -2.9f;
		}

		if (mWorldPosition.z <= -0.1f)
		{
			mWorldPosition.z = -0.1f;
		}
		else if (mWorldPosition.z >= 4.2f)
		{
			mWorldPosition.z = 4.2f;
		}
		break;
	}

	//checkProjectileLaunch(gt, )

	Entity::updateCurrent(gt);
}

void Aircraft::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()[mSprite].get();
	renderer->Geo = game->getGeometries()["ShapeGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs[mSprite].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs[mSprite].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs[mSprite].BaseVertexLocation;

	game->getRenderItems().push_back(std::move(render));
}

unsigned int Aircraft::getCategory() const
{
	switch (mType)
	{
	case Eagle:
		return Category::PlayerAircraft;

	default:
		return Category::EnemyAircraft;
	}
}

void Aircraft::checkProjectileLaunch(const GameTimer& gt, CommandQueue& commands)
{
}

void Aircraft::launchMissile()
{
	std::unique_ptr<Missile> MissileInstance(new Missile(game));
	XMFLOAT3	Pos = mWorldPosition;
	Pos.z += 1.f;
	MissileInstance->setPosition(Pos.x, Pos.y, Pos.z);
	MissileInstance->setScale(1.0, 1.0, 1.0);
	MissileInstance->setWorldRotation(0.0, 0.0, 0.0);
	MissileInstance->setVelocity(0.f, 3.f);
	MissileInstance->build();
	attachChild(std::move(MissileInstance));
	//game->GetWorld()->GetSceneGraph()->attachChild(std::move(MissileInstance));
}
