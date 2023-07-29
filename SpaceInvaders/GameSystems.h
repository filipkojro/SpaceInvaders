#pragma once
#include "GameSystems.cpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include <iostream>

class Object {
public:

    sf::Vector2f position;
    bool hidden;
    bool collision;
    bool controllable;

    int collisionBox[4];

    sf::Texture texture;
    //sf::Image image;
    sf::Sprite sprite;

    void setTexture(sf::Texture* playerTexture);

    void autoCollision(sf::Image img);

    void render(sf::RenderWindow* window);

    void move(sf::Vector2f objPosition);

    bool checkCollision(sf::Vector2f projectilePosition, int* projectileCollisionBox);

};

class Projectile : Object {
public:
    Projectile(sf::Vector2f startPosition, sf::Vector2i direction, sf::Image image);
};

class Player : public Object {
private:
    float movementSpeed = 100.f;

public:
    Player() {
        hidden = false;
        collision = true;
        controllable = true;
    }

    void controll(float delta) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            move(sf::Vector2f(-1 * movementSpeed * delta, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            move(sf::Vector2f(1 * movementSpeed * delta, 0));
        }
    }

    void shoot();

};

class Enemy : public Object {
public:
    Enemy() {
        hidden = false;
        collision = true;
        controllable = false;
    }
};