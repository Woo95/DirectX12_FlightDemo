#pragma once
#include "Entity.hpp"

class Missile :
    public Entity
{
public:
	/**
	* @brief Constructor for the Missile class
	*/
	Missile(Game* game);
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

	virtual void		drawCurrent() const;


private:
	/**
	* @brief Destructor for the Missile class
	*/
	float		Distance;
	XMFLOAT2		mSaveVelocity;
};

