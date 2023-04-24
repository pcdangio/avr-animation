/// \file animation/step/analog/level.hpp
/// \brief Defines the animation::step::analog::level class.
#ifndef ANIMATION___STEP___ANALOG___LEVEL_H
#define ANIMATION___STEP___ANALOG___LEVEL_H

// animation
#include <animation/step/step.hpp>

namespace animation {
namespace step {
/// \brief Contains all code for analog animation steps.
namespace analog {

/// \brief An animation step that sets the level of an analog output pin.
class level
    : public animation::step::step
{
public:
    // CONSTRUCTORS
    /// \brief Creates a new analog level step.
    /// \param pin The analog output pin to animate.
    /// \param level The output level of the pin for this animation step.
    level(uint8_t pin, uint8_t level);

    // CONTROL
    void start() override;

    // RUN
    bool run_once() override;

private:
    // IO
    /// \brief The analog output pin to animate.
    const uint8_t m_pin;
    /// \brief The analog pin level to set for this step.
    const uint8_t m_level;
};

}}}

#endif