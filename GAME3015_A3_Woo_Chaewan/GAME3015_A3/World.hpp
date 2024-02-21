#pragma once
#include "SceneNode.hpp"
#include "Aircraft.hpp"
#include "SpriteNode.h"
#include "CommandQueue.h"
#include <queue>

/**
 * @brief World class that handles update, draw, and building the game world
 */
class World
{
public:
	/**
	 * @brief Explicit constructor for the World class
	 */
	explicit							World(Game* window);
	/**
	 * @brief Destructor for the World class
	 */
	~World();
	/**
	* @brief Invoke the World instance's update routine on each frame
	* @param Utilize the GameTimer reference gt to access the deltaTime property for updating the aircraft instance
	*/
	void								update(const GameTimer& gt);
	/**
	* @brief Draws the game
	*/
	void								draw();

	//void								loadTextures();
	/**
	* @brief Builds the initial scene for the game
	*/
	void								buildScene();
	/**
	  * @brief Get the command queue of the world.
	  * @return A reference to the CommandQueue.
	  */
	CommandQueue& getCommandQueue();
	/**
	 * @brief Get the root node of the scene graph.
	 * @return A pointer to the root node of the scene graph.
	 */
	SceneNode* GetSceneGraph()
	{
		return mSceneGraph;
	}


private:
	enum Layer
	{
		Background,
		Air,
		LayerCount
	};

public:
	/**
	 * @brief Add a command to be executed after the current frame.
	 * @tparam T The type of object.
	 * @param Obj The object pointer.
	 * @param Func The member function pointer to be executed.
	 */
	template <typename T>
	void AddPostCommandQueue(T* Obj, void(T::* Func)())
	{
		mPostCommandQueue.push(std::bind(Func, Obj));
	}


private:
	Game* mGame;

	SceneNode* mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;
	CommandQueue						mCommandQueue;

	XMFLOAT4							mWorldBounds;
	XMFLOAT2		    				mSpawnPosition;
	float								mScrollSpeed;
	Aircraft* mPlayerAircraft;
	SpriteNode* mBackground;
	float								mBackGroundXSize;
	float								mBackGroundZSize;
	float								mBackGroundZStartPos;
	Aircraft* mEnemy;
	std::queue<std::function<void()>>			mPostCommandQueue;
};
