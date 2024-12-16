/// \file animation/script.hpp
/// \brief Defines the animation::script class.
#ifndef ANIMATION___SCRIPT_H
#define ANIMATION___SCRIPT_H

// animation
#include <animation/step.hpp>

/// \brief Contains all code for the Arduino animation library.
namespace animation {

/// \brief An animation script comprised of sequential animation steps.
class script
    : public animation::step
{
public:
    // CONSTRUCTORS
    /// \brief Creates a new script instance.
    script();

    // CONTROL
    void start() override;
    /// \brief Stops the script.
    /// \param reset Indicates if the script's reset_state method will be called.
    void stop(bool reset = false);

    // RUN
    bool run_once() override;
    /// \brief Runs the script (and blocks) until it is complete.
    /// \note start() does not need to be called before using this method.
    void run();

protected:
    // STEPS
    /// \brief Creates a step to run as part of the script.
    /// \param index The index of the step to create.
    /// \return A pointer to the step to run. NULLPTR if script is complete.
    virtual animation::step* create_step(size_t index) = 0;

    // CONTROL
    /// \brief Resets the state of all animated entities to their default values.
    virtual void reset_state();

private:
    // STEPS
    /// \brief The current step index being run.
    size_t m_step_index;
    /// \brief The current step being run.
    animation::step* m_step;
};

}

#endif