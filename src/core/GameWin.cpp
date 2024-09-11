#include "GameWin.h"

#pragma once

GameWin::GameWin()
	: wnd{ {1600U,900U,32U}, "Game Template" }
{

}

sf::RenderWindow& GameWin::window()
{
	return wnd;
}
