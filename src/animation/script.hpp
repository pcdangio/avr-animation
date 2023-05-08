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
    /// \param step_count The number of steps in the script.
    script(size_t step_count);
    ~script();

    // CONFIGURATION
    /// \brief Makes a new step at a specified position in the script.
    /// \param index The index to assign the new step to.
    /// \param step The new step instance.
    /// \return TRUE if the step was set successfully, FALSE if index out of range.
    /// \note Do not reuse step instance pointers. To reuse an existing step, use the copy version of set_step().
    bool make_step(size_t index, animation::step* step);
    /// \brief Copies an existing step to another position in the script.
    /// \param index The index to assign the copied step to.
    /// \param copy_index The index of the step to copy from.
    /// \return TRUE if the step was set successfully, FALSE if either index is out of range.
    bool copy_step(size_t index, size_t copy_index);
    /// \brief Copies multiple existing steps to another position in the script.
    /// \param index The index to start assigning copied steps to.
    /// \param copy_index The index of the first step in the range to copy.
    /// \param step_count The number of steps to copy.
    /// \param copy_count The number of times to copy the range of steps.
    /// \return TRUE if the steps were copied successfully, FALSE if any indices are out of range.
    bool copy_step(size_t index, size_t copy_index, size_t step_count, size_t copy_count = 1);
    /// \brief Clears a step at a desired position in the script.
    /// \param index The index of the step to clear.
    /// \return TRUE if the step was cleared successfully, FALSE if the index is out of range.
    bool clear_step(size_t index);
    /// \brief Clears all steps in the script.
    void clear();

    // RUN
    void start() override;
    bool run_once() override;
    /// \brief Runs the script (and blocks) until it is complete.
    /// \note start() does not need to be called before using this method.
    void run();

    // PROPERTIES
    /// \brief The number of steps in the script.
    const size_t step_count;

private:
    // ENTRY
    /// \brief An animation step entry in the script.
    /// \details This class allows shared use and management of an animation step pointer.
    class entry
    {
    public:
        // CONSTRUCTORS
        /// \brief Creates a new empty entry.
        entry();
        ~entry();
        
        // ASSIGNMENT
        /// \brief Assigns a new step instance to this entry.
        /// \param step The new step instance to assign.
        void assign(animation::step* step);
        /// \brief Copies an existing step instance to this entry.
        /// \param other The existing step instance to copy.
        void assign(const entry* other);
        /// \brief Clears this entry.
        void clear();

        // RUN
        /// \brief Starts the step instance if it exists.
        void start();
        /// \brief Runs the step instance once if it exists.
        /// \return TRUE if the step instance is complete or does not exist, FALSE if step instance is not complete.
        bool run_once();

    private:
        // INSTANCE
        /// \brief The shared step instance.
        animation::step* m_step;
        /// \brief The number of entries currently referencing the shared step instance.
        size_t* m_reference_count;
        /// \brief Decrements the reference count of the shared step instance, and frees the instance if there are no more references.
        void decrement_reference();
    };

    // STEPS
    /// \brief A pointer to the beginning of the step entry array.
    script::entry* m_steps_begin;
    /// \brief A pointer to the end of the step entry array.
    script::entry* m_steps_end;
    /// \brief A pointer to the current position in the step entry array.
    script::entry* m_current_step;
};

}

#endif