#include <animation/steps/analog/function.hpp>

using namespace animation::steps::analog;

// CONSTRUCTORS
function::function(uint8_t pin, float update_rate)
    : m_pin(pin),
      m_update_period(1000.0 / update_rate),
      m_start_time(0),
      m_update_time(0)
{}

// RUN
void function::start()
{
    // Capture the start time.
    function::m_start_time = millis();

    // Set last update time to the past so an update is triggered on first run.
    function::m_update_time = function::m_start_time - function::m_update_period;
}
bool function::run_once()
{
    // Get current time.
    uint32_t current_time = millis();

    // Check if update necessary.
    if(current_time - function::m_update_time >= function::m_update_period)
    {
        // Calculate the current time, in seconds.
        float time = static_cast<float>(current_time - function::m_start_time) / 1000.0;

        // Run the level function to get the output level and completion status.
        bool complete;
        uint8_t level = function::level(time, complete);

        // Set the analog output level.
        analogWrite(function::m_pin, level);

        // Update last update time.
        function::m_update_time = current_time;

        // Indicate completion status.
        return complete;
    }

    return false;
}