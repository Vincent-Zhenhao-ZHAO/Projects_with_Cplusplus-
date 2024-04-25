#include <iostream>
#include "string"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "vector"
using namespace std;

class FlappyBird {
public:
    FlappyBird();
    void run();

private:
    sf::RenderWindow window;
    sf::CircleShape bird;

    float birdVelocity;
    float gravity;
    float birdAcceleration;
    int score;
    bool gameover;

    vector<sf::RectangleShape> pipes;
    float pipeSpawnTimer;

    void processEvents();
    void update(float deltaTime);
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void spawnPipe();
    void movePipes(float deltaTime);
    void checkCollision();
    void checkScore();
};

FlappyBird::FlappyBird() : window(sf::VideoMode(800, 600), "Flappy Bird"), bird(20.0f) {
    bird.setFillColor(sf::Color::Green);
    bird.setPosition(100.0f, 300.0f);
    birdVelocity = 0.0f;
    birdAcceleration = 0.0f;
    gravity = 100.0f;
    score = 0;
    gameover = false;
}

void FlappyBird::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        processEvents();
        float deltaTime = clock.restart().asSeconds();
        update(deltaTime);
        render();
    }
}

void FlappyBird::processEvents() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            handlePlayerInput(event.key.code, true);
        }
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
            handlePlayerInput(event.key.code, false);
        }
    }
}

void FlappyBird::update(float deltaTime) {
    if (!gameover) {
        birdVelocity += birdAcceleration * deltaTime;
        bird.move(0.0f, birdVelocity * deltaTime);
        pipeSpawnTimer += deltaTime;
        if (pipeSpawnTimer >= 1.5f) {
            pipeSpawnTimer = 0.0f;
            spawnPipe();
        }
        movePipes(deltaTime);
        checkCollision();
    }
}

void FlappyBird::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::Space) {
        if (isPressed) {
            birdAcceleration = -gravity;
        }
    }
}

void FlappyBird::render() {
    window.clear();
    window.draw(bird);
    for (auto &pipe : pipes) {
        window.draw(pipe);
    }
    window.display();
}

void FlappyBird::spawnPipe() {
    sf::RectangleShape pipe;
    pipe.setSize(sf::Vector2f(50.0f, 300.0f));
    pipe.setFillColor(sf::Color::Red);
    pipe.setPosition(800.0f, 0.0f);
    pipes.push_back(pipe);
}

void FlappyBird::movePipes(float deltaTime) {
    for (auto &pipe : pipes) {
        pipe.move(-100.0f * deltaTime, 0.0f);
    }
}

void FlappyBird::checkCollision() {
    for (auto &pipe : pipes) {
        if (bird.getGlobalBounds().intersects(pipe.getGlobalBounds())) {
            gameover = true;
        }
    }
}

void FlappyBird::checkScore() {
    for (auto &pipe : pipes) {
        if (bird.getPosition().x > pipe.getPosition().x && pipe.getFillColor() != sf::Color::Green) {
            score++;
            pipe.setFillColor(sf::Color::Green);
        }
    }
}

int main() {
    FlappyBird game;
    game.run();
    return 0;
}

