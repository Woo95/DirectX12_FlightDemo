#include "Input.h"
#include "CommandQueue.h"

Input::Input()
{
}

void Input::InputEvent()
{
	for (auto& pair : mKeyBinding)
	{
		if (GetAsyncKeyState(pair.second.Key) & 0x8000)
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

void Input::handleEvent(CommandQueue& commands)
{
	for (auto pair : mKeyBinding)
	{
		if (pair.second.Press)
			commands.push(pair.second.command);
	}
}

void Input::handleRealtimeEvent(CommandQueue& commands)
{
	// Traverse all assigned keys and check if they are pressed
	for (auto pair : mKeyBinding)
	{
		if (pair.second.Hold)
			commands.push(pair.second.command);
	}
}
