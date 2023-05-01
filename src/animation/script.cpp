#include <animation/script.hpp>

using namespace animation;

// CONSTRUCTORS
script::script()
    : m_steps_begin(nullptr),
      m_steps_end(nullptr),
      m_current_step(nullptr)
{}
script::~script()
{
    // Clear steps array.
    script::clear();
}

// CONFIGURATION
void script::build(animation::step** steps, size_t step_count)
{
    // Clear any existing steps.
    script::clear();

    // Store array pointer.
    script::m_steps_begin = steps;
    script::m_steps_end = script::m_steps_begin + step_count;
}
void script::clear()
{
    // Check if array is already empty.
    if(!script::m_steps_begin)
    {
        return;
    }

    // Clean up step pointers.
    for(animation::step** step = script::m_steps_begin; step != script::m_steps_end; ++step)
    {
        delete *step;
    }

    // Clean up step array.
    delete [] script::m_steps_begin;

    // Reset array pointers.
    script::m_steps_begin = nullptr;
    script::m_steps_end = nullptr;
}

// RUN
void script::start()
{
    // Set position to start of step array.
    script::m_current_step = script::m_steps_begin;

    // Start the step if it exists.
    if(script::m_current_step)
    {
        (*script::m_current_step)->start();
    }
}
bool script::run_once()
{
    // Check if there is a current step.
    if(!script::m_current_step)
    {
        // Indicate that script is done.
        return true;
    }

    // Run the current step and check if it's complete.
    if((*script::m_current_step)->run_once())
    {
        // Increment the current step and check for script completion.
        if(++script::m_current_step == script::m_steps_end)
        {
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
    for(script::m_current_step = script::m_steps_begin; script::m_current_step != script::m_steps_begin; ++script::m_current_step)
    {
        // Start the step.
        (*script::m_current_step)->start();

        // Run the step until its complete.
        while(!(*script::m_current_step)->run_once())
        {}
    }
}

// PROPERTIES
size_t script::step_count() const
{
    return script::m_steps_end - script::m_steps_begin;
}