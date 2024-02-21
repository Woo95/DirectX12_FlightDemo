#pragma once

#include "Command.h"
#include "Common/d3dApp.h"
#include "Common/MathHelper.h"
#include <map>

class CommandQueue;

class Player
{
public:
	Player();
	void					InputEvent();
	void					handleEvent(CommandQueue& commands);
	void					handleRealtimeEvent(CommandQueue& commands);
#pragma region step 1
	//static const float		PlayerSpeed;
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		GetPosition,
		Missile,
		ActionCount
	};

	struct ActionData
	{
		Action	action;
		bool	Press;
		bool	Hold;
		bool	Release;

		ActionData()
		{
			Press = false;
			Hold = false;
			Release = false;
		}

		ActionData(Action _action)
		{
			action = _action;
			Press = false;
			Hold = false;
			Release = false;
		}
	};

	/**
	* @brief Assigns a key to a specific action.
	* @param action The action to assign a key to.
	* @param key The key to assign to the action.
	*/
	void assignKey(Action action, const unsigned char key);

	/**
	 * @brief Gets the assigned key for a specific action.
	 * @param action The action to get the assigned key for.
	 * @return The assigned key for the action.
	 */
	unsigned char getAssignedKey(Action action) const;

private:
	/**
	 * @brief Initializes player actions and key bindings.
	 */
	void initializeActions();

	/**
	 * @brief Checks if an action is a real-time action.
	 * @param action The action to check.
	 * @return True if the action is real-time, false otherwise.
	 */
	static bool isRealtimeAction(Action action);

	/**
	 * @brief Handles missile input.
	 * @param node The scene node to fire missile from.
	 * @param gt The GameTimer reference.
	 */
	void MissileInput(SceneNode& node, const GameTimer& gt);


private:
	std::map<unsigned char, ActionData>			mKeyBinding;
	std::map<Action, Command>				mActionBinding;
#pragma endregion
};

