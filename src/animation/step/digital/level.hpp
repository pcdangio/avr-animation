/// \file animation/step/digital/level.hpp
/// \brief Defines the animation::step::digital::level class.
#ifndef ANIMATION___STEP___DIGITAL___LEVEL_H
#define ANIMATION___STEP___DIGITAL___LEVEL_H

// animation
#include <animation/step/step.hpp>

namespace animation {
namespace step {
/// \brief Contains all code for digital animation steps.
namespace digital {

/// \brief An animation step that sets the level of a digital output pin.
class level
    : public animation::step::step
{
public:
    // CONSTRUCTORS
    /// \brief Creates a new digital level step.
    /// \param pin The digital output pin to animate.
    /// \param level The output level of the pin for this animation step.
    level(uint8_t pin, bool level);

    // CONTROL
    void start() override;

    // RUN
    bool run_once() override;

private:
    // IO
    /// \brief The digital output pin to animate.
    const uint8_t m_pin;
    /// \brief The digital pin level to set for this step.
    const bool m_level;
};

}}}

#endif