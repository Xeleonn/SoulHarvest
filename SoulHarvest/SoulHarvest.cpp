#include "upgrades.h"
#include "player.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <format>
#include <cmath>

std::string updateTimeLabel(sf::Text label, int hours, int minutes, float seconds);

int main()
{
    // Initializes the clock used for keeping time played
    sf::Clock clock;
    sf::Clock tick;

    // The size of the window
    const int WINDOW_WIDTH = 1920;
    const int WINDOW_HEIGHT = 1080;

    // Sets the font for all of the text
    const sf::Font font("fonts/KONSTANTINE.ttf");

    // Player data
    PlayerData player;                      // Load player data
    player.name = "Player";                 // Give player default name
    player.soulsOwned = 0;                  // Ensure player's souls start at 0
    player.currentLevel = 0;
    player.totalSoulsEarned = 0;
    float clickMultiplier = 1.0f;           // The multiplier for souls earned by clicking
    float costIncreasePercentage = 0.15f;   // The percentage that the cost of an upgrade goes up by each time it's purchased

    // Create the scythe upgrade
    Upgrade scythes;
    scythes.amountOwned = 0;
    scythes.cost = 15;
    scythes.soulsPerSec = 1;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Soul Harvest");
    window.setMinimumSize(std::optional<sf::Vector2u>(sf::Vector2u(1280, 720)));

    // Create title text
    sf::Text title(font, "SOUL HARVEST", 42);
    sf::FloatRect title_lb = title.getLocalBounds();
    title.setOrigin(title_lb.getCenter());
    title.setPosition({ WINDOW_WIDTH / 2, 50 });

    // Create time text
    sf::Text time_label(font, "Time Played: 00:00:00", 24);
    time_label.setPosition({ 15, 15 });

    // Create souls text
    sf::Text souls_label(font, "Souls: " + std::to_string(souls), 24);
    souls_label.setPosition({ 15, 45 });

    // Create scythes text
    sf::Text scythes_label(font, "Scythes: " + std::to_string(scythes.amountOwned) + "   Cost: " + std::to_string(scythes.cost), 24);
    scythes_label.setPosition({ 15, 75 });

    // Create soul_button
    sf::CircleShape soul_button(100.f);
    soul_button.setFillColor(sf::Color::Cyan);
    sf::FloatRect soul_button_lb = soul_button.getLocalBounds();
    soul_button.setOrigin(soul_button_lb.getCenter());
    soul_button.setPosition({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });

    // State of soul_button
    bool soul_button_isOver = false;
    bool soul_button_isPressedInside = false;

    // Create scythes_button
    sf::RectangleShape scythes_button({ 100.0f, 50.0f });
    scythes_button.setFillColor(sf::Color::Cyan);
    sf::FloatRect scythes_button_lb = scythes_button.getLocalBounds();
    scythes_button.setOrigin(scythes_button_lb.getCenter());
    scythes_button.setPosition({ WINDOW_WIDTH / 2, 250 });

    // State of soul_button
    bool scythes_button_isOver = false;
    bool scythes_button_isPressedInside = false;

    // State of mouse
    bool isMousePressed = false;

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();

            // Resize window
            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                std::cout << "new width: " << resized->size.x << std::endl;
                std::cout << "new height: " << resized->size.y << std::endl;
            }
        }

        // Get the elapsed time since the last frame
        sf::Time tick_elapsed = tick.getElapsedTime();

        // Check if a full second has passed
        if (tick_elapsed.asSeconds() >= 1.0f) {
            // Increment the counter
            for (int i = 0; i < scythes.amountOwned; ++i)
                souls += scythes.soulsPerSec;

            // Restart the clock to time the next second
            tick.restart();
        }

        // Get the elapsed time since the clock started and calculate all the values for the timer.
        sf::Time elapsed = clock.getElapsedTime();

        float total_seconds = elapsed.asSeconds();

        int hours = static_cast<int>(total_seconds / 3600);
        total_seconds -= hours * 3600;

        int minutes = static_cast<int>(total_seconds / 60);
        total_seconds -= minutes * 60;

        float seconds = total_seconds;

        // Update the text with the new time string
        time_label.setString(updateTimeLabel(time_label, hours, minutes, seconds));

        // Mouse position
        auto mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));

        // Mouse state
        bool onMousePress = false;
        bool onMouseRelease = false;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            if (not isMousePressed)
                onMousePress = true;
            isMousePressed = true;
        }
        else
        {
            if (isMousePressed)
                onMouseRelease = true;
            isMousePressed = false;
        }

        // When mouse is over soul_button
        if (soul_button.getGlobalBounds().contains(mouse_pos))
        {
            // When mouse is pressed
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) and soul_button_isPressedInside)
            {
                soul_button.setFillColor(sf::Color::Cyan);
            }
            else
            {
                soul_button.setFillColor(sf::Color(0, 170, 255));
            }

            // On mouse enter
            if (not soul_button_isOver)
            {
                std::cout << "Enter\n";
            }

            // On mouse press
            if (onMousePress)
            {
                std::cout << "Press\n";

                // Set pressed inside
                soul_button_isPressedInside = true;
            }

            // On mouse release
            if (onMouseRelease and soul_button_isPressedInside)
            {
                souls += 1 * clickMultiplier;
                std::cout << "Release\n";
            }

            // Set state
            soul_button_isOver = true;
        }
        else
        {
            soul_button.setFillColor(sf::Color::White);

            // On mouse leave
            if (soul_button_isOver)
            {
                std::cout << "Leave\n";
            }

            // Reset state
            soul_button_isOver = false;
        }

        // When mouse is over scythes_button
        if (scythes_button.getGlobalBounds().contains(mouse_pos))
        {
            // When mouse is pressed
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) and scythes_button_isPressedInside)
            {
                scythes_button.setFillColor(sf::Color::Cyan);
            }
            else
            {
                scythes_button.setFillColor(sf::Color(0, 170, 255));
            }

            // On mouse enter
            if (not scythes_button_isOver)
            {
                std::cout << "Enter\n";
            }

            // On mouse press
            if (onMousePress)
            {
                std::cout << "Press\n";

                // Set pressed inside
                scythes_button_isPressedInside = true;
            }

            // On mouse release
            if (onMouseRelease and scythes_button_isPressedInside)
            {
                if (souls >= scythes.cost)
                {
                    souls -= scythes.cost;
                    scythes.cost = std::round(scythes.cost * (1 + costIncreasePercentage));
                    scythes.amountOwned += 1;
                    scythes_label.setString("Scythes: " + std::to_string(scythes.amountOwned) + "   Cost: " + std::to_string(scythes.cost));
                }
                std::cout << "Release\n";
            }

            // Set state
            scythes_button_isOver = true;
        }
        else
        {
            scythes_button.setFillColor(sf::Color::White);

            // On mouse leave
            if (scythes_button_isOver)
            {
                std::cout << "Leave\n";
            }

            // Reset state
            scythes_button_isOver = false;
        }

        // Reset pressed inside
        if (not isMousePressed)
        {
            soul_button_isPressedInside = false;
        }

        // Update souls label every frame.
        souls_label.setString("Souls: " + std::to_string(souls));

        // Clear screen
        window.clear(sf::Color(20, 20, 20));

        // Draw the screen elements
        window.draw(title);
        window.draw(time_label);
        window.draw(souls_label);
        window.draw(scythes_label);
        window.draw(soul_button);
        window.draw(scythes_button);

        // Update the window
        window.display();
    }
}

std::string updateTimeLabel(sf::Text label, int hours, int minutes, float seconds)
{
    // Format the time played to be human-readable.
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << hours << ":"
        << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::fixed << std::setprecision(2) << std::setw(5) << std::setfill('0') << seconds;

    std::string timeString = "Time Played: " + ss.str();

    return timeString;
}