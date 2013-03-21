#ifndef TIMER_H_
#define TIMER_H_

#include <sys/time.h>

namespace uk_ac_ox_cs_c875114
{

class Timer
{
    public:
        void Start()
        {
            gettimeofday(&start_time, NULL);
        }

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
