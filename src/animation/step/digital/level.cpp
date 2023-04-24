#include <animation/step/digital/level.hpp>

using namespace animation::step::digital;

// CONSTRUCTORS
level::level(uint8_t pin, bool level)
    : m_pin(pin),
      m_level(level)
{}

// CONTROL
void level::start()
{
    // No start routine required.
}

// RUN
bool level::run_once()
{
    // Set the digital level.
    digitalWrite(level::m_pin, level::m_level);

    // Indicate step complete.
    return true;
}