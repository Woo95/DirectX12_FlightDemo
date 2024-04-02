#pragma once

#include "State.h"
#include "StateIdentifiers.h"

#include <vector>
#include <utility>
#include <functional>
#include <map>

class StateStack
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear,
	};


public:
	explicit			StateStack(State::Context context);

	template <typename T>
	void				registerState(States::ID stateID);

	bool				update(const GameTimer& gt);
	void				draw();
	void				InputEvent();
	void				handleEvent(CommandQueue& commands);
	void				handleRealtimeEvent(CommandQueue& commands);

	void				pushState(States::ID stateID);
	void				popState();
	void				clearStates();

	bool				isEmpty() const;


private:
	State::Ptr			createState(States::ID stateID);
	bool				applyPendingChanges();


private:
	struct PendingChange
	{
		explicit			PendingChange(Action action, States::ID stateID = States::None);

		Action				action;
		States::ID			stateID;
	};


private:
	std::vector<State::Ptr>								mStack;
	std::vector<PendingChange>							mPendingList;

	State::Context										mContext;
	std::map<States::ID, std::function<State::Ptr()>>	mFactories;
};


template <typename T>
void StateStack::registerState(States::ID stateID)
{
	mFactories[stateID] = [this]()
		{
			T* State = new T(*this, mContext);
			State->init();

			return State::Ptr(State);
		};
}
