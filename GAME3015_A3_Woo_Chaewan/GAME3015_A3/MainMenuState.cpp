#include "MainMenuState.h"

MainMenuState::MainMenuState(StateStack& stack, Context context)
	: State(stack, context)
{
}

void MainMenuState::draw()
{
	/*sf::RenderWindow& window = *getContext().window;
	window.draw(mBackgroundSprite);

	if (mShowText)
		window.draw(mText);*/
}

bool MainMenuState::update(const GameTimer& gt)
{
	/*mTextEffectTime += dt;

	if (mTextEffectTime >= sf::seconds(0.5f))
	{
		mShowText = !mShowText;
		mTextEffectTime = sf::Time::Zero;
	}*/

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
