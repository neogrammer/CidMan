#include <playStage/intro/IntroStage.h>
#include <gameState/play/PlayState.h>
#include <misc/globals.h>
IntroStage::IntroStage()
	:PlayStage{}
{
}

IntroStage::IntroStage(PlayState* mgr_, Cfg::Textures tsetTex_, const std::string& tilesetName_, const std::string& mapName_)
	: PlayStage{mgr_, tsetTex_, tilesetName_, mapName_ }
{
	
}

void IntroStage::input()
{

	
}

void IntroStage::update()
{

}

void IntroStage::render(sf::RenderWindow& wnd_)
{
	sf::Sprite bgSpr = {};
	bgSpr.setTexture(Cfg::textures.get((int)Cfg::Textures::SpaceBG));
	wnd_.draw(bgSpr);

	if (!tilemap) return;
		tilemap->render(wnd_);
}
