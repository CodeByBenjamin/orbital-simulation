#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

enum class CellType {
	Empty,
	Rock
};

class Cell {
private:
	size_t x;
	size_t y;
	CellType type;
public:
	Cell(size_t x, size_t y, CellType type) : x(x), y(y), type(type) {
	}

	size_t getX() const { return x; }
	size_t getY() const { return y; }
	CellType getType() const { return type; }

	void setType(CellType type);

	void Draw(sf::RenderWindow& window, size_t cellSize);
};