// ============================================================
// 
// PURPOSE: Abstract interface for any class that can display
//          its own details to standard output.
//
// JUSTIFICATION:
//   The "is-a" relationship is satisfied here. A Vehicle IS
//   displayable. A CarListing IS displayable. A User IS
//   displayable. Rather than duplicating a displayDetails()
//   method in every unrelated class, we declare a single
//   contract (pure virtual function) that forces each
//   derived class to provide its own implementation.
//   
// ============================================================

#ifndef IDISPLAYABLE_H
#define IDISPLAYABLE_H

class IDisplayable
{
public:
    
    virtual void displayDetails() const = 0;

    virtual ~IDisplayable() {}
};

#endif 
