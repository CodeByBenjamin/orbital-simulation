#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include "Cell.h"

class World {
private:
	size_t width;
	size_t height;
	size_t cellSize;
	std::vector<Cell> cells;
public:
	World(size_t width, size_t height, size_t cellSize);
	
	Cell& getCell(size_t x, size_t y);
	Cell& getCellById(size_t Id);

	void DrawWorld(sf::RenderWindow& window);
};