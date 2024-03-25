#pragma once
#include "State.h"
class MainMenuState :
    public State
{
public:
	MainMenuState(StateStack& stack, Context context);

	virtual void		init();
	virtual void		draw();
	virtual bool		update(const GameTimer& gt);
	virtual	bool		InputEvent();
	virtual	bool		handleEvent(CommandQueue& commands);
	virtual	bool		handleRealtimeEvent(CommandQueue& commands);


private:
	void KeyUp(SceneNode& Node, const GameTimer& gt);
	void KeyDown(SceneNode& Node, const GameTimer& gt);
	void Select(SceneNode& Node, const GameTimer& gt);

private:
	enum class MenuStatus : char
	{
		Start,
		Quit
	};

	MenuStatus mCurrentStatus;
};

