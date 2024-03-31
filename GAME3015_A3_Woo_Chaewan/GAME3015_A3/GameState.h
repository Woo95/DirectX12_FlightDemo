#pragma once

#include "State.h"

#define VK_P 0x50

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
	void Pause(SceneNode& Node, const GameTimer& gt);

private:
	class Player* mPlayer;
	class Aircraft* mPlayerAircraft;
	class SpriteNode* mBackground;
};

