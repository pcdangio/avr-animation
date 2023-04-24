/// \file animation/step/digital/high.hpp
/// \brief Defines the animation::step::digital::high class.
#ifndef ANIMATION___STEP___DIGITAL___HIGH_H
#define ANIMATION___STEP___DIGITAL___HIGH_H

// animation
#include <animation/step/digital/level.hpp>

namespace animation {
namespace step {
namespace digital {

/// \brief An animation step that sets a digital output pin to high.
class high
    : public animation::step::digital::level
{
public:
    // CONSTRUCTORS
    /// \brief Creates a new digital high animation step instance.
    /// \param pin The digital output pin to set high.
    high(uint8_t pin);
};

}}}

#endif