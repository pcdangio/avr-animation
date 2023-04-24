/// \file animation/step/digital/low.hpp
/// \brief Defines the animation::step::digital::low class.
#ifndef ANIMATION___STEP___DIGITAL___LOW_H
#define ANIMATION___STEP___DIGITAL___LOW_H

// animation
#include <animation/step/digital/level.hpp>

namespace animation {
namespace step {
namespace digital {

/// \brief An animation step that sets a digital output pin to low.
class low
    : public animation::step::digital::level
{
public:
    // CONSTRUCTORS
    /// \brief Creates a new digital low animation step instance.
    /// \param pin The digital output pin to set low. 
    low(uint8_t pin);
};

}}}

#endif