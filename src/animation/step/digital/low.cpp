#include <animation/step/digital/low.hpp>

using namespace animation::step::digital;

low::low(uint8_t pin)
    : animation::step::digital::level(pin, false)
{}