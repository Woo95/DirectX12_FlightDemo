#include "TitleState.h"
#include "SpriteNode.h"

TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
{
}

void TitleState::init()
{
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mContext.game, this, "Title", "box"));
	SpriteNode* Node = backgroundSprite.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	Node->setPosition(0, 0, 47.5);
	Node->setScale(1.0, 0.4, 1.0);
	//mBackground->setVelocity(0, -mScrollSpeed);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	mSceneGraph->build();
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
	requestStackPop();
	requestStackPush(States::Menu);

	return true;
}

bool TitleState::handleRealtimeEvent(CommandQueue& commands)
{
	return true;
}
