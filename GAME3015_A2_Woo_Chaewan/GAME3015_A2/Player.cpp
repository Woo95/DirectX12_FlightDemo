#include "Player.h"
#include "Aircraft.hpp"
#include "CommandQueue.h"
#include <algorithm>

struct AircraftMover
{
	AircraftMover(float vx, float vy)
		: velocity(vx, vy)
	{
	}

	void operator() (Aircraft& aircraft, const GameTimer& gt) const
	{
		aircraft.accelerate(velocity);
	}

	XMFLOAT2 velocity;
};

Player::Player()
{
	// Set initial key bindings
	mKeyBinding[VK_LEFT] = ActionData(MoveLeft);
	mKeyBinding[VK_RIGHT] = ActionData(MoveRight);
	mKeyBinding[VK_DOWN] = ActionData(MoveDown);
	mKeyBinding[VK_UP] = ActionData(MoveUp);
	mKeyBinding[VK_SPACE] = ActionData(Missile);

	// Set initial action bindings
	initializeActions();

	// Assign all categories to player's aircraft
	for (auto& pair : mActionBinding)
		pair.second.category = Category::PlayerAircraft;
}

// Make Key State
void Player::InputEvent()
{
	for (auto& pair : mKeyBinding)
	{
		if (GetAsyncKeyState(pair.first) & 0x8000)
		{
			// first press
			if (!pair.second.Press && !pair.second.Hold)
			{
				pair.second.Press = true;
				pair.second.Hold = true;
			}

			else
				pair.second.Press = false;
		}

		else if (pair.second.Hold)
		{
			pair.second.Press = false;
			pair.second.Hold = false;
			pair.second.Release = true;
		}

		else if (pair.second.Release)
			pair.second.Release = false;
	}
}

void Player::handleEvent(CommandQueue& commands)
{
	for (auto pair : mKeyBinding)
	{
		if (pair.second.Press && !isRealtimeAction(pair.second.action))
			commands.push(mActionBinding[pair.second.action]);
	}
}

void Player::handleRealtimeEvent(CommandQueue& commands)
{
	// Traverse all assigned keys and check if they are pressed
	for (auto pair : mKeyBinding)
	{
		if (pair.second.Hold && isRealtimeAction(pair.second.action))
			commands.push(mActionBinding[pair.second.action]);
	}
}

void Player::assignKey(Action action, const unsigned char Key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second.action == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyBinding[Key] = action;
}

unsigned char Player::getAssignedKey(Action action) const
{
	for (auto pair : mKeyBinding)
	{
		if (pair.second.action == action)
			return pair.first;
	}

	return 0;
}

void Player::initializeActions()
{
	const float playerSpeed = 2.f;

	mActionBinding[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
	mActionBinding[MoveRight].action = derivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.f));
	mActionBinding[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, playerSpeed));
	mActionBinding[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));

	mActionBinding[Missile].action = derivedAction<Aircraft>([](Aircraft& a, const GameTimer& gt) { a.launchMissile(); });
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
	case MoveLeft:
	case MoveRight:
	case MoveDown:
	case MoveUp:
		return true;

	default:
		return false;
	}
}

void Player::MissileInput(SceneNode& node, const GameTimer& gt)
{
}

#pragma endregion
