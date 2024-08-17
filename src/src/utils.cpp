#include <utils.h>


sf::Color GetRandomColor(){
    return sf::Color(GetRandomInRange<uint8>(0,255), GetRandomInRange<uint8>(0,255), GetRandomInRange<uint8>(0,255), 255);
}