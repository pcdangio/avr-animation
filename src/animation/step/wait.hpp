/// \file animation/step/wait.hpp
/// \brief Defines the animation::step::wait class.
#ifndef ANIMATION___STEP___WAIT_H
#define ANIMATION___STEP___WAIT_H

// animation
#include <animation/step/step.hpp>

namespace animation {
namespace step {

/// \brief An animation step that waits for a specified duration.
class wait
    : public animation::step::step
{
public:
    // CONSTRUCTORS
    /// \brief Creates a new wait animation step instance.
    /// \param duration The duration of time to wait, in milliseconds.
    wait(uint32_t duration);

    // CONTROL
    void start() override;

    // RUN
    bool run_once() override;

private:
    /// \brief The duration to wait, in milliseconds.
    const uint32_t m_duration;
    /// \brief The timestamp that this step was started at.
    uint32_t m_start_time;
};

}}

#endif