#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include <iostream>
#include "GameObjects.cpp"

class GameSystem {
public:
	std::vector<Object*>objects;
	std::vector<sf::Sprite*> allSprites;

	unsigned int nextAvaiableID = 0;

	void renderAll(sf::RenderWindow* window) {
		for (int i = 0; i < objects.size(); i++) {
			//window->draw(*allSprites[i]);
			objects[i]->render(window);
		}
	}
};