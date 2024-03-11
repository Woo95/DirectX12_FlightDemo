#pragma once

#include "Common/d3dApp.h"
#include "Category.hpp"
#include <functional>
#include <cassert>


class SceneNode;
/**
 * @brief Structure representing a command to be executed on a scene node.
 *
 * This structure encapsulates an action to be performed on a scene node, along with its category.
 */
struct Command
{
	typedef std::function<void(SceneNode&, const GameTimer& gt)> Action;

	Command();

	Action						action;
	unsigned int				category;
};

template <typename GameObject, typename Function>
Command::Action derivedAction(Function fn)
{
	return [=](SceneNode& node, const GameTimer& gt)
		{
			// Check if cast is safe
			assert(dynamic_cast<GameObject*>(&node) != nullptr);

			// Downcast node and invoke function on it
			fn(static_cast<GameObject&>(node), gt);
		};
}
