#pragma once

#include <unordered_map>
#include <memory>
#include <res/Cfg.h>
#include <utility>
#include <gameState/GameState.h>
#include <deque>
#include <string>
#include <stack>

class Game;
class GameState;

class GameStateMgr
{
	GameStateType nextState{ GameStateType::NotSet };
	bool needsToSwitchState{ false };
	bool popOffCurrent{ true };
	StageType stageToLoad{ StageType::NotSet };

	std::unordered_map<GameStateType, std::shared_ptr<GameState> > stateMap{};
public:
	std::stack<GameState*> stateStack;
	Game* game;
	GameStateMgr(Game* game_ = nullptr);
	void setGame(Game* game_);
	~GameStateMgr();
	GameStateMgr& operator=(const GameStateMgr&) = delete;
	GameStateMgr(const GameStateMgr&) = delete;
	GameStateMgr& operator=(GameStateMgr&&) = delete;
	GameStateMgr(GameStateMgr&&) = delete;

	void renderUnder(sf::RenderWindow& wnd_);
	bool hasUnder();
	void input();
	void update();
	void render(sf::RenderWindow& wnd_);
	void safeStateSwitch();

	void changeState(GameStateType type_, bool popCurrent_ = true, StageType stage_ = StageType::NotSet);
	void popTop();
	void resetState(GameStateType type_);

};

//#endif
//
//class GameStateMgr
//{
//	std::unordered_map<GameStateType, std::shared_ptr<GameState> > stateMap;
//	std::deque<std::shared_ptr<GameState> > stateQue;
//	std::weak_ptr<GameState> currState;
//public:
//	GameStateMgr();
//	~GameStateMgr();
//	GameStateMgr(const GameStateMgr&) = delete;
//	GameStateMgr(GameStateMgr&&) = default;
//	GameStateMgr& operator=(const GameStateMgr&) = delete;
//	GameStateMgr& operator=(GameStateMgr&&) = default;
//
//	void input();
//	void update();
//	void render(sf::RenderWindow& wnd_);
//
//	void pushBack(GameStateType type_);
//	GameState& getState(GameStateType type_);
//	void replaceBack(GameStateType type_);
//	GameState& getCurrentState();
//
//
//};