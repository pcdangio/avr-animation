/// \file animation/steps/analog/function.hpp
/// \brief Defines the animation::step::analog::function class.
#ifndef ANIMATION___STEPS___ANALOG___FUNCTION_H
#define ANIMATION___STEPS___ANALOG___FUNCTION_H

// animation
#include <animation/step.hpp>

namespace animation {
namespace steps {
/// \brief Contains all code for analog animation steps.
namespace analog {

/// \brief An animation step that sets an analog output pin according to a user defined function.
class function
    : public animation::step
{
public:
    // CONSTRUCTORS
    /// \brief Creates a new analog function step.
    /// \param pin The analog output pin to animate.
    /// \param update_rate The rate (Hz) that the function should update the output level at.
    function(uint8_t pin, float update_rate);
    
    // RUN
    void start() override;
    bool run_once() override;

protected:
    // FUNCTION
    /// \brief The function that determines the output level as a function of time.
    /// \param time The current time (s) since the step started.
    /// \param complete OUTPUT Indicates if the function has completed.
    virtual uint8_t level(float time, bool& complete) = 0;

private:
    // IO
    /// \brief The analog output pin to animate.
    const uint8_t m_pin;
    
    // TIME
    /// \brief The period (ms) of the output update rate.
    const uint32_t m_update_period;
    /// \brief The timestamp (ms) that the step was started at.
    uint32_t m_start_time;
    /// \brief The timestamp (ms) that the level was last updated at.
    uint32_t m_update_time;
};

}}}

#endif