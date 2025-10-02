#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

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