#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <res/Cfg.h>
class GameStateMgr;
class GameState {
protected:
    bool pop_me{ false };
    GameStateType next{ GameStateType::NotSet };
    GameStateMgr* mgr;
    public:
        GameState(GameStateMgr* mgr_);
        virtual ~GameState() = default;

        virtual void input() = 0;
        virtual void update() = 0;
        virtual void render(sf::RenderWindow& wnd_) = 0;

        bool shouldBePopped();
        void popMe();
        void unpopMe();
        void clearNext();
        GameStateType getStateToAdd();

};