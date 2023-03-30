#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
using namespace std;

const int width = 50;
const int height = 25;

class Snake {
    private:
        int x, y;
    public:
        Snake() {
            x = width / 2;
            y = height / 2;
        }
        void move(char direction) {
            switch(direction) {
                case 'w':
                    y--;
                    break;
                case 'a':
                    x--;
                    break;
                case 's':
                    y++;
                    break;
                case 'd':
                    x++;
                    break;
            }
        }
        int getX() const {
            return x;
        }
        int getY() const {
            return y;
        }
};

class Fruit {
private:
    int x, y;
public:
    Fruit() {
        update();
    }
    int getX() const {
        return x;
    }
    int getY() const {
        return y;
    }
    void update() {
        do {
            x = rand() % width;
            y = rand() % height;
        } while (x == 0 || x == width-1 || y == 0 || y == height-1); // Ensure the fruit is not generated on the border or inside the snake
    }
};

class Board {
private:
    Snake snake;
    Fruit fruit;
    bool gameOver;
    int gameSpeed;
    int score;
public:
    int getScore() const {
        return score;
    }
    Board(int speed) {
        gameOver = false;
        gameSpeed = speed;
        score=0;
    }
    void draw() const {
        system("clear");
        for (int i = 0; i < width + 2; i++) {
            cout << "#";
        }
        cout << endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0 || j == width-1) {
                    cout << "#";
                }
                else if (i == snake.getY() && j == snake.getX()) {
                    cout << "o";
                }
                else if (i == fruit.getY() && j == fruit.getX()) {
                    cout << "F";
                }
                else {
                    cout << " ";
                }
            }
            cout << endl;
        }
        for (int i = 0; i < width + 2; i++) {
            cout << "#";
        }
        cout << endl;
        cout << "Score: " << score << endl;
    }

    void input() {
        char direction;
        cin >> direction;
        snake.move(direction);
    }
    void logic() {
        if (snake.getX() < 1 || snake.getX() >= width-1 || snake.getY() < 1 || snake.getY() >= height-1) {
            gameOver = true;
        }
        if (snake.getX() == fruit.getX() && snake.getY() == fruit.getY()) {
            fruit.update();
            score++;
        } 
        else {
            this_thread::sleep_for(chrono::milliseconds(gameSpeed));
        }
    }
    bool isGameOver() const {
        return gameOver;
    }
};

int main() {
    srand(time(NULL)); // initialize random seed
    int gameSpeed = 100; // set the game speed to 100 milliseconds per frame
    Board board(gameSpeed);
    while (!board.isGameOver()) {
        board.draw();
        board.input();
        board.logic();
    }
    cout << "Game over!" << endl;
    return 0;
}
