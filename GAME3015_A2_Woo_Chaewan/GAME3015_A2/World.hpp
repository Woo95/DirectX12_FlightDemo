#pragma once
#include "SceneNode.hpp"
#include "Aircraft.hpp"
#include "SpriteNode.h"

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


private:
	enum Layer
	{
		Background,
		Air,
		LayerCount
	};


private:
	Game* mGame;

	SceneNode* mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;

	XMFLOAT4							mWorldBounds;
	XMFLOAT2		    				mSpawnPosition;
	float								mScrollSpeed;
	Aircraft* mPlayerAircraft;
	SpriteNode* mBackground;
	float								mBackGroundXSize;
	float								mBackGroundZSize;
	float								mBackGroundZStartPos;
	Aircraft* mEnemy;
};
