#include "GameState.h"

GameState::GameState(StateStack& stack, Context context)
	: State(stack, context),
	mWorld(context.game),
	mPlayer(context.player)
{
	mWorld.buildScene();
}

void GameState::draw()
{
	mWorld.draw();
}

bool GameState::update(const GameTimer& gt)
{
	mWorld.update(gt);

	return true;
}

bool GameState::InputEvent()
{
	return true;
}

bool GameState::handleEvent(CommandQueue& commands)
{
	//requestStackPop();
	//requestStackPush(States::Menu);

	return true;
}

bool GameState::handleRealtimeEvent(CommandQueue& commands)
{
	return true;
}
