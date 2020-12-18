#include "board.h"
#include <iostream>

// Vaš kod dolazi ovdje

Board::Board(): mGrid(sf::Lines)
{
    mR.seed(std::time(0));
    mGrid.resize(2*33);
    mGrid[0].position = sf::Vector2f(mLeftMargin,mTopMargin);
    mGrid[1].position = sf::Vector2f(mLeftMargin,mTopMargin+mHeight);

    mGrid[2].position = sf::Vector2f(mLeftMargin,mTopMargin);
    mGrid[3].position = sf::Vector2f(mLeftMargin+mWidth,mTopMargin);

    for(int i = 1; i!=11; i++)
    {
        mGrid[4*i].position = sf::Vector2f(mLeftMargin+i*mWidth/10,mTopMargin);
        mGrid[4*i+1].position = sf::Vector2f(mLeftMargin+i*mWidth/10,mTopMargin+mHeight);

        mGrid[4*i+2].position = sf::Vector2f(mLeftMargin,mTopMargin+i*mHeight/10);
        mGrid[4*i+3].position = sf::Vector2f(mLeftMargin+mWidth,mTopMargin+i*mHeight/10);

        mGrid[42+2*i].position = sf::Vector2f(mLeftMargin,mTopMargin+(i-1)*mHeight/10+mHeight/20);
        mGrid[42+2*i+1].position = sf::Vector2f(mLeftMargin+mWidth,mTopMargin+(i-1)*mHeight/10+mHeight/20);
    }

    for(int i=0; i<mRows; i++)
        for(int j=0; j<mCols; j++) mGridContent[i][j] = EMPTY;
}

void Board::update(int a)
{
    switch (a) {
    case 1: movePiece(0,-1);
        break;
    case 2: movePiece(0,1);
        break;
    case 4: while(movePiece(1,0));
        break;
    case 3: rotatePiece();
        break;
    }
    if(mPiece.mClock.getElapsedTime().asSeconds() >= 1/mGameSpeed){
        mPiece.mClock.restart();
        if(mPiece.mXposition==0 && mPiece.mYposition==0) spawnPiece();
        else if(!movePiece(1,0)) {
            mNoLinesCompleted = clearLines();
                if(checkSpace()) spawnPiece();
            else mGameOver = true;
        }
    }

}

void Board::spawnPiece()
{
    if(mPiece.mXposition == 0 && mPiece.mYposition == 0)
    {
        std::uniform_int_distribution<int> dist;
        int x = dist(mR)%7;
        mPiece.mType = (Tetrimino::Types)x;
        mPiece.mRotacija = dist(mR)%4;
    }

    int a = mPiece.mType;
    int b = mPiece.mRotacija;

    int i1 = 0;
    int test = 0;

    for(int i=0; i!=4; i++)
    {
        for(int j=0; j!=4; j++)
        {
            if(mPiece.mDijelovi[a][b][i][j] == 1) {mGridContent[i1][j+3] = mPiece.mType; test=1;}
            else if(mPiece.mDijelovi[a][b][i][j] == 2){
                mGridContent[i1][j+3] = mPiece.mType;
                mPiece.mXposition = i1;
                mPiece.mYposition = j+3;
                test=1;
            }

        }
        if(test) i1++;
    }
}

bool Board::isGameOver() const
{
    return mGameOver;
}

int Board::getNoLinesCompleted() const
{
    return mNoLinesCompleted;
}

void Board::restart(float s)
{
    for(int i=0; i<mRows; i++)
        for(int j=0; j<mCols; j++) mGridContent[i][j] = EMPTY;

    mGameOver = false;
    mNoLinesCompleted = 0;
    mGameSpeed = s;
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mGrid, states);

    float x=mLeftMargin, y=mTopMargin;

    for(int i = 0; i < mRows; i++)
    {
        for(int j = 0; j < mCols; j++)
        {
            if(mGridContent[i][j] != EMPTY)
            {
                sf::RectangleShape mRect;
                mRect.setSize(sf::Vector2f(mDx,mDy));
                mRect.setFillColor(mPiece.mColors[mGridContent[i][j]]);
                mRect.setPosition(sf::Vector2f(x,y));
                target.draw(mRect, states);
            }
            x += mWidth/10;
        }
        y += mHeight/20;
        x = mLeftMargin;
    }

}

