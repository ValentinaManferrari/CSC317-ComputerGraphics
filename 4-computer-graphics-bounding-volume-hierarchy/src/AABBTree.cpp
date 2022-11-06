#include "AABBTree.h"
#include "insert_box_into_box.h"
#include <iostream>
#include <limits>

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  /* Reference Sources used to write this function:
         - Texbook Section 12.3.2: Hierarchical Bounding Boxes (p. 304-305)
         - Lecture 4 Slides 
    */
    this->left = NULL;
    this->right = NULL;

    switch (num_leaves) {
    case 0:
        return;

    case 1:
        this->left = objects[0];
        insert_box_into_box(objects[0]->box, this->box);
        return;

    case 2:
        this->left = objects[0];
        insert_box_into_box(objects[0]->box, this->box);

        this->right = objects[1];
        insert_box_into_box(objects[1]->box, this->box);
        return;

    default:
        // Find longest axis
        std::vector<double> min_axis(3, std::numeric_limits<double>::infinity()); // initialize min axis to +inf
        std::vector<double> max_axis(3, -std::numeric_limits<double>::infinity()); // initialize max axis to -inf
        // loop through each object to get max/min corners along each axis
        for (auto object : objects) { 
            for (int ax = 0; ax < 3; ax++) {
                double min = object->box.min_corner[ax];
                double max = object->box.max_corner[ax];
                // update min_axis and max_axis vectors if necessary
                min_axis[ax] = (min < min_axis[ax]) ? min : min_axis[ax]; 
                max_axis[ax] = (max > max_axis[ax]) ? max : max_axis[ax];
            }
        }
        // set longest axis to x
        int axis = 0;
        // compare with y and z axis to see if they are actually the longest
        for (int ax = 1; ax < 3; ax++) {
            if ((max_axis[ax] - min_axis[ax]) > (max_axis[axis] - min_axis[axis])) {
                axis = ax;
            }
        }

        // Function to sort objects based on their bounding box centers along longest axis
        auto comparator = [&axis](const std::shared_ptr<Object>& A, const std::shared_ptr<Object>& B) {
            bool check = A->box.center()[axis] < B->box.center()[axis];
            return check;
        };
        // Sort objects using comparator
        std::vector<std::shared_ptr<Object>> obj(objects);
        std::sort(obj.begin(), obj.end(), comparator);

        // Balance AABBtree by splitting objects in half
        auto start = obj.begin();
        auto middle = obj.begin() + num_leaves / 2;
        auto end = obj.end();
        // Recursively attach AABB trees to children nodes
        this->left = std::make_shared<AABBTree>(std::vector<std::shared_ptr<Object>>(start, middle), this->depth + 1);
        this->right = std::make_shared<AABBTree>(std::vector<std::shared_ptr<Object>>(middle, end), this->depth + 1);

        // Update bounding box
        insert_box_into_box(this->left->box, this->box);
        insert_box_into_box(this->right->box, this->box);
        return;
    }
  ////////////////////////////////////////////////////////////////////////////
}
