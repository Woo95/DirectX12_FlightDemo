#pragma once
#include "State.h"
class PauseState :
    public State
{
public:
	PauseState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(const GameTimer& gt);
	virtual	bool		InputEvent();
	virtual	bool		handleEvent(CommandQueue& commands);
	virtual	bool		handleRealtimeEvent(CommandQueue& commands);
};

