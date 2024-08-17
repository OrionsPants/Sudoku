#pragma once

#include <SFML/Graphics.hpp>

#include <cstdint>

// uints
using uint = unsigned int;
using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

struct ColorSet
{
	sf::Color fg;
	sf::Color bg;
	sf::Color border;
	sf::Color on_focus;
};

namespace color
{
const auto black = sf::Color(0, 0, 0, 255);
const auto white = sf::Color(255, 255, 255, 255);
const auto light_grey = sf::Color(150, 150, 150, 255);
const auto shaded = sf::Color(175, 175, 175, 255);
const auto grey = sf::Color(125, 125, 125, 255);
const auto crimson = sf::Color(128, 41, 32, 255);
} // namespace color

enum class GridState{
    Solved = 0,
    Solveable,
    Error,
    Unknown
};