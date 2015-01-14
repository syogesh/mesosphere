#include "Job.h"

#include <iostream>

using namespace std;

Job::Job(int job_number_, int resources_needed_, int time_needed_)
    : job_number(job_number_), resources_needed(resources_needed_),
    time_needed(time_needed_), time_remaining(time_needed_)
{}

void Job::update() {
    time_remaining--;
}

ostream& operator<< (ostream& os, const Job& job) {
    os << "Job #" << job.job_number
       << ": Resources Needed: " << job.resources_needed
       << " Time Needed: " << job.time_needed
       << " Time Remaining: " << job.time_remaining;

    return os;
}
