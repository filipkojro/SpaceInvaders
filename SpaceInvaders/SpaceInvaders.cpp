#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include <iostream>
#include "GameCore.cpp"
#include "GameObjects.cpp"

int main(){
    GameSystem gameSystem;

    sf::RenderWindow window(sf::VideoMode(256, 256), "Space Invaders");
    sf::CircleShape shape(1000.f);
    shape.move(-500.f, -500.f);
    shape.setFillColor(sf::Color::Green);

    sf::Image playerImage;
    playerImage.loadFromFile("./assets/sprites/player.png");
    sf::Texture playerTexture;
    playerTexture.loadFromImage(playerImage);

    sf::Image enemyImage;
    enemyImage.loadFromFile("./assets/sprites/enemy1.png");
    sf::Texture enemyTexture;
    enemyTexture.loadFromImage(enemyImage);

    sf::Image bulletImage;
    bulletImage.loadFromFile("./assets/sprites/bullet.png");
    sf::Texture bulletTexture;
    bulletTexture.loadFromImage(bulletImage);


    //std::vector<Object*>objects;


    Player player;
    gameSystem.objects.push_back(&player);
    player.autoCollision(playerImage);

    player.setTexture(&playerTexture);
    player.move(sf::Vector2f(16, 15 * 16));
    //player.position = ;

    const int sizeX = 7;
    const int sizeY = 4;
    std::vector<Enemy> enemies(sizeX * sizeY);
    for (int i = 0; i < enemies.size(); i++) {
        auto& enemy = enemies[i];
        int x = 1 + i % sizeX;
        int y = i / sizeX;
        enemy.setTexture(&enemyTexture);
        enemy.autoCollision(enemyImage);
        enemy.move(sf::Vector2f(32 * x - 16, 32 * y - 16));
        gameSystem.objects.push_back(&enemy);
            // enemies[enemies.size() - 1].setTexture(&enemyTexture);
            // enemies[enemies.size() - 1].autoCollision(enemyImage);
            // enemies[enemies.size() - 1].move(sf::Vector2f(32 * x - 16, 32 * y - 16)); 
    }

    for (int x = 1; x <= 7; x++) {
        for (int y = 1; y <= 4; y++) {
        }
    }



    std::vector<Projectile>projectiles;


    //Projectile bullet;

    int tColBox[4] = { 0, 0, 0, 0 };
    
    sf::Clock clock;
    sf::Time delta;
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

        delta = clock.getElapsedTime();
        
        if (delta.asMilliseconds() > 0) {
            clock.restart();
            player.controll(delta.asMilliseconds() / 1000.f);

            //std::cout << delta.asMilliseconds() / 1000.f << " " << player.position.x << "\n";
        }

        sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        if (enemies[0].checkCollision(mouse, tColBox)) {
            std::cout << "help collision\n";
        }

        
        for (int i = 0; i < enemies.size(); i++) {
            if (enemies[i].checkCollision(mouse, tColBox)) enemies.erase(enemies.begin() + i);

            //to do delete from objects

        }
        std::cout << enemies.size() << "\n";

        window.clear();
        window.draw(shape);

        gameSystem.renderAll(&window);

        window.display();
    }

    return 0;
}