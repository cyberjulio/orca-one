#include "Color.h"

#include <TFT_eSPI.h>
#include <sstream>
#include <tuple>

String Domain::Entities::colorSchemeToString(ColorScheme scheme)
{
    std::stringstream ss;
    switch (scheme)
    {
        case ColorScheme::Default:
            ss << "Default";
            break;
        case ColorScheme::FlipperZero:
            ss << "Flipper Zero";
            break;
        case ColorScheme::Bruce:
            ss << "Bruce";
            break;
        default:
            ss << "Color not found!";
            break;
    }
    return String(ss.str().c_str());
}

uint16_t Domain::Entities::colorToUInt16(Color color)
{
    switch (color)
    {
        case Color::Black:
            return TFT_BLACK;
        case Color::White:
            return TFT_WHITE;
        case Color::Orange:
            return TFT_ORANGE;
        case Color::Green:
            return TFT_GREEN;
        case Color::Yellow:
            return TFT_YELLOW;
        case Color::Marron:
            return TFT_MAROON;
        case Color::Purple:
            return TFT_PURPLE;
        default:
            return 0; // or any other default value
    }
}

Domain::Entities::ColorSchemeData Domain::Entities::colorSchemeToData(ColorScheme scheme)
{
    switch (scheme)
    {
        case ColorScheme::Default:
            return ColorSchemeData(Color::Green, Color::Black);
        case ColorScheme::FlipperZero:
            return ColorSchemeData(Color::Marron, Color::Orange);
        case ColorScheme::Bruce:
            return ColorSchemeData(Color::Purple, Color::Black);
        default:
            return ColorSchemeData(Color::Green, Color::Black);
    }
}
