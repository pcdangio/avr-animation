#include <animation/script.hpp>

using namespace animation;

// CONSTRUCTORS
script::script(size_t step_count)
    : m_steps(step_count),
      m_current_step(nullptr)
{}

// CONFIGURATION
bool script::set_step(size_t index, const std::shared_ptr<animation::step>& step)
{
    // Validate index.
    if(index >= script::m_steps.size)
    {
        return false;
    }

    // Store step at index.
    script::m_steps[index] = step;

    return true;
}
bool script::set_step(size_t index, size_t copy_index)
{
    // Validate indices.
    if(index >= script::m_steps.size || copy_index >= script::m_steps.size)
    {
        return false;
    }

    // Copy source index to destination index.
    script::m_steps[index] = script::m_steps[copy_index];

    return true;
}
bool script::clear_step(size_t index)
{
    // Validate index.
    if(index >= script::m_steps.size)
    {
        return false;
    }

    // Reset shared_ptr at index.
    script::m_steps[index].reset();

    return true;
}
void script::clear()
{
    // Reset all shared_ptrs in the array.
    for(auto entry = script::m_steps.begin(); entry != script::m_steps.end(); ++entry)
    {
        entry->reset();
    }
}

// CONTROL
void script::start()
{
    // Set current step to beginning of array.
    script::m_current_step = script::m_steps.begin();

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
        if(++script::m_current_step == script::m_steps.end())
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
    for(script::m_current_step = script::m_steps.begin(); script::m_current_step != script::m_steps.end(); ++script::m_current_step)
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