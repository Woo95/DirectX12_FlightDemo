#include "SpriteNode.h"
#include "Game.hpp"

SpriteNode::SpriteNode(Game* game, State* state, const std::string& SpriteName, const std::string& ShapeName) :
	Entity(game, state)
	, mSpriteName(SpriteName)
	, mShapeName(ShapeName)
{
}

SpriteNode::~SpriteNode()
{
}

void SpriteNode::updateCurrent(const GameTimer& gt)
{
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

	renderer->World = getTransform();
	renderer->NumFramesDirty++;
}

void SpriteNode::drawCurrent() const
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

void SpriteNode::buildCurrent()
{
	renderer = std::make_unique<RenderItem>();
	renderer->World = getTransform();
	//XMStoreFloat4x4(&renderer->TexTransform, XMMatrixScaling(1.0f, mWorldScaling.z / 10.f, 1.0f));	// worldScale / 10.0f amount of desert texture
	renderer->ObjCBIndex = mGame->getRenderItems().size();
	renderer->Mat = mGame->getMaterials()[mSpriteName].get();
	renderer->Geo = mGame->getGeometries()["ShapeGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs[mShapeName].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs[mShapeName].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs[mShapeName].BaseVertexLocation;

	//game->getRenderItems().push_back(std::move(render));
}
