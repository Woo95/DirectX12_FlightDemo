#include "StateStack.h"

StateStack::StateStack(State::Context context)
	: mStack()
	, mPendingList()
	, mFactories()
	, mContext(context)
{
}

bool StateStack::update(const GameTimer& gt)
{
	// Iterate from top to bottom, stop as soon as update() returns false
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->update(gt))
			break;
	}

	return applyPendingChanges();
}

void StateStack::draw()
{
	// Draw all active states from bottom to top
	for (State::Ptr& state : mStack)
		state->draw();
}

void StateStack::InputEvent()
{
	// Iterate from top to bottom, stop as soon as handleEvent() returns false
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->InputEvent())
			break;
	}
}

void StateStack::handleEvent(CommandQueue& commands)
{
	// Iterate from top to bottom, stop as soon as handleEvent() returns false
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->handleEvent(commands))
			break;
	}

	applyPendingChanges();
}

void StateStack::handleRealtimeEvent(CommandQueue& commands)
{
	// Iterate from top to bottom, stop as soon as handleEvent() returns false
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->handleRealtimeEvent(commands))
			break;
	}

	applyPendingChanges();
}

void StateStack::pushState(States::ID stateID)
{
	mPendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState()
{
	mPendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates()
{
	mPendingList.push_back(PendingChange(Clear));
}

bool StateStack::isEmpty() const
{
	return mStack.empty();
}

State::Ptr StateStack::createState(States::ID stateID)
{
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());

	return found->second();
}

bool StateStack::applyPendingChanges()
{
	bool	Change = false;

	for (PendingChange change : mPendingList)
	{
		switch (change.action)
		{
		case Push:
		{
			/*State::Ptr ptr = createState(change.stateID);
			ptr->init();
			mStack.push_back(ptr);*/
			mStack.push_back(createState(change.stateID));
			//mStack.back()->init();

			Change = true;
		}
			break;

		case Pop:
			mStack.pop_back();
			break;

		case Clear:
			mStack.clear();
			break;
		}
	}

	mPendingList.clear();

	return Change;
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
	: action(action)
	, stateID(stateID)
{
}
