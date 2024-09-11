#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <tile/Tilemap.h>
#include <memory>
class PlayState;

class PlayStage
{
protected:
	PlayState* mgr;

	std::unique_ptr<Tilemap> tilemap;
public:
	PlayStage();
	PlayStage(PlayState* mgr_, Cfg::Textures tsetTex_, const std::string& tilesetName_, const std::string& mapName_);
	virtual ~PlayStage() = default;

	virtual void input() = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderWindow& wnd_) = 0;
	Tilemap& getTilemap();
};