#include <tile/Tilemap.h>
#include <tile/Tileset.h>
#include <fstream>

Tilemap::Tilemap(Cfg::Textures tex_, const std::string& tilesetName_, const std::string& mapName_, int zone)
	: tileset{ std::make_unique<Tileset>(tex_, tilesetName_) }
	, tiles{}
{
	tiles.clear();

	std::ifstream file;
	file.open(mapName_);
	if (file.is_open())
	{

		file >> width >> height;

		
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int tileNum;
				file >> tileNum;
				tiles.push_back(tileset->getTile(tileNum));
				tiles.back().setPos({(float)(x * tileset->getTW()), (float)(y * tileset->getTH())});
			}
		}

		file.close();
	}
}

Tilemap::~Tilemap()
{

}

std::vector<Tile>& Tilemap::getTiles()
{
	return tiles;
}

void Tilemap::render(sf::RenderWindow& wnd_)
{
	for (auto& ti : tiles)
	{
		sf::Sprite tileSpr = {};
		tileSpr.setTexture(Cfg::textures.get((int)tileset->getTexType()));
		tileSpr.setPosition(ti.getPos());
		tileSpr.setTextureRect(ti.getTexRect());
		wnd_.draw(tileSpr);
	}
}
