#include "TitleState.h"

TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
{
}

void TitleState::draw()
{
	/*sf::RenderWindow& window = *getContext().window;
	window.draw(mBackgroundSprite);

	if (mShowText)
		window.draw(mText);*/
}

bool TitleState::update(const GameTimer& gt)
{
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
