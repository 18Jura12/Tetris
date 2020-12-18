#include "playstate.h"
#include "game.h"


// Vaš kod.

PlayState::PlayState(Game *pGame): GameState(pGame)
{

}

void PlayState::start()
{
    mPause = false;
    mLP = false;
    mRP = false;
    mUP = false;
    mSP = false;
    mPP = false;
    x = 0;
    mBoard.restart(mpGame->mGameSpeed);
    mScore.restart();
}

void PlayState::handleEvents(sf::Event event)
{

    switch(event.type)
    {
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::Left && !mLP)
        {x=1; mLP = true;}
        if(event.key.code == sf::Keyboard::Right && !mRP)
        {x=2; mRP = true;}
        if(event.key.code == sf::Keyboard::Up && !mUP)
        {x=3; mUP = true;}
        if(event.key.code == sf::Keyboard::Space && !mSP)
        {x=4; mSP = true;}
        if(event.key.code == sf::Keyboard::P && !mPP)
        {mPause = !mPause; mPP = true;}
        break;
    break;

    case sf::Event::KeyReleased:
        if(event.key.code == sf::Keyboard::Left)
        {x=0; mLP = false;}
        if(event.key.code == sf::Keyboard::Right)
        {x=0; mRP = false;}
        if(event.key.code == sf::Keyboard::Up)
        {x=0; mUP = false;}
        if(event.key.code == sf::Keyboard::Space)
        {x=0; mSP = false;}
        if(event.key.code == sf::Keyboard::P)
        {mPP = false;}
        break;
    break;
    }
}

void PlayState::update()
{
    if(mBoard.isGameOver()) {mpGame->mGameScore =mScore.getScore(); mpGame->setState(State::Speed);}
    else
    {
        mBoard.update(x);
        mScore.addNoLinesCompleted(mBoard.getNoLinesCompleted());
        mBoard.clearNoLinesCompleted();
    }
}

void PlayState::render()
{
    mpGame->getWindow()->clear();


    mpGame->getWindow()->draw(mBoard);
    mpGame->getWindow()->draw(mScore);

    mpGame->getWindow()->display();
}
