#include "Upgrades.h"
#include "Player.h"
#include "Clock.h"

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
    Player player;                          // Load player data
    player.data.name = "Player";            // Give player default name
    player.data.soulsOwned = 0.0f;          // Ensure player's souls start at 0
    player.data.currentLevel = 0;
    player.data.totalSoulsEarned = 0.0f;
    player.data.totalSoulsSpent = 0.0f;
    player.data.totalUpgradesOwned = 0;

    // Game variables
    float costIncreasePercentage = 0.15f;   // The percentage that the cost of an upgrade goes up by each time it's purchased

    // Create the scythe upgrade
    Upgrade scythes;
    scythes.amountOwned = 0;
    scythes.cost = 15;
    scythes.soulsPerSec = 0.10f;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Soul Harvest");
    window.setMinimumSize(std::optional<sf::Vector2u>(sf::Vector2u(1280, 720)));
    window.setFramerateLimit(120);

    // Create title text
    sf::Text title(font, "SOUL HARVEST", 42);
    sf::FloatRect titleLb = title.getLocalBounds();
    title.setOrigin(titleLb.getCenter());
    title.setPosition({ WINDOW_WIDTH / 2, 50 });

    // Create player name text
    sf::Text playerNameLabel(font, player.data.name + "'s Soul Farm", 24);
    sf::FloatRect playerNameLb = playerNameLabel.getLocalBounds();
    playerNameLabel.setOrigin({ playerNameLb.size.x, 0 });
    playerNameLabel.setPosition({ WINDOW_WIDTH - 15, 15 });

    // Create time text
    sf::Text timeLabel(font, "Time Played: 00:00:00", 24);
    timeLabel.setPosition({ 15, 15 });

    // Create souls text
    sf::Text soulsLabel(font, "Souls: " + std::to_string(round(player.data.soulsOwned)), 24);
    soulsLabel.setPosition({ 15, 45 });

    // Create scythes text
    sf::Text scythesLabel(font, "Scythes: " + std::to_string(scythes.amountOwned) + "   Cost: " + std::to_string(scythes.cost), 24);
    scythesLabel.setPosition({ 15, 75 });

    // Create soul_button
    sf::CircleShape soulButton(100.f);
    soulButton.setFillColor(sf::Color::Cyan);
    sf::FloatRect soulButtonLb = soulButton.getLocalBounds();
    soulButton.setOrigin(soulButtonLb.getCenter());
    soulButton.setPosition({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });

    // State of soul_button
    bool soulButton_isOver = false;
    bool soulButton_isPressedInside = false;

    // Create scythes_button
    sf::RectangleShape scythesButton({ 100.0f, 50.0f });
    scythesButton.setFillColor(sf::Color::Cyan);
    sf::FloatRect scythesButtonLb = scythesButton.getLocalBounds();
    scythesButton.setOrigin(scythesButtonLb.getCenter());
    scythesButton.setPosition({ WINDOW_WIDTH / 2, 250 });

    // State of soul_button
    bool scythesButton_isOver = false;
    bool scythesButton_isPressedInside = false;

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
        }

        // Get the elapsed time since the last frame
        sf::Time tick_elapsed = tick.getElapsedTime();

        // Check if a full second has passed
        if (tick_elapsed.asSeconds() >= 1.0f) {
            // Increment the counter
            for (int i = 0; i < scythes.amountOwned; ++i)
                player.data.soulsOwned += scythes.soulsPerSec;
                player.data.totalSoulsEarned += scythes.soulsPerSec;

            // Restart the clock to time the next second
            tick.restart();
        }

        // Get the elapsed time since the clock started and calculate all the values for the timer.
        sf::Time elapsed = clock.getElapsedTime();

        float totalSeconds = elapsed.asSeconds();

        int hours = static_cast<int>(totalSeconds / 3600);
        totalSeconds -= hours * 3600;

        int minutes = static_cast<int>(totalSeconds / 60);
        totalSeconds -= minutes * 60;

        float seconds = totalSeconds;

        // Update the text with the new time string
        timeLabel.setString(updateTimeLabel(timeLabel, hours, minutes, seconds));

        // Mouse position
        auto mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

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
        if (soulButton.getGlobalBounds().contains(mousePos))
        {
            // When mouse is pressed
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) and soulButton_isPressedInside)
            {
                soulButton.setFillColor(sf::Color::Cyan);
            }
            else
            {
                soulButton.setFillColor(sf::Color(0, 170, 255));
            }

            // On mouse enter
            if (not soulButton_isOver)
            {
                std::cout << "Enter\n";
            }

            // On mouse press
            if (onMousePress)
            {
                std::cout << "Press\n";

                // Set pressed inside
                soulButton_isPressedInside = true;
            }

            // On mouse release
            if (onMouseRelease and soulButton_isPressedInside)
            {
                player.addSouls(1);
                std::cout << "Release\n";
            }

            // Set state
            soulButton_isOver = true;
        }
        else
        {
            soulButton.setFillColor(sf::Color::White);

            // On mouse leave
            if (soulButton_isOver)
            {
                std::cout << "Leave\n";
            }

            // Reset state
            soulButton_isOver = false;
        }

        // When mouse is over scythes_button
        if (scythesButton.getGlobalBounds().contains(mousePos))
        {
            // When mouse is pressed
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) and scythesButton_isPressedInside)
            {
                scythesButton.setFillColor(sf::Color::Cyan);
            }
            else
            {
                scythesButton.setFillColor(sf::Color(0, 170, 255));
            }

            // On mouse enter
            if (not scythesButton_isOver)
            {
                std::cout << "Enter\n";
            }

            // On mouse press
            if (onMousePress)
            {
                std::cout << "Press\n";

                // Set pressed inside
                scythesButton_isPressedInside = true;
            }

            // On mouse release
            if (onMouseRelease and scythesButton_isPressedInside)
            {
                if (player.data.soulsOwned >= scythes.cost)
                {
                    player.data.soulsOwned -= scythes.cost;
                    scythes.cost = std::round(scythes.cost * (1 + costIncreasePercentage));
                    scythes.amountOwned += 1;
                    player.data.totalUpgradesOwned += 1;
                    scythesLabel.setString("Scythes: " + std::to_string(scythes.amountOwned) + "   Cost: " + std::to_string(scythes.cost));
                }
                std::cout << "Release\n";
            }

            // Set state
            scythesButton_isOver = true;
        }
        else
        {
            scythesButton.setFillColor(sf::Color::White);

            // On mouse leave
            if (scythesButton_isOver)
            {
                std::cout << "Leave\n";
            }

            // Reset state
            scythesButton_isOver = false;
        }

        // Reset pressed inside
        if (not isMousePressed)
        {
            soulButton_isPressedInside = false;
        }

        // Update souls label every frame
        soulsLabel.setString("Souls: " + std::to_string(static_cast<int>(player.data.soulsOwned)));

        // Clear screen
        window.clear(sf::Color(20, 20, 20));

        // Draw the screen elements
        window.draw(title);
        window.draw(playerNameLabel);
        window.draw(timeLabel);
        window.draw(soulsLabel);
        window.draw(scythesLabel);
        window.draw(soulButton);
        window.draw(scythesButton);

        // Update the window
        window.display();
    }
}