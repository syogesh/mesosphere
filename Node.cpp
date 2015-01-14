#include "Node.h"

#include <iostream>

using namespace std;


Node::Node(int node_number_, int resource_units_)
    : resource_units(resource_units_), node_number(node_number_),
    resources_free(resource_units_)
{}

// update all jobs, remove finished jobs
void Node::update() {
    for (auto job_it = job_list.begin(); job_it != job_list.end(); ) {
        shared_ptr<Job> job = *job_it;

        job->update();
        if ( job->is_finished() ) {
            resources_free += job->get_resources_needed();

            cout << "Job #" << job->get_job_number() << " complete"
                 << "; Node #" << node_number
                 << " Resources remaining: " << resources_free << endl;

            job_list.erase(job_it++);
        }
        else
            ++job_it;
    }
}

void Node::assign_job(shared_ptr<Job> new_job) {
    job_list.push_back(new_job);
    resources_free -= new_job->get_resources_needed();

    cout << "Assigned Job #" << new_job->get_job_number()
         << " to Node #" << node_number << "; Resources remaining: "
         << resources_free << endl;
}

ostream& operator<< (ostream& os, const Node& node) {
    os << "Node #" << node.node_number
       << " Total Resources: " << node.resource_units
       << " Free Resources: " << node.resources_free
       << " Num Jobs: " << node.job_list.size();

    for (auto job_ptr : node.job_list) {
        cout << *job_ptr << endl;
    }

    return os;
}

