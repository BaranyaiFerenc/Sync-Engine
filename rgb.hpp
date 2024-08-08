#ifndef RGB_HPP
#define RGB_HPP


#include <iostream>
#include <iomanip>
#include <sstream>

namespace RGB
{
    std::string rgbToHex(int r, int g, int b) {
        std::stringstream ss;
        ss << "#" << std::hex << std::setw(2) << std::setfill('0') << r
        << std::setw(2) << std::setfill('0') << g
        << std::setw(2) << std::setfill('0') << b;
        return ss.str();
    }
}

#endif