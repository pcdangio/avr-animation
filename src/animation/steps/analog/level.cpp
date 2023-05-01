#include <animation/steps/analog/level.hpp>

using namespace animation::steps::analog;

// CONSTRUCTORS
level::level(uint8_t pin, uint8_t level)
    : m_pin(pin),
      m_level(level)
{}

// RUN
void level::start()
{
    // No start routine required.
}
bool level::run_once()
{
    // Set the analog level.
    analogWrite(level::m_pin, level::m_level);

    // Indicate step complete.
    return true;
}