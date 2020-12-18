#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <SFML/Window/Event.hpp>

#include "gamestate.h"
#include "board.h"
#include "score.h"

// Ovo je bivša klasa Game. Doraditi.

class PlayState : public GameState
{
public:
    PlayState(Game * pGame);
    void  start() override;
private:
    Board mBoard;
    Score mScore;

    sf::Time mTime;
    bool mPause = false;

    bool mLP = false;
    bool mRP = false;
    bool mUP = false;
    bool mSP = false;
    bool mPP = false;

    virtual void handleEvents(sf::Event event) override;
    virtual void update() override;
    virtual void render() override;
};

#endif // PLAY_STATE_H
