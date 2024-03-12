#pragma once
#include "Common/d3dApp.h"
#include "Common/MathHelper.h"
#include "Common/UploadBuffer.h"
#include "Common/GeometryGenerator.h"
#include "Common/Camera.h"
#include "FrameResource.h"
#include "Category.hpp"
#include "Command.h"

using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::PackedVector;

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")

// Lightweight structure stores parameters to draw a shape.  This will
// vary from app-to-app.
struct RenderItem
{
	RenderItem() = default;

	// World matrix of the shape that describes the object's local space
	// relative to the world space, which defines the position, orientation,
	// and scale of the object in the world.
	XMFLOAT4X4 World = MathHelper::Identity4x4();

	XMFLOAT4X4 TexTransform = MathHelper::Identity4x4();

	// Dirty flag indicating the object data has changed and we need to update the constant buffer.
	// Because we have an object cbuffer for each FrameResource, we have to apply the
	// update to each FrameResource.  Thus, when we modify obect data we should set 
	// NumFramesDirty = gNumFrameResources so that each frame resource gets the update.
	int NumFramesDirty = gNumFrameResources;

	// Index into GPU constant buffer corresponding to the ObjectCB for this render item.
	UINT ObjCBIndex = -1;

	Material* Mat = nullptr;
	MeshGeometry* Geo = nullptr;

	// Primitive topology.
	D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	// DrawIndexedInstanced parameters.
	UINT IndexCount = 0;
	UINT StartIndexLocation = 0;
	int BaseVertexLocation = 0;
};

class Game;
class State;

// 씬그래프의 트리 구조를 구성하기 위한 노드 클래스이다.
// 이 클래스를 상속받아 출력하기 위한 클래스들을 만들어주는 용도로 사용한다.
/**
* @brief This class serves the purpose of constructing a tree structure for a scene graph and is meant to be inherited for creating classes responsible for rendering
*/
class SceneNode
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;


public:
	/**
	* @brief Constructor for the SceneNode class
	* @param game ptr to the Game instance
	*/
	SceneNode(Game* game, State* state);
	/**
	* @brief Destructor for the SceneNode class
	*/
	virtual ~SceneNode();

	/**
	* @brief Attaches a child node to the current SceneNode instance
	* @param child sceneNode instance ptr
	*/
	void					attachChild(Ptr child);
	/**
	* @brief Detaches a child node to the current SceneNode instance
	* @param child sceneNode instance reference
	*/
	Ptr						detachChild(const SceneNode& node);

	/**
	* @brief Invoke the SceneNode instance's update routine on each frame
	* @param Utilize the GameTimer reference gt to access the deltaTime property for updating the aircraft instance
	*/
	void					update(const GameTimer& gt);
	/**
	* @brief Draws on SceneNode instance
	*/
	void					draw() const;
	/**
	* @brief Builds on SceneNode instance
	*/
	void					build();

	/**
	* @brief Get x,y,z World Position
	*/
	XMFLOAT3				getWorldPosition() const;
	/**
	* @brief Set x,y,z World Position
	*/
	void					setPosition(float x, float y, float z);
	/**
	* @brief Get x,y,z World Rotation
	*/
	XMFLOAT3				getWorldRotation() const;
	/**
	* @brief Set x,y,z World Rotation
	*/
	void					setWorldRotation(float x, float y, float z);
	/**
	* @brief Get x,y,z World Scale
	*/
	XMFLOAT3				getWorldScale() const;
	/**
	* @brief Set x,y,z World Scale
	*/
	void					setScale(float x, float y, float z);

	/**
	* @brief Get 4x4 matrix world transform for parent and child instance
	*/
	XMFLOAT4X4				getWorldTransform() const;
	/**
	* @brief Get 4x4 matrix transform for current instance
	*/
	XMFLOAT4X4				getTransform() const;

	void					onCommand(const Command& command, const GameTimer& gt);
	virtual unsigned int	getCategory() const;

	/**
	* @brief Move current instance by x,y,z
	*/
	void					move(float x, float y, float z);
		
protected:
	/**
	* @brief Update current SceneNode instance
	* @param Utilize the GameTimer reference gt to access the deltaTime property for updating the aircraft instance
	*/
	virtual void			updateCurrent(const GameTimer& gt);
	/**
	* @brief Update SceneNode's child instance
	* @param Utilize the GameTimer reference gt to access the deltaTime property for updating the aircraft instance
	*/
	void					updateChildren(const GameTimer& gt);

	/**
	* @brief Draw current SceneNode instance
	*/
	virtual void			drawCurrent() const;
	/**
	* @brief Draw SceneNode's child instance
	*/
	void					drawChildren() const;
	/**
	* @brief Build current SceneNode instance
	*/
	virtual void			buildCurrent();
	/**
	* @brief Build SceneNode's child instance
	*/
	void					buildChildren();

protected:
	State* mState;
	Game*	mGame;
	std::unique_ptr<RenderItem> renderer;

protected:
	XMFLOAT3				mWorldPosition;
	XMFLOAT3				mWorldRotation;
	XMFLOAT3				mWorldScaling;
	std::vector<Ptr>		mChildren;
	SceneNode* mParent;
	bool		mActive;

public:
	bool GetActive()
	{
		return mActive;
	}

	void SetActive(bool Active)
	{
		mActive = Active;
	}
};

