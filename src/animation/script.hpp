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

    // CONFIGURATION
    /// \brief Sets the step at a specified position in the script.
    /// \param index The index to assign the new step to.
    /// \param step The step instance to set.
    /// \return TRUE if the step was set successfully, FALSE if index out of range.
    bool set_step(size_t index, const std::shared_ptr<animation::step>& step);
    /// \brief Copies an existing step to another position in the script.
    /// \param index The index to assign the copied step to.
    /// \param copy_index The index of the step to copy from.
    /// \return TRUE if the step was set successfully, FALSE if either index is out of range.
    bool set_step(size_t index, size_t copy_index);
    /// \brief Clears a step at a desired position in the script.
    /// \param index The index of the step to clear.
    /// \return TRUE if the step was cleared successfully, FALSE if the index is out of range.
    bool clear_step(size_t index);
    /// \brief Clears all steps in the script.
    void clear();

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
    /// \brief The array of steps that make up the script.
    std::array<std::shared_ptr<animation::step>> m_steps;
    /// \brief The current step being executed in the script.
    std::iterator<std::shared_ptr<animation::step>> m_current_step;
};

}

#endif