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

/**
* @brief Class representing the input handling system.
*/
class Input
{
public:
	Input();
	/**
	* @brief Handles input events.
	*/
	void					InputEvent();
	/**
	* @brief Handles specific events for the input system.
	* @param commands The CommandQueue to handle commands.
	*/
	void					handleEvent(CommandQueue& commands);
	/**
	* @brief Handles real-time events for the input system.
	* @param commands The CommandQueue to handle real-time commands.
	*/
	void					handleRealtimeEvent(CommandQueue& commands);

	/**
	* @brief Struct representing action data for key bindings.
	*/
	struct ActionData
	{
		std::string	Name;
		char	Key;
		Command	command;
		KeyCheckType	Type;
		bool	Press;
		bool	Hold;
		bool	Release;

		/**
		* @brief Default constructor for ActionData.
		*/
		ActionData()
		{
			Type = KeyCheckType::Complete;
			Press = false;
			Hold = false;
			Release = false;
		}

		/**
		* @brief Constructor for ActionData with name and key.
		* @param name The name of the action.
		* @param key The key assigned to the action.
		*/
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
	* @param Name The name of the action to assign a key to.
	* @param key The key to assign to the action.
	* @param CheckType The type of key check (Trigger, Down, Complete).
	* @param Category The category type for the action.
	* @param Obj The object pointer to bind the action with.
	* @param Func The member function pointer for the action.
	* @tparam T The type of the object.
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

