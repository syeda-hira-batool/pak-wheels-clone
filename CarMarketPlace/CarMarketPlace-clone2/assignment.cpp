#include <iostream>
#include <string>
#include <iomanip>   // learnt for precisions in big prizes
#include "IDisplayable.h"
#include "INotifiable.h"
#include "ISearchable.h"
#include "IReviewable.h"
using namespace std;




class Address
{
private:
    string street, city, province, country, postalCode;

public:
    Address()
        : street("N/A"), city("N/A"), province("N/A"),
          country("Pakistan"), postalCode("00000") {}

    Address(const string &st, const string &ci, const string &pr,
            const string &pc, const string &co = "Pakistan")
        : street(st), city(ci), province(pr), postalCode(pc), country(co) {}

    Address(const Address &a) : street(a.street), city(a.city), province(a.province), country(a.country), postalCode(a.postalCode) {}

    string getCity() const
    {
        return city;
    }
    string getProvince() const
    {
        return province;
    }
    string getFullAddress() const
    {
        return street + ", " + city + ", " + province + " - " + country + " " + postalCode;
    }

    void setCity(const string &c) { city = c; }
    void update(const string &st, const string &ci,
                const string &pr, const string &pc)
    {
        street = st;
        city = ci;
        province = pr;
        postalCode = pc;
    }

    bool isInCity(const string &c) const { return city == c; }

    void display() const
    {
        cout << "  Location  : " << getFullAddress() << "\n";
    }
    bool operator==(const Address &other) const
    {
        return city == other.city && province == other.province;
    }

    bool operator!=(const Address &other) const
    {
        return !(*this == other);
    }

    friend ostream &operator<<(ostream &os, const Address &a);
};

ostream &operator<<(ostream &os, const Address &a)
{
    os << a.street << ", " << a.city << ", " << a.province
       << " - " << a.country << " " << a.postalCode;
    return os;
}

class Vehicle : public IDisplayable, public ISearchable
{
protected:
    string make, model, color, engineType;
    int year, mileage;

public:
    static const int MAX_MILEAGE = 999999;
    static const int MIN_YEAR = 1980;

    Vehicle()
        : make("Unknown"), model("Unknown"), year(2000),
          color("White"), engineType("Petrol"), mileage(0) {}

    Vehicle(const string &mk, const string &mo, int yr,
            const string &col, const string &eng, int mil)
        : make(mk), model(mo), color(col), engineType(eng)
    {
        year = (yr >= MIN_YEAR && yr <= 2025) ? yr : MIN_YEAR;
        mileage = (mil >= 0 && mil <= MAX_MILEAGE) ? mil : 0;
    }

    Vehicle(const Vehicle &v)
        : make(v.make), model(v.model), year(v.year),
          color(v.color), engineType(v.engineType), mileage(v.mileage) {}

    virtual ~Vehicle() {}

    string getMake() const { return make; }
    string getModel() const { return model; }
    int getYear() const { return year; }
    string getEngineType() const { return engineType; }
    int getMileage() const { return mileage; }
    int getAge() const { return 2025 - year; }

    void setColor(const string &c) { color = c; }
    void setMileage(int m)
    {
        if (m >= 0 && m <= MAX_MILEAGE)
            mileage = m;
    }

    bool matchesBrand(const string &brand) const
    {
        return brand.empty() || make == brand;
    }
    bool matchesModel(const string &mdl) const
    {
        return mdl.empty() || model == mdl;
    }

    virtual void displayDetails() const override
    {
        cout << "  Vehicle   : " << year << " " << make << " " << model << "\n";
        cout << "  Color     : " << color << "\n";
        cout << "  Engine    : " << engineType << "\n";
        cout << "  Mileage   : " << mileage << " km\n";
    }

    virtual bool matchesFilter(const string &brand, const string &mdl,
                               long long minP, long long maxP,
                               int minY, int maxY, int maxMil) const override
    {
        (void)minP;
        (void)maxP;
        if (!matchesBrand(brand))
            return false;
        if (!matchesModel(mdl))
            return false;
        if (year < minY || year > maxY)
            return false;
        if (mileage > maxMil)
            return false;
        return true;
    }

    bool operator==(const Vehicle &other) const
    {
        return make == other.make && model == other.model && year == other.year;
    }

    bool operator<(const Vehicle &other) const { return year < other.year; }

    bool operator>(const Vehicle &other) const { return year > other.year; }

    friend ostream &operator<<(ostream &os, const Vehicle &v);

    friend void compareVehicles(const Vehicle &a, const Vehicle &b);
};

ostream &operator<<(ostream &os, const Vehicle &v)
{
    os << v.year << " " << v.make << " " << v.model
       << " | " << v.engineType << " | " << v.mileage << " km";
    return os;
}

