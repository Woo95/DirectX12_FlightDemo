#pragma once

#include "State.h"

// Define the virtual key code for 'P' key
#define VK_P 0x50

/**
 * @brief Represents the game state within the application's state stack.
 */
class GameState : public State
{
public:
    /**
    * @brief Constructor for the GameState class.
    * @param stack Reference to the StateStack managing game states.
    * @param context Reference to the Context providing necessary resources.
    */
    GameState(StateStack& stack, Context context);

    /**
    * @brief Initializes the game state.
    */
    virtual void init() override;

    /**
    * @brief Draws the game state.
    */
    virtual void draw() override;

    /**
    * @brief Updates the game state.
    * @param gt Reference to the GameTimer for timing information.
    * @return True if the update was successful, false otherwise.
    */
    virtual bool update(const GameTimer& gt) override;

    /**
    * @brief Handles input events for the game state.
    * @return True if an input event was handled, false otherwise.
    */
    virtual bool InputEvent() override;

    /**
    * @brief Handles specific events for the game state.
    * @param commands Reference to the CommandQueue for issuing commands.
    * @return True if the event was handled, false otherwise.
    */
    virtual bool handleEvent(CommandQueue& commands) override;

    /**
    * @brief Handles real-time events for the game state.
    * @param commands Reference to the CommandQueue for issuing commands.
    * @return True if the real-time event was handled, false otherwise.
    */
    virtual bool handleRealtimeEvent(CommandQueue& commands) override;

private:
    /**
    * @brief Pauses specific game elements.
    * @param Node Reference to the SceneNode to pause.
    * @param gt Reference to the GameTimer for timing information.
    */
    void Pause(SceneNode& Node, const GameTimer& gt);

private:
    class Player* mPlayer; ///< Pointer to the Player object.
    class Aircraft* mPlayerAircraft; ///< Pointer to the Player's Aircraft object.
    class SpriteNode* mBackground; ///< Pointer to the background SpriteNode.
};