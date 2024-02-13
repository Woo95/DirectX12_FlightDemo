#include "SpriteNode.h"
#include "Game.hpp"

SpriteNode::SpriteNode(Game* game) : Entity(game)
{
}

SpriteNode::~SpriteNode()
{
}

void SpriteNode::drawCurrent() const
{
	renderer->World = getTransform();
	renderer->NumFramesDirty++;
}

void SpriteNode::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	//XMStoreFloat4x4(&renderer->TexTransform, XMMatrixScaling(1.0f, mWorldScaling.z / 10.f, 1.0f));	// worldScale / 10.0f amount of desert texture
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()["Desert"].get();
	renderer->Geo = game->getGeometries()["ShapeGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["grid"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["grid"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["grid"].BaseVertexLocation;

	game->getRenderItems().push_back(std::move(render));
}
