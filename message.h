#pragma once

#include <string>
#include <vector>
#include <cstdint>

class Message {
private:
    static bool GetBit(std::uint8_t value, unsigned int index);
    static std::uint8_t SetBit(std::uint8_t value, unsigned int index);
    static std::uint8_t ClearBit(std::uint8_t value, unsigned int index);

public:
    static void displayTestBits();
};


