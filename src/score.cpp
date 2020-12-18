#include "score.h"
#include <cstdlib>
#include <iostream>

Score::Score()
{
    if(!mFont.loadFromFile("Gasalt-Regular.ttf")){
        std::cerr << "Ne mogu učitati font: Gasalt-Regular.ttf !" << std::endl;
        std::exit(1);
    }
   // Vaš kod dolazi ovdje
    mScoreText.setFont(mFont);
    mScoreText.setString("Score: 0");
    mScoreText.setPosition(sf::Vector2f(350.f,50.f));
}

void Score::addNoLinesCompleted(int n)
{
  // Vaš kod.
    if(n)
    {
        switch(n)
        {
        case 1: mScore += 10; break;
        case 2: mScore += 20; break;
        case 3: mScore += 30; break;
        case 4: mScore += 40; break;
        }

        mScoreText.setString("Score: " + std::to_string(mScore));
    }

}

void Score::restart()
{
    mScore = 0;
    mScoreText.setString(("Score: 0"));
    mTotalLinesCompleted = 0;
}

void Score::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  // Vaš kod.
    states.transform *= getTransform();
    target.draw(mScoreText,states);
}
