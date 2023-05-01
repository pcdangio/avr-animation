#include <animation/steps/wait.hpp>

using namespace animation::steps;

// CONSTRUCTORS
wait::wait(uint32_t duration)
    : m_duration(duration),
      m_start_time(0)
{}

// RUN
void wait::start()
{
    // Set start time.
    wait::m_start_time = millis();
}
bool wait::run_once()
{
    // Check if duration has passed.
    return (millis() - wait::m_start_time) > wait::m_duration;
}