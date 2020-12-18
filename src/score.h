#pragma once
#include <SFML/Graphics.hpp>

// Doraditi klasu ako je potrebno.

class Score : public sf::Drawable, public sf::Transformable{
public:
    Score();
    void addNoLinesCompleted(int n);
    int  getScore() const { return mScore; }
    void restart();
private:
    sf::Font mFont;
    sf::Text mScoreText;
    int mTotalLinesCompleted = 0;
    int mScore = 0;

    void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};