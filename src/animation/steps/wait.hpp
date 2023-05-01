/// \file animation/steps/wait.hpp
/// \brief Defines the animation::steps::wait class.
#ifndef ANIMATION___STEPS___WAIT_H
#define ANIMATION___STEPS___WAIT_H

// animation
#include <animation/step.hpp>

namespace animation {
/// \brief Contains all code for predefined animation steps.
namespace steps {

/// \brief An animation step that waits for a specified duration.
class wait
    : public animation::step
{
public:
    // CONSTRUCTORS
    /// \brief Creates a new wait animation step instance.
    /// \param duration The duration of time to wait, in milliseconds.
    wait(uint32_t duration);
    
    // RUN
    void start() override;
    bool run_once() override;

private:
    /// \brief The duration to wait, in milliseconds.
    const uint32_t m_duration;
    /// \brief The timestamp that this step was started at.
    uint32_t m_start_time;
};

}}

#endif