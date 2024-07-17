#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;
const int RECT_WIDTH = 5;
const int NUM_ELEMENTS = WIDTH / RECT_WIDTH;

void drawArray(sf::RenderWindow& window, const vector<int>& arr, int highlight1 = -1, int highlight2 = -1) {
    window.clear(sf::Color::White);

    for (int i = 0; i < arr.size(); ++i) {
        sf::RectangleShape rectangle(sf::Vector2f(RECT_WIDTH - 1, arr[i]));
        rectangle.setPosition(i * RECT_WIDTH, HEIGHT - arr[i]);

        if (i == highlight1 || i == highlight2) {
            rectangle.setFillColor(sf::Color::Red);
        } else {
            rectangle.setFillColor(sf::Color::Black);
        }

        window.draw(rectangle);
    }

    window.display();
}

void insertionSort(sf::RenderWindow& window, vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            drawArray(window, arr, j, j + 1);
            sf::sleep(sf::milliseconds(10));
            --j;
        }
        arr[j + 1] = key;
        drawArray(window, arr, j + 1);
        sf::sleep(sf::milliseconds(50));
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Insertion Sort Visualization");

    vector<int> arr(NUM_ELEMENTS);
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        arr[i] = rand() % HEIGHT;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        insertionSort(window, arr);
    }

    return 0;
}
