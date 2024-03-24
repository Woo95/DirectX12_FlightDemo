#pragma once
#include "State.h"
class TitleState :
    public State
{
public:
	TitleState(StateStack& stack, Context context);

	virtual void		init();
	virtual void		draw();
	virtual bool		update(const GameTimer& gt);
	virtual	bool		InputEvent();
	virtual	bool		handleEvent(CommandQueue& commands);
	virtual	bool		handleRealtimeEvent(CommandQueue& commands);

private:
	void NextState(SceneNode& Node, const GameTimer& gt);
};

