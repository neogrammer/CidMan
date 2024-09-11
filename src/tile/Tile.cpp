#include "Tile.h"

Tile::Tile(bool c_, sf::IntRect iRect_, sf::Vector2f pos_)
{
    setup(c_, iRect_, pos_);
}

bool Tile::getSolid()
{
    return solid;
}

void Tile::setSolid(bool c_)
{
    solid = c_;
}

sf::IntRect Tile::getTexRect()
{
    return texRect;
}

void Tile::setTexRect(sf::IntRect iRect_)
{
    texRect = iRect_;
}

sf::Vector2f Tile::getPos()
{
    return pos;
}

void Tile::setPos(sf::Vector2f pos_)
{
    pos = pos_;
}

void Tile::setup(bool c_, sf::IntRect iRect_, sf::Vector2f pos_)
{
    setSolid(false);
    setTexRect(iRect_);
    setPos(pos_);
}
