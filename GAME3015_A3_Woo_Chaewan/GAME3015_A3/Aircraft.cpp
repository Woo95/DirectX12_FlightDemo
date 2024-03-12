#include "Aircraft.hpp"
#include "Game.hpp"
#include "Missile.h"

Aircraft::Aircraft(Type type, Game* game, State* state) : Entity(game, state)
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

		if (mWorldPosition.z <= -1.5f)
		{
			mWorldPosition.z = -1.5f;
		}
		else if (mWorldPosition.z >= 2.5f)
		{
			mWorldPosition.z = 2.5f;
		}
		break;
	}

	//checkProjectileLaunch(gt, )

	Entity::updateCurrent(gt);

	auto currObjectCB = mGame->GetCurrentFrameResource()->ObjectCB.get();

	// Do nothing by default
	XMMATRIX world = XMLoadFloat4x4(&renderer->World);
	XMMATRIX texTransform = XMLoadFloat4x4(&renderer->TexTransform);

	ObjectConstants objConstants;
	XMStoreFloat4x4(&objConstants.World, XMMatrixTranspose(world));
	XMStoreFloat4x4(&objConstants.TexTransform, XMMatrixTranspose(texTransform));

	renderer->ObjCBIndex = mGame->GetCurrentRenderCount();

	currObjectCB->CopyData(renderer->ObjCBIndex, objConstants);
	mGame->AddCurrentRenderCount();
}

void Aircraft::buildCurrent()
{
	renderer = std::make_unique<RenderItem>();
	renderer->World = getTransform();
	//renderer->ObjCBIndex = mGame->getRenderItems().size();
	renderer->Mat = mGame->getMaterials()[mSprite].get();
	renderer->Geo = mGame->getGeometries()["ShapeGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs[mSprite].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs[mSprite].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs[mSprite].BaseVertexLocation;

	//mGame->getRenderItems().push_back(std::move(render));
}

void Aircraft::drawCurrent() const
{
	UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
	UINT matCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(MaterialConstants));

	FrameResource* CurrentFrame = mGame->GetCurrentFrameResource();

	auto objectCB = CurrentFrame->ObjectCB->Resource();
	auto matCB = CurrentFrame->MaterialCB->Resource();

	ID3D12GraphicsCommandList* cmdList = mGame->GetGraphicsCommandList().Get();

	cmdList->IASetVertexBuffers(0, 1, &renderer->Geo->VertexBufferView());
	cmdList->IASetIndexBuffer(&renderer->Geo->IndexBufferView());
	cmdList->IASetPrimitiveTopology(renderer->PrimitiveType);

	ComPtr<ID3D12DescriptorHeap>	SrvDescriptorHeap = mGame->GetDescriptorHeap();
	UINT	CbvSrvDescriptorSize = mGame->GetDescriptorHeapSize();

	//step18
	CD3DX12_GPU_DESCRIPTOR_HANDLE tex(SrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
	tex.Offset(renderer->Mat->DiffuseSrvHeapIndex, CbvSrvDescriptorSize);

	D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress() + renderer->ObjCBIndex * objCBByteSize;
	D3D12_GPU_VIRTUAL_ADDRESS matCBAddress = matCB->GetGPUVirtualAddress() + renderer->Mat->MatCBIndex * matCBByteSize;

	//step19
	cmdList->SetGraphicsRootDescriptorTable(0, tex);
	cmdList->SetGraphicsRootConstantBufferView(1, objCBAddress);
	cmdList->SetGraphicsRootConstantBufferView(3, matCBAddress);

	cmdList->DrawIndexedInstanced(renderer->IndexCount, 1, renderer->StartIndexLocation, renderer->BaseVertexLocation, 0);
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
	// STL vector에 문제가 발생하고 있어서, postCommand를 통해서 해결했다.
	mState->AddPostCommandQueue<Aircraft>(this, &Aircraft::CreateMissile);
}

void Aircraft::CreateMissile()
{
	std::unique_ptr<Missile> MissileInstance(new Missile(mGame, mState));
	XMFLOAT3	Pos = mWorldPosition;
	Pos.z += 1.f;
	MissileInstance->setPosition(Pos.x, Pos.y, Pos.z + 1.0);
	//MissileInstance->setPosition(0.0, 0.0, 1.0);
	MissileInstance->setScale(0.5, 1.0, 0.5);
	MissileInstance->setWorldRotation(0.0, 0.0, 0.0);
	//MissileInstance->setVelocity(0.f, 3.f);
	MissileInstance->setSaveVelocity(0.f, 3.f);
	MissileInstance->build();
	//attachChild(std::move(MissileInstance));
	mState->GetSceneGraph()->attachChild(std::move(MissileInstance));
}
