#include <time.h>

#ifndef TIME_H
#define TIME_H

class Time {
public:
    static double CurrentTime(){
        return float(clock())/CLOCKS_PER_SEC;
    }
    static double TimeElapsed(double startTime){
        return float(CurrentTime() - startTime);
    }
};

#endif
