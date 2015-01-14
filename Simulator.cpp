#include <iostream>
#include <utility>
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <memory>
#include <map>

#include "Job.h"
#include "Node.h"

using namespace std;

void process_jobs(vector<shared_ptr<Node> >& nodes, list<shared_ptr<Job> >& jobs);
void insert_job_into_backlog(shared_ptr<Job> new_job, list<shared_ptr<Job> >& job_backlog);

int main() {
    map<int, int> node_data;
    vector<shared_ptr<Node> > nodes;
    list<shared_ptr<Job> > jobs;

    // Read in nodes
    string input;
    getline(cin, input);
    istringstream node_stream(input);

    int first, second;
    while (true) {
        node_stream.ignore(256, '(');
        if ( !(node_stream >> first >> second) )
            break;

        node_data[first] = second;
    }

    for (auto node_it : node_data) {
        nodes.push_back(shared_ptr<Node>(new Node(node_it.first, node_it.second)));
        cout << *nodes.back() << endl;
    }

    // sort nodes by total resources available
    sort(nodes.begin(), nodes.end(),
    [](const shared_ptr<Node> & a, const shared_ptr<Node> & b)
    {
        return a->get_total_resources() < b->get_total_resources();
    });

    cout << "Sorted by resources available\n";
    for (auto node : nodes)
        cout << *node << endl;

    // Read in jobs
    getline(cin, input);
    istringstream job_stream(input);
    int job_number = 1;
    while (true) {
        job_stream.ignore(256, '(');
        if ( !(job_stream >> first >> second) )
            break;

        shared_ptr<Job> job = shared_ptr<Job>(new Job(job_number++, first, second));
        jobs.push_back(job);
        cout << *job << endl;
    }

    process_jobs(nodes, jobs);

    return 0;
}

// main logic
void process_jobs(vector<shared_ptr<Node> >& nodes, list<shared_ptr<Job> >& jobs) {
    list<shared_ptr<Job> > job_backlog;

    int tick = 0;
    // each new job in the list counts as a tick
    while ( !jobs.empty() || !job_backlog.empty() ) {
        cout << "\nTick #" << tick++ << endl;

        // get latest job and add to backlog at an appropriate spot
        if ( !jobs.empty() ) {
            insert_job_into_backlog(jobs.front(), job_backlog);
            jobs.pop_front();
        }

        for ( auto node : nodes ) {
            // update node
            node->update();

            // add any available jobs to the nodes
            for (auto job_it = job_backlog.begin(); job_it != job_backlog.end(); ) {

                // this could be improved by keeping track of the resources needed by the smallest job
                if ( node->get_available_resources() == 0 )
                    break;

                if ( node->get_available_resources()
                        >= (*job_it)->get_resources_needed() ) {
                    node->assign_job(*job_it);

                    job_backlog.erase(job_it++);
                }
                else
                    break;
            }
        }
    }

    int jobs_remaining;
    do {
        jobs_remaining = 0;
        cout << "\nTick #" << tick++ << endl;

        for ( auto node : nodes ) {
            if (node->get_num_jobs()) {
                node->update();
                jobs_remaining += node->get_num_jobs();
            }
        }
    } while (jobs_remaining);
}

void insert_job_into_backlog(shared_ptr<Job> new_job, list<shared_ptr<Job> >& job_backlog) {
    auto it = job_backlog.begin();
    while (it != job_backlog.end()) {
        if ( (*it)->get_resources_needed() > new_job->get_resources_needed() ) {
            job_backlog.insert(it, new_job);
            return;
        }
    }
    job_backlog.push_back(new_job);
}
