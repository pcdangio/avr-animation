/// \file animator.h
/// \brief Defines the Animation::Animator class.
#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "Arduino.h"

#include "script.h"

/// \brief Contains code for the Animation library.
namespace Animation
{

/// \brief Provides non-blocking Script of pins according to a script of steps.
class Animator
{
public:
    /// \brief Creates a new Animator instance.
    /// \param MaxConcurrentScripts Sets the maximum amount of Scripts that the Animator will track/animate concurrently.
    Animator(byte MaxConcurrentScripts = 5);
    /// \brief Destroys the Animator instance and cleans up resources.
    ~Animator();

    /// \brief Performs the Animator's regular duties and carries out Scripts.
    void Spin();
    /// \brief Adds an Script to the Animator and immediately begins running the Script.
    /// \param NewScript The new Script to add.
    /// \return Returns TRUE if the Script was added, otherwise FALSE.
    /// \details This method will only add an Script if there is space (see MaxConcurrentScripts in constructor) and there are
    /// no other currently running Scripts with the same Script ID.
    bool AddScript(Script* NewScript);
    /// \brief Signals the Animator to stop an Script once it completes it's current cycle.
    /// \param ID The ID of the Script to stop.
    /// \note This method is only relevant for infinite Scripts, i.e. Scripts with a DesiredRuns value of -1.
    void StopScript(unsigned int ID);
    /// \brief Stops all Scripts currently running in the Animator.
    /// \note This method is only relevant for infinite Scripts, i.e. Scripts with a DesiredRuns value of -1.
    void StopAllScripts();

private:
    /// \brief Contains the internal buffer of running scripts.
    Script** mScripts;
    /// \brief The current size of the script buffer.
    byte mNScripts;
};

}

#endif // ANIMATOR_H
