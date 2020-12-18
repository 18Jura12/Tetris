#include "gamestate.h"
#include "game.h"
#include <cstdlib>
#include <iostream>


// Vaš kod dolazi ovdje.


WelcomeState::WelcomeState(Game *pGame): GameState(pGame)
{
    if(!mFont.loadFromFile("Gasalt-Regular.ttf")){
        std::cerr << "Ne mogu učitati font: Gasalt-Regular.ttf !" << std::endl;
        std::exit(1);
    }
   // Vaš kod dolazi ovdje
    mText1.setFont(mFont);
    mText1.setString("Tetris clone by J.Juric    ");
    mText1.setOrigin(sf::Vector2f(mText1.getLocalBounds().width/2.f,mText1.getLocalBounds().height/2.f));
    mText1.setPosition(sf::Vector2f(250.f,250.f));
    mText1.setStyle(sf::Text::Bold);

    mText2.setFont(mFont);
    mText2.setString("Press any key to continue");
    mText2.setOrigin(sf::Vector2f(mText2.getLocalBounds().width/2.f,mText2.getLocalBounds().height/2.f));
    mText2.setPosition(sf::Vector2f(250.f,250.f+2*mText1.getLocalBounds().height));
    mText2.setStyle(sf::Text::Italic);
    mText2.setScale(0.7f,0.7f);
}

void WelcomeState::handleEvents(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed) test++;
}

void WelcomeState::update()
{
    if(test) mpGame->setState(State::Playing);
}

void WelcomeState::render()
{
    mpGame->getWindow()->clear();

    mpGame->getWindow()->draw(mText1);
    mpGame->getWindow()->draw(mText2);

    mpGame->getWindow()->display();
}

SpeedState::SpeedState(Game *pGame): GameState(pGame)
{
    if(!mFont.loadFromFile("Gasalt-Regular.ttf")){
        std::cerr << "Ne mogu učitati font: Gasalt-Regular.ttf !" << std::endl;
        std::exit(1);
    }
   // Vaš kod dolazi ovdje
    mText0.setFont(mFont);
    mText0.setString("Score = " + std::to_string(mpGame->mGameScore));
    mText0.setOrigin(sf::Vector2f(mText0.getLocalBounds().width/2.f,mText0.getLocalBounds().height/2.f));
    mText0.setPosition(sf::Vector2f(250.f,150.f));
    mText0.setScale(0.8f,0.8f);

    mText1.setFont(mFont);
    mText1.setString("Current Speed = " + std::to_string(mpGame->mGameSpeed));
    mText1.setOrigin(sf::Vector2f(mText1.getLocalBounds().width/2.f,mText1.getLocalBounds().height/2.f));
    mText1.setPosition(sf::Vector2f(250.f,200.f));
    mText1.setScale(0.8f,0.8f);

    mText2.setFont(mFont);
    mText2.setString("Use keys Up and Down to change the speed");
    mText2.setOrigin(sf::Vector2f(mText2.getLocalBounds().width/2.f,mText2.getLocalBounds().height/2.f));
    mText2.setPosition(sf::Vector2f(250.f,250.f));
    mText2.setScale(0.8f,0.8f);

    mText3.setFont(mFont);
    mText3.setString("Enter to continue");
    mText3.setOrigin(sf::Vector2f(mText3.getLocalBounds().width/2.f,mText3.getLocalBounds().height/2.f));
    mText3.setPosition(sf::Vector2f(250.f,300.f));
    mText3.setScale(0.8f,0.8f);

}

void SpeedState::handleEvents(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed)
    {
    if(event.key.code == sf::Keyboard::Up) mpGame->mGameSpeed ++;
    else if(event.key.code == sf::Keyboard::Down && mpGame->mGameSpeed>1) mpGame->mGameSpeed --;
    else if(event.key.code == sf::Keyboard::Return) mpGame->setState(Playing);
}
}

void SpeedState::update()
{
    mText0.setString("Score = " + std::to_string(mpGame->mGameScore));
    mText1.setString("Current Speed = " + std::to_string(mpGame->mGameSpeed));
}

void SpeedState::render()
{
    mpGame->getWindow()->clear();

    mpGame->getWindow()->draw(mText0);
    mpGame->getWindow()->draw(mText1);
    mpGame->getWindow()->draw(mText2);
    mpGame->getWindow()->draw(mText3);

    mpGame->getWindow()->display();
}
