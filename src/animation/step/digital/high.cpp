#include <animation/step/digital/high.hpp>

using namespace animation::step::digital;

high::high(uint8_t pin)
    : animation::step::digital::level(pin, true)
{}