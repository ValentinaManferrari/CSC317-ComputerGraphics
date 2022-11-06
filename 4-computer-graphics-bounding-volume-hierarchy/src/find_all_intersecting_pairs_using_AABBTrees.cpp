#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 
typedef std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>> listItem;

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////
 
    // create and populate queue
    std::list<listItem> queue;
    queue.push_back(make_pair(rootA, rootB));

    while (!queue.empty()) {
        // get first element from priority queue
        listItem temp = queue.front();
        queue.pop_front();

        std::shared_ptr<Object> a = temp.first;
        std::shared_ptr<Object> b = temp.second;

        std::shared_ptr<AABBTree> A = std::dynamic_pointer_cast<AABBTree>(temp.first);
        std::shared_ptr<AABBTree> B = std::dynamic_pointer_cast<AABBTree>(temp.second);

        // both A and B are tree leaves
        if (!A && !B) {
            leaf_pairs.push_back(make_pair(a, b)); 
        }
        // A is not a leaf while B is
        else if (A && !B) {
            if (A->left && box_box_intersect(A->left->box, temp.second->box)) {
                queue.push_back(make_pair(A->left, b));
            }
            if (A->right && box_box_intersect(A->right->box, b->box)) {
                queue.push_back(make_pair(A->right, b));
            }
        }
        // A is a leaf while B is not
        else if (!A && B) {
            if (B->left && box_box_intersect(a->box, B->left->box)) {
                queue.push_back(make_pair(a, B->left));
            }
            if (B->right && box_box_intersect(a->box, B->right->box)) {
                queue.push_back(make_pair(a, B->right));
            }
        }
        // We there are not leaf nodes push pairs to queue
        else {
            if (A->left && B->left && box_box_intersect(A->left->box, B->left->box)) {
                queue.push_back(make_pair(A->left, B->left));
            }
            if (A->left && B->right && box_box_intersect(A->left->box, B->right->box)) {
                queue.push_back(make_pair(A->left, B->right));
            }
            if (A->right && B->left && box_box_intersect(A->right->box, B->left->box)) {
                queue.push_back(make_pair(A->right, B->left));
            }
            if (A->right && B->right && box_box_intersect(A->right->box, B->right->box)) {
                queue.push_back(make_pair(A->right, B->right));
            }
        }
    }
  ////////////////////////////////////////////////////////////////////////////
}
