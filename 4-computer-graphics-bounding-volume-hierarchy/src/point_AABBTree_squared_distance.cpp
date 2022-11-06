#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue
typedef std::pair <std::shared_ptr<Object>, double> Qitem; // used to store (AABB node, distance)

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  ////////////////////////////////////////////////////////////////////////////
    /* Compute the distance from a query point to the object stored in a AABBTree using a priority queue
       Reference Sources used to write this function:
         - Lecture 4 Slides (#31)
         - C++ Priority Queue https://www.programiz.com/cpp-programming/priority-queue
         - https://www.geeksforgeeks.org/priority-queue-using-binary-heap/
    */
    // set initial squared distance to +infinity
    sqrd = std::numeric_limits<double>::infinity();

    // Queue has the minimum distance on top - initialized with root values
    std::priority_queue <Qitem, std::vector<Qitem>, std::greater<Qitem>> queue;
    queue.push(make_pair(root, point_box_squared_distance(query, root->box)));

    while (!queue.empty()) {
        Qitem temp = queue.top();
        queue.pop();

        std::shared_ptr<AABBTree> AABBnode = std::dynamic_pointer_cast<AABBTree>(temp.first);
        double temp_distance = temp.second;

        // Check if the subtree distance is smaller than what we currently have
        if (sqrd > temp_distance) {
            // leaf node is reached
            if (!AABBnode) {
                //udpade square distance and descendant values
                sqrd = temp_distance;
                descendant = temp.first;
            }
            // push to queue left and right subtrees (when exist)
            else {
                if (AABBnode->left) {
                    queue.push(make_pair(AABBnode->left, point_box_squared_distance(query, AABBnode->left->box)));
                }
                if (AABBnode->right) {
                    queue.push(make_pair(AABBnode->right, point_box_squared_distance(query, AABBnode->right->box)));
                }
                
            }
        }
    }
    bool hasDescendant = (min_sqrd <= sqrd && sqrd <= max_sqrd);
    return hasDescendant;
  ////////////////////////////////////////////////////////////////////////////
}
