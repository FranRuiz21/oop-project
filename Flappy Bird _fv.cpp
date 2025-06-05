#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

const int WIDTH = 40;
const int HEIGHT = 20;
const int INITIAL_PIPE_GAP = 6;
const int PIPE_FREQ = 20;
const int INITIAL_SPEED = 80;
const int MIN_SPEED = 30;

void ClearScreen() {
    COORD topLeft = {0, 0};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written, cells = WIDTH * HEIGHT;
    FillConsoleOutputCharacter(console, ' ', cells, topLeft, &written);
    SetConsoleCursorPosition(console, topLeft);
}

void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

class Pipe {
public:
    int x, gapY;
    Pipe(int startX, int gap) {
        x = startX;
        gapY = rand() % (HEIGHT - gap - 3) + 1;
    }

    void move() { x--; }

    bool isOffScreen() const { return x < 0; }

    bool hits(int bx, int by, int gap) const {
        if (x == bx && (by < gapY || by > gapY + gap)) return true;
        return false;
    }

    bool passed(int bx) const { return x == bx - 1; }
};

class Bird {
public:
    int x, y, velocity;

    Bird(int sx, int sy) {
        x = sx;
        y = sy;
        velocity = 0;
    }

    void flap() {
        velocity = -3;
        Beep(750, 80);
    }

    void fall() {
        velocity++;
        y += velocity;
    }

    bool isDead() const {
        return y < 0 || y >= HEIGHT;
    }
};

class Game {
private:
    Bird bird;
    vector<Pipe> pipes;
    int score, frameCount, speed, pipeGap;
    bool running;
    int highScore;

public:
    Game() : bird(5, HEIGHT / 2) {
        frameCount = 0;
        score = 0;
        speed = INITIAL_SPEED;
        pipeGap = INITIAL_PIPE_GAP;
        running = true;
        srand((unsigned int)time(0));
        loadHighScore();
    }

    void titleScreen() {
        ClearScreen();
        SetColor(11);
        cout << "=== CONSOLE FLAPPY BIRD ===\n";
        SetColor(15);
        cout << "\nInstructions:\n";
        cout << " - Press SPACE to flap\n";
        cout << " - Press X to exit\n";
        cout << " - Avoid the pipes!\n\n";
        cout << "Press any key to start...\n";
        _getch();
    }

    void draw() {
        ClearScreen();
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                if (x == bird.x && y == bird.y) {
                    SetColor(14); cout << 'O'; SetColor(15);
                } else {
                    bool isPipe = false;
                    for (int i = 0; i < pipes.size(); ++i) {
                        Pipe& pipe = pipes[i];
                        if (x == pipe.x && (y < pipe.gapY || y > pipe.gapY + pipeGap)) {
                            SetColor(10); cout << '|'; SetColor(15);
                            isPipe = true;
                            break;
                        }
                    }
                    if (!isPipe) cout << ' ';
                }
            }
            cout << "\n";
        }
        SetColor(8);
        for (int i = 0; i < WIDTH; ++i) cout << "=";
        SetColor(15);
        cout << "\nScore: " << score << "  |  High Score: " << highScore << "\n";
        cout << "Speed: " << (100 - speed + 20) << "%  |  Pipe Gap: " << pipeGap << "\n";
    }

    void input() {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == ' ') bird.flap();
            if (ch == 'x' || ch == 'X') running = false;
        }
    }

    void update() {
        bird.fall();

        if (frameCount % PIPE_FREQ == 0)
            pipes.push_back(Pipe(WIDTH - 1, pipeGap));

        for (int i = 0; i < pipes.size(); ++i) {
            Pipe& pipe = pipes[i];
            pipe.move();
            if (pipe.hits(bird.x, bird.y, pipeGap)) running = false;
            if (pipe.passed(bird.x)) {
                score++;
                if (score % 5 == 0 && speed > MIN_SPEED) speed -= 5;
                if (score % 10 == 0 && pipeGap > 3) pipeGap--;
            }
        }

        if (!pipes.empty() && pipes[0].isOffScreen())
            pipes.erase(pipes.begin());

        if (bird.isDead()) running = false;
        frameCount++;
    }

    void gameLoop() {
        while (running) {
            draw();
            input();
            update();
            Sleep(speed);
        }
    }

    void gameOver() {
        Beep(300, 200);
        ClearScreen();
        cout << "\n\n=== GAME OVER ===\n";
        cout << "Your score: " << score << "\n";
        if (score > highScore) {
            cout << "?? New High Score! ??\n";
            highScore = score;
            saveHighScore();
        } else {
            cout << "High Score: " << highScore << "\n";
        }
        cout << "\nPress R to restart or any other key to quit.\n";
        char ch = _getch();
        if (ch == 'r' || ch == 'R') {
            restart();
        } else {
            exit(0);
        }
    }

    void restart() {
        pipes.clear();
        bird = Bird(5, HEIGHT / 2);
        score = 0;
        frameCount = 0;
        speed = INITIAL_SPEED;
        pipeGap = INITIAL_PIPE_GAP;
        running = true;
    }

    void loadHighScore() {
        ifstream in("highscore.txt");
        if (in.is_open()) {
            in >> highScore;
            in.close();
        } else {
            highScore = 0;
        }
    }

    void saveHighScore() {
        ofstream out("highscore.txt");
        if (out.is_open()) {
            out << highScore;
            out.close();
        }
    }

    void start() {
        titleScreen();
        while (true) {
            gameLoop();
            gameOver();
        }
    }
};

int main() {
    Game game;
    game.start();
    return 0;
}

   
