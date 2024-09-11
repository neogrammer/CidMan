#include <mgr/GameStateMgr.h>
#include <gameState/play/PlayState.h>
#include <gameState/stageSelect/StageSelectState.h>
#include <gameState/over/OverState.h>
#include <gameState/paused/PausedState.h>
#include <gameState/persist/PersistState.h>
#include <gameState/splash/SplashState.h>
#include <gameState/title/TitleState.h>
#include <gameState/menu/MenuState.h>
#include <misc/globals.h>
#include <iostream>
GameStateMgr::GameStateMgr(Game* game_)
	: game{ game_ }
{


	stateMap.emplace(std::pair{ GameStateType::Splash, std::move(std::make_shared<SplashState>(this)) });
	stateMap.emplace(std::pair{ GameStateType::Title, std::move(std::make_shared<TitleState>(this)) });
	stateMap.emplace(std::pair{ GameStateType::Paused, std::move(std::make_shared<PausedState>(this)) });
	stateMap.emplace(std::pair{ GameStateType::Play, std::move(std::make_shared<PlayState>(this)) });
	stateMap.emplace(std::pair{ GameStateType::StageSelect, std::move(std::make_shared<StageSelectState>(this)) });
	stateStack.push(stateMap.at(GameStateType::Splash).get());

}
void GameStateMgr::setGame(Game* game_)
{
	game = game_;
}
GameStateMgr::~GameStateMgr()
{
	while (!stateStack.empty())
	{
		stateStack.pop();
	}
	stateMap.clear();
}

void GameStateMgr::renderUnder(sf::RenderWindow& wnd_)
{
	std::stack<GameState*> tmpStack = {};
	while (!stateStack.empty())
	{
		tmpStack.push(stateStack.top());
		stateStack.pop();

	}

	// statestack is empty, lets put the states back, and render each one  as we do so as to render the under ones first
	while (!tmpStack.empty())
	{
		stateStack.push(tmpStack.top());
		tmpStack.pop();
		stateStack.top()->render(wnd_);
	}

	// tmpStack is now empty again and all states on the stack have been rendered in order

}

bool GameStateMgr::hasUnder()
{
	return (stateStack.size() > 1);
}

void GameStateMgr::input()
{
	if (!needsToSwitchState)
		stateStack.top()->input();
	return;
}

void GameStateMgr::update()
{
	if (needsToSwitchState)
		safeStateSwitch();
	if (!needsToSwitchState)
		stateStack.top()->update();
	return;
}



void GameStateMgr::popTop()
{
	stateStack.pop();
}

void GameStateMgr::resetState(GameStateType type_)
{
	if (stateMap.find(type_) != stateMap.end())
	{
		stateMap.erase(stateMap.find(type_));
		stateMap.insert_or_assign(type_, std::make_unique<PlayState>(this));
	}

}

void GameStateMgr::render(sf::RenderWindow& wnd_)
{
	if (!needsToSwitchState)
	{
		if (hasUnder())
		{
			renderUnder(wnd_);
		}
		else
		{
			stateStack.top()->render(wnd_);
		}
	}
	return;
}

void GameStateMgr::safeStateSwitch()
{
	if (needsToSwitchState)
	{
		needsToSwitchState = false;
		if (nextState == GameStateType::NotSet)
		{
			std::cout << "Trying to change states to GameStateType::None!" << std::endl;
			return;
		}
		else
		{

			//gWnd.setView(gWnd.getDefaultView());
			if (popOffCurrent)
				stateStack.pop();

			stateStack.push(stateMap.at(nextState).get());

			if (nextState == GameStateType::Play)
			{

				gView = gMainDefaultView;
				dynamic_cast<PlayState*>(stateStack.top())->loadStage(StageType::Intro);
			}

		}
		nextState = GameStateType::NotSet;
		popOffCurrent = true;

		return;
	}
	return;
}



void GameStateMgr::changeState(GameStateType type_, bool popCurrent_, StageType stage_)
{
	nextState = type_;
	if (nextState == GameStateType::Play)
	{
		if (stage_ == StageType::NotSet)
		{
			std::cout << "Stage not Set!" << std::endl;
			return;
		}
		stageToLoad = stage_;
		
	}
	popOffCurrent = popCurrent_;
	needsToSwitchState = true;
	return;
}


