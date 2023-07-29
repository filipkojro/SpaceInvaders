#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include <iostream>
#include "GameObjects.cpp"

class GameSystem {
public:
	std::vector<Object*>objects;

	unsigned int nextAvaiableID = 0;

	void setID(Object* object) {
		object->assignID(nextAvaiableID);
		nextAvaiableID++;
	}

	void renderAll(sf::RenderWindow* window) {
		for (int i = 0; i < objects.size(); i++) {
			objects[i]->render(window);
		}
	}
};