#include "SFML/Graphics.hpp"
#include "World.h"

World::World(int width, int height, size_t cellSize)
    : width(width / cellSize), height(height / cellSize), cellSize(cellSize) {

    cells.reserve(this->width * this->height);

    for (int y = 0; y < this->height; ++y) {
        for (int x = 0; x < this->width; ++x) {
            cells.emplace_back(x, y, CellType::Empty);
        }
    }
}

Cell* World::getCell(int x, int y) {
    if (!inBounds(x, y)) {
        return nullptr;
    }
    return &getCellById(x + y * width);
}

Cell& World::getCellById(size_t id) {
    return cells.at(id);
}

bool World::isOccupied(int x, int y) {
    Cell* cell = getCell(x, y);
    return (cell != nullptr) ? cell->getType() != CellType::Empty : true;
}

bool World::moveCell(Cell& cellToMove, int x2, int y2) {
    if (!inBounds(x2, y2) || isOccupied(x2, y2)) {
        return false;
    }

    Cell* cellAtPos = getCell(x2, y2);

    cellAtPos->setType(cellToMove.getType());
    cellAtPos->setVelocity(cellToMove.getVelocity());
    cellAtPos->setAcceleration(cellToMove.getAcceleration());

    cellAtPos->setRealX(static_cast<float>(cellToMove.getX()));
    cellAtPos->setRealY(static_cast<float>(cellToMove.getY()));

    cellAtPos->setUpdated(true);

    cellToMove.setType(CellType::Empty);
    sf::Vector2f zero(0, 0);
    cellToMove.setVelocity(zero);
    cellToMove.setAcceleration(zero);

    cellToMove.setRealX(cellToMove.getRealX());
    cellToMove.setRealY(cellToMove.getRealY());

    return true;
}

void World::applyInitialVelocity(Cell* cell, sf::Vector2f vel) {
    cell->setVelocity(cell->getVelocity() + vel);
}

void World::applyGlobalForces(float G) {
    std::vector<Cell*> activeRocks;
    activeRocks.reserve(cells.size() / 10);

    for (auto& cell : cells) {
        if (cell.getType() == CellType::Rock) {
            activeRocks.push_back(&cell);
        }
    }

    for (size_t i = 0; i < activeRocks.size(); ++i) {
        Cell* cellA = activeRocks[i];

        for (size_t j = i + 1; j < activeRocks.size(); ++j) {
            Cell* cellB = activeRocks[j];

            float dx = cellA->getRealX() - cellB->getRealX();
            float dy = cellA->getRealY() - cellB->getRealY();

            float r2 = static_cast<float>(dx * dx + dy * dy);
    
            if (r2 < 0.1f) {
                continue;
            }

            float r = std::sqrt(r2);

            float softening = 10.0f;
            float forceMag = G * (cellA->getMass() * cellB->getMass()) / (r2 + softening);

            float fx = forceMag * (dx / r);
            float fy = forceMag * (dy / r);

            cellA->applyGravity(-fx, -fy);

            cellB->applyGravity(fx, fy);
        }
    }
}

void World::update(float deltaTime) {
    for (auto& cell : cells) {
        cell.setUpdated(false);
    }

    for (auto& cell : cells) {
        if (cell.getType() == CellType::Empty || cell.isUpdated()) {
            continue;
        }

        cell.updatePhysics(deltaTime, *this);
    }
}

void World::drawWorld(sf::RenderWindow& window) {
    sf::VertexArray vertices(sf::PrimitiveType::Triangles);

    for (auto& cell : cells) {
        if (cell.getType() == CellType::Empty) {
            continue;
        }

        float px = cell.getX() * cellSize;
        float py = cell.getY() * cellSize;
        float size = static_cast<float>(cellSize);

        float speed = std::sqrt(cell.getVelocity().x * cell.getVelocity().x +
            cell.getVelocity().y * cell.getVelocity().y);

        uint8_t intensity = static_cast<uint8_t>(std::min(speed * 10.0f + 100.0f, 255.0f));
        sf::Color color(intensity, 0, 255 - intensity);

        sf::Vector2f topLeft(px, py);
        sf::Vector2f topRight(px + size, py);
        sf::Vector2f bottomRight(px + size, py + size);
        sf::Vector2f bottomLeft(px, py + size);

        vertices.append(sf::Vertex{ topLeft, color });
        vertices.append(sf::Vertex{ topRight, color });
        vertices.append(sf::Vertex{ bottomLeft, color });

        vertices.append(sf::Vertex{ topRight, color });
        vertices.append(sf::Vertex{ bottomRight, color });
        vertices.append(sf::Vertex{ bottomLeft, color });
    }

    window.draw(vertices);
}