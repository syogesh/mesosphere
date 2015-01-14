#ifndef NODE_H
#define NODE_H

#include "Job.h"

#include <list>
#include <iostream>
#include <memory>

class Node {
public:
    Node(int node_number_, int resource_units_);

    int get_total_resources() const
    { return resource_units; }

    int get_available_resources() const
    { return resources_free; }

    int get_num_jobs() const
    { return job_list.size(); }

    void update();

    void assign_job(std::shared_ptr<Job> new_job);

private:
    int resource_units;
    int node_number;
    int resources_free;

    std::list<std::shared_ptr<Job> > job_list;

    friend std::ostream& operator<< (std::ostream& os, const Node& node);
};

std::ostream& operator<< (std::ostream& os, const Node& node);

#endif
