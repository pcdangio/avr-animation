/// \file step.h
/// \brief Defines the Animation::Step class.
#ifndef STEP_H
#define STEP_H

namespace Animation
{

/// \brief A structure representing a single step in an Animation.
struct Step
{
    /// \brief The pin number that the step will execute on.
    int Pin;
    /// \brief The state that the step will set the pin to.
    int State;
    /// \brief The duration (in milliseconds) that the step will execute for.
    /// \note The duration can also be used to specify the time until the next step is executed.
    unsigned long Duration;

    /// \brief The default constructor sets all values to zero.
    Step();
    /// \brief Initializes a Step structure with the specified values.
    /// \param Pin The pin number that the step will execute on.
    /// \param State The state that the step will set the pin to.
    /// \param Duration The duration (in milliseconds) that the step will execute for.
    Step(int Pin, int State, unsigned long Duration);
};

}

#endif // STEP_H
