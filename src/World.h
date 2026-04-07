#pragma once

#include "Cell.h"

class World {
private:
	int width;
	int height;
	size_t cellSize;
	std::vector<Cell> cells;
public:
	World(int width, int height, size_t cellSize);
	
	Cell* getCell(int x, int y);
	Cell& getCellById(size_t Id);

	bool inBounds(int x, int y) const { return x >= 0 && y >= 0 && x < width && y < height; };
	bool isOccupied(int x, int y);
	bool moveCell(Cell& cellToMove, int x2, int y2);

	void applyInitialVelocity(Cell* cell, sf::Vector2f vel);
	void applyGlobalForces(float G);
	void update(float deltaTime);

	void drawWorld(sf::RenderWindow& window);
};