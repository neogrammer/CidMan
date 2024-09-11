#pragma once

#include <res/Cfg.h>
#include <vector>
#include <tile/Tile.h>
#include <string>
#include <memory>
class Projectile;
class Tileset;
class Tilemap
{
	std::unique_ptr<Tileset> tileset;

	std::vector<Tile> tiles;
	int width{};
	int height{};
public:
	Tilemap() = delete;
	explicit Tilemap(Cfg::Textures tex_, const std::string& tilesetName_, const std::string& mapName_, int zone = 1);
	~Tilemap();
	Tilemap(const Tilemap&) = delete;
	Tilemap& operator=(const Tilemap&) = delete;
	Tilemap(Tilemap&&) = delete;
	Tilemap& operator=(Tilemap&&) = delete;
	std::vector<Tile>& getTiles();
	void render(sf::RenderWindow& wnd_);

};

