#include "script.h"

using namespace Animation;

Script::Script(unsigned int ID, Step* Steps, int NSteps, long DesiredRuns)
{
  Script::mID = ID;
  Script::mSteps = Steps;
  Script::mNSteps = NSteps;
  Script::mDesiredRuns = DesiredRuns;
  Script::mActualRuns = 0;
  Script::mCurrentStepStartTime = 0;
  // Use a current step of -1 so that the first step can be transitioned into.
  Script::mCurrentStep = -1;
  Script::mStopRequested = false;
}
Script::~Script()
{
  delete [] Script::mSteps;
}
bool Script::Spin()
{
  // Check if we are within the number of desired repeats.
  if(Script::mDesiredRuns == -1 || Script::mActualRuns < Script::mDesiredRuns)
  {
    // Pull the current step's time Duration to check if it has elapsed.
    // A current step of -1 means the Script hasn't started yet, so transition to step 0.
    if(Script::mCurrentStep == -1 || millis() - Script::mCurrentStepStartTime >= Script::mSteps[Script::mCurrentStep].Duration)
    {
      // The current step's time has elapsed.  Transition to next step.
      // First increment the current step.  Check if we can increment or if we need to wrap back to step 0.
      if(Script::mCurrentStep < Script::mNSteps - 1)
      {
        // Continue iterating forward through steps.
        Script::mCurrentStep++;
      }
      else
      {
        // Last step has been completed, restart.
        Script::mCurrentStep = 0;
        // Increment actual repeats.
        Script::mActualRuns++;
        // Check if the Script repeats are complete.
        if(Script::mStopRequested || Script::mActualRuns == Script::mDesiredRuns)
        {
          // The Script is complete, return true.
          return true;
        }
      }
      // Set the Script transition time.
      Script::mCurrentStepStartTime = millis();
      // Execute the Script action.
      digitalWrite(Script::mSteps[Script::mCurrentStep].Pin, Script::mSteps[Script::mCurrentStep].State);
    }

    // If this point is reached, the Script is not complete.
    return false;
  }
  else
  {
    // The Script has reached or exceeded the number of desired repeats.
    return true;
  }
}
void Script::Stop()
{
  Script::mStopRequested = true;
}
unsigned int Script::ID()
{
  return Script::mID;
}
