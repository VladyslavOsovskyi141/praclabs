#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <random>

using namespace std;

const int WIDTH = 100;
const int HEIGHT = 30;
const int V = 1;
const int MOVE_DELAY = 100;
const int CHANGE_DIR_SEC = 3;


mutex printMutex;

int randomDir() {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(-1, 1);
    int d;
    do {
        d = dist(gen);
    } while (d == 0);
    return d;
}

class Rabbit {
public:
    string name;
    int x, y;
    int dx, dy;
    bool albino;

    Rabbit(string n, int x, int y, bool albino)
        : name(n), x(x), y(y), albino(albino) {
        if (albino) {
            dx = 1;
            dy = 0;
        } else {
            dx = randomDir();
            dy = randomDir();
        }
    }

    void move() {
        auto lastChange = chrono::steady_clock::now();

        while (true) {
            {
                lock_guard<mutex> lock(printMutex);
                cout << name << " at (" << x << ", " << y << ")" << endl;
            }

            x += dx * V;
            y += dy * V;

            if (x <= 0 || x >= WIDTH) dx *= -1;
            if (y <= 0 || y >= HEIGHT) dy *= -1;

            if (!albino) {
                auto now = chrono::steady_clock::now();
                if (chrono::duration_cast<chrono::seconds>(now - lastChange).count() >= CHANGE_DIR_SEC) {
                    dx = randomDir();
                    dy = randomDir();
                    lastChange = now;
                }
            }

            this_thread::sleep_for(chrono::milliseconds(MOVE_DELAY));
        }
    }
};


int main() {
    vector<thread> threads;

    // Звичайні кролики
    threads.emplace_back(&Rabbit::move, Rabbit("Rabbit_1", 10, 5, false));
    threads.emplace_back(&Rabbit::move, Rabbit("Rabbit_2", 30, 15, false));

    // Альбіноси
    threads.emplace_back(&Rabbit::move, Rabbit("Albino_1", 0, 10, true));
    threads.emplace_back(&Rabbit::move, Rabbit("Albino_2", WIDTH, 20, true));

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
