#pragma once
#include "Entity.hpp"

/**
 * @brief SpriteNode class in the scene graph and is used for rendering sprites in a game
 */
class SpriteNode :
    public Entity
{
public:
    /**
     * @brief Constructor for the SpriteNode class
     * @param game Pointer to the Game instance
     */
    SpriteNode(Game* game);

    /**
     * @brief Destructor for the SpriteNode class
     */
    virtual ~SpriteNode();

protected:
    virtual void			updateCurrent(const GameTimer& gt);
    /**
     * @brief Draws the current SpriteNode
     */
    virtual void drawCurrent() const;

    /**
     * @brief Builds the current SpriteNode
     */
    virtual void buildCurrent();
};