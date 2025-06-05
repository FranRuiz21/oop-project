#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

#define WIDTH 40
#define HEIGHT 20
#define SNAKE_CHAR 'O'
#define FOOD_CHAR 'F'

#define COLOR_RESET (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define COLOR_RED (FOREGROUND_RED | FOREGROUND_INTENSITY)
#define COLOR_GREEN (FOREGROUND_GREEN)
#define COLOR_LIGHT_GREEN (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define COLOR_CYAN (FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void setCursorPosition(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

struct Point {
    int x, y;
};

class Food {
public:
    int x, y;
    void spawn(const vector<Point>& snake) {
        while (true) {
            x = rand() % (WIDTH - 2) + 1;
            y = rand() % (HEIGHT - 2) + 1;
            bool onSnake = false;
            for (size_t i = 0; i < snake.size(); ++i) {
                if (snake[i].x == x && snake[i].y == y) {
                    onSnake = true;
                    break;
                }
            }
            if (!onSnake) break;
        }
    }
    void draw() const {
        setCursorPosition(x, y);
        setColor(COLOR_RED);
        cout << FOOD_CHAR;
        setColor(COLOR_RESET);
    }
};

class Snake {
public:
    vector<Point> body;
    int dx, dy;
    bool grow;

    Snake() {
        body.push_back({ WIDTH / 2, HEIGHT / 2 });
        dx = 1; dy = 0;
        grow = false;
    }

    void update() {
        Point head = body[0];
        head.x += dx;
        head.y += dy;
        body.insert(body.begin(), head);
        if (!grow)
            body.pop_back();
        else
            grow = false;
    }

    void changeDirection(char input) {
        switch (input) {
            case 'w': case 'W': if (dy == 0) { dx = 0; dy = -1; } break;
            case 's': case 'S': if (dy == 0) { dx = 0; dy = 1; } break;
            case 'a': case 'A': if (dx == 0) { dx = -1; dy = 0; } break;
            case 'd': case 'D': if (dx == 0) { dx = 1; dy = 0; } break;
            case 72: if (dy == 0) { dx = 0; dy = -1; } break; // up
            case 80: if (dy == 0) { dx = 0; dy = 1; } break;  // down
            case 75: if (dx == 0) { dx = -1; dy = 0; } break; // left
            case 77: if (dx == 0) { dx = 1; dy = 0; } break;  // right
        }
    }

    bool isCollision() {
        Point head = body[0];
        if (head.x <= 0 || head.x >= WIDTH - 1 || head.y <= 0 || head.y >= HEIGHT - 1)
            return true;
        for (size_t i = 1; i < body.size(); ++i)
            if (body[i].x == head.x && body[i].y == head.y)
                return true;
        return false;
    }

    void draw() const {
        setCursorPosition(body[0].x, body[0].y);
        setColor(COLOR_LIGHT_GREEN);
        cout << SNAKE_CHAR;
        for (size_t i = 1; i < body.size(); ++i) {
            setCursorPosition(body[i].x, body[i].y);
            setColor((i % 2 == 0) ? COLOR_GREEN : COLOR_LIGHT_GREEN);
            cout << SNAKE_CHAR;
        }
        setColor(COLOR_RESET);
    }
};

class Game {
    Snake snake;
    Food food;
    int score;
    int highScore;
    bool paused;
    bool running;

    void loadHighScore() {
        ifstream file("highscore.txt");
        highScore = 0;
        if (file.is_open()) file >> highScore;
        file.close();
    }

    void saveHighScore() {
        if (score > highScore) {
            ofstream file("highscore.txt");
            if (file.is_open()) file << score;
            file.close();
        }
    }

    void drawBorder() {
        for (int i = 0; i < WIDTH; ++i) {
            setCursorPosition(i, 0); cout << '#';
            setCursorPosition(i, HEIGHT - 1); cout << '#';
        }
        for (int i = 0; i < HEIGHT; ++i) {
            setCursorPosition(0, i); cout << '#';
            setCursorPosition(WIDTH - 1, i); cout << '#';
        }
    }

    void drawScore() {
        setCursorPosition(0, HEIGHT);
        setColor(COLOR_CYAN);
        cout << "Score: " << score << "  High Score: " << highScore;
        setColor(COLOR_RESET);
    }

public:
    Game() {
        srand((unsigned)time(0));
        loadHighScore();
    }

    void start() {
        snake = Snake();
        food.spawn(snake.body);
        score = 0;
        paused = false;
        running = true;

        hideCursor();
        system("cls");

        while (running) {
            Sleep(max(50, 150 - score * 2));
            if (_kbhit()) {
                char key = _getch();
                if (key == 'p' || key == 'P') paused = !paused;
                else if (!paused) snake.changeDirection(key);
            }
            if (paused) continue;

            snake.update();
            if (snake.isCollision()) break;

            if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
                snake.grow = true;
                food.spawn(snake.body);
                score += 1;
                Beep(1000, 100); // sound effect on food
            }

            system("cls");
            drawBorder();
            drawScore();
            food.draw();
            snake.draw();
        }

        saveHighScore();
        gameOver();
    }

    void gameOver() {
        system("cls");
        setColor(COLOR_CYAN);
        cout << "\n\n\t=== GAME OVER ===\n\n";
        setColor(COLOR_RESET);
        cout << "\tYour Score: " << score << endl;
        cout << "\tHigh Score: " << highScore << endl;
        cout << "\n\tPress R to Restart or Q to Quit" << endl;
        while (true) {
            char key = _getch();
            if (key == 'r' || key == 'R') { start(); break; }
            if (key == 'q' || key == 'Q') { exit(0); }
        }
    }

    void menu() {
        system("cls");
        setColor(COLOR_CYAN);
        cout << "\n\n\t=== SNAKE GAME ===\n\n";
        setColor(COLOR_RESET);
        cout << "\t[1] Start Game\n";
        cout << "\t[2] Quit\n";
        cout << "\n\tUse Arrow Keys or WASD to move" << endl;

        char key;
        while (true) {
            key = _getch();
            if (key == '1') { start(); break; }
            else if (key == '2') { exit(0); }
        }
    }
};

int main() {
    Game game;
    while (true)
        game.menu();
    return 0;
}




