#include "GameState.h"
#include "Aircraft.hpp"
#include "SpriteNode.h"
#include "Input.h"

GameState::GameState(StateStack& stack, Context context)
	: State(stack, context),
	mPlayer(context.player)
{
}

void GameState::init()
{
	mInput = new Input;

	std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Eagle, mContext.game, this));
	mPlayerAircraft = player.get();
	mPlayerAircraft->setPosition(0.0, 15.0, 0.5);
	mPlayerAircraft->setScale(1.0, 1.0, 1.0);
	mPlayerAircraft->setWorldRotation(0.0, 0.0, 0.0);
	//mPlayerAircraft->setVelocity(2.f, 0.f);
	mSceneGraph->attachChild(std::move(player));


	mInput->assignKey<Aircraft>("MoveLeft", VK_LEFT, KeyCheckType::Trigger, Category::PlayerAircraft, mPlayerAircraft, &Aircraft::MoveLeft);
	mInput->assignKey<Aircraft>("MoveRight", VK_RIGHT, KeyCheckType::Trigger, Category::PlayerAircraft, mPlayerAircraft, &Aircraft::MoveRight);
	mInput->assignKey<Aircraft>("MoveForward", VK_UP, KeyCheckType::Trigger, Category::PlayerAircraft, mPlayerAircraft, &Aircraft::MoveForward);
	mInput->assignKey<Aircraft>("MoveBackward", VK_DOWN, KeyCheckType::Trigger, Category::PlayerAircraft, mPlayerAircraft, &Aircraft::MoveBackward);
	mInput->assignKey<Aircraft>("Fire", VK_SPACE, KeyCheckType::Down, Category::PlayerAircraft, mPlayerAircraft, &Aircraft::launchMissile);
	mInput->assignKey<GameState>("Pause", VK_P, KeyCheckType::Down, Category::Scene, this, &GameState::Pause);

	std::unique_ptr<Aircraft> enemy1(new Aircraft(Aircraft::Raptor, mContext.game, this));
	auto raptor = enemy1.get();
	raptor->setPosition(1, 0, -1);
	raptor->setScale(1.0, 1.0, 1.0);
	raptor->setWorldRotation(0.0, 0.0, 0.0);
	mPlayerAircraft->attachChild(std::move(enemy1));

	std::unique_ptr<Aircraft> enemy2(new Aircraft(Aircraft::Raptor, mContext.game, this));
	auto raptor2 = enemy2.get();
	raptor2->setPosition(-1, 0, -1);
	raptor2->setScale(1.0, 1.0, 1.0);
	raptor2->setWorldRotation(0.0, 0.0, 0.0);
	mPlayerAircraft->attachChild(std::move(enemy2));

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mContext.game, this, "Desert", "grid"));
	mBackground = backgroundSprite.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	mBackground->setPosition(0, 0, 47.5);
	mBackground->setScale(1.0, 0.4, 1.0);
	//mBackground->setVelocity(0, -mScrollSpeed);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	mSceneGraph->build();
}

void GameState::draw()
{
	State::draw();
}

bool GameState::update(const GameTimer& gt)
{
	mBackground->setVelocity(0, -15.0f);

	State::update(gt);

	return true;
}

bool GameState::InputEvent()
{
	return true;
}

bool GameState::handleEvent(CommandQueue& commands)
{
	return true;
}

bool GameState::handleRealtimeEvent(CommandQueue& commands)
{
	return true;
}

void GameState::Pause(SceneNode& Node, const GameTimer& gt)
{
	requestStackPop();
	requestStackPush(States::Pause);
}
