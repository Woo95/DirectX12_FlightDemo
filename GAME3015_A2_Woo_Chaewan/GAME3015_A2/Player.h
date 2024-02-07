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

	void					assignKey(Action action, const unsigned char key);
	unsigned char			getAssignedKey(Action action) const;


private:
	void					initializeActions();
	static bool				isRealtimeAction(Action action);
	void MissileInput(SceneNode& node, const GameTimer& gt);


private:
	std::map<unsigned char, ActionData>			mKeyBinding;
	std::map<Action, Command>				mActionBinding;
#pragma endregion
};

