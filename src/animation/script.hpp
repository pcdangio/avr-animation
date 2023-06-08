/// \file animation/script.hpp
/// \brief Defines the animation::script class.
#ifndef ANIMATION___SCRIPT_H
#define ANIMATION___SCRIPT_H

// animation
#include <animation/step.hpp>

// std
#include <std.hpp>

/// \brief Contains all code for the Arduino animation library.
namespace animation {

/// \brief An animation script comprised of sequential animation steps.
class script
    : public animation::step
{
public:
    // CONSTRUCTORS
    /// \brief Creates a new script instance.
    /// \param step_count The number of steps in the script.
    script(size_t step_count);

    // STEPS
    /// \brief The array of steps that make up the script.
    std::array<std::shared_ptr<animation::step>> steps;

    // CONTROL
    void start() override;
    /// \brief Stops the script.
    /// \param reset Indicates if animated entities should be reset to their default values.
    void stop(bool reset = false);

    // RUN
    bool run_once() override;
    /// \brief Runs the script (and blocks) until it is complete.
    /// \note start() does not need to be called before using this method.
    void run();

    // PROPERTIES
    /// \brief Get the number of steps in the script.
    /// \return The number of steps.
    size_t step_count() const;

protected:
    // CONTROL
    /// \brief Resets the state of all animated entities to their default values.
    virtual void reset_state();

private:
    // STEPS
    /// \brief The current step being executed in the script.
    std::iterator<std::shared_ptr<animation::step>> m_current_step;
};

}

#endif