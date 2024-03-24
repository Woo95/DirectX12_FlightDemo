#include "TitleState.h"
#include "SpriteNode.h"
#include "Input.h"

TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
{
}

void TitleState::init()
{
	mInput = new Input;

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mContext.game, this, "Title", "box"));
	SpriteNode* Node = backgroundSprite.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	Node->setPosition(0, 16.8, -5.5);
	Node->setScale(1.15, 1.0, 0.85);
	//Node->setWorldRotation(90 * XM_PI / 180, 0, 180 * XM_PI / 180);
	Node->setWorldRotation(3.14 / -2 + 3.14 / 16, 0, 0);


	//mCamera.SetPosition(0, 17, -6.5);
	//mCamera.Pitch(3.14 / 16);

	//mBackground->setVelocity(0, -mScrollSpeed);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	mSceneGraph->build();

	mInput->assignKey<TitleState>("NextState", VK_SPACE, KeyCheckType::Down, Category::Scene,
		this, &TitleState::NextState);
}

void TitleState::draw()
{
	State::draw();
	/*sf::RenderWindow& window = *getContext().window;
	window.draw(mBackgroundSprite);

	if (mShowText)
		window.draw(mText);*/
}

bool TitleState::update(const GameTimer& gt)
{
	State::update(gt);
	/*mTextEffectTime += dt;

	if (mTextEffectTime >= sf::seconds(0.5f))
	{
		mShowText = !mShowText;
		mTextEffectTime = sf::Time::Zero;
	}*/

	return true;
}

bool TitleState::InputEvent()
{
	return true;
}

bool TitleState::handleEvent(CommandQueue& commands)
{
	return true;
}

bool TitleState::handleRealtimeEvent(CommandQueue& commands)
{
	return true;
}

void TitleState::NextState(SceneNode& Node, const GameTimer& gt)
{
	requestStackPop();
	//requestStackPush(States::Menu);
	requestStackPush(States::Game);
}
