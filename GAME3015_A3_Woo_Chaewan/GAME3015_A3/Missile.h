#pragma once
#include "Entity.hpp"

class Missile :
    public Entity
{
public:
	/**
	* @brief Constructor for the Missile class
	*/
	Missile(Game* game, State* state);
	/**
	* @brief Destructor for the Missile class
	*/
	virtual ~Missile();


private:
	/**
	* @brief Invoke the Missile instance's update routine on each frame
	* @param Utilize the GameTimer reference gt to access the deltaTime property for updating the Missile instance
	*/
	virtual	void		updateCurrent(const GameTimer& gt);
	/**
	* @brief Setting up the Missile instance data
	*/
	virtual void		buildCurrent();
	/**
	* @brief Drawing the Missile
	*/
	virtual void		drawCurrent() const;


private:
	/**
	* @brief Destructor for the Missile class
	*/
	float			m_Distance;
	XMFLOAT2		mSaveVelocity;

public:
	void setSaveVelocity(float x, float y)
	{
		mSaveVelocity.x = x;
		mSaveVelocity.y = y;
	}
};

