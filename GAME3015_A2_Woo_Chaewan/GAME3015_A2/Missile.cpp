#include "Missile.h"
#include "Game.hpp"

Missile::Missile(Game* game)	:
	Entity(game),
	Distance(3.f)
{
}

Missile::~Missile()
{
}

void Missile::updateCurrent(const GameTimer& gt)
{
	mSaveVelocity = mVelocity;

	Entity::updateCurrent(gt);

	mVelocity = mSaveVelocity;

	XMFLOAT2 mV;
	mV.x = mVelocity.x * gt.DeltaTime();
	mV.y = mVelocity.y * gt.DeltaTime();
	
	float	Dist = XMVectorGetX(XMVector2Length(XMLoadFloat2(&mV)));

	Distance -= Dist;
}

void Missile::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()["Missile"].get();
	renderer->Geo = game->getGeometries()["ShapeGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;

	game->getRenderOpaqueItems().push_back(render.get());
	game->getRenderItems().push_back(std::move(render));
}
