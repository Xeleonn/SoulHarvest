#include "Upgrades.h"
#include "Player.h"
#include "Clock.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <format>
#include <cmath>

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

    // State of mouse
    bool isMousePressed = false;

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

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Soul Harvest");
    window.setMinimumSize(std::optional<sf::Vector2u>(sf::Vector2u(1280, 720)));
    window.setFramerateLimit(120);

    // Create title text
    sf::Text title(font, "SOUL HARVEST", 36);
    sf::FloatRect titleLb = title.getLocalBounds();
    title.setOrigin(titleLb.getCenter());
    title.setPosition({ WINDOW_WIDTH / 2, 40 });

    // Create player name text
    sf::Text playerNameLabel(font, player.data.name + "'s Soul Farm", 24);
    sf::FloatRect playerNameLb = playerNameLabel.getLocalBounds();
    playerNameLabel.setOrigin({ playerNameLb.size.x, 0 });
    playerNameLabel.setPosition({ WINDOW_WIDTH - 15, 15 });

    // Create time text
    sf::Text timeLabel(font, "Time Played:", 24);
    timeLabel.setPosition({ 15, 15 });



    // Create soulButton
    sf::CircleShape soulButton(100.f);
    soulButton.setFillColor(sf::Color::Cyan);
    sf::FloatRect soulButtonLb = soulButton.getLocalBounds();
    soulButton.setOrigin(soulButtonLb.getCenter());
    soulButton.setPosition({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });

    // State of soulButton
    bool soulButton_isOver = false;
    bool soulButton_isPressedInside = false;

    // Create souls text
    sf::Text soulsLabel(font, "Souls: " + std::to_string(round(player.data.soulsOwned)), 24);
    soulsLabel.setPosition({ 15, 45 });



    // Create the Scythe upgrade
    Upgrade scythe;
    scythe.amountOwned = 0;
    scythe.cost = 15;
    scythe.soulsPerSec = 0.10f;

    // Create scytheButton
    sf::RectangleShape scytheButton({ 50.0f, 20.0f });
    scytheButton.setFillColor(sf::Color::Cyan);
    sf::FloatRect scytheButtonLb = scytheButton.getLocalBounds();
    scytheButton.setPosition({ 15, 80 });

    // Create scythe text
    sf::Text scytheLabel(font, "Scythes: " + std::to_string(scythe.amountOwned) + "     Cost: " + std::to_string(scythe.cost), 24);
    scytheLabel.setPosition({ 75, 75 });

    // State of scytheButton
    bool scytheButton_isOver = false;
    bool scytheButton_isPressedInside = false;



    // Create the Gravedigger upgrade
    Upgrade gravedigger;
    gravedigger.amountOwned = 0;
    gravedigger.cost = 100;
    gravedigger.soulsPerSec = 1.0f;

    // Create gravediggerButton
    sf::RectangleShape gravediggerButton({ 50.0f, 20.0f });
    gravediggerButton.setFillColor(sf::Color::Cyan);
    sf::FloatRect gravediggerButtonLb = gravediggerButton.getLocalBounds();
    gravediggerButton.setPosition({ 15, 110 });

    // Create Gravedigger text
    sf::Text gravediggerLabel(font, "Gravediggers: " + std::to_string(gravedigger.amountOwned) + "     Cost: " + std::to_string(gravedigger.cost), 24);
    gravediggerLabel.setPosition({ 75, 105 });

    // State of gravediggerButton
    bool gravediggerButton_isOver = false;
    bool gravediggerButton_isPressedInside = false;



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
            if (scythe.amountOwned > 0)
            {
                for (int i = 0; i < scythe.amountOwned; ++i)
                {
                    player.data.soulsOwned += scythe.soulsPerSec;
                    player.data.totalSoulsEarned += scythe.soulsPerSec;
                }
            }

            if (gravedigger.amountOwned > 0)
            {
                for (int i = 0; i < gravedigger.amountOwned; ++i)
                {
                    player.data.soulsOwned += gravedigger.soulsPerSec;
                    player.data.totalSoulsEarned += gravedigger.soulsPerSec;
                }
            }

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



        // When mouse is over soulButton
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



        // When mouse is over scytheButton
        if (scytheButton.getGlobalBounds().contains(mousePos))
        {
            // When mouse is pressed
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) and scytheButton_isPressedInside)
            {
                scytheButton.setFillColor(sf::Color::Cyan);
            }
            else
            {
                scytheButton.setFillColor(sf::Color(0, 170, 255));
            }

            // On mouse enter
            if (not scytheButton_isOver)
            {
                std::cout << "Enter\n";
            }

            // On mouse press
            if (onMousePress)
            {
                std::cout << "Press\n";

                // Set pressed inside
                scytheButton_isPressedInside = true;
            }

            // On mouse release
            if (onMouseRelease and scytheButton_isPressedInside)
            {
                if (player.data.soulsOwned >= scythe.cost)
                {
                    player.subtractSouls(scythe.cost);
                    scythe.cost = std::round(scythe.cost * (1 + costIncreasePercentage));
                    scythe.addAmountOwned(1);
                    player.data.totalUpgradesOwned += 1;
                    scytheLabel.setString("Scythe: " + std::to_string(scythe.amountOwned) + "     Cost: " + std::to_string(scythe.cost));
                }
                std::cout << "Release\n";
            }

            // Set state
            scytheButton_isOver = true;
        }
        else
        {
            scytheButton.setFillColor(sf::Color::White);

            // On mouse leave
            if (scytheButton_isOver)
            {
                std::cout << "Leave\n";
            }

            // Reset state
            scytheButton_isOver = false;
        }



        // When mouse is over gravediggerButton
        if (gravediggerButton.getGlobalBounds().contains(mousePos))
        {
            // When mouse is pressed
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) and gravediggerButton_isPressedInside)
            {
                gravediggerButton.setFillColor(sf::Color::Cyan);
            }
            else
            {
                gravediggerButton.setFillColor(sf::Color(0, 170, 255));
            }

            // On mouse enter
            if (not gravediggerButton_isOver)
            {
                std::cout << "Enter\n";
            }

            // On mouse press
            if (onMousePress)
            {
                std::cout << "Press\n";

                // Set pressed inside
                gravediggerButton_isPressedInside = true;
            }

            // On mouse release
            if (onMouseRelease and gravediggerButton_isPressedInside)
            {
                if (player.data.soulsOwned >= gravedigger.cost)
                {
                    player.subtractSouls(gravedigger.cost);
                    gravedigger.cost = std::round(gravedigger.cost * (1 + costIncreasePercentage));
                    gravedigger.addAmountOwned(1);
                    player.data.totalUpgradesOwned += 1;
                    gravediggerLabel.setString("Gravediggers: " + std::to_string(gravedigger.amountOwned) + "     Cost: " + std::to_string(gravedigger.cost));
                }
                std::cout << "Release\n";
            }

            // Set state
            gravediggerButton_isOver = true;
        }
        else
        {
            gravediggerButton.setFillColor(sf::Color::White);

            // On mouse leave
            if (gravediggerButton_isOver)
            {
                std::cout << "Leave\n";
            }

            // Reset state
            gravediggerButton_isOver = false;
        }



        // Reset pressed inside
        if (not isMousePressed)
        {
            soulButton_isPressedInside = false;
            scytheButton_isPressedInside = false;
            gravediggerButton_isPressedInside = false;
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
        window.draw(soulButton);
        window.draw(scytheLabel);
        window.draw(scytheButton);
        window.draw(gravediggerLabel);
        window.draw(gravediggerButton);

        // Update the window
        window.display();
    }
}