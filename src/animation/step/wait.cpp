#include <animation/step/wait.hpp>

using namespace animation::step;

// CONSTRUCTORS
wait::wait(uint32_t duration)
    : m_duration(duration),
      m_start_time(0)
{}

// CONTROL
void wait::start()
{
    // Set start time.
    wait::m_start_time = millis();
}

// RUN
bool wait::run_once()
{
    // Check if duration has passed.
    return (millis() - wait::m_start_time) > wait::m_duration;
}