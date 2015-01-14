#ifndef JOB_H
#define JOB_H

#include <iostream>

class Job {
public:
    Job(int job_number, int resources_needed_, int time_needed_);

    int get_time_remaining() const
    { return time_remaining; }

    int get_resources_needed() const
    { return resources_needed; }

    int get_job_number() const
    { return job_number; }

    bool is_finished() const
    { return time_remaining == 0; }

    void update();

private:
    int job_number;
    int resources_needed;
    int time_needed;
    int time_remaining;


    friend std::ostream& operator<< (std::ostream& os, const Job& node);
};

std::ostream& operator<< (std::ostream& os, const Job& job);

#endif
