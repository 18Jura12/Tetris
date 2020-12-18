#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include "tetrimino.h"
#include <random>

/** Klasa Board
 *
 *  Klasa implementira svu logiku Tetris igre.
 */
class Board : public sf::Drawable, public sf::Transformable, public sf::NonCopyable {
public:
    Board();
    // Aktualizacija
    void update(int a);
    // Pozicioniraj novi tetrimino na ploči.
    void spawnPiece();
    // Vraća true ako je igra gotova, inače false
    bool isGameOver() const;
    // Broj obrisanih linija od zadnje aktualizacije scene.
    int getNoLinesCompleted() const;
    void clearNoLinesCompleted() { mNoLinesCompleted = 0; }
    void restart( float s);
private:
    static const int EMPTY = -1;
    static const int mCols = 10;       // Broj stupaca u mreži
    static const int mRows = 2* mCols; // Broj redaka u mreži

    sf::VertexArray mGrid;             // Linije koje čine mrežu.
    int mGridContent[mRows][mCols];    // Logički prikaz mreže

    std::default_random_engine mR;

    // Dimenzije mreže
    float mLeftMargin = 50.f;
    float mTopMargin = 50.0f;
    float mWidth= 250.f;
    float mHeight=2*mWidth;
    // Početak mreže = gornji lijevi kut
    float mOriginX = mLeftMargin + 1.f;
    float mOriginY = mTopMargin+1.f;
    // Dimenzije ćelija
    float mDx = ( mWidth - 11.f ) / 10.f;
    float mDy = mDx;
    // Vremenski interval između propadanja tetrimina.
    float mDt = 0.3f; // sekunde
    // Signalizacija da je igra završena
    bool mGameOver = false;
    float mGameSpeed = 3;
    // Broj linija obrisanih od jednom (0,1,2,3 ili 4)
    int mNoLinesCompleted = 0;

    // Generiranje slučajnog elementa.

    // Komad koji pada
    Tetrimino mPiece;
    // Iscrtavanje
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

    // Provjerava da li se komad može smjestiti na ploču.
    bool checkSpace();
    // Smjesti komad na ploču. Pretpostavlja se da je checkSpace(piece) vratio true.
    void placePiece();
    // Ukloni komad sa ploče.
    void removePiece();
    // Pomakni komad ako je moguće. Vrati true ako je pomak izvršen, inače false.
    bool movePiece(int x, int y);
    // Rotiraj komad. Vrati true ako je rotacija izvršena, inače false.
    bool rotatePiece();
    // Da li je linija y prazna ili nije ?
    bool isLineFull(int y) const;
    // Obriši kompletne linije i vrati broj obrisanih linija
    int clearLines();
    // Eventualno vaše dodatne metode dolaze ovdje.
    // Privatne metode koje ne trebate možete slobodno ukloniti.

};

#endif // BOARD_H
