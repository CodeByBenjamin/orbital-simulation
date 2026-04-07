#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

#include "World.h"
#include "Cell.h"

void drawCells(World& world, sf::Vector2i mousePos, int mouseRadius, const size_t cellSize);
void addVelocity(World& world, sf::Vector2i clickStartPos, sf::Vector2i clickEndPos, int mouseRadius, const size_t cellSize);

int main()
{
    std::srand(std::time(nullptr));

    float fpsTimer = 0.0f;
    int frameCounter = 0;

    static const unsigned int width = 768u;
    static const unsigned int height = 432u;
    static const size_t cellSize = 6;

    sf::Clock clock;
    static const float G = 30;

    bool setup = true;
    World world(width, height, cellSize);

    auto window = sf::RenderWindow(sf::VideoMode({ width, height }), "Orbital Simulation");
    window.setFramerateLimit(60);

    enum simMode
    {
        Drawing,
        Velocity
    };

    simMode mode = Drawing;

    sf::Vector2i mousePos;
    int mouseRadius = 3;

    sf::Vector2i clickStartPos;

    sf::RectangleShape mousePreview(sf::Vector2f(cellSize, cellSize));
    mousePreview.setFillColor(sf::Color(255, 100, 100, 100));
    mousePreview.setOrigin(sf::Vector2f(cellSize / 2.0f, cellSize / 2.0f));

    bool modeActive = false;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        fpsTimer += dt;
        frameCounter++;

        if (fpsTimer >= 1.0f)
        {
            window.setTitle("Orbital Simulation - FPS: " + std::to_string(frameCounter));
            frameCounter = 0;
            fpsTimer -= 1.0f;
        }

        mousePos = sf::Mouse::getPosition(window);

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const auto* scroll = event->getIf<sf::Event::MouseWheelScrolled>())
            {
                if (scroll->delta > 0)
                {
                    mouseRadius = fmin(mouseRadius + 1, 7);
                }
                else if (scroll->delta < 0)
                {
                    mouseRadius = fmax(mouseRadius - 1, 0);
                }
            }

            if (const auto* mouse_press = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouse_press->button == sf::Mouse::Button::Left)
                {
                    clickStartPos = { mouse_press->position.x, mouse_press->position.y };

                    modeActive = true;
                }
            }

            if (const auto* mouse_release = event->getIf<sf::Event::MouseButtonReleased>())
            {
                if (mouse_release->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2i clickEndPos = { mouse_release->position.x, mouse_release->position.y };

                    modeActive = false;

                    switch (mode)
                    {
                    case Drawing:
                        break;

                    case Velocity:
                        addVelocity(world, clickStartPos, clickEndPos, mouseRadius, cellSize);
                        break;

                    default:
                        break;
                    }
                }
            }

            if (const auto* key = event->getIf<sf::Event::KeyPressed>())
            {
                modeActive = false;

                switch (key->scancode)
                {
                case sf::Keyboard::Scancode::Num1:
                    mode = Drawing;
                    break;

                case sf::Keyboard::Scancode::Num2:
                    mode = Velocity;
                    break;

                default:
                    break;
                }
            }
        }

        if (modeActive) {
            if (mode == Drawing) {
                drawCells(world, mousePos, mouseRadius, cellSize);
            }
        }
        else {
            world.applyGlobalForces(G);
            world.update(dt);
        }

        float sideLength = (mouseRadius * 2.0f + 1.0f) * cellSize;

        mousePreview.setSize(sf::Vector2f(sideLength, sideLength));

        mousePreview.setOrigin(sf::Vector2f(sideLength / 2.0f, sideLength / 2.0f));
        mousePreview.setPosition(sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)));

        window.clear(sf::Color::Black);

        world.drawWorld(window);
        window.draw(mousePreview);
        window.display();
    }
}

void drawCells(World& world, sf::Vector2i mousePos, int mouseRadius, const size_t cellSize) {
    int gridMouseX = mousePos.x / cellSize;
    int gridMouseY = mousePos.y / cellSize;

    for (int dy = -mouseRadius; dy <= mouseRadius; dy++) {
        for (int dx = -mouseRadius; dx <= mouseRadius; dx++) {
            int cellX = gridMouseX + dx;
            int cellY = gridMouseY + dy;

            if (world.inBounds(cellX, cellY)) {
                Cell* cell = world.getCell(cellX, cellY);
                if (cell->getType() == CellType::Empty) {
                    cell->setType(CellType::Rock);

                    cell->setVelocity({ 0.f, 0.f });
                    cell->setAcceleration({ 0.f, 0.f });
                    cell->setRealX(static_cast<float>(cellX));
                    cell->setRealY(static_cast<float>(cellY));
                }
            }
        }
    }
}

void addVelocity(World& world, sf::Vector2i clickStartPos, sf::Vector2i clickEndPos, int mouseRadius, const size_t cellSize) {
    sf::Vector2f throwVector(
        static_cast<float>(clickStartPos.x - clickEndPos.x),
        static_cast<float>(clickStartPos.y - clickEndPos.y)
    );

    sf::Vector2f initialVelocity = throwVector / 8.0f;

    int gridMouseX = clickStartPos.x / cellSize;
    int gridMouseY = clickStartPos.y / cellSize;

    for (int dy = -mouseRadius; dy <= mouseRadius; dy++)
    {
        for (int dx = -mouseRadius; dx <= mouseRadius; dx++)
        {
            int cellX = gridMouseX + dx;
            int cellY = gridMouseY + dy;

            if (world.inBounds(cellX, cellY))
            {
                Cell* cell = world.getCell(cellX, cellY);
                if (cell->getType() != CellType::Empty) {
                    world.applyInitialVelocity(cell, initialVelocity);
                }
            }
        }
    }
}