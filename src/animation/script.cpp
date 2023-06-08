#include <animation/script.hpp>

using namespace animation;

// CONSTRUCTORS
script::script(size_t step_count)
    : steps(step_count),
      m_current_step(nullptr)
{}

// CONTROL
void script::start()
{
    // Set current step to beginning of array.
    script::m_current_step = script::steps.begin();

    // Start step if valid.
    if(script::m_current_step->valid())
    {
        (*script::m_current_step)->start();
    }
}
void script::stop(bool reset)
{
    // Reset the current step.
    script::m_current_step = nullptr;

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
    // Validate current step.
    if(!script::m_current_step->valid())
    {
        // Indicate script is complete.
        return true;
    }

    // Run the current step and check if it's complete.
    if((*script::m_current_step)->run_once())
    {
        // Increment the current step and check for script completion.
        if(++script::m_current_step == script::steps.end())
        {
            // Reset current step to nullptr.
            script::m_current_step = nullptr;
            // Indicate script complete.
            return true;
        }

        // Start the new step.
        (*script::m_current_step)->start();
    }

    return false;
}
void script::run()
{
    // Iterate through the step array.
    for(script::m_current_step = script::steps.begin(); script::m_current_step != script::steps.end(); ++script::m_current_step)
    {
        // Validate step.
        if(!script::m_current_step->valid())
        {
            break;
        }
        
        // Start the step.
        (*script::m_current_step)->start();

        // Run the step until its complete.
        while(!(*script::m_current_step)->run_once())
        {}
    }

    // Reset current step to nullptr.
    script::m_current_step = nullptr;
}