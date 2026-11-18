#include "message.h"
#include <iostream>

bool Message::GetBit(std::uint8_t value, unsigned int index) {
    return (value >> index) & 1u;
}

std::uint8_t Message::SetBit(std::uint8_t value, unsigned int index) {
    return value | (1u << index);
}

std::uint8_t Message::ClearBit(std::uint8_t value, unsigned int index) {
    return value & ~(1u << index);
}

void Message::displayTestBits() {
    // Correspondance exacte d'après le tableau pour le mot "test" :
    // 't' : 01110100[cite: 2]
    // 'e' : 01100101[cite: 2]
    // 's' : 01110011[cite: 2]
    // 't' : 01110100[cite: 2]
    std::vector<std::uint8_t> message_bytes = { 't', 'e', 's', 't' };

    for (std::uint8_t val : message_bytes) {
        std::cout  << static_cast<char>(val);
        for (int i = 7; i >= 0; --i) {

        }

    }
}