//
//
//GameStateMgr::GameStateMgr()
//    : stateMap{}
//    , currState{}
//{   
//
//    // Insert a PlayState into the map
//    std::shared_ptr<GameState> playState = std::make_shared<PlayState>();
//    std::shared_ptr<GameState> menuState = std::make_shared<MenuState>();
//    std::shared_ptr<GameState> stageSelectState = std::make_shared<StageSelectState>();
//    std::shared_ptr<GameState> pausedState = std::make_shared<PausedState>();
//    std::shared_ptr<GameState> overState = std::make_shared<OverState>();
//    std::shared_ptr<GameState> persistState = std::make_shared<PersistState>();
//    std::shared_ptr<GameState> splashState = std::make_shared<SplashState>();
//    std::shared_ptr<GameState> titleState = std::make_shared<TitleState>();
//    stateMap[GameStateType::Play ] = playState;
//    stateMap[GameStateType::Menu] = menuState;
//    stateMap[GameStateType::StageSelect] = stageSelectState;
//    stateMap[GameStateType::Paused] = pausedState;
//    stateMap[GameStateType::Over] = overState;
//    stateMap[GameStateType::Persist] = persistState;
//    stateMap[GameStateType::Splash] = splashState;
//    stateMap[GameStateType::Title] = titleState;
//
//
//    stateQue.push_back(stateMap[GameStateType::Splash]);
//
//    currState = stateQue.back();
//
//}
//
//GameStateMgr::~GameStateMgr()
//{
//}
//
//void GameStateMgr::pushBack(GameStateType type_)
//{
//    stateQue.push_back(stateMap[type_]);
//    currState = stateQue.back();
//}
//
//void GameStateMgr::replaceBack(GameStateType type_)
//{
//    stateQue.pop_back();
//    stateQue.push_back(stateMap[type_]);
//    currState = stateQue.back();
//}
//
//GameState& GameStateMgr::getCurrentState()
//{
//    if (currState.lock() == nullptr)
//    {
//        if (stateQue.begin() == stateQue.end()) { pushBack(GameStateType::Splash); }
//        currState = stateQue.back();
//        return *currState.lock();
//    }
//    else
//    {
//        return *currState.lock();
//    }
//}
//
//void GameStateMgr::input()
//{
//    currState = stateQue.back();
//    for (int i = 0; i < stateQue.size(); i++)
//    {
//        if (stateQue[i]->shouldBePopped()) { continue; }
//        stateQue[i]->input();
//    }
//}
//
//void GameStateMgr::update()
//{
//    
//    if (currState.lock() != nullptr)
//    {
//        auto aST = currState.lock()->getStateToAdd();
//        if (aST != GameStateType::NotSet)
//        {
//            currState.lock()->clearNext();
//
//            if (currState.lock()->shouldBePopped())
//            {
//                currState.lock()->unpopMe();
//                replaceBack(aST);
//            }
//            else
//            {
//                pushBack(aST);
//            }
//            
//        }
//        else
//        {
//            if (currState.lock()->shouldBePopped())
//            {
//                currState.lock()->unpopMe();
//                stateQue.pop_back();
//            }
//        }
//    }
//    
//    if (currState.lock() == nullptr)
//    {
//        if (stateQue.begin() == stateQue.end())
//        {
//            stateQue.push_back(stateMap[GameStateType::Splash]);
//        }
//
//        currState = stateQue.back();
//    }
//    /*std::vector<std::deque<std::shared_ptr<GameState>>::iterator> itVec{};
//startOver:
//    itVec.clear();
//    
//    for (std::deque<std::shared_ptr<GameState>>::iterator it = stateQue.begin(); it != stateQue.end(); it++)
//    {
//        if ((*it)->shouldBePopped())
//        {
//
//            itVec.push_back(it);
//
//        }
//        else
//        {
//            if ((*it)->getStateToAdd() != GameStateType::NotSet)
//            {
//                pushBack((*it)->getStateToAdd());
//                (*it)->clearNext();
//                
//            }
//        }
//    }
//
//    for (int i = (int)itVec.size() - 1; i >= 0; i--)
//    {
//        if (itVec[i]->get()->getStateToAdd() != GameStateType::NotSet)
//        {
//            pushBack(itVec[i]->get()->getStateToAdd());
//            itVec[i]->get()->clearNext();
//            goto startOver;
//            
//        }
//        stateQue.erase(itVec[i]);
//    }
//    itVec.clear();
//
//    if (stateQue.begin() == stateQue.end()) { pushBack(GameStateType::Splash); }
//    currState = stateQue.back();*/
//
//
//    for (int i = 0; i < stateQue.size(); i++)
//    {
//        stateQue[i]->update();
//    }
//   
//    
//}
//
//void GameStateMgr::render(sf::RenderWindow& wnd_)
//{
//    currState = stateQue.back();
//    for (int i = 0; i < stateQue.size(); i++)
//    {
//        if (stateQue[i]->shouldBePopped()) { continue; }
//        stateQue[i]->render(wnd_);
//    }
//}
//
//GameState& GameStateMgr::getState(GameStateType type_)
//{
//   
//    return *stateMap.at(type_);
//}
//
//
