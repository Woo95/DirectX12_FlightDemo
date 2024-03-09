#include "Missile.h"
#include "Game.hpp"

Missile::Missile(Game* game, World* world)	:
	Entity(game, world),
	m_Distance(10.f)
{
}

Missile::~Missile()
{
}

void Missile::updateCurrent(const GameTimer& gt)
{
	mVelocity = mSaveVelocity;

	XMFLOAT3	SavePos = mWorldPosition;

	Entity::updateCurrent(gt);

	XMFLOAT3	Dir;

	Dir.x = mWorldPosition.x - SavePos.x;
	Dir.y = mWorldPosition.y - SavePos.y;
	Dir.z = mWorldPosition.z - SavePos.z;

	float	Dist = XMVectorGetX(XMVector3Length(XMLoadFloat3(&Dir)));

	m_Distance -= Dist;

	if (m_Distance <= 0.f)
	{
		SetActive(false);
	}


	auto currObjectCB = mGame->GetCurrentFrameResource()->ObjectCB.get();

	XMMATRIX world = XMLoadFloat4x4(&renderer->World);
	XMMATRIX texTransform = XMLoadFloat4x4(&renderer->TexTransform);

	ObjectConstants objConstants;
	XMStoreFloat4x4(&objConstants.World, XMMatrixTranspose(world));
	XMStoreFloat4x4(&objConstants.TexTransform, XMMatrixTranspose(texTransform));

	renderer->ObjCBIndex = mGame->GetCurrentRenderCount();

	currObjectCB->CopyData(renderer->ObjCBIndex, objConstants);
	mGame->AddCurrentRenderCount();
}

void Missile::buildCurrent()
{
	renderer = std::make_unique<RenderItem>();
	renderer->World = getTransform();
	renderer->ObjCBIndex = mGame->getRenderItems().size();
	renderer->Mat = mGame->getMaterials()["Missile"].get();
	renderer->Geo = mGame->getGeometries()["ShapeGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;

	//game->getRenderOpaqueItems().push_back(render.get());
	//game->getRenderItems().push_back(std::move(render));
}

void Missile::drawCurrent() const
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
