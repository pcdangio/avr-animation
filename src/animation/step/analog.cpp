#include <animation/step/analog.hpp>

using namespace animation::step;

// CONSTRUCTORS
analog::analog(uint8_t pin, uint8_t duty_cycle, uint32_t duration)
    : animation::step::step(duration),
      m_pin(pin),
      m_duty_cycle(duty_cycle)
{}

// EXECUTION
void analog::execute()
{
    // Write to analog pin.
    analogWrite(analog::m_pin, analog::m_duty_cycle);
}