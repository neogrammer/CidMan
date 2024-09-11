#include <core/Game.h>
#include <res/Cfg.h>

int main()
{
	Cfg::Initialize();

	Game demo;

	demo.run();

	return EXIT_SUCCESS;
}