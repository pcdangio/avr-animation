/// \file animation/step/analog.hpp
/// \brief Defines the animation::step::analog class.
#ifndef ANIMATION___STEP___ANALOG_H
#define ANIMATION___STEP___ANALOG_H

// animation
#include <animation/step/step.hpp>

namespace animation {
namespace step {

/// \brief An analog output animation step.
class analog
    : public animation::step::step
{
public:
    // CONSTRUCTORS
    /// \brief Creates a new analog output step.
    /// \param pin The analog output pin to animate.
    /// \param duty_cycle The duty cycle of the pin for this animation step.
    /// \param duration The duration of this step, in milliseconds.
    analog(uint8_t pin, uint8_t duty_cycle, uint32_t duration);

    // EXECUTION
    void execute() override;

private:
    // FIELDS
    /// \brief The analog output pin to animate.
    uint8_t m_pin;
    /// \brief The duty cycle of the pin for this animation step.
    uint8_t m_duty_cycle;
};

}}

#endif