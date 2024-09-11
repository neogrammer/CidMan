#include <gameState/GameState.h>
#include <mgr/GameStateMgr.h>
GameState::GameState(GameStateMgr* mgr_)
    : mgr{mgr_}
{
}

bool GameState::shouldBePopped()
{
    return pop_me;
}

void GameState::unpopMe()
{
    pop_me = false;
}

void GameState::popMe()
{
    pop_me = true;
}

void GameState::clearNext()
{
    next = GameStateType::NotSet;
}

GameStateType GameState::getStateToAdd()
{
    return next;
}