void compareVehicles(const Vehicle &a, const Vehicle &b)
{
    cout << "\n  [Compare Vehicles]\n";
    cout << "  A: " << a << "\n";
    cout << "  B: " << b << "\n";
    if (a.year == b.year)
        cout << "  Same year.\n";
    else
        cout << "  Newer: " << (a.year > b.year ? a.make + " " + a.model : b.make + " " + b.model) << "\n";
    cout << "  Lower mileage: "
         << (a.mileage <= b.mileage ? a.make + " " + a.model
                                    : b.make + " " + b.model)
         << "\n";
}

class Car : public Vehicle
{
private:
    int doors;
    string bodyType;
    bool isAutomatic;

public:
    Car() : Vehicle(), doors(4), bodyType("Sedan"), isAutomatic(true) {}

    Car(const string &mk, const string &mo, int yr, const string &col,
        const string &eng, int mil, int dr, const string &bt, bool autoTrans)
        : Vehicle(mk, mo, yr, col, eng, mil),
          doors(dr), bodyType(bt), isAutomatic(autoTrans) {}

    Car(const Car &c)
        : Vehicle(c), doors(c.doors),
          bodyType(c.bodyType), isAutomatic(c.isAutomatic) {}

    string getBodyType() const { return bodyType; }
    int getDoors() const { return doors; }
    bool getIsAutomatic() const { return isAutomatic; }

    void displayDetails() const override
    {
        Vehicle::displayDetails();
        cout << "  Body Type : " << bodyType << " | Doors: " << doors
             << " | Trans: " << (isAutomatic ? "Auto" : "Manual") << "\n";
    }

    Car &operator+=(int km)
    {
        if (mileage + km <= MAX_MILEAGE)
            mileage += km;
        return *this;
    }
};

class Bike : public Vehicle
{
private:
    int engineCC;
    string bikeType;

public:
    Bike() : Vehicle(), engineCC(125), bikeType("Standard") {}

    Bike(const string &mk, const string &mo, int yr, const string &col,
         const string &eng, int mil, int cc, const string &bt)
        : Vehicle(mk, mo, yr, col, eng, mil), engineCC(cc), bikeType(bt) {}

    Bike(const Bike &b)
        : Vehicle(b), engineCC(b.engineCC), bikeType(b.bikeType) {}

    int getEngineCC() const { return engineCC; }
    string getBikeType() const { return bikeType; }

    void displayDetails() const override
    {
        Vehicle::displayDetails();
        cout << "  Bike Type : " << bikeType
             << " | Engine CC: " << engineCC << "\n";
    }
};

class Message
{
private:
    int messageID, senderID, receiverID;
    string content, timestamp;
    bool isRead;

public:
    static const int MAX_MSG_LEN = 500;

    Message()
        : messageID(0), senderID(0), receiverID(0),
          content(""), timestamp("N/A"), isRead(false) {}

    Message(int mid, int sid, int rid, const string &msg, const string &time)
        : messageID(mid), senderID(sid), receiverID(rid), isRead(false), timestamp(time)
    {
        content = (msg.size() > MAX_MSG_LEN) ? msg.substr(0, MAX_MSG_LEN) : msg;
    }

    Message(const Message &m)
        : messageID(m.messageID), senderID(m.senderID),
          receiverID(m.receiverID), content(m.content),
          timestamp(m.timestamp), isRead(m.isRead) {}

    int getMessageID() const { return messageID; }
    int getSenderID() const { return senderID; }
    int getReceiverID() const { return receiverID; }
    string getContent() const { return content; }
    bool getIsRead() const { return isRead; }
    void markAsRead() { isRead = true; }

    bool belongsToUser(int uid) const
    {
        return (senderID == uid || receiverID == uid);
    }

    void display() const
    {
        cout << "[MSG #" << messageID << "] From #" << senderID
             << " -> To #" << receiverID << "\n"
             << "\"" << content << "\"\n"
             << "Sent: " << timestamp
             << (isRead ? "  [READ]\n" : "  [UNREAD]\n");
    }

    bool operator==(const Message &other) const
    {
        return messageID == other.messageID;
    }
};

class CarListing : public IDisplayable, public ISearchable
{
private:
    int listingID, sellerID;
    Vehicle *vehiclePtr;
    Address location;
    long long price;
    string description, status;
    bool isFeatured;
    bool ownsVehicle;

public:
    static int totalListings;
    static const long long LISTING_FEE;

    CarListing()
        : listingID(0), sellerID(0), vehiclePtr(NULL),
          price(0), description(""), status("Pending"),
          isFeatured(false), ownsVehicle(false) {}

