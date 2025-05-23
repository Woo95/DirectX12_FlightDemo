#include "State.h"
#include "StateStack.h"
#include "SceneNode.hpp"
#include "Input.h"

State::Context::Context(Game* _game, Player* _player)	:
	player(_player)
	, game(_game)
{
}

State::State(StateStack& stack, Context context)
	: mStack(&stack)
	, mContext(context)
	, mSceneGraph(new SceneNode(context.game, this))
	, mInput(nullptr)
{
}

State::~State()
{
	if (mInput)
		delete mInput;

	if (mSceneGraph)
	{
		delete mSceneGraph;
	}
}

void State::init()
{
}

void State::draw()
{
	mSceneGraph->draw();
}

bool State::update(const GameTimer& gt)
{
	if (mInput)
	{
		mInput->InputEvent();

		mInput->handleEvent(mCommandQueue);

		mInput->handleRealtimeEvent(mCommandQueue);
	}

	while (!mCommandQueue.isEmpty())
		mSceneGraph->onCommand(mCommandQueue.pop(), gt);

	while (!mPostCommandQueue.empty())
	{
		mPostCommandQueue.front()();
		mPostCommandQueue.pop();
	}

	mSceneGraph->update(gt);

	return true;
}

void State::requestStackPush(States::ID stateID)
{
	mStack->pushState(stateID);
}

void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStateClear()
{
	mStack->clearStates();
}

State::Context State::getContext() const
{
	return mContext;
}
