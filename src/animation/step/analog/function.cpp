#include <animation/step/analog/function.hpp>

using namespace animation::step::analog;

// CONSTRUCTORS
function::function(uint8_t pin)
    : m_pin(pin),
      m_start_time(0)
{}

// CONTROL
void function::start()
{
    // Capture the start time.
    function::m_start_time = millis();
}

// RUN
bool function::run_once()
{
    // Calculate the current time, in seconds.
    float time = static_cast<float>(millis() - function::m_start_time) / 1000.0;

    // Run the level function to get the output level and completion status.
    bool complete;
    uint8_t level = function::level(time, complete);

    // Set the analog output level.
    analogWrite(function::m_pin, level);

    // Indicate completion status.
    return complete;
}