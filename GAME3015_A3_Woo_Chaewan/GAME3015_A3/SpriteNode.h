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
    SpriteNode(Game* game, State* state, const std::string& SpriteName, const std::string& ShapeName);

    /**
     * @brief Destructor for the SpriteNode class
     */
    virtual ~SpriteNode();

protected:
    std::string		mSpriteName;
    std::string		mShapeName;

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