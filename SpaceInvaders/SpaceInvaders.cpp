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
        if(!hidden)window->draw(sprite);
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

    sf::Image bulletImage;
    bulletImage.loadFromFile("./assets/sprites/bullet.png");
    sf::Texture bulletTexture;
    bulletTexture.loadFromImage(bulletImage);


    Player player;
    player.autoCollision(playerImage);

    player.setTexture(&playerTexture);
    player.move(sf::Vector2f(16, 15 * 16));
    //player.position = ;


    std::vector<Enemy>enemies;

    for (int x = 1; x <= 7; x++) {
        for (int y = 1; y <= 4; y++) {
            enemies.emplace_back();
            enemies[enemies.size() - 1].setTexture(&enemyTexture);
            enemies[enemies.size() - 1].autoCollision(enemyImage);
            enemies[enemies.size() - 1].move(sf::Vector2f(32 * x - 16, 32 * y - 16));
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
        //std::cout << mouse.x << " " << mouse.y << "\n";

        
        for (int i = 0; i < enemies.size(); i++) {
            if (enemies[i].checkCollision(mouse, tColBox))enemies.erase(enemies.begin() + i);
        }
        std::cout << enemies.size() << "\n";

        window.clear();
        window.draw(shape);


        player.render(&window);

        for (int i = 0; i < enemies.size(); i++)enemies[i].render(&window);

        window.display();
    }

    return 0;
}