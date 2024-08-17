#pragma once

#include <SFML/Graphics.hpp>

#include "types.h"

#include <random>

template<typename T>
T GetRandomInRange(const T min, const T max){
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(min, max);

    return static_cast<T>(distr(gen));
}

sf::Color GetRandomColor();