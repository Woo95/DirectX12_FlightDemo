#pragma once
#include "Entity.hpp"
#include <string>

/**
 * @brief This class, inheriting from the Entity class, is designed to create an aircraft in a game.
 */
class Aircraft :
    public Entity
{
public:
	/**
	 * @brief Enumerate defining the types of Aircraft.
	 */
	enum Type
	{
		Eagle,
		Raptor,
	};


public:
	/**
	* @brief Constructor for the Aircraft class
	*/
	Aircraft(Type type, Game* game);
	/**
	* @brief Destructor for the Aircraft class
	*/
	virtual ~Aircraft();


private:
	/**
	* @brief Invoke the aircraft instance's update routine on each frame
	* @param Utilize the GameTimer reference gt to access the deltaTime property for updating the aircraft instance
	*/
	virtual	void		updateCurrent(const GameTimer& gt);
	/**
	* @brief Setting up the aircraft instance data
	*/
	virtual void		buildCurrent();


private:
	Type				mType;
	std::string			mSprite;
};
