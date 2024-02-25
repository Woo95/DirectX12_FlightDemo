#pragma once

#include "Command.h"
#include "StateIdentifiers.h"
#include <memory>

class Player;
class Game;
class StateStack;
class CommandQueue;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context(Game* _game, Player* _player);

		Game* game;
		Player* player;
	};

public:
	State(StateStack& stack, Context context);
	virtual				~State();

	virtual void		draw() = 0;
	virtual bool		update(const GameTimer& gt) = 0;
	virtual	bool		InputEvent() = 0;
	virtual	bool		handleEvent(CommandQueue& commands) = 0;
	virtual	bool		handleRealtimeEvent(CommandQueue& commands) = 0;


protected:
	void				requestStackPush(States::ID stateID);
	void				requestStackPop();
	void				requestStateClear();

	Context				getContext() const;


private:
	StateStack* mStack;
	Context				mContext;
};

