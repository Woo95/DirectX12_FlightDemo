#pragma once

#include "Command.h"
#include "StateIdentifiers.h"
#include <memory>
#include <queue>
#include "CommandQueue.h"

class Player;
class Game;
class StateStack;
class SceneNode;
class Input;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context(Game* _game, Player* _player);

		Game* game;
		Player* player;
	};

public:
	State(StateStack& stack, Context context);
	virtual				~State();

	virtual void		init();
	virtual void		draw();
	virtual bool		update(const GameTimer& gt);
	virtual	bool		InputEvent() = 0;
	virtual	bool		handleEvent(CommandQueue& commands) = 0;
	virtual	bool		handleRealtimeEvent(CommandQueue& commands) = 0;
	/**
	  * @brief Get the command queue of the world.
	  * @return A reference to the CommandQueue.
	  */
	CommandQueue& getCommandQueue()
	{
		return mCommandQueue;
	}
	/**
	 * @brief Get the root node of the scene graph.
	 * @return A pointer to the root node of the scene graph.
	 */
	SceneNode* GetSceneGraph()
	{
		return mSceneGraph;
	}

public:
	/**
	 * @brief Add a command to be executed after the current frame.
	 * @tparam T The type of object.
	 * @param Obj The object pointer.
	 * @param Func The member function pointer to be executed.
	 */
	template <typename T>
	void AddPostCommandQueue(T* Obj, void(T::* Func)())
	{
		mPostCommandQueue.push(std::bind(Func, Obj));
	}


protected:
	void				requestStackPush(States::ID stateID);
	void				requestStackPop();
	void				requestStateClear();

	Context				getContext() const;


protected:
	StateStack*			mStack;
	Context				mContext;
	SceneNode*			mSceneGraph;
	CommandQueue						mCommandQueue;
	std::queue<std::function<void()>>			mPostCommandQueue;
	Input* mInput;
};

