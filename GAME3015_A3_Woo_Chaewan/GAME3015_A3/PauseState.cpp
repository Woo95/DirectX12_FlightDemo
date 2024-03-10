#include "PauseState.h"


PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context)
{
}

void PauseState::draw()
{
}

bool PauseState::update(const GameTimer& gt)
{

	return true;
}

bool PauseState::InputEvent()
{
	return true;
}

bool PauseState::handleEvent(CommandQueue& commands)
{
	//requestStackPop();
	//requestStackPush(States::Menu);

	return true;
}

bool PauseState::handleRealtimeEvent(CommandQueue& commands)
{
	return true;
}
