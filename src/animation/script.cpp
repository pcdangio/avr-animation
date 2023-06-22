#include <animation/script.hpp>

using namespace animation;

// CONSTRUCTORS
script::script()
    : m_step_index(0),
      m_step(nullptr)
{}

// CONTROL
void script::start()
{
    // Reset the current step index to the beginning.
    script::m_step_index = 0;

    // Get the step for this index.
    script::m_step.reset(create_step(script::m_step_index));

    // Start step if it's valid.
    if(script::m_step.valid())
    {
        script::m_step->start();
    }
}
void script::stop(bool reset)
{
    // Reset step index and current step.
    script::m_step_index = 0;
    script::m_step.reset();

    // Reset states if necessary.
    if(reset)
    {
        // Call the derived reset_state method.
        reset_state();
    }
}
void script::reset_state()
{
    // Do nothing in base implementation.
}

// RUN
bool script::run_once()
{
    // Check if there is a valid current step.
    if(!script::m_step.valid())
    {
        // Indicate script is complete.
        return true;
    }

    // Run the currest step and check if it's complete.
    if(script::m_step->run_once())
    {
        // Increment current step and index.
        script::m_step.reset(create_step(++script::m_step_index));

        // Check if script is complete.
        if(!script::m_step.valid())
        {
            return true;
        }

        // Start the next step.
        script::m_step->start();
    }

    return false;
}
void script::run()
{
    // Reset step index and get first step.
    script::m_step_index = 0;
    script::m_step.reset(create_step(script::m_step_index));

    // Iterate until no more steps.
    while(script::m_step.valid())
    {
        // Start the step.
        script::m_step->start();

        // Run the step until it's complete.
        while(!script::m_step->run_once())
        {}

        // Increment to next step.
        script::m_step.reset(create_step(++script::m_step_index));
    }
}