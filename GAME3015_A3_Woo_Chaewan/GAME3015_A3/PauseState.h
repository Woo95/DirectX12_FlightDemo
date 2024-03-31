#pragma once
#include "State.h"

class SpriteNode;

class PauseState :
    public State
{
public:
	PauseState(StateStack& stack, Context context);

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
	enum class PauseStatus : char
	{
		Resume,
		MainMenu
	};

	PauseStatus mCurrentStatus;
	SpriteNode* mCursor;
};

