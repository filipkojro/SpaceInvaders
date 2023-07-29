#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include <iostream>

class Object {
public:
    unsigned int ID;
    sf::Vector2f position;
    bool hidden;
    bool collision;
    bool controllable;

    int collisionBox[4];

    sf::Texture texture;
    //sf::Image image;
    sf::Sprite sprite;

    void assignID(unsigned int id) {
        ID = id;
    }

    void setTexture(sf::Texture* playerTexture) {
        sprite = sf::Sprite(*playerTexture);
    }

    void autoCollision(sf::Image img) {

        collisionBox[0] = img.getSize().x;
        collisionBox[1] = img.getSize().y;
        collisionBox[2] = 0;
        collisionBox[3] = 0;


        for (int x = 0; x < img.getSize().x; x++) {
            for (int y = 0; y < img.getSize().y; y++) {
                if (img.getPixel(x, y) != sf::Color::Transparent) {
                    if (x < collisionBox[0])collisionBox[0] = x;
                    if (y < collisionBox[1])collisionBox[1] = y;
                    if (x > collisionBox[2])collisionBox[2] = x;
                    if (y > collisionBox[3])collisionBox[3] = y;
                }
            }
        }
        collisionBox[2] -= collisionBox[0];
        collisionBox[3] -= collisionBox[1];
    }

    void render(sf::RenderWindow* window) {
        if (!hidden) window->draw(sprite);
    }

    void move(sf::Vector2f objPosition) {
        sprite.setPosition(position + objPosition);
        position = sprite.getPosition();
    }

    bool checkCollision(sf::Vector2f projectilePosition, int* projectileCollisionBox) {
        if (position.x + collisionBox[0] <= projectilePosition.x + projectileCollisionBox[0] + projectileCollisionBox[2] &&
            position.y + collisionBox[1] <= projectilePosition.y + projectileCollisionBox[1] + projectileCollisionBox[3] &&
            position.x + collisionBox[0] + collisionBox[2] >= projectilePosition.x + projectileCollisionBox[0] &&
            position.y + collisionBox[1] + collisionBox[3] >= projectilePosition.y + projectileCollisionBox[1]) {
            return true;
        }
        return false;
    }

};

class Projectile : Object {
public:
    Projectile(sf::Vector2f startPosition, sf::Vector2i direction, sf::Image image) {
        hidden = false;
        collision = true;
        controllable = false;

        autoCollision(image);

        position = startPosition;
    }
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