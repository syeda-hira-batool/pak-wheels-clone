// ============================================================
// 
// PURPOSE: Abstract interface for entities that carry a
//          persistent numeric rating 
//
// JUSTIFICATION:
//   Only Seller currently holds a rating, but the interface
//   is defined separately so that other classes (e.g., a
//   future Dealership or Product class) can also become
//   reviewable without modifying existing code.
//
// ============================================================

#ifndef IREVIEWABLE_H
#define IREVIEWABLE_H

class IReviewable
{
public:
    
    virtual double getRating() const = 0;

    virtual void updateRating(double newRating) = 0;

    virtual ~IReviewable() {}
};

#endif 
