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
	void					handleEvent(CommandQueue& commands);
	void					handleRealtimeInput(CommandQueue& commands);
#pragma region step 1
	//static const float		PlayerSpeed;
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		GetPosition,
		ActionCount
	};
	void					assignKey(Action action, const unsigned char key);
	unsigned char			getAssignedKey(Action action) const;


private:
	void					initializeActions();
	static bool				isRealtimeAction(Action action);


private:
	std::map<unsigned char, Action>			mKeyBinding;
	std::map<Action, Command>				mActionBinding;
#pragma endregion
};

