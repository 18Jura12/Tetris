#include "game.h"
#include "playstate.h"

#include <iostream>

Game::Game() : mWindow(sf::VideoMode(500,600), "Tetris"), mGameSpeed(3.0f),
               mGameScore(0)
{
    // Inicijalizacija stanja dolazi ovdje
    GameState * Welcome=new WelcomeState(this);
    GameState * Playing=new PlayState(this);
    GameState * Speed=new SpeedState(this);
    mAllStates[0]=Welcome;
    mAllStates[1]=Playing;
    mAllStates[2]=Speed;
    setState(GameState::Welcome);
}

Game::~Game()
{
    for(auto x: mAllStates) delete x;
}

void Game::run(){
    while(mWindow.isOpen()){
        processEvents();
        update();
        render();
    }
}

void Game::setState(GameState::State st)
{
    mpGameState = mAllStates[st];
    mpGameState->start();
}

sf::RenderWindow * Game::getWindow()
{
    return &mWindow;
}

void Game::processEvents()
{
    sf::Event event;

    mAllStates[1]->x=0;

    while(mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            mWindow.close();
        else if(event.type ==sf::Event::Resized){
            // Spriječi deformaciju objekata prilikom promjene veličine prozora
            sf::FloatRect viewRect(0, 0, event.size.width, event.size.height);
            mWindow.setView(sf::View(viewRect));
        }
        else {
            mpGameState->handleEvents(event);
		}
    }
}

void Game::update()
{
    mpGameState->update();
}

void Game::render()
{
     mWindow.clear();
     mpGameState->render();
     mWindow.display();
}
