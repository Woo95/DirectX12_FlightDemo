#include "PauseState.h"
#include "SpriteNode.h"
#include "Input.h"
#include "Game.hpp"

PauseState::PauseState(StateStack& stack, Context context)	: 
	State(stack, context),
	mCurrentStatus(PauseStatus::Resume),
	mCursor(nullptr)
{
}

void PauseState::init()
{
	mInput = new Input;

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mContext.game, this, "Pause", "box"));
	SpriteNode* Node = backgroundSprite.get();
	Node->setPosition(0, 16.8, -5.49);
	Node->setScale(2.0, 1.1, 1.1);
	Node->setWorldRotation(3.14 / -2 + 3.14 / 16, 0, 0);

	mSceneGraph->attachChild(std::move(backgroundSprite));

	std::unique_ptr<SpriteNode> cursorSprite(new SpriteNode(mContext.game, this, "Cursor", "box"));
	Node = cursorSprite.get();
	Node->setPosition(-0.15f, 16.77f, -5.51f);
	Node->setScale(0.2f, 1.0f, 0.1f);
	Node->setWorldRotation(3.14f / -2 + 3.14f / 16, 0.0f, 0.0f);

	mCursor = Node;

	mSceneGraph->attachChild(std::move(cursorSprite));

	mSceneGraph->build();

	mInput->assignKey<PauseState>("KeyUp", VK_UP, KeyCheckType::Down, Category::Scene,
		this, &PauseState::KeyUp);
	mInput->assignKey<PauseState>("KeyDown", VK_DOWN, KeyCheckType::Down, Category::Scene,
		this, &PauseState::KeyDown);
	mInput->assignKey<PauseState>("Select", VK_RETURN, KeyCheckType::Complete, Category::Scene,
		this, &PauseState::Select);

	mContext.game->SetPause(true);
}

void PauseState::draw()
{
	State::draw();
}

bool PauseState::update(const GameTimer& gt)
{
	State::update(gt);

	return true;
}

bool PauseState::InputEvent()
{
	return true;
}

bool PauseState::handleEvent(CommandQueue& commands)
{
	return true;
}

bool PauseState::handleRealtimeEvent(CommandQueue& commands)
{
	return true;
}

void PauseState::KeyUp(SceneNode& Node, const GameTimer& gt)
{
	mCurrentStatus = PauseStatus::Resume;

	mCursor->setPosition(-0.15, 16.77, -5.51);
}

void PauseState::KeyDown(SceneNode& Node, const GameTimer& gt)
{
	mCurrentStatus = PauseStatus::MainMenu;

	mCursor->setPosition(-0.15, 16.64, -5.53);
}

void PauseState::Select(SceneNode& Node, const GameTimer& gt)
{
	if (mCurrentStatus == PauseStatus::Resume)
	{
		mContext.game->SetPause(false);
		requestStackPop();
	}
	else if (mCurrentStatus == PauseStatus::MainMenu)
	{
		mContext.game->SetPause(false);
		requestStackPop();
		requestStackPop();
		requestStackPush(States::Menu);
	}
}