bool Board::checkSpace()
{
    std::uniform_int_distribution<int> dist;
    int a = dist(mR)%7;
    int b = dist(mR)%4;

    int i1 = 0;
    int test = 0;

    for(int i=0; i!=4; i++)
    {
        for(int j=0; j!=4; j++)
        {
            if(mPiece.mDijelovi[a][b][i][j] > 0){
                if(mGridContent[i1][j+3] >= 0) return false;
                test=1;
            }
        }
        if(test) i1++;
    }

    mPiece.mType =(Tetrimino::Types) a;
    mPiece.mRotacija = b;

    return true;
}

void Board::placePiece()
{
    int a = mPiece.mType;
    int b = mPiece.mRotacija;

    int i1 = mPiece.mXposition - 1;
    int j1 = mPiece.mYposition - 2;

    for(int i=0; i!=4; i++)
    {
        for(int j=0; j!=4; j++) {
            if(mPiece.mDijelovi[a][b][i][j]) mGridContent[i1+i][j1+j] = mPiece.mType;
        }
    }
}

void Board::removePiece()
{
    int a = mPiece.mType;
    int b = mPiece.mRotacija;

    int i1 = mPiece.mXposition - 1;
    int j1 = mPiece.mYposition - 2;

    for(int i=0; i!=4; i++)
    {
        for(int j=0; j!=4; j++) {
            if(mPiece.mDijelovi[a][b][i][j]) mGridContent[i1+i][j1+j] = EMPTY;
        }
    }
}

bool Board::movePiece(int x, int y)
{
    removePiece();

    int a = mPiece.mType;
    int b = mPiece.mRotacija;

    int i1 = mPiece.mXposition - 1;
    int j1 = mPiece.mYposition - 2;

    for(int i=0; i!=4; i++)
    {
        for(int j=0; j!=4; j++) {
            if(mPiece.mDijelovi[a][b][i][j]==1 || mPiece.mDijelovi[a][b][i][j]==2)
            {
                if(i1+i+x>19 || j1+j+y<0 || j1+j+y>9) {placePiece(); return false;}
                if (mGridContent[i1+i+x][j1+j+y] != EMPTY) {placePiece(); return false;}
            }
        }
    }

    mPiece.move(x,y);
    placePiece();

    return true;
}

bool Board::rotatePiece()
{
    removePiece();

    int a = mPiece.mType;;
    int b = (mPiece.mRotacija + 1)%4;

    int i1 = mPiece.mXposition - 1;
    int j1 = mPiece.mYposition - 2;

    for(int i=0; i!=4; i++)
    {
        for(int j=0; j!=4; j++) {
                        if(i1+i>19 || j1+j<0 || j1+j>9 || i1+i<0) {placePiece(); return false;}
                        if(mPiece.mDijelovi[a][b][i][j]) if (mGridContent[i1+i][j1+j] != EMPTY) { placePiece(); return false;}
        }
    }

    mPiece.mRotacija = (mPiece.mRotacija + 1) % 4;
    placePiece();
    return true;
}

bool Board::isLineFull(int y) const
{
    for(int i=0;i<10;i++) if(mGridContent[y][i] == EMPTY) return false;
    return true;
}

int Board::clearLines()
{
    int l = 0;

    int x=mPiece.mXposition-1;
    if(x < 0) x++;

    for(; x!=mPiece.mXposition+3; x++){
        if(isLineFull(x)){
            l++;
            for(int i=0;i!=10;i++) mGridContent[x][i] = EMPTY;
            for(int i=x;i>=0;i--)
                for(int j=0; j<10 ; j++)
                    if(i==0) mGridContent[i][j] = EMPTY;
                    else if(mGridContent[i-1][j] != EMPTY){mGridContent[i][j]=mGridContent[i-1][j]; mGridContent[i-1][j] = EMPTY;}
        }
        if(x==19) break;
    }
    mPiece.move(l,0);

    return l;
}
