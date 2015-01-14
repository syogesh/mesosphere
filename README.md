# mesosphere coding challenge
## yogesh seetharaman

### How to run
"make" into "make run"

### Critical Assumptions
There were two ways to interpret the input for this problem: 1. we had knowledge of all the nodes before we start processing 2. we do not have knowledge of all the nodes before we start processing. The second method would mean that each tick we gained awareness of one new node or knowledge of one node was updated. In the interest of time, I chose the first method to implement the solution as the second method requires additional functiononality (ex: if one of our nodes processing a job suddenly has a lot fewer resources, does the job get kicked out? does it need to be restarted? etc.). Either way, I designed the structure such that updating to the second interpretation would not require many changes.

I also assumed that each new job read would be the beginning of a new tick

### Reading the input/output
The first line of the input is the list of nodes; the second line is the list of jobs where each job is a tick
I first print all the nodes and jobs as I read them. Then each "tick", I assign the latest job to a node and print the node's remaining resources. When a job is completed, I print that and show the updated amount of resources available for that node.

### Thought Process and choices
I didn't want large processes to just be waiting around for resources to free up; to reduce the chance of this happenning, I chose to sort the list of nodes (in ascending order) by the number of resources available. When a new job is seen, it is placed in the smallest (by number of potential resources) that is available. This increases the chances that the larger jobs can be started as soon as possible.

Each tick follows the following algorithm:
    1. A new job is received; it is placed in the backlog at an appropriate location
    2. For each node (ascending order)
        - Update the node (the remaining time of each job in the node decreases by 1)
        - Check if you can add any jobs to the node from the backlog (if so add it to the node and remove it from the backlog)
        - If you can't add the first job you see, break (as ever other job is larger)

The backlog is ordered by size (ascending). This means that the smallest jobs are placed into the smallest available computers first. I believe this is better as the entire queue isn't bottlenecked by one large job waiting for a single node. A lot of smaller jobs get executed while the large job waits. This also provides a minor optimization in that if a node does not have space for the first job it sees in the backlog, there is no need to check the rest of the backlog as the backlog is always sorted.

This is of course naive as it now is possible for the nodes to be constantly swarmed by smaller jobs and the larger jobs stay in the queue forever. While I didn't have enough time to correct for this issue in my code, I would implement some kind of waiting system where if a Job has been waiting for too long it gets priority. Another possible solution for this problem is to change the way we assign jobs to nodes. Instead of simply assinging it to the smallest node, we could assign a job to the smallest node that already contains other jobs. This way free nodes tend to stay free for any larger jobs in the queue.

