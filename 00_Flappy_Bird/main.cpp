#include <iostream>
#include "string"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "vector"

#include <unistd.h>
#include <limits.h>

void printCurrentWorkingDirectory() {
    char buffer[PATH_MAX];
    if (getcwd(buffer, sizeof(buffer)) != NULL) {
        std::cout << "Current Working Directory: " << buffer << std::endl;
    } else {
        perror("getcwd() error");
    }
}

using namespace std;
// Flappy Bird game
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
    bool pressed;

    sf::Font font;
    sf::Text scoreText;

    const float PIPE_WIDTH = 50.0f;
    const float MIN_PIPE_HEIGHT = 50.0f;
    const float MAX_PIPE_HEIGHT = 300.0f;
    const float PIPE_GAP = 250.0f;
    const float PIPE_X_POSITION = 800.0f;

    vector<sf::RectangleShape> pipes;
    float pipeSpawnTimer;

    void processEvents();
    void update(float deltaTime);
    void render();
    void handlePlayerInput(sf::Keyboard::Key key);
    void spawnPipe();
    void movePipes(float deltaTime);
    void checkCollision();
    void checkScore();
};

FlappyBird::FlappyBird() : pressed(false), window(sf::VideoMode(800, 600), "Flappy Bird"), bird(20.0f) {
    bird.setFillColor(sf::Color::Green);
    bird.setPosition(100.0f, 300.0f);
    birdVelocity = 0.0f;
    gravity = 100.0f;
    birdAcceleration = gravity;
    score = 0;
    gameover = false;
    if (!font.loadFromFile("../fonts/Inter-Bold.ttf")){
        cout << "Error loading font" << endl;
        printCurrentWorkingDirectory();
    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(30); // Set the character size
    scoreText.setFillColor(sf::Color::White); // Set the text color
    scoreText.setPosition(10, 10); // Position the score in the top right corner
    scoreText.setString("Score: " + to_string(score));
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
        if (event.key.code == sf::Keyboard::Space && event.type == sf::Event::KeyPressed && !pressed) {
            handlePlayerInput(event.key.code);
        }
        if (event.key.code == sf::Keyboard::Space && event.type == sf::Event::KeyReleased && pressed) {
            handlePlayerInput(event.key.code);
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
        checkScore();
    }
}

void FlappyBird::handlePlayerInput(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Space && !pressed) {
        birdVelocity = -gravity * 0.5f;
        pressed = true;
    }
    else {
        pressed = false;
    }
}

void FlappyBird::render() {
    window.clear();
    window.draw(bird);
    window.draw(scoreText);
    for (auto &pipe : pipes) {
        window.draw(pipe);
        window.draw(scoreText);
    }
    window.display();
}

void FlappyBird::spawnPipe() {
    float randomHeight1 = MIN_PIPE_HEIGHT + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (MAX_PIPE_HEIGHT - MIN_PIPE_HEIGHT)));
    float randomHeight2 = 600.0f - randomHeight1 - PIPE_GAP;

    sf::RectangleShape pipe1(sf::Vector2f(PIPE_WIDTH, randomHeight1));
    pipe1.setFillColor(sf::Color::Red);
    pipe1.setPosition(PIPE_X_POSITION, 0.0f);
    pipes.push_back(pipe1);

    sf::RectangleShape pipe2(sf::Vector2f(PIPE_WIDTH, randomHeight2));
    pipe2.setFillColor(sf::Color::Blue);
    pipe2.setPosition(PIPE_X_POSITION, randomHeight1 + PIPE_GAP);
    pipes.push_back(pipe2);
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
            scoreText.setString("Score: " + to_string(score));
        }
    }
}

int main() {
    FlappyBird game;
    game.run();
    return 0;
}

