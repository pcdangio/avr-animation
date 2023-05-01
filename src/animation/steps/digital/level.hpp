/// \file animation/steps/digital/level.hpp
/// \brief Defines the animation::steps::digital::level class.
#ifndef ANIMATION___STEPS___DIGITAL___LEVEL_H
#define ANIMATION___STEPS___DIGITAL___LEVEL_H

// animation
#include <animation/step.hpp>

namespace animation {
namespace steps {
/// \brief Contains all code for digital animation steps.
namespace digital {

/// \brief An animation step that sets the level of a digital output pin.
class level
    : public animation::step
{
public:
    // CONSTRUCTORS
    /// \brief Creates a new digital level step.
    /// \param pin The digital output pin to animate.
    /// \param level The output level of the pin for this animation step.
    level(uint8_t pin, bool level);
    
    // RUN
    void start() override;
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