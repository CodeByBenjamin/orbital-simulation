#include <SFML/Graphics.hpp>
#include "World.h"
#include "Cell.h"

int main()
{
    static const unsigned int width = 800u;
    static const unsigned int height = 600u;

    const size_t cellSize = 4;

    bool setup = true;
    World world(width, height, cellSize);

    auto window = sf::RenderWindow(sf::VideoMode({ width, height }), "Orbital Simulation");
    window.setFramerateLimit(60);

    sf::Vector2i mousePos;

    while (window.isOpen())
    {
        while (window.isOpen())
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                {
                    window.close();
                }
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                mousePos = sf::Mouse::getPosition(window);

                for (int y = -20; y < 20; y++)
                {
                    for (int x = -20; x < 20; x++)
                    {
                        int cellX = (static_cast<int>(mousePos.x) + x) / cellSize;
                        int cellY = (static_cast<int>(mousePos.y) + y) / cellSize;

                        if (cellX >= 0 && cellX < static_cast<int>(width / cellSize) &&
                            cellY >= 0 && cellY < static_cast<int>(height / cellSize))
                        {
                            Cell& cell = world.getCell(cellX, cellY);
                            cell.setType(CellType::Rock);
                        }
                    }
                }

            }

            window.clear(sf::Color::Black); 
            world.DrawWorld(window);
            window.display();
        }
    }
}
