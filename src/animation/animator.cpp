#include "animator.h"

using namespace Animation;

Animator::Animator(byte MaxConcurrentScripts)
{
  // Initialize an empty Script pointer buffer.
  Animator::mScripts = new Script*[MaxConcurrentScripts];
  // Fill the buffer will null pointers.
  for(byte i = 0; i < MaxConcurrentScripts; i++)
  {
    Animator::mScripts[i] = NULL;
  }
  // Store the buffer size.
  Animator::mNScripts = MaxConcurrentScripts;
}
Animator::~Animator()
{
  // Delete all Scripts via pointer.
  for(byte i = 0; i < Animator::mNScripts; i++)
  {
    if(Animator::mScripts[i])
    {
      delete Animator::mScripts[i];
    }
  }
  // Delete the Scripts pointer array.
  delete [] Animator::mScripts;
}
void Animator::Spin()
{
  // Iterate through the Scripts in the buffer and spin them.
  for(byte i = 0; i < Animator::mNScripts; i++)
  {
    if(Animator::mScripts[i])
    {
      bool Complete = Animator::mScripts[i]->Spin();
      // If the Script is complete, delete it and remove it from the buffer.
      if(Complete)
      {
        delete Animator::mScripts[i];
        Animator::mScripts[i] = NULL;
      }
    }
  }
}
bool Animator::AddScript(Script* NewScript)
{
  // Check if the Script is already present in the buffer.
  int OpenPosition = -1;
  for(byte i = 0; i < Animator::mNScripts; i++)
  {
    if(Animator::mScripts[i])
    {
      // Check if the IDs match.
      if(NewScript->ID() == Animator::mScripts[i]->ID())
      {
        // Quit here as the ID already exists in the buffer.
        return false;
      }
    }
    else
    {
      // This position is a null, which means it is open.
      OpenPosition = i;
    }
  }

  // If this point is reached, there are no conflicting IDs.
  // Check if there is an open position.
  if(OpenPosition >= 0)
  {
    // Open position found.  Add the new Script.
    Animator::mScripts[OpenPosition] = NewScript;
    return true;
  }
  else
  {
    // No open positions were found.
    return false;
  }
}
void Animator::StopScript(unsigned int ID)
{
  // Find the Script in the buffer.
  for(byte i = 0; i < Animator::mNScripts; i++)
  {
    // Check if this position has an Script, and if the Script has a matching ID.
    if(Animator::mScripts[i] && Animator::mScripts[i]->ID() == ID)
    {
      Animator::mScripts[i]->Stop();
      // Quit here, as there can only be one of this ID in the buffer.
      return;
    }
  }
}
void Animator::StopAllScripts()
{
  for(byte i = 0; i < Animator::mNScripts; i++)
  {
    if(Animator::mScripts[i])
    {
      Animator::mScripts[i]->Stop();
    }
  }
}
