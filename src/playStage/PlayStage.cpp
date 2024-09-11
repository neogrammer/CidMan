#include <playStage/PlayStage.h>
#include <gameState/play/PlayState.h>

PlayStage::PlayStage()
	: mgr{nullptr}
	, tilemap{}
{
}

PlayStage::PlayStage(PlayState* mgr_, Cfg::Textures tsetTex_, const std::string& tilesetName_, const std::string& mapName_)
	: mgr{mgr_}
	, tilemap{std::make_unique<Tilemap>(tsetTex_,tilesetName_,mapName_,1)}
{
}

Tilemap& PlayStage::getTilemap()
{
	return *tilemap;
}
