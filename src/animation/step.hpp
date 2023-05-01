/// \file animation/step.hpp
/// \brief Defines the animation::step class.
#ifndef ANIMATION___STEP_H
#define ANIMATION___STEP_H

// arduino
#include <Arduino.h>

namespace animation {

/// \brief A base representation of a step within an animation.
struct step
{
    // RUN
    /// \brief Starts the step's animation.
    /// \note This must be called before run_once().
    virtual void start();
    /// \brief Runs a single iteration of the animation step.
    /// \return TRUE if the step has completed, otherwise FALSE.
    virtual bool run_once();
};

}

#endif