    CarListing(int lid, int sid, const Vehicle &v,
               const Address &addr, long long pr, const string &desc)
        : listingID(lid), sellerID(sid), location(addr),
          price(pr), description(desc), status("Pending"),
          isFeatured(false), ownsVehicle(false)
    {
        vehiclePtr = const_cast<Vehicle *>(&v);
        totalListings++;
    }

    CarListing(const CarListing &cl)
        : listingID(cl.listingID), sellerID(cl.sellerID),
          vehiclePtr(cl.vehiclePtr), location(cl.location),
          price(cl.price), description(cl.description),
          status(cl.status), isFeatured(cl.isFeatured),
          ownsVehicle(false) {}

    ~CarListing() {}

    int getListingID() const { return listingID; }
    int getSellerID() const { return sellerID; }
    long long getPrice() const { return price; }
    string getStatus() const { return status; }
    bool getIsFeatured() const { return isFeatured; }
    const Vehicle *getVehicle() const { return vehiclePtr; }
    const Address &getLocation() const { return location; }

    void setPrice(long long p)
    {
        if (p > 0)
            price = p;
    }
    void setDescription(const string &d) { description = d; }
    void setStatus(const string &s) { status = s; }
    void setFeatured(bool f) { isFeatured = f; }

    static int getTotalListings() { return totalListings; }

    void displayDetails() const override
    {
        cout << "\n  +------------------------------------------+\n";
        cout << "  | Listing #" << listingID
             << "  [" << status << "]"
             << (isFeatured ? "  * FEATURED" : "") << "\n";
        cout << "  +------------------------------------------+\n";
        if (vehiclePtr)
            vehiclePtr->displayDetails();
        location.display();
        cout << "  Price     : PKR " << price << "\n";
        cout << "  Desc      : " << description << "\n";
        cout << "  Seller ID : " << sellerID << "\n";
    }

    void display() const { displayDetails(); }

    bool matchesFilter(const string &brand, const string &mdl,
                       long long minP, long long maxP,
                       int minY, int maxY, int maxMil) const override
    {
        if (status != "Approved")
            return false;
        if (price < minP || price > maxP)
            return false;
        if (vehiclePtr)
            return vehiclePtr->matchesFilter(brand, mdl, minP, maxP, minY, maxY, maxMil);
        return false;
    }

    void updatePrice(long long newPrice)
    {
        if (newPrice > 0)
        {
            price = newPrice;
            cout << "  [Listing #" << listingID
                 << "] Price updated to PKR " << newPrice << "\n";
        }
    }

    void markAsSold()
    {
        status = "Sold";
        cout << "  [Listing #" << listingID << "] Marked as SOLD.\n";
    }

    bool operator==(const CarListing &other) const
    {
        return listingID == other.listingID;
    }

    bool operator<(const CarListing &other) const
    {
        return price < other.price;
    }

    friend ostream &operator<<(ostream &os, const CarListing &cl);

    friend void transferListing(CarListing &cl, int newSellerID);
};

int CarListing::totalListings = 0;
const long long CarListing::LISTING_FEE = 500;

ostream &operator<<(ostream &os, const CarListing &cl)
{
    os << "Listing #" << cl.listingID << " [" << cl.status << "] "
       << "PKR " << cl.price;
    return os;
}

void transferListing(CarListing &cl, int newSellerID)
{
    cout << "  [Transfer] Listing #" << cl.listingID
         << " moved from Seller #" << cl.sellerID
         << " to Seller #" << newSellerID << "\n";
    cl.sellerID = newSellerID;
}

class Seller;
class Buyer;

class User : public IDisplayable, public INotifiable
{
protected:
    int userID;
    string name, email, phone;
    string notifications[20];
    int notifCount;

public:
    static int totalUsers;

    User()
        : userID(0), name("Unknown"), email(""), phone(""),
          notifCount(0) { totalUsers++; }

    User(int uid, const string &nm, const string &em, const string &ph)
        : userID(uid), name(nm), email(em), phone(ph),
          notifCount(0) { totalUsers++; }

    User(const User &u)
        : userID(u.userID), name(u.name), email(u.email),
          phone(u.phone), notifCount(u.notifCount)
    {
        for (int i = 0; i < notifCount; i++)
            notifications[i] = u.notifications[i];
    }

    virtual ~User() {}

    int getUserID() const { return userID; }
    string getName() const { return name; }
    string getEmail() const { return email; }

    void setEmail(const string &e) { email = e; }
    void setPhone(const string &p) { phone = p; }

    void receiveNotification(const string &msg) override
    {
        if (notifCount < 20)
            notifications[notifCount++] = msg;
        cout << "  [Notification -> " << name << "]: " << msg << "\n";
    }

    void displayDetails() const override
    {
        cout << "\n  User #" << userID << " | " << name
             << " | " << email << "\n";
    }

