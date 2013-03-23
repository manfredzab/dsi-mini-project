#ifndef TIMER_H_
#define TIMER_H_

#include <sys/time.h>

namespace uk_ac_ox_cs_c875114
{

/**
 * Measures the wall-clock time (in microseconds) between the Start() and Stop() calls.
 */
class Timer
{
    public:
        /*
         * Starts measuring the time.
         */
        void Start()
        {
            gettimeofday(&start_time, NULL);
        }

        /*
         * Stops measuring the time and returns the time elapsed since the call to Start()
         * in fractional parts of a second (in the accuracy of microseconds).
         * @returns Elapsed time since the call to Start() in fractions of a second.
         */
        double Stop()
        {
            timeval end_time;
            long seconds, useconds;
            double duration;

            gettimeofday(&end_time, NULL);

            seconds  = end_time.tv_sec  - start_time.tv_sec;
            useconds = end_time.tv_usec - start_time.tv_usec;

            duration = seconds + useconds / 1000000.0;

            return duration;
        }

    private:
        timeval start_time;
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* TIMER_H_ */
