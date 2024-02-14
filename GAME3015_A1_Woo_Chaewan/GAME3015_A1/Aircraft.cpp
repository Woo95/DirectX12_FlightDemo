#include "Aircraft.hpp"
#include "Game.hpp"

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
	case (Eagle):	// move eagle
		if (mWorldPosition.x >= 2.0)
		{
			mWorldPosition.x = 2.0;
			setVelocity(-2.f, 0.f);
		}

		else if (mWorldPosition.x <= -2.0)
		{
			mWorldPosition.x = -2.0;
			setVelocity(2.f, 0.f);
		}
		break;
	}

	Entity::updateCurrent(gt);
}

void Aircraft::drawCurrent()
{
	auto vbv = renderer->Geo->VertexBufferView();
	auto ibv = renderer->Geo->IndexBufferView();

	UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
	UINT matCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(MaterialConstants));

	auto objectCB = mCurrFrameResource->ObjectCB->Resource();
	auto matCB = mCurrFrameResource->MaterialCB->Resource();

	cmdList->IASetVertexBuffers(0, 1, &vbv);
	cmdList->IASetIndexBuffer(&ibv);
	cmdList->IASetPrimitiveTopology(renderer->PrimitiveType);

	D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress() + renderer->ObjCBIndex * objCBByteSize;
	D3D12_GPU_VIRTUAL_ADDRESS matCBAddress = matCB->GetGPUVirtualAddress() + renderer->Mat->MatCBIndex * matCBByteSize;

	cmdList->SetGraphicsRootConstantBufferView(1, objCBAddress);
	cmdList->SetGraphicsRootConstantBufferView(3, matCBAddress);

	cmdList->DrawIndexedInstanced(renderer->IndexCount, 1, renderer->StartIndexLocation, renderer->BaseVertexLocation, 0);
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