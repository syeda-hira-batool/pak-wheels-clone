// ============================================================
// Abstract interface for any object that can be
//          tested against a multi-field search filter.
//
// JUSTIFICATION:
//   Both Vehicle and CarListing participate in search, but
//   they filter differently:
//     - Vehicle checks make, model, year, mileage.
//     - CarListing first checks price and status, then
//       delegates to its contained Vehicle.
//   By making both implement ISearchable through the same
//   virtual signature, the SearchFilter::applyTo() method
//   can call matchesFilter() on a CarListing without needing
//   to know anything about the internal Vehicle 
//
// ============================================================

#ifndef ISEARCHABLE_H
#define ISEARCHABLE_H

#include <string>
using std::string;

class ISearchable
{
public:
    
    virtual bool matchesFilter(const string &brand,
                               const string &mdl,
                               long long minP,
                               long long maxP,
                               int minY,
                               int maxY,
                               int maxMil) const = 0;

    virtual ~ISearchable() {}
};

#endif 
