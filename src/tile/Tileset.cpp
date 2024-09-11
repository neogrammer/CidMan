#include <tile/Tileset.h>
#include <fstream>
Tileset::Tileset(Cfg::Textures tex_, const std::string& tileset_)
	: texType{tex_}
{
	std::ifstream file;
	file.open(tileset_);
	if (file.is_open())
	{

		file >> numTiles >> tw >> th >> pitch;

		int rows = 0;

		if (numTiles < pitch)
		{
			rows = 1;
		}
		else
		{
			rows = numTiles / pitch;

			if (numTiles % pitch != 0)
				rows += 1;
		}
	
		
		for (int y = 0; y < rows; y++)
		{
			for (int x = 0; x < pitch; x++)
			{
				if (y * pitch + x >= numTiles)
					break;
				int sol;
				file >> sol;
				tiles.emplace_back(std::make_unique<Tile>());
				tiles.back()->setup((sol == 1) ? true : false, { {x * tw, y * th},{tw,th} }, { 0.f, 0.f});
			}
		}

		file.close();
	}

}

Tileset::~Tileset()
{

}

Cfg::Textures Tileset::getTexType()
{
	return texType;
}

bool Tileset::isSolid(int index_)
{
	return tiles.at(index_)->getSolid();
}

bool Tileset::isSolid(int col_, int row_)
{
	return tiles.at(row_ * pitch + col_)->getSolid();

}

sf::IntRect Tileset::getTexRect(int index_)
{
	
		return tiles.at(index_)->getTexRect();

}

sf::IntRect Tileset::getTexRect(int col_, int row_)
{
	return tiles.at(row_ * pitch + col_)->getTexRect();

}

Tile Tileset::getTile(int index_)
{
	return *tiles.at(index_);
}

Tile Tileset::getTile(int col_, int row_)
{
	return *tiles.at(row_ * pitch + col_);
}

int Tileset::getTW()
{
	return tw;
}

int Tileset::getTH()
{
	return th;
}
