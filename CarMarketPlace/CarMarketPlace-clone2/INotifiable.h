// ============================================================
//
// PURPOSE: Abstract interface for any object that can receive
//          and process a text notification.
//
// JUSTIFICATION:
//   Both Seller (a User subclass) and Buyer (another User
//   subclass) can receive notifications, as can any future
//   user role.

// ============================================================

#ifndef INOTIFIABLE_H
#define INOTIFIABLE_H

#include <string>
using std::string;

class INotifiable
{
public:
    
    virtual void receiveNotification(const string &msg) = 0;

    
    virtual ~INotifiable() {}
};

#endif 
