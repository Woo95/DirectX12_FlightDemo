#pragma once
#include "State.h"

class TitleState : public State
{
public:
    /**
    * @brief Constructor for TitleState.
    * @param stack Reference to the StateStack managing game states.
    * @param context Reference to the Context providing necessary resources.
    */
    TitleState(StateStack& stack, Context context);

    /**
    * @brief Initializes the title state.
    */
    virtual void init() override;

    /**
    * @brief Draws the title state.
    */
    virtual void draw() override;

    /**
    * @brief Updates the title state.
    * @param gt Reference to the GameTimer for timing information.
    * @return True if the update was successful, false otherwise.
    */
    virtual bool update(const GameTimer& gt) override;

    /**
    * @brief Handles input events for the title state.
    * @return True if an input event was handled, false otherwise.
    */
    virtual bool InputEvent() override;

    /**
    * @brief Handles specific events for the title state.
    * @param commands The CommandQueue for issuing commands.
    * @return True if the event was handled, false otherwise.
    */
    virtual bool handleEvent(CommandQueue& commands) override;

    /**
    * @brief Handles real-time events for the title state.
    * @param commands The CommandQueue for issuing real-time commands.
    * @return True if the real-time event was handled, false otherwise.
    */
    virtual bool handleRealtimeEvent(CommandQueue& commands) override;

private:
    /**
    * @brief Handles the next state transition event.
    * @param Node Reference to the SceneNode.
    * @param gt Reference to the GameTimer for timing information.
    */
    void NextState(SceneNode& Node, const GameTimer& gt);
};