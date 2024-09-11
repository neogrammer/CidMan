#pragma once

#include <res/Cfg.h>
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include <memory>
#include <utility>
#include <tile/Tile.h>
class Tileset
{
	Cfg::Textures texType;
	std::vector<std::unique_ptr<Tile>> tiles;

	int numTiles{};
	int tw{}, th{};
	int pitch{};
public:
	Tileset() = delete;
	explicit Tileset(Cfg::Textures tex_, const std::string& tileset_);
	~Tileset();
	Tileset(const Tileset&) = delete;
	Tileset& operator=(const Tileset&) = delete;
	Tileset(Tileset&&) = delete;
	Tileset& operator=(Tileset&&) = delete;
	Cfg::Textures getTexType();
	bool isSolid(int index_);
	bool isSolid(int col_, int row_);
	sf::IntRect getTexRect(int index_);
	sf::IntRect getTexRect(int col_, int row_);
	Tile getTile(int index_);
	Tile getTile(int col_, int row_);
	int getTW();
	int getTH();
};

