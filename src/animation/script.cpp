#include <animation/script.hpp>

using namespace animation;

// CONSTRUCTORS
script::script(size_t step_count)
    : step_count(step_count),
      m_steps_begin(new script::entry[step_count]),
      m_steps_end(script::m_steps_begin + script::step_count),
      m_current_step(nullptr)
{}
script::~script()
{
    // Clean the step entry array.
    delete [] script::m_steps_begin;
}

// CONFIGURATION
bool script::make_step(size_t index, animation::step* step)
{
    // Get pointer to desired entry.
    script::entry* entry = script::m_steps_begin + index;
    // Check if desired entry is valid.
    if(entry >= script::m_steps_end)
    {
        return false;
    }

    // Create raw step instance and assign it to the entry.
    entry->assign(step);

    return true;
}
bool script::copy_step(size_t index, size_t copy_index)
{
    // Get reference to destination and check for validity.
    script::entry* destination_entry = script::m_steps_begin + index;
    if(destination_entry >= script::m_steps_end)
    {
        return false;
    }

    // Get reference to step to copy from and check for validity.
    script::entry* source_entry = script::m_steps_begin + copy_index;
    if(source_entry >= script::m_steps_end)
    {
        return false;
    }

    // Assign source entry to destination entry.
    destination_entry->assign(source_entry);

    return true;
}
bool script::copy_step(size_t index, size_t copy_index, size_t step_count, size_t copy_count)
{
    // Validate counts.
    if(step_count == 0 || copy_count == 0)
    {
        // No copy necessary.
        return true;
    }

    // Get reference to start destination and check for validity.
    script::entry* destination_begin = script::m_steps_begin + index;
    if(destination_begin >= script::m_steps_end)
    {
        return false;
    }

    // Get reference to end destination and check for validity.
    script::entry* destination_end = destination_begin + step_count * copy_count;
    if(destination_end > script::m_steps_end)
    {
        return false;
    }

    // Get reference to start source and check for validity.
    script::entry* source_begin = script::m_steps_begin + copy_index;
    if(source_begin >= script::m_steps_end)
    {
        return false;
    }

    // Get reference to end source and check for validity.
    script::entry* source_end = source_begin + step_count;
    if(source_end > script::m_steps_end)
    {
        return false;
    }

    // Iterate over number over destination range.
    script::entry* source;
    script::entry* destination = destination_begin;
    while(destination < destination_end)
    {
        // Iterate over the source range.
        for(source = source_begin; source != source_end; ++source)
        {
            // Copy source to destination and increment destination pointer.
            (destination++)->assign(source);
        }
    }

    return true;
}
bool script::clear_step(size_t index)
{
    // Get pointer to desired entry.
    script::entry* entry = script::m_steps_begin + index;
    // Check if desired entry is valid.
    if(entry >= script::m_steps_end)
    {
        return false;
    }

    // Clear entry.
    entry->clear();

    return true;
}
void script::clear()
{
    // Iterate over step entries.
    for(script::entry* entry = script::m_steps_begin; entry != script::m_steps_end; ++entry)
    {
        entry->clear();
    }
}

// RUN
void script::start()
{
    // Validate script.
    if(script::m_steps_begin == script::m_steps_end)
    {
        // Set current step to nullptr.
        script::m_current_step = nullptr;
        return;
    }

    // Set position to start of step array.
    script::m_current_step = script::m_steps_begin;

    // Start the current step.
    script::m_current_step->start();
}
bool script::run_once()
{
    // Validate current step (means that script was started).
    if(!script::m_current_step)
    {
        // Indicate script is complete.
        return true;
    }

    // Run the current step and check if it's complete.
    if(script::m_current_step->run_once())
    {
        // Increment the current step and check for script completion.
        if(++script::m_current_step == script::m_steps_end)
        {
            // Reset current step to nullptr.
            script::m_current_step = nullptr;
            // Indicate script complete.
            return true;
        }

        // Start the new step.
        script::m_current_step->start();
    }

    return false;
}
void script::run()
{
    // Iterate through the step array.
    for(script::m_current_step = script::m_steps_begin; script::m_current_step != script::m_steps_begin; ++script::m_current_step)
    {
        // Start the step.
        script::m_current_step->start();

        // Run the step until its complete.
        while(!script::m_current_step->run_once())
        {}
    }

    // Reset current step to nullptr.
    script::m_current_step = nullptr;
}

// ENTRY

// CONSTRUCTORS
script::entry::entry()
    : m_step(nullptr),
      m_reference_count(nullptr)
{}
script::entry::~entry()
{
    // Decrement reference count.
    script::entry::decrement_reference();
}

// ASSIGNMENT
void script::entry::assign(animation::step* step)
{
    // Decrement reference count for existing step instance.
    script::entry::decrement_reference();

    // Create new step and reference count instances.
    script::entry::m_step = step;
    script::entry::m_reference_count = new size_t(1);
}
void script::entry::assign(const entry* other)
{
    // Decrement reference count for existing step instance.
    script::entry::decrement_reference();

    // Copy step and reference count from other entry.
    script::entry::m_step = other->m_step;
    script::entry::m_reference_count = other->m_reference_count;

    // Increment reference count for new step instance.
    if(script::entry::m_reference_count)
    {
        ++(*script::entry::m_reference_count);
    }
}
void script::entry::clear()
{
    // Decrement reference count for existing step instance.
    script::entry::decrement_reference();

    // Set step and reference count to nullptr.
    script::entry::m_step = nullptr;
    script::entry::m_reference_count = nullptr;
}

// RUN
void script::entry::start()
{
    // Check if step exists.
    if(script::entry::m_step)
    {
        // Start step.
        script::entry::m_step->start();
    }
}
bool script::entry::run_once()
{
    // Check if step exists.
    if(!script::entry::m_step)
    {
        // Indicate step is complete since it does not exist.
        return true;
    }

    // Run step.
    return script::entry::m_step->run_once();
}

// REFERENCE COUNT
void script::entry::decrement_reference()
{
    // Decrement reference count and check if no references left.
    if(script::entry::m_reference_count && --(*script::entry::m_reference_count) == 0)
    {
        // Clean up step and reference count instances.
        delete script::entry::m_step;
        delete script::entry::m_reference_count;
    }
}