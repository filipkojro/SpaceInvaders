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

    float collisionBox[4];

    sf::Texture texture;
    sf::Sprite sprite;

    void setTexture(sf::Texture* playerTexture) {
        sprite = sf::Sprite(*playerTexture);
    }

    void render(sf::RenderWindow* window) {
        window->draw(sprite);
    }

    void move(sf::Vector2f objPosition) {
        sprite.setPosition(position + objPosition);
        position = sprite.getPosition();
    }
    /*
    bool checkCollision(Projectile* projectile) {
        if (collisionBox[0] > *projectile->collisionBox) {
            return true;
        }
        return false;
    }*/

};

class Projectile : Object {
public:
    Projectile() {
        hidden = false;
        collision = true;
        controllable = false;
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


int main(){
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


    Player player;

    player.setTexture(&playerTexture);

    player.position = sf::Vector2f(16, 15 * 16);


    std::vector<Enemy>enemies;

    for (int x = 1; x <= 7; x++) {
        for (int y = 1; y <= 4; y++) {
            enemies.emplace_back();
            enemies[enemies.size() - 1].setTexture(&enemyTexture);
            enemies[enemies.size() - 1].move(sf::Vector2f(32 * x - 16, 32 * y - 16));
        }
    }


    Projectile bullet;



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

        

        window.clear();
        window.draw(shape);


        player.render(&window);

        for (int i = 0; i < enemies.size(); i++)enemies[i].render(&window);

        window.display();
    }

    return 0;
}