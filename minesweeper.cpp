#include "minesweeper.h"
#include <QDebug>
#include <QUrl>
Minesweeper::Minesweeper()
{

    crashSound = new QSoundEffect();
    crashSound->setSource(QUrl::fromLocalFile("sounds/crash.wav"));
    crashSound->setVolume(0.9);
    qDebug() << "Crash sound loaded:" << crashSound->isLoaded();

    backgroundMusic = new QMediaPlayer();
    backgroundOutput = new QAudioOutput();
    backgroundMusic->setAudioOutput(backgroundOutput);
    backgroundMusic->setSource(QUrl::fromLocalFile("sounds/Door.wav"));
    backgroundMusic->setLoops(QMediaPlayer::Infinite);
    backgroundOutput->setVolume(1.0);
    backgroundMusic->play();




    reset();
}

Minesweeper::~Minesweeper()
{
    delete crashSound;
    delete backgroundMusic;
    delete backgroundOutput;
}

void Minesweeper::reset()
{
    mines.assign(BOARD_SIZE, std::vector<bool>(BOARD_SIZE, false));
    revealed.assign(BOARD_SIZE, std::vector<bool>(BOARD_SIZE, false));
    flagged.assign(BOARD_SIZE, std::vector<bool>(BOARD_SIZE, false));
    remaining = BOARD_SIZE * BOARD_SIZE - MINES;
    std::srand(std::time(nullptr));
    firstClick = true;
}

void Minesweeper::placeMines(int safeX, int safeY)
{
    int placed = 0;
    while (placed < MINES) {
        int x = std::rand() % BOARD_SIZE;
        int y = std::rand() % BOARD_SIZE;

        if (std::abs(x - safeX) <= 1 && std::abs(y - safeY) <= 1)
            continue;

        if (!mines[x][y]) {
            mines[x][y] = true;
            placed++;
        }
    }
}

int Minesweeper::countAdjacentMines(int x, int y) const
{
    int count = 0;
    for (int i = std::max(0, x - 1); i <= std::min(BOARD_SIZE - 1, x + 1); i++) {
        for (int j = std::max(0, y - 1); j <= std::min(BOARD_SIZE - 1, y + 1); j++) {
            if (mines[i][j])
                count++;
        }
    }
    return count;
}

bool Minesweeper::reveal(int x, int y)
{
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || revealed[x][y] || flagged[x][y])
        return false;


    if (firstClick) {
        placeMines(x, y);
        firstClick = false;
    }

    revealed[x][y] = true;

    if (mines[x][y]) {
        if (crashSound && crashSound->isLoaded())
            crashSound->play();
        return true;
    }

    remaining--;

    if (countAdjacentMines(x, y) == 0) {
        for (int i = std::max(0, x - 1); i <= std::min(BOARD_SIZE - 1, x + 1); i++) {
            for (int j = std::max(0, y - 1); j <= std::min(BOARD_SIZE - 1, y + 1); j++) {
                if (!revealed[i][j]) {
                    reveal(i, j);
                }
            }
        }
    }

    return false;
}

void Minesweeper::toggleFlag(int x, int y)
{
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || revealed[x][y])
        return;
    flagged[x][y] = !flagged[x][y];
}

bool Minesweeper::isFlagged(int x, int y) const
{
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE)
        return false;
    return flagged[x][y];
}

bool Minesweeper::isWon() const
{
    return remaining == 0;
}

bool Minesweeper::isRevealed(int x, int y) const
{
    return revealed[x][y];
}

bool Minesweeper::hasMine(int x, int y) const
{
    return mines[x][y];
}

int Minesweeper::adjacentMines(int x, int y) const
{
    return countAdjacentMines(x, y);
}
