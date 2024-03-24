#include "MainMenuState.h"
#include "SpriteNode.h"
#include "Input.h"

MainMenuState::MainMenuState(StateStack& stack, Context context)
	: State(stack, context)
{
}

void MainMenuState::init()
{
	mInput = new Input;

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mContext.game, this, "MainMenu", "box"));
	SpriteNode* Node = backgroundSprite.get();
	Node->setPosition(0, 16.8, -5.5);
	Node->setScale(1.15, 1.0, 0.85);
	Node->setWorldRotation(3.14 / -2 + 3.14 / 16, 0, 0);

	mSceneGraph->attachChild(std::move(backgroundSprite));

	std::unique_ptr<SpriteNode> StartButtonSprite(new SpriteNode(mContext.game, this, "StartButton", "box"));
	Node = StartButtonSprite.get();
	Node->setPosition(0, 16.8, -5.55);
	Node->setScale(0.2, 1.0, 0.1);
	Node->setWorldRotation(3.14 / -2 + 3.14 / 16, 0, 0);

	mSceneGraph->attachChild(std::move(StartButtonSprite));

	mSceneGraph->build();

	mInput->assignKey<MainMenuState>("KeyUp", VK_UP, KeyCheckType::Down, Category::Scene,
		this, &MainMenuState::KeyUp);

	mInput->assignKey<MainMenuState>("KeyDown", VK_DOWN, KeyCheckType::Down, Category::Scene,
		this, &MainMenuState::KeyDown);

	mInput->assignKey<MainMenuState>("Select", VK_RETURN, KeyCheckType::Down, Category::Scene,
		this, &MainMenuState::Select);
}

void MainMenuState::draw()
{
	State::draw();
}

bool MainMenuState::update(const GameTimer& gt)
{
	State::update(gt);

	return true;
}

bool MainMenuState::InputEvent()
{
	return true;
}

bool MainMenuState::handleEvent(CommandQueue& commands)
{
	//mGUIContainer.handleEvent(event);

	return true;
}

bool MainMenuState::handleRealtimeEvent(CommandQueue& commands)
{
	return true;
}

void MainMenuState::KeyUp(SceneNode& Node, const GameTimer& gt)
{
}

void MainMenuState::KeyDown(SceneNode& Node, const GameTimer& gt)
{
}

void MainMenuState::Select(SceneNode& Node, const GameTimer& gt)
{
}
