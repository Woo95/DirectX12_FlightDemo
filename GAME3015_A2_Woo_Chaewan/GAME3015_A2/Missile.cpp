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

	Entity::updateCurrent(gt);


	auto currObjectCB = game->GetCurrentFrameResource()->ObjectCB.get();

	XMMATRIX world = XMLoadFloat4x4(&renderer->World);
	XMMATRIX texTransform = XMLoadFloat4x4(&renderer->TexTransform);

	ObjectConstants objConstants;
	XMStoreFloat4x4(&objConstants.World, XMMatrixTranspose(world));
	XMStoreFloat4x4(&objConstants.TexTransform, XMMatrixTranspose(texTransform));

	renderer->ObjCBIndex = game->GetCurrentRenderCount();

	currObjectCB->CopyData(renderer->ObjCBIndex, objConstants);
	game->AddCurrentRenderCount();
}

void Missile::buildCurrent()
{
	renderer = std::make_unique<RenderItem>();
	renderer->World = getTransform();
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()["Missile"].get();
	renderer->Geo = game->getGeometries()["ShapeGeo"].get();
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

	FrameResource* CurrentFrame = game->GetCurrentFrameResource();

	auto objectCB = CurrentFrame->ObjectCB->Resource();
	auto matCB = CurrentFrame->MaterialCB->Resource();

	ID3D12GraphicsCommandList* cmdList = game->GetGraphicsCommandList().Get();

	cmdList->IASetVertexBuffers(0, 1, &renderer->Geo->VertexBufferView());
	cmdList->IASetIndexBuffer(&renderer->Geo->IndexBufferView());
	cmdList->IASetPrimitiveTopology(renderer->PrimitiveType);

	ComPtr<ID3D12DescriptorHeap>	SrvDescriptorHeap = game->GetDescriptorHeap();
	UINT	CbvSrvDescriptorSize = game->GetDescriptorHeapSize();

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
