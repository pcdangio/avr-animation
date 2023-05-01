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
    ~script();

    // RUN
    void start() override;
    bool run_once() override;
    /// \brief Runs the script (and blocks) until it is complete.
    /// \note start() does not need to be called before using this method.
    void run();

    // PROPERTIES
    /// \brief Gets the number of steps in the script.
    /// \return The number of steps in the script.
    size_t step_count() const;

protected:
    // CONFIGURATION
    /// \brief Builds the script using a sequence of steps.
    /// \param steps The step sequence in array form (class will assume ownership).
    /// \param count The number of steps in the step array.
    void build(animation::step** steps, size_t count);
    /// \brief Clears all steps in the script.
    void clear();

private:
    // STEPS
    /// \brief A pointer to the beginning of the steps array.
    animation::step** m_steps_begin;
    /// \brief A pointer to the end of the steps array.
    animation::step** m_steps_end;
    /// \brief A pointer to the current position in the step array.
    animation::step** m_current_step;
};

}

#endif