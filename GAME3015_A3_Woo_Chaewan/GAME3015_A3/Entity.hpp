#pragma once
#include "SceneNode.hpp"

/**
 * @brief Entity class that is to extends the SceneNode class to include velocity properties
 */
class Entity :
	public SceneNode
{
public:
	/**
	* @brief Constructor for the Entity class
	*/
	Entity(Game* game);
	/**
	* @brief Destructor for the Entity class
	*/
	virtual ~Entity();
	/**
	 * @brief Sets the velocity of the Entity
	 * @param XMFLOAT2 type representing the velocity
	 */
	void				setVelocity(XMFLOAT2 velocity);
	/**
	 * @brief Sets the velocity of the Entity
	 * @param float type representing the velocity x
	 * @param float type representing the velocity y
	 */
	void				setVelocity(float vx, float vy);
	/**
	 * @brief Get the velocity of the Entity
	 */
	XMFLOAT2			getVelocity() const;
	void				accelerate(XMFLOAT2 velocity);
	void				accelerate(float vx, float vy);

	/**
	* @brief Invoke the Entity instance's update routine on each frame
	* @param Utilize the GameTimer reference gt to access the deltaTime property for updating the aircraft instance
	*/
	virtual	void		updateCurrent(const GameTimer& gt);

public:
	XMFLOAT2		mVelocity;
};