    bool operator==(const User &other) const
    {
        return userID == other.userID;
    }

    friend ostream &operator<<(ostream &os, const User &u);

    friend void printSellerBuyerPair(const Seller &s, const Buyer &b);
};

int User::totalUsers = 0;

ostream &operator<<(ostream &os, const User &u)
{
    os << "User #" << u.userID << " [" << u.name << "] " << u.email;
    return os;
}

class Seller : public User, public IReviewable
{
private:
    string shopName;
    double rating;
    int totalSales;
    int listingIDs[50];
    int listingCount;

public:
    static int totalSellers;

    Seller()
        : User(), shopName(""), rating(0.0),
          totalSales(0), listingCount(0)
    {
        for (int i = 0; i < 50; i++)
            listingIDs[i] = 0;
        totalSellers++;
    }

    Seller(int sid, const string &nm, const string &em,
           const string &ph, const string &shop)
        : User(sid, nm, em, ph), shopName(shop),
          rating(0.0), totalSales(0), listingCount(0)
    {
        for (int i = 0; i < 50; i++)
            listingIDs[i] = 0;
        totalSellers++;
    }

    Seller(const Seller &s)
        : User(s), shopName(s.shopName), rating(s.rating),
          totalSales(s.totalSales), listingCount(s.listingCount)
    {
        for (int i = 0; i < 50; i++)
            listingIDs[i] = s.listingIDs[i];
    }

    double getRating() const override { return rating; }
    void updateRating(double r) override
    {
        if (r >= 0.0 && r <= 5.0)
            rating = r;
    }

    int getSellerID() const { return userID; }
    int getListingCount() const { return listingCount; }
    int getTotalSales() const { return totalSales; }
    static int getTotalSellers() { return totalSellers; }

    void addListingID(int lid)
    {
        if (listingCount < 50)
            listingIDs[listingCount++] = lid;
        else
            cout << "  [Seller #" << userID << "] Listing limit reached.\n";
    }

    void removeListingID(int lid)
    {
        for (int i = 0; i < listingCount; i++)
            if (listingIDs[i] == lid)
            {
                for (int j = i; j < listingCount - 1; j++)
                    listingIDs[j] = listingIDs[j + 1];
                listingCount--;
                return;
            }
    }

    void recordSale()
    {
        totalSales++;
        cout << "  [Seller: " << name << "] Sale recorded. Total: " << totalSales << "\n";
    }

    void displayDetails() const override
    {
        cout << "\n  Seller #" << userID << " | " << name
             << " | Shop: " << shopName << "\n";
        cout << "  Rating: " << rating << " | Sales: " << totalSales
             << " | Active Listings: " << listingCount << "\n";
    }

    void display() const { displayDetails(); }

    friend void printSellerBuyerPair(const Seller &s, const Buyer &b);
};

int Seller::totalSellers = 0;

class Buyer : public User
{
private:
    long long budget;
    int favouriteIDs[20];
    int favouriteCount;
    Message inbox[30];
    int inboxCount;

public:
    static int totalBuyers;

    Buyer()
        : User(), budget(0),
          favouriteCount(0), inboxCount(0)
    {
        for (int i = 0; i < 20; i++)
            favouriteIDs[i] = 0;
        totalBuyers++;
    }

    Buyer(int bid, const string &nm, const string &em,
          const string &ph, long long bud)
        : User(bid, nm, em, ph), budget(bud),
          favouriteCount(0), inboxCount(0)
    {
        for (int i = 0; i < 20; i++)
            favouriteIDs[i] = 0;
        totalBuyers++;
    }

    Buyer(const Buyer &b)
        : User(b), budget(b.budget),
          favouriteCount(b.favouriteCount), inboxCount(b.inboxCount)
    {
        for (int i = 0; i < 20; i++)
            favouriteIDs[i] = b.favouriteIDs[i];
        for (int i = 0; i < 30; i++)
            inbox[i] = b.inbox[i];
    }

    int getBuyerID() const { return userID; }
    long long getBudget() const { return budget; }
    int getFavCount() const { return favouriteCount; }
    int getFavID(int i) const { return (i >= 0 && i < favouriteCount) ? favouriteIDs[i] : -1; }
    static int getTotalBuyers() { return totalBuyers; }

    void setBudget(long long b)
    {
        if (b > 0)
            budget = b;
    }

    void saveFavourite(int lid)
    {
        if (favouriteCount < 20)
        {
            favouriteIDs[favouriteCount++] = lid;
            cout << "  [Buyer: " << name << "] Saved listing #" << lid << "\n";
        }
    }

    void receiveMessage(const Message &msg)
    {
        if (inboxCount < 30)
            inbox[inboxCount++] = msg;
    }

