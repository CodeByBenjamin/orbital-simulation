#include "Cell.h"

void Cell::setType(CellType type)
{
    this->type = type;
}

void Cell::Draw(sf::RenderWindow& window, size_t cellSize)
{
    sf::RectangleShape rect(sf::Vector2f(cellSize, cellSize));
    rect.setPosition(sf::Vector2f(getX() * static_cast<float>(cellSize), getY() * static_cast<float>(cellSize)));

    switch (type)
    {
    case CellType::Empty:
        return;

    case CellType::Rock:
        rect.setFillColor(sf::Color::Blue);
        break;
    }
    window.draw(rect);
}