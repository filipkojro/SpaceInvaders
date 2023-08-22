#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include <iostream>
#include "GameCore.cpp"
#include "GameObjects.cpp"

class Projectile : public Object {
public:
    bool outOfBounds = true;

    sf::Vector2f dir;
    
    Projectile(sf::Vector2f direction, sf::Image* image) {
        hidden = true;
        collision = false;
        controllable = false;

        dir = direction;

        autoCollision(*image);

        
    }
    void deploy(sf::Vector2f startPosition) {
        setPosition(startPosition);
        outOfBounds = false;
        hidden = false;
    }

    void movement(float delta) {
        
        if (outOfBounds)return;
        if (position.y < 0) {
            hidden = true;
            outOfBounds = true;
            return;
        }
        //position.y += dir.y * delta;
        move(sf::Vector2f(0, dir.y * delta * 0));
        //std::cout << hidden << " " << outOfBounds << "\n";
    }
};


class Player : public Object {
private:
    float movementSpeed = 100.f;

    GameSystem* gameSystem;

public:
    sf::Image bulletImage;
    sf::Texture bulletTexture;
    sf::Vector2f dir = sf::Vector2f(0, -100);

    Projectile bullet = Projectile(dir, &bulletImage);

    
    

    Player(GameSystem* gs) {

        //nextAvaiableID = nxtAvlblID;
        gameSystem = gs;
        hidden = false;
        collision = true;
        controllable = true;

        
        bulletImage.loadFromFile("./assets/sprites/bullet.png");
        bulletTexture.loadFromImage(bulletImage);
        bullet.setTexture(&bulletTexture);

        gs->objects.push_back(&bullet);

        //projectileImage.loadFromFile("./assets/sprites/bullet.png");
        //projectileTexture.loadFromImage(projectileImage);
    }

    void controll(float delta) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            move(sf::Vector2f(-1 * movementSpeed * delta, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            move(sf::Vector2f(1 * movementSpeed * delta, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            //bullets.emplace_back(position, sf::Vector2i(0, -1), projectileImage);
            //assignID();
            if (bullet.position.y < -100) {
                bullet.deploy(position);
            }
            //bullet.deploy(position);
        }
    }
};

class Enemy : public Object {
public:
    Enemy() {
        hidden = false;
        collision = true;
        controllable = false;
    }
};