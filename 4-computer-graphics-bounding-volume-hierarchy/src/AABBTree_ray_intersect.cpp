#include "AABBTree.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
    /* Reference Sources used to write this function:
         - Texbook Section 12.3.2: Hierarchical Bounding Boxes (p. 302-303)
         - Lecture 4 Slides
    */
    // Check tree descendants iff ray hits the box 
    if (ray_intersect_box(ray, this->box, min_t, max_t)) {
        
        // Check if ray intersects with left children 
        std::shared_ptr<Object> leftChildren = this->left;
        double left_t;
        bool left_hit = this->left && this->left->ray_intersect(ray, min_t, max_t, left_t, leftChildren);
        
        // Check if ray intersects with right children 
        std::shared_ptr<Object> rightChildren = this->right;
        double right_t;
        bool right_hit = this->right && this->right->ray_intersect(ray, min_t, max_t, right_t, rightChildren);

        // No hit
        if (!left_hit && !right_hit) {
            return false;
        }
        // 2 hits
        else if (left_hit && right_hit) { 
            t = std::min(left_t, right_t); // select closest hit
            descendant = (left_t < right_t) ? leftChildren : rightChildren;
            return true;
        }
        // 1 hit left
        else if (left_hit) {
            t = left_t;
            descendant = leftChildren;
            return true;
        }
        // 1 hit right
        else if (right_hit) {
            t = right_t;
            descendant = rightChildren;
            return true;
        }
    }
    // if ray doesn't hit box return false
    return false; 
  ////////////////////////////////////////////////////////////////////////////
}

