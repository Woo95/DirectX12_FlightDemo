#include "World.hpp"

World::World(Game* game)
	: mSceneGraph(new SceneNode(game))
	, mGame(game)
	, mPlayerAircraft(nullptr)
	, mBackground(nullptr)
	, mWorldBounds(-1.5f, 1.5f, 200.0f, 0.0f) //Left, Right, Down, Up
	, mSpawnPosition(0.f, 0.f)
	, mScrollSpeed(15.0f)
	, mBackGroundXSize(10.0f)
	, mBackGroundZSize(100.0f)
	, mBackGroundZStartPos(mBackGroundZSize / 2.0f - 2.5f)
{
}

World::~World()
{
	if (mSceneGraph)
	{
		delete mSceneGraph;
	}
}

void World::update(const GameTimer& gt)
{
	mBackground->setVelocity(0, -mScrollSpeed);

	//if (mBackground->getWorldPosition().z <= -mBackGroundZStartPos)
	//	mBackground->setPosition(0.f, 0.f, mBackGroundZStartPos);

	while (!mCommandQueue.isEmpty())
		mSceneGraph->onCommand(mCommandQueue.pop(), gt);

	while (!mPostCommandQueue.empty())
	{
		mPostCommandQueue.front()();
		mPostCommandQueue.pop();
	}

	mSceneGraph->update(gt);
}

void World::draw()
{
	mSceneGraph->draw();
}

void World::buildScene()
{
	std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Eagle, mGame));
	mPlayerAircraft = player.get();
	mPlayerAircraft->setPosition(0.0, 15.0, 0.5);
	mPlayerAircraft->setScale(1.0, 1.0, 1.0);
	mPlayerAircraft->setWorldRotation(0.0, 0.0, 0.0);
	//mPlayerAircraft->setVelocity(2.f, 0.f);
	mSceneGraph->attachChild(std::move(player));

	std::unique_ptr<Aircraft> enemy1(new Aircraft(Aircraft::Raptor, mGame));
	auto raptor = enemy1.get();
	raptor->setPosition(1, 0, -1);
	raptor->setScale(1.0, 1.0, 1.0);
	raptor->setWorldRotation(0.0, 0.0, 0.0);
	mPlayerAircraft->attachChild(std::move(enemy1));

	std::unique_ptr<Aircraft> enemy2(new Aircraft(Aircraft::Raptor, mGame));
	auto raptor2 = enemy2.get();
	raptor2->setPosition(-1, 0, -1);
	raptor2->setScale(1.0, 1.0, 1.0);
	raptor2->setWorldRotation(0.0, 0.0, 0.0);
	mPlayerAircraft->attachChild(std::move(enemy2));

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame));
	mBackground = backgroundSprite.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	mBackground->setPosition(0, 0, mBackGroundZStartPos);
	mBackground->setScale(1.0, 0.4, 1.0);
	//mBackground->setVelocity(0, -mScrollSpeed);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	mSceneGraph->build();
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}
