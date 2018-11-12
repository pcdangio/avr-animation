#include "step.h"

using namespace Animation;

Step::Step()
{
  Step::Pin = 0;
  Step::State = LOW;
  Step::Duration = 0;
}
Step::Step(int Pin, int State, unsigned long Duration)
{
  Step::Pin = Pin;
  Step::State = State;
  Step::Duration = Duration;
}
