#pragma once

#include "Command.h"
#include "Common/d3dApp.h"
#include "Common/MathHelper.h"
#include "Category.hpp"
#include <map>

class CommandQueue;

enum class KeyCheckType
{
	Trigger,
	Down,
	Complete
};

class Input
{
public:
	Input();
	void					InputEvent();
	void					handleEvent(CommandQueue& commands);
	void					handleRealtimeEvent(CommandQueue& commands);


	struct ActionData
	{
		std::string	Name;
		char	Key;
		Command	command;
		KeyCheckType	Type;
		bool	Press;
		bool	Hold;
		bool	Release;

		ActionData()
		{
			Type = KeyCheckType::Complete;
			Press = false;
			Hold = false;
			Release = false;
		}

		ActionData(const std::string& name, char key)
		{
			Name = name;
			Key = key;
			Press = false;
			Hold = false;
			Release = false;
		}
	};

	/**
	* @brief Assigns a key to a specific action.
	* @param action The action to assign a key to.
	* @param key The key to assign to the action.
	*/
	template <typename T>
	void assignKey(const std::string& Name, const unsigned char key, KeyCheckType CheckType, Category::Type Category, T* Obj, void(T::*Func)(SceneNode&, const GameTimer&))
	{
		if (mKeyBinding.find(Name) != mKeyBinding.end())
			return;

		ActionData		data;

		data.Name = Name;
		data.Key = key;
		data.Type = CheckType;
		data.command.category = Category;
		data.command.action = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);

		mKeyBinding.insert(std::make_pair(Name, data));
	}

private:
	std::map<std::string, ActionData>			mKeyBinding;
};

