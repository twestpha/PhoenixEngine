#include <time.h>

#pragma once

class Time {
public:
    static double CurrentTime(){
        return float(clock())/CLOCKS_PER_SEC;
    }
    static double TimeElapsed(double startTime){
        return float(CurrentTime() - startTime);
    }
};
