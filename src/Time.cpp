#include "Time.hpp"

double Time::lastFrameTime = 0.0f;

double Time::CurrentTime(){
    return float(clock())/CLOCKS_PER_SEC;
}

double Time::TimeElapsed(double startTime){
    return float(CurrentTime() - startTime);
}

double Time::TimeDelta(){
    return TimeElapsed(lastFrameTime);
}

void Time::UpdatelastFrameTime(){
    lastFrameTime = CurrentTime();
}