    void displayInbox() const
    {
        cout << "\n  --- Inbox for " << name << " ---\n";
        if (!inboxCount)
        {
            cout << "  No messages.\n";
            return;
        }
        for (int i = 0; i < inboxCount; i++)
            inbox[i].display();
    }

    void displayDetails() const override
    {
        cout << "\n  Buyer #" << userID << " | " << name
             << " | Budget: PKR " << budget << "\n";
        cout << "  Saved Listings: " << favouriteCount
             << " | Messages: " << inboxCount << "\n";
    }

    void display() const { displayDetails(); }

    Buyer operator+(const Buyer &other) const
    {
        Buyer combined(*this);
        combined.budget += other.budget;
        return combined;
    }

    friend void mergeBuyerFavourites(const Buyer &a, const Buyer &b);

    friend void printSellerBuyerPair(const Seller &s, const Buyer &b);

    friend class Marketplace;
};

int Buyer::totalBuyers = 0;

void mergeBuyerFavourites(const Buyer &a, const Buyer &b)
{
    cout << "\n  [Merge Favourites: " << a.name << " + " << b.name << "]\n";
    cout << "  Combined list: ";
    for (int i = 0; i < a.favouriteCount; i++)
        cout << "#" << a.favouriteIDs[i] << " ";
    for (int i = 0; i < b.favouriteCount; i++)
        cout << "#" << b.favouriteIDs[i] << " ";
    cout << "\n";
}

class Admin : public User
{
private:
    string role;
    int actionsCount;
    bool isActive;

public:
    static const int MAX_ACTIONS = 1000;

    Admin()
        : User(), role("Moderator"), actionsCount(0), isActive(true) {}

    Admin(int aid, const string &nm, const string &em, const string &rl)
        : User(aid, nm, em, ""), role(rl), actionsCount(0), isActive(true) {}

    Admin(const Admin &a)
        : User(a), role(a.role), actionsCount(a.actionsCount), isActive(a.isActive) {}

    int getAdminID() const { return userID; }
    int getActionsCount() const { return actionsCount; }
    bool getIsActive() const { return isActive; }
    void deactivate() { isActive = false; }

    void approveListing(CarListing &cl) const
    {
        cl.setStatus("Approved");
        cout << "  [Admin: " << name << "] Approved listing #"
             << cl.getListingID() << "\n";
    }

    void rejectListing(CarListing &cl)
    {
        cl.setStatus("Rejected");
        actionsCount++;
        cout << "  [Admin: " << name << "] Rejected listing #"
             << cl.getListingID() << "\n";
    }

    void featureListing(CarListing &cl)
    {
        cl.setFeatured(true);
        actionsCount++;
        cout << "  [Admin: " << name << "] Featured listing #"
             << cl.getListingID() << "\n";
    }

    void displayDetails() const override
    {
        cout << "\n  Admin #" << userID << " | " << name
             << " | Role: " << role
             << " | Actions: " << actionsCount << "\n";
    }

    void display() const { displayDetails(); }
};

class SearchFilter
{
private:
    string brand, model, city;
    long long minPrice, maxPrice;
    int minYear, maxYear, maxMileage;

public:
    static const long long MAX_PRICE_LIMIT;

    SearchFilter()
        : brand(""), model(""), city(""),
          minPrice(0), maxPrice(1000000000LL),
          minYear(1980), maxYear(2025), maxMileage(999999) {}

    SearchFilter(const string &br, const string &mo,
                 long long minP, long long maxP, int minY, int maxY,
                 int maxMil, const string &ci = "")
        : brand(br), model(mo), city(ci),
          minPrice(minP), maxPrice(maxP),
          minYear(minY), maxYear(maxY), maxMileage(maxMil) {}

    void setBrand(const string &b) { brand = b; }
    void setModel(const string &m) { model = m; }
    void setCity(const string &c) { city = c; }
    void setMinPrice(long long p) { minPrice = p; }
    void setMaxPrice(long long p) { maxPrice = p; }
    void setMinYear(int y) { minYear = y; }
    void setMaxYear(int y) { maxYear = y; }
    void setMaxMileage(int m) { maxMileage = m; }

    string getBrand() const { return brand; }
    string getModel() const { return model; }
    string getCity() const { return city; }
    long long getMinPrice() const { return minPrice; }
    long long getMaxPrice() const { return maxPrice; }
    int getMinYear() const { return minYear; }
    int getMaxYear() const { return maxYear; }
    int getMaxMileage() const { return maxMileage; }

    void display() const
    {
        cout << "\n  [Search Filter]\n";
        cout << "  Brand   : " << (brand.empty() ? "Any" : brand) << "\n";
        cout << "  Model   : " << (model.empty() ? "Any" : model) << "\n";
        cout << "  City    : " << (city.empty() ? "Any" : city) << "\n";
        cout << "  Price   : PKR " << minPrice << " - " << maxPrice << "\n";
        cout << "  Year    : " << minYear << " - " << maxYear << "\n";
        cout << "  Mileage : up to " << maxMileage << " km\n";
    }

