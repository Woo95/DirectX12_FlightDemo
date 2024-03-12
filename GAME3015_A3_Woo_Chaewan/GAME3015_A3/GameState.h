#pragma once

#include "State.h"

class GameState :
    public State
{
public:
	GameState(StateStack& stack, Context context);

	virtual void		init();
	virtual void		draw();
	virtual bool		update(const GameTimer& gt);
	virtual	bool		InputEvent();
	virtual	bool		handleEvent(CommandQueue& commands);
	virtual	bool		handleRealtimeEvent(CommandQueue& commands);

private:
	class Player* mPlayer;
	class Aircraft* mPlayerAircraft;
	class SpriteNode* mBackground;
};

