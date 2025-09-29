#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    // Variables
    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 720;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Soul Harvest");

    // Create a graphical text to display
    const sf::Font font("fonts/AndreaTyped-Demo.otf");
    sf::Text title(font, "Soul Harvest", 42);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Clear screen
        window.clear();

        // Draw the title text
        sf::FloatRect rc = title.getLocalBounds();
        title.setOrigin(rc.getCenter());
        title.setPosition({ WINDOW_WIDTH / 2, 50 });
        window.draw(title);

        // Update the window
        window.display();
    }
}