    void reset()
    {
        brand = model = city = "";
        minPrice = 0;
        maxPrice = 1000000000LL;
        minYear = 1980;
        maxYear = 2025;
        maxMileage = 999999;
    }

    bool applyTo(const CarListing &cl) const
    {
        return cl.matchesFilter(brand, model, minPrice, maxPrice,
                                minYear, maxYear, maxMileage);
    }

    bool operator==(const SearchFilter &other) const
    {
        return brand == other.brand && model == other.model &&
               minPrice == other.minPrice && maxPrice == other.maxPrice;
    }
};

const long long SearchFilter::MAX_PRICE_LIMIT = 1000000000LL;

class Review
{
private:
    int reviewID, sellerID, buyerID, stars;
    string comment, date;

public:
    static const int MAX_STARS = 5;

    Review()
        : reviewID(0), sellerID(0), buyerID(0),
          stars(0), comment(""), date("N/A") {}

    Review(int rid, int sid, int bid, int s,
           const string &cmt, const string &dt)
        : reviewID(rid), sellerID(sid), buyerID(bid), date(dt)
    {
        stars = (s >= 1 && s <= MAX_STARS) ? s : 1;
        comment = cmt;
    }

    Review(const Review &r)
        : reviewID(r.reviewID), sellerID(r.sellerID),
          buyerID(r.buyerID), stars(r.stars),
          comment(r.comment), date(r.date) {}

    int getReviewID() const { return reviewID; }
    int getSellerID() const { return sellerID; }
    int getBuyerID() const { return buyerID; }
    int getStars() const { return stars; }
    string getComment() const { return comment; }

    bool isPositive() const { return stars >= 4; }
    bool isForSeller(int sid) const { return sellerID == sid; }
    void updateComment(const string &cmt) { comment = cmt; }

    void display() const
    {
        cout << "  Review #" << reviewID << " | Stars: "
             << stars << "/" << MAX_STARS << "\n";
        cout << "  \"" << comment << "\"  (" << date << ")\n";
    }

    bool operator<=(const Review &other) const { return stars <= other.stars; }
    bool operator>=(const Review &other) const { return stars >= other.stars; }
};

class Marketplace
{
private:
    CarListing listings[200];
    int listingCount;

    Seller sellers[50];
    int sellerCount;

    Buyer buyers[100];
    int buyerCount;

    Message msgLog[500];
    int msgCount;

    Review reviews[300];
    int reviewCount;

    string platformName;
    static int totalTransactions;

public:
    static const int MAX_LISTINGS = 200;

    Marketplace()
        : listingCount(0), sellerCount(0), buyerCount(0),
          msgCount(0), reviewCount(0), platformName("CarMarket PK") {}

    Marketplace(const string &name)
        : listingCount(0), sellerCount(0), buyerCount(0),
          msgCount(0), reviewCount(0), platformName(name) {}

    static int getTotalTransactions() { return totalTransactions; }

    bool addListing(const CarListing &cl)
    {
        if (listingCount >= MAX_LISTINGS)
        {
            cout << "  [Marketplace] Listing limit reached.\n";
            return false;
        }
        listings[listingCount++] = cl;
        cout << "  [Marketplace] Listing #" << cl.getListingID() << " added.\n";
        return true;
    }

    bool deleteListing(int lid)
    {
        for (int i = 0; i < listingCount; i++)
            if (listings[i].getListingID() == lid)
            {
                for (int j = i; j < listingCount - 1; j++)
                    listings[j] = listings[j + 1];
                listingCount--;
                cout << "  [Marketplace] Listing #" << lid << " deleted.\n";
                return true;
            }
        cout << "  [Marketplace] Listing #" << lid << " not found.\n";
        return false;
    }

    bool updateListingPrice(int lid, long long newPrice)
    {
        for (int i = 0; i < listingCount; i++)
            if (listings[i].getListingID() == lid)
            {
                listings[i].updatePrice(newPrice);
                return true;
            }
        return false;
    }

    void approveListing(int lid)
    {
        for (int i = 0; i < listingCount; i++)
            if (listings[i].getListingID() == lid)
            {
                listings[i].setStatus("Approved");
                cout << "  [Marketplace] Listing #" << lid << " approved.\n";
                return;
            }
    }

    void searchListings(const SearchFilter &sf) const
    {
        cout << "\n  === Search Results ===\n";
        int found = 0;
        for (int i = 0; i < listingCount; i++)
            if (sf.applyTo(listings[i]))
            {
                listings[i].displayDetails();
                found++;
            }
        cout << (found ? "  Total found: " : "  No listings matched. Found: ")
             << found << "\n";
    }

    void logMessage(const Message &msg)
    {
        if (msgCount < 500)
            msgLog[msgCount++] = msg;
    }

    void addReview(const Review &rv)
    {
        if (reviewCount < 300)
        {
            reviews[reviewCount++] = rv;
            cout << "  [Marketplace] Review #" << rv.getReviewID() << " added.\n";
        }
    }

    void displayAllListings() const
    {
        cout << "\n  === All Listings on " << platformName << " ===\n";
        for (int i = 0; i < listingCount; i++)
            listings[i].displayDetails();
        cout << "  Total: " << listingCount << "\n";
    }

    static void recordTransaction()
    {
        totalTransactions++;
        cout << "  [Marketplace] Transaction recorded. Total: "
             << totalTransactions << "\n";
    }

    friend void printSellerBuyerPair(const Seller &s, const Buyer &b);
};

int Marketplace::totalTransactions = 0;

void printSellerBuyerPair(const Seller &s, const Buyer &b)
{
    cout << "\n  [Pair] Seller: " << s.name
         << " <-> Buyer: " << b.name
         << " | Budget vs Shop: PKR " << b.budget
         << " at " << s.shopName << "\n";
}

int main()
{
    cout << "======================================================\n";
    cout << "   CAR MARKETPLACE SYSTEM                             \n";
    cout << "======================================================\n";

    Car car1("Toyota", "Corolla", 2020, "White", "Petrol", 45000,
             4, "Sedan", true);
    Car car2("Honda", "Civic", 2018, "Black", "Petrol", 80000,
             4, "Sedan", true);
    Car car3("Suzuki", "Swift", 2022, "Red", "Petrol", 15000,
             5, "Hatchback", false);
    Car car4("Honda", "City", 2019, "Silver", "Hybrid", 60000,
             4, "Sedan", true);
    Bike bike1("Yamaha", "YBR 125", 2021, "Blue", "Petrol", 20000,
               125, "Standard");

    Vehicle *vehicles[] = {&car1, &car2, &car3, &car4, &bike1};
    for (int i = 0; i < 5; i++)
        vehicles[i]->displayDetails();

    cout << "  car1 == car2  (same make/model/year)? "
         << (car1 == car2 ? "Yes" : "No") << "\n";
    cout << "  car1 < car2   (car 1 older or car 2)?            "
         << (car1 < car2 ? "Yes" : "No") << "\n";
    cout << "  car3 > car2   (car 3 is new or car 2)?            "
         << (car3 > car2 ? "Yes" : "No") << "\n";
    cout << "  car1 via <<: " << car1 << "\n";

    compareVehicles(car1, car2);

    cout << "\n  [+=] Adding 5000 km to car3\n";
    car3 += 5000;
    cout << "  car 3 mileage now: " << car3.getMileage() << " km\n";

    Address a1("Main Blvd", "Lahore", "Punjab", "670");
    Address a2("Tariq Road", "Karachi", "Sindh", "67600");
    Address a3("Blue Area", "Islamabad", "ICT", "67000");
    Address a4("Saddar Bazar", "Karachi", "Sindh", "676700");
    Address a5("Johar Town", "Lahore", "Punjab", "676767");
    
    cout << "  a 1 == a 5 (both Lahore)? " << (a1 == a5 ? "Yes" : "No") << "\n";
    cout << "  a 1 != a 2?               " << (a1 != a2 ? "Yes" : "No") << "\n";
    cout << "  a 2 via <<: " << a2 << "\n";

    CarListing cl1(101, 1, car1, a1, 3800000LL, "Excellent condition");
    CarListing cl2(102, 1, car2, a2, 4500000LL, "Fresh import");
    CarListing cl3(103, 2, car3, a3, 2200000LL, "Brand new look");
    CarListing cl4(104, 2, car4, a4, 3100000LL, "Clean");
    CarListing cl5(105, 3, bike1, a5, 280000LL, "Low mileage");

    cout << "  cl 3 cheaper than cl1? " << (cl3 < cl1 ? "Yes" : "No") << "\n";
    cout << "  cl 1 via <<: " << cl1 << "\n";

    Seller s1(1, "Ali Motors", "ali@motors.pk", "0300-6767676", "Ali Motors Lahore");
    Seller s2(2, "Karachi Cars", "kc@cars.pk", "0321-2267652", "Karachi Cars Hub");
    Seller s3(3, "Bike World", "bw@bikes.pk", "0333-3336767", "Bike World Lahore");

    Buyer b1(1, "Sunghoon", "sunghoon@mail.com", "0333-5555555", 4000000LL);
    Buyer b2(2, "Saba Batool", "saba@mail.com", "0312-6666666", 5000000LL);

    Admin admin1(1, "Haider Admin", "haider@pw.pk", "Super Admin");

    User *users[] = {&s1, &s2, &b1, &b2, &admin1};
    for (int i = 0; i < 5; i++)
        users[i]->displayDetails();
    cout << "  s 1 == s 2? " << (s1 == s2 ? "Yes" : "No") << "\n";
    cout << "  b 1 via <<: " << b1 << "\n";
    Buyer combined = b1 + b2;
    cout << "  Combined budget of " << b1.getName() << " + "
         << b2.getName() << " = PKR " << combined.getBudget() << "\n";

    Marketplace market("PakWheels Clone");

    s1.addListingID(101);
    s1.addListingID(102);
    s2.addListingID(103);
    s2.addListingID(104);
    s3.addListingID(105);

    market.addListing(cl1);
    market.addListing(cl2);
    market.addListing(cl3);
    market.addListing(cl4);
    market.addListing(cl5);

    market.approveListing(101);
    market.approveListing(102);
    market.approveListing(103);
    market.approveListing(104);
    market.approveListing(105);

    market.displayAllListings();

    cout << "\n--- Search: Honda cars under PKR 5,000,000 ---\n";
    SearchFilter sf1("Honda", "", 0, 5000000LL, 2015, 2025, 100000);
    sf1.display();
    market.searchListings(sf1);

    cout << "\n--- Search: Any car PKR 2M - 3.5M ---\n";
    SearchFilter sf2;
    sf2.setMinPrice(2000000LL);
    sf2.setMaxPrice(3500000LL);
    sf2.display();
    market.searchListings(sf2);

    SearchFilter sf3;
    sf3.setMinPrice(2000000LL);
    sf3.setMaxPrice(3500000LL);
    cout << "  sf2 == sf3 (same price range)? "
         << (sf2 == sf3 ? "Yes" : "No") << "\n";

    b1.saveFavourite(101);
    b1.saveFavourite(103);
    b2.saveFavourite(102);
    b2.saveFavourite(105);

    mergeBuyerFavourites(b1, b2);

    Message msg1(1, b1.getBuyerID(), s1.getSellerID(),
                 "Is the Corolla still available? Can we negotiate?",
                 "2025-06-01 10:30");
    market.logMessage(msg1);
    b1.receiveMessage(msg1);

    cout << "\n--- Buyer 1 Inbox ---\n";
    b1.displayInbox();

    s1.receiveNotification("Your listing #101 has been viewed 50 times!");
    b1.receiveNotification("Price drop on your saved listing #103!");

    cout << "\n--- Admin Actions ---\n";
    market.updateListingPrice(102, 4200000LL);
    cl1.markAsSold();
    admin1.rejectListing(cl3);
    admin1.featureListing(cl2);
    market.deleteListing(103);

    cout << "\n--- Reviews ---\n";
    Review rv1(1, s1.getSellerID(), b1.getBuyerID(),
               5, "Great seller, smooth transaction!", "2025-06-02");
    Review rv2(2, s1.getSellerID(), b2.getBuyerID(),
               4, "Good communication, fair price.", "2025-06-03");
    market.addReview(rv1);
    market.addReview(rv2);
    rv1.display();
    rv2.display();

    s1.updateRating(4.7);
    cout << "  Seller " << s1.getName() << " rating: " << s1.getRating() << "\n";

    cout << "  rv 1 >= rv 2 (rv 1 has higher/equal stars)? "
         << (rv1 >= rv2 ? "Yes" : "No") << "\n";

    cout << "\n--- [FRIEND FUNCTIONS] ---\n";

    transferListing(cl4, 1);

    printSellerBuyerPair(s1, b1);

    cout << "\n--- Platform Stats ---\n";
    cout << "  Total Listings Created : " << CarListing::getTotalListings() << "\n";
    cout << "  Total Sellers          : " << Seller::getTotalSellers() << "\n";
    cout << "  Total Buyers           : " << Buyer::getTotalBuyers() << "\n";
    cout << "  Total Users (base)     : " << User::totalUsers << "\n";
    cout << "  Listing Fee            : PKR " << CarListing::LISTING_FEE << "\n";
    cout << "  Vehicle Max Mileage    : " << Vehicle::MAX_MILEAGE << " km\n";

    Marketplace::recordTransaction();
    Marketplace::recordTransaction();

    cout << "\n--- Seller Profiles ---\n";
    s1.display();
    s2.display();
    s3.display();
    cout << "\n--- Buyer Profiles ---\n";
    b1.display();
    b2.display();
    cout << "\n--- Admin Profile ---\n";
    admin1.display();

    return 0;
}
