
#include "Common/d3dApp.h"
#include "Common/Camera.h"
#include "World.hpp"
#include "Player.h"

/**
 * @brief Game class that represents the main application
 */
class Game : public D3DApp
{
public:
	/**
	 * @brief Constructor for the Game class
	 */
	Game(HINSTANCE hInstance);
	/**
	 * @brief Copy constructor for the Game class
	 */
	Game(const Game& rhs) = delete;
	/**
	 * @brief Copy assignment operator for the Game class
	 */
	Game& operator=(const Game& rhs) = delete;
	/**
	 * @brief Destructor for the Game class
	 */
	~Game();

	/**
	 * @brief Initializes the game.
	 * @return If initalized successful it returns true. But false otherwise
	 */
	virtual bool Initialize()override;
private:
	/**
	* @brief Callback on resizing game window
	*/
	virtual void OnResize()override;
	/**
	* @brief Updates the Game instance
	*/
	virtual void Update(const GameTimer& gt)override;

	/**
	* @brief Draw the Game instance
	*/
	virtual void Draw(const GameTimer& gt)override;

	/**
	* @brief Callback on mouse down
	*/
	virtual void OnMouseDown(WPARAM btnState, int x, int y)override;
	/**
	* @brief Callback on mouse up
	*/
	virtual void OnMouseUp(WPARAM btnState, int x, int y)override;
	/**
	* @brief Callback on mouse move
	*/
	virtual void OnMouseMove(WPARAM btnState, int x, int y)override;

	/**
	* @brief Callback on keyboard input
	*/
	void OnKeyboardInput(const GameTimer& gt);
	/**
	* @brief Updates the camera
	*/
	void UpdateCamera(const GameTimer& gt);
	/**
	* @brief Animates materials
	*/
	void AnimateMaterials(const GameTimer& gt);
	/**
	* @brief Updates the shader constant buffer
	*/
	void UpdateObjectCBs(const GameTimer& gt);
	/**
	* @brief Updates the material constant buffer
	*/
	void UpdateMaterialCBs(const GameTimer& gt);
	/**
	* @brief Updates the main pass constant buffer
	*/
	void UpdateMainPassCB(const GameTimer& gt);

	//step5

	/*
	* @brief Load Textures
	*/
	void LoadTextures();

	/*
	* @brief Build root signature for the shader
	*/
	void BuildRootSignature();

	//step9

	/**
	 * @brief Builds descriptor heaps
	 */
	void BuildDescriptorHeaps();

	/**
	 * @brief Builds shaders and input layout
	 */
	void BuildShadersAndInputLayout();

	/**
	 * @brief Builds shape geometry
	 */
	void BuildShapeGeometry();

	/**
	 * @brief Builds the Pipeline State Objects
	 */
	void BuildPSOs();

	/**
	 * @brief Builds frame resources
	 */
	void BuildFrameResources();

	/**
	 * @brief Builds materials for the game
	 */
	void BuildMaterials();

	/**
	 * @brief Builds render items for the game
	 */
	void BuildRenderItems();

	/**
	 * @brief Draws render items
	 * @param cmdList ptr to the ID3D12GraphicsCommandList
	 * @param ritems vector of RenderItem ptrs
	 */
	void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);

	std::array<const CD3DX12_STATIC_SAMPLER_DESC, 6> GetStaticSamplers();

private:

	std::vector<std::unique_ptr<FrameResource>> mFrameResources;
	FrameResource* mCurrFrameResource = nullptr;
	int mCurrFrameResourceIndex = 0;

	UINT mCbvSrvDescriptorSize = 0;

	ComPtr<ID3D12RootSignature> mRootSignature = nullptr;

	//step11
	ComPtr<ID3D12DescriptorHeap> mSrvDescriptorHeap = nullptr;

	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;
	std::unordered_map<std::string, std::unique_ptr<Material>> mMaterials;

	//step7
	std::unordered_map<std::string, std::unique_ptr<Texture>> mTextures;

	std::unordered_map<std::string, ComPtr<ID3DBlob>> mShaders;

	std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;

	ComPtr<ID3D12PipelineState> mOpaquePSO = nullptr;

	// List of all the render items.
	std::vector<std::unique_ptr<RenderItem>> mAllRitems;

	// Render items divided by PSO.
	std::vector<RenderItem*> mOpaqueRitems;

	PassConstants mMainPassCB;

	//XMFLOAT3 mEyePos = { 0.0f, 0.0f, -10.0f };
	//XMFLOAT4X4 mView = MathHelper::Identity4x4();
	//XMFLOAT4X4 mProj = MathHelper::Identity4x4();

	//float mTheta = 1.3f * XM_PI;
	//float mPhi = 0.4f * XM_PI;
	//float mRadius = 2.5f;

	POINT mLastMousePos;
	Camera mCamera;
	World mWorld;
	Player					mPlayer;

public:
	World* GetWorld()
	{
		return &mWorld;
	}

public:
	std::vector<std::unique_ptr<RenderItem>>& getRenderItems() { return mAllRitems; }
	std::vector<RenderItem*>& getRenderOpaqueItems() { return mOpaqueRitems; }
	std::unordered_map<std::string, std::unique_ptr<Material>>& getMaterials() { return mMaterials; }
	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>>& getGeometries() { return mGeometries; }
};
