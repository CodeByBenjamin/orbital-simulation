#include "World.h"

World::World(size_t width, size_t height, size_t cellSize) : width(width / cellSize), height(height / cellSize), cellSize(cellSize){
    cells.reserve(width * height / (cellSize * cellSize));

    for (size_t y = 0; y < height / cellSize; ++y) {
        for (size_t x = 0; x < width / cellSize; ++x) {
            cells.emplace_back(x, y, CellType::Empty);
        }
    }
}

Cell& World::getCell(size_t x, size_t y)
{
    return cells.at(x + y * width);
}

Cell& World::getCellById(size_t id)
{
    return cells.at(id);
}

void World::DrawWorld(sf::RenderWindow& window)
{
    for (auto& cell : cells)
    {
        cell.Draw(window, cellSize);
    }
}