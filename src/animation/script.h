/// \file script.h
/// \brief Defines the Animation::Script class.
#ifndef SCRIPT_H
#define SCRIPT_H

#include "Arduino.h"

#include "step.h"

namespace Animation
{

/// \brief Represents a single Script as a list of Animation::Steps.
class Script
{
public:
    // CONSTRUCTORS
    /// \brief Creates a new Script instance.
    /// \param ID The unique Identifier of the Script.
    /// \param Steps A heap array of steps representing the Script script.
    /// \param NSteps The number of steps provided in the Steps heap array.
    /// \param DesiredRuns The number of times to run the Script.  -1 signifies to repeat forever.
    /// \note This class will assume control of the Steps heap array input parameter and delete it upon class destruction.
    Script(unsigned int ID, Step* Steps, int NSteps, long DesiredRuns);
    /// \brief Destroys the Script instance and cleans up resources.
    ~Script();

    // METHODS
    /// \brief Implements the Script runtime.  Place this method in your main loop.
    /// \return Returns TRUE if the Script is complete, otherwise FALSE.
    /// \note This is a non-blocking method.
    bool Spin();
    /// \brief Signals the Script to stop AFTER it completes its current cycle.
    void Stop();

    // PROPERTIES
    /// \brief Gets the unique ID of the Script.
    /// \return The Script's ID.
    unsigned int ID();

private:
    /// \brief The unique identifier of the Script.
    unsigned int mID;
    /// \brief Stores the heap array of steps for the Script.
    Step* mSteps;
    /// \brief Stores the number of steps in the heap array.
    int mNSteps;
    /// \brief Stores the number of desired runs for the Script.
    long mDesiredRuns;
    /// \brief Stores the number of actual runs the Script has conducted.
    long mActualRuns;
    /// \brief Stores the time that the current step was started.
    unsigned long mCurrentStepStartTime;
    /// \brief Stores the current step that the Script is on.
    int mCurrentStep;
    /// \brief Flag indicating if a stop was requested.
    bool mStopRequested;
};

}

#endif // SCRIPT_H
