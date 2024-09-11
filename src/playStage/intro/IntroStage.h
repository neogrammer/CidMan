#pragma once
#include <playStage/PlayStage.h>
class PlayState;

class IntroStage : public PlayStage
{
public:
	IntroStage();
	IntroStage(PlayState* mgr_, Cfg::Textures tsetTex_, const std::string& tilesetName_, const std::string& mapName_);
	~IntroStage() override final = default;
	void input() override final;
	void update() override final;
	void render(sf::RenderWindow& wnd_) override final;

};