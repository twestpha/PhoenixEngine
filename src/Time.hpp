#include <time.h>

#ifndef TIME_H
#define TIME_H

class Time {
private:
    static double lastFrameTime;

public:
    static double CurrentTime();
    static double TimeElapsed(double startTime);
    static double TimeDelta();
    static void UpdatelastFrameTime();
};

#endif
