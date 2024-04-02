#pragma once
#include "State.h"

class SpriteNode;

/**
* @brief Represents the pause menu state of the game.
*/
class PauseState : public State
{
public:
    /**
    * @brief Constructor for PauseState.
    * @param stack Reference to the StateStack managing game states.
    * @param context Reference to the Context providing necessary resources.
    */
    PauseState(StateStack& stack, Context context);

    /**
    * @brief Initializes the pause menu state.
    */
    virtual void init() override;

    /**
    * @brief Draws the pause menu state.
    */
    virtual void draw() override;

    /**
    * @brief Updates the pause menu state.
    * @param gt Reference to the GameTimer for timing information.
    * @return True if the update was successful, false otherwise.
    */
    virtual bool update(const GameTimer& gt) override;

    /**
    * @brief Handles input events for the pause menu state.
    * @return True if an input event was handled, false otherwise.
    */
    virtual bool InputEvent() override;

    /**
    * @brief Handles specific events for the pause menu state.
    * @param commands The CommandQueue for issuing commands.
    * @return True if the event was handled, false otherwise.
    */
    virtual bool handleEvent(CommandQueue& commands) override;

    /**
    * @brief Handles real-time events for the pause menu state.
    * @param commands The CommandQueue for issuing real-time commands.
    * @return True if the real-time event was handled, false otherwise.
    */
    virtual bool handleRealtimeEvent(CommandQueue& commands) override;

private:
    /**
    * @brief Handles the key up event.
    * @param Node Reference to the SceneNode.
    * @param gt Reference to the GameTimer for timing information.
    */
    void KeyUp(SceneNode& Node, const GameTimer& gt);

    /**
    * @brief Handles the key down event.
    * @param Node Reference to the SceneNode.
    * @param gt Reference to the GameTimer for timing information.
    */
    void KeyDown(SceneNode& Node, const GameTimer& gt);

    /**
    * @brief Handles the selection event.
    * @param Node Reference to the SceneNode.
    * @param gt Reference to the GameTimer for timing information.
    */
    void Select(SceneNode& Node, const GameTimer& gt);

private:
    enum class PauseStatus : char
    {
        Resume, 
        MainMenu
    };

    PauseStatus mCurrentStatus;
    SpriteNode* mCursor;       
};