#include <iostream>
#include <string>
using namespace std;

//  CLASS 1: Address
//  PURPOSE: Stores city/location of a car listing.
//           Embedded inside CarListing by value => COMPOSITION.
class Address
{
private:
    string street;
    string city;
    string province;
    string country;
    string postalCode;

public:
    Address()
    {
        street = "N/A";
        city = "N/A";
        province = "N/A";
        country = "Pakistan";
        postalCode = "00000";
    }

    Address(const string &st, const string &ci, const string &pr, const string &pc, const string &co = "Pakistan")
    {
        street = st;
        city = ci;
        province = pr;
        postalCode = pc;
        country = co;
    }

    Address(const Address &a)
    {
        street = a.street;
        city = a.city;
        province = a.province;
        country = a.country;
        postalCode = a.postalCode;
    }

    string getCity() const
    {
        return city;
    }
    string getProvince() const
    {
        return province;
    }

    void setCity(const string &c)
    {
        city = c;
    }

    string getFullAddress() const
    {
        return street + ", " + city + ", " + province + " - " + country + " " + postalCode;
    }

    void display() const
    {
        cout << "  Location  : " << getFullAddress() << "\n";
    }

    void update(const string &st, const string &ci, const string &pr, const string &pc)
    {
        street = st;
        city = ci;
        province = pr;
        postalCode = pc;
    }

    bool isInCity(const string &c) const
    {
        return city == c;
    }
};

//  CLASS 2: Vehicle
//  PURPOSE: Stores car's technical details (make, model, year, mileage, etc.)
//           Embedded inside CarListing by value => COMPOSITION.
class Vehicle
{
private:
    string make;
    string model;
    int year;
    string color;
    string engineType;
    int mileage;

public:
    static const int MAX_MILEAGE = 999999;
    static const int MIN_YEAR = 1980;

    Vehicle()
    {
        make = "Unknown";
        model = "Unknown";
        year = 2000;
        color = "White";
        engineType = "Petrol";
        mileage = 0;
    }

    Vehicle(const string &mk, const string &mo, int yr, const string &col, const string &eng, int mil)
    {
        make = mk;
        model = mo;
        color = col;
        engineType = eng;
        year = (yr >= MIN_YEAR && yr <= 2025) ? yr : MIN_YEAR;
        mileage = (mil >= 0 && mil <= MAX_MILEAGE) ? mil : 0;
    }

    Vehicle(const Vehicle &v)
    {
        make = v.make;
        model = v.model;
        year = v.year;
        color = v.color;
        engineType = v.engineType;
        mileage = v.mileage;
    }

    string getMake() const
    {
        return make;
    }
    string getModel() const
    {
        return model;
    }

    int getYear() const
    {
        return year;
    }

    string getEngineType() const
    {
        return engineType;
    }

    int getMileage() const
    {
        return mileage;
    }

    void setColor(const string &c)
    {
        color = c;
    }
    void setMileage(int m)
    {
        if (m >= 0 && m <= MAX_MILEAGE)
            mileage = m;
    }

    void display() const
    {
        cout << "  Vehicle   : " << year << " " << make << " " << model << "\n";
        cout << "  Color     : " << color << "\n";
        cout << "  Engine    : " << engineType << "\n";
        cout << "  Mileage   : " << mileage << " km\n";
    }

    int getAge() const
    {
        return 2025 - year;
    }

    bool matchesBrand(const string &brand) const
    {
        if (brand.empty())
            return true;
        return make == brand;
    }

    bool matchesModel(const string &mdl) const
    {
        if (mdl.empty())
            return true;
        return model == mdl;
    }
};

//  CLASS 3: Message
//  PURPOSE: Chat message from buyer to seller.
//           Stored in Buyer::inbox[] (aggregation) and Marketplace::msgLog[].

class Message
{
private:
    int messageID;
    int senderID;
    int receiverID;
    string content;
    string timestamp;
    bool isRead;

public:
    static const int MAX_MSG_LEN = 500;

    Message() : messageID(0), senderID(0), receiverID(0), content(""), timestamp("N/A"), isRead(false)
    {
    }

    Message(int mid, int sid, int rid, const string &msg, const string &time) : messageID(mid), senderID(sid), receiverID(rid), isRead(false), timestamp(time)
    {
        content = (msg.size() > MAX_MSG_LEN) ? msg.substr(0, MAX_MSG_LEN) : msg;
    }

    Message(const Message &m) : messageID(m.messageID), senderID(m.senderID), receiverID(m.receiverID), content(m.content), timestamp(m.timestamp), isRead(m.isRead)
    {
    }

    int getMessageID() const
    {
        return messageID;
    }
    int getSenderID() const
    {
        return senderID;
    }
    int getReceiverID() const
    {
        return receiverID;
    }
    string getContent() const
    {
        return content;
    }
    bool getIsRead() const
    {
        return isRead;
    }

    void markAsRead()
    {
        isRead = true;
    }

    void display() const
    {
        cout << "[MSG #" << messageID << "] " << "From #" << senderID << " -> To #" << receiverID << "\n"
             << "\"" << content << "\"\n"
             << "Sent: " << timestamp << (isRead ? "  [READ]\n" : "  [UNREAD]\n");
    }

    bool belongsToUser(int uid) const
    {
        return (senderID == uid || receiverID == uid);
    }
};

//  CLASS 4: CarListing
//  PURPOSE: One car ad on the platform. Contains a Vehicle and Address
//           by value => COMPOSITION (they live and die with the listing).
//           Also tracks total listings via a STATIC member.
class CarListing
{
private:
    int listingID;
    int sellerID;
    Vehicle vehicle;
    Address location;
    double price;
    string description;
    string status;
    bool isFeatured;

public:
    static int totalListings;

    static const double LISTING_FEE;

    CarListing()
    {
        listingID = 0;
        sellerID = 0;
        price = 0.0;
        description = "";
        status = "Pending";
        isFeatured = false;
    }

    CarListing(int lid, int sid, const Vehicle &v, const Address &addr, double pr, const string &desc)
    {
        listingID = lid;
        sellerID = sid;
        vehicle = v;
        location = addr;
        price = pr;
        description = desc;
        status = "Pending";
        isFeatured = false;
        totalListings++;
    }

    CarListing(const CarListing &cl)
    {
        listingID = cl.listingID;
        sellerID = cl.sellerID;
        vehicle = cl.vehicle;
        location = cl.location;
        price = cl.price;
        description = cl.description;
        status = cl.status;
        isFeatured = cl.isFeatured;
    }

    int getListingID() const
    {
        return listingID;
    }
    int getSellerID() const
    {
        return sellerID;
    }
    double getPrice() const
    {
        return price;
    }
    string getStatus() const
    {
        return status;
    }
    bool getIsFeatured() const
    {
        return isFeatured;
    }

    const Vehicle &getVehicle() const
    {
        return vehicle;
    }
    const Address &getLocation() const
    {
        return location;
    }

    void setPrice(double p)
    {
        if (p > 0)
        {
            price = p;
        }
    }

    void setDescription(const string &d)
    {
        description = d;
    }
    void setStatus(const string &s)
    {
        status = s;
    }
    void setFeatured(bool f) { isFeatured = f; }

    static int getTotalListings() { return totalListings; }

    void display() const
    {
        cout << "\n  +------------------------------------------+\n";
        cout << "  | Listing #" << listingID
             << "  [" << status << "]"
             << (isFeatured ? "  * FEATURED" : "") << "\n";
        cout << "  +------------------------------------------+\n";
        vehicle.display();
        location.display();
        cout << "  Price     : PKR " << price << "\n";
        cout << "  Desc      : " << description << "\n";
        cout << "  Seller ID : " << sellerID << "\n";
    }

    bool matchesFilter(const string &brand, const string &mdl, double minP, double maxP, int minY, int maxY, int maxMil) const
    {
        if (status != "Approved")
            return false;
        if (!vehicle.matchesBrand(brand))
            return false;
        if (!vehicle.matchesModel(mdl))
            return false;
        if (price < minP || price > maxP)
            return false;
        if (vehicle.getYear() < minY || vehicle.getYear() > maxY)
            return false;
        if (vehicle.getMileage() > maxMil)
            return false;
        return true;
    }

    void updatePrice(double newPrice)
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
};

int CarListing::totalListings = 0;
const double CarListing::LISTING_FEE = 500.0;

//  CLASS 5: Seller
//  PURPOSE: A person/dealer who posts car listings.
//           Stores listing IDs only (not objects) => AGGREGATION with CarListing.

class Seller
{
private:
    int sellerID;
    string name;
    string email;
    string phone;
    string shopName;
    double rating;
    int totalSales;
    int listingIDs[50];
    int listingCount;

public:
    static int totalSellers;

    Seller()
    {
        sellerID = 0;
        name = "Unknown";
        email = "";
        phone = "";
        shopName = "";
        rating = 0.0;
        totalSales = 0;
        listingCount = 0;
        for (int i = 0; i < 50; i++)
            listingIDs[i] = 0;
    }

    Seller(int sid, const string &nm, const string &em,
           const string &ph, const string &shop)
    {
        sellerID = sid;
        name = nm;
        email = em;
        phone = ph;
        shopName = shop;
        rating = 0.0;
        totalSales = 0;
        listingCount = 0;
        for (int i = 0; i < 50; i++)
            listingIDs[i] = 0;
        totalSellers++;
    }

    Seller(const Seller &s)
    {
        sellerID = s.sellerID;
        name = s.name;
        email = s.email;
        phone = s.phone;
        shopName = s.shopName;
        rating = s.rating;
        totalSales = s.totalSales;
        listingCount = s.listingCount;
        for (int i = 0; i < 50; i++)
            listingIDs[i] = s.listingIDs[i];
    }

    int getSellerID() const
    {
        return sellerID;
    }
    string getName() const
    {
        return name;
    }
    string getEmail() const
    {
        return email;
    }
    double getRating() const
    {
        return rating;
    }
    int getListingCount() const
    {
        return listingCount;
    }
    static int getTotalSellers()
    {
        return totalSellers;
    }

    void setRating(double r)
    {
        if (r >= 0.0 && r <= 5.0)
        {
            rating = r;
        }
    }
    void setEmail(const string &e)
    {
        email = e;
    }
    void setPhone(const string &p)
    {
        phone = p;
    }

    void addListingID(int lid)
    {
        if (listingCount < 50)
        {
            listingIDs[listingCount++] = lid;
        }
        else
        {
            cout << "  [Seller #" << sellerID << "] Listing limit reached.\n";
        }
    }

    void removeListingID(int lid)
    {
        for (int i = 0; i < listingCount; i++)
        {
            if (listingIDs[i] == lid)
            {
                for (int j = i; j < listingCount - 1; j++)
                    listingIDs[j] = listingIDs[j + 1];
                listingCount--;
                return;
            }
        }
    }

    void recordSale()
    {
        totalSales++;
        cout << "  [Seller: " << name << "] Sale recorded. Total: " << totalSales << "\n";
    }

    void display() const
    {
        cout << "\n  Seller #" << sellerID << " | " << name << " | Shop: " << shopName << "\n";
        cout << "  Rating: " << rating << " | Sales: " << totalSales << " | Active Listings: " << listingCount << "\n";
    }
};

int Seller::totalSellers = 0;

//  CLASS 6: Buyer
//  PURPOSE: A user who searches, saves favourites, and sends messages.
//           Stores Message objects by value in inbox[] => AGGREGATION

class Buyer
{
private:
    int buyerID;
    string name;
    string email;
    string phone;
    double budget;
    int favouriteIDs[20];
    int favouriteCount;
    Message inbox[30];
    int inboxCount;

public:
    static int totalBuyers;

    Buyer()
    {
        buyerID = 0;
        name = "Unknown";
        email = "";
        phone = "";
        budget = 0.0;
        favouriteCount = 0;
        inboxCount = 0;
        for (int i = 0; i < 20; i++)
        {
            favouriteIDs[i] = 0;
        }
    }

    Buyer(int bid, const string &nm, const string &em, const string &ph, double bud)
    {
        buyerID = bid;
        name = nm;
        email = em;
        phone = ph;
        budget = bud;
        favouriteCount = 0;
        inboxCount = 0;
        for (int i = 0; i < 20; i++)
        {
            favouriteIDs[i] = 0;
        }
        totalBuyers++;
    }

    Buyer(const Buyer &b)
    {
        buyerID = b.buyerID;
        name = b.name;
        email = b.email;
        phone = b.phone;
        budget = b.budget;
        favouriteCount = b.favouriteCount;
        inboxCount = b.inboxCount;
        for (int i = 0; i < 20; i++)
        {
            favouriteIDs[i] = b.favouriteIDs[i];
        }
        for (int i = 0; i < 30; i++)
        {
            inbox[i] = b.inbox[i];
        }
    }

    int getBuyerID() const
    {
        return buyerID;
    }
    string getName() const
    {
        return name;
    }
    double getBudget() const
    {
        return budget;
    }
    static int getTotalBuyers()
    {
        return totalBuyers;
    }

    void setBudget(double b)
    {
        if (b > 0)
        {
            budget = b;
        }
    }
    void setPhone(const string &p)
    {
        phone = p;
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
        {
            inbox[inboxCount++] = msg;
        }
    }

    void displayInbox() const
    {
        cout << "\n  --- Inbox for " << name << " ---\n";
        if (inboxCount == 0)
        {
            cout << "  No messages.\n";
            return;
        }
        for (int i = 0; i < inboxCount; i++)
        {
            inbox[i].display();
        }
    }

    void display() const
    {
        cout << "\n  Buyer #" << buyerID << " | " << name << " | Budget: PKR " << budget << "\n";
        cout << "  Saved Listings: " << favouriteCount << " | Messages: " << inboxCount << "\n";
    }
};

int Buyer::totalBuyers = 0;

//  CLASS 7: Admin
//  PURPOSE: Platform moderator who approves/removes listings.
//           Has elevated permissions. Tracks actions taken.

class Admin
{
private:
    int adminID;
    string name;
    string email;
    string role;
    int actionsCount;
    bool isActive;

public:
    static const int MAX_ACTIONS = 1000;

    Admin()
    {
        adminID = 0;
        name = "Unknown";
        email = "";
        role = "Moderator";
        actionsCount = 0;
        isActive = true;
    }

    Admin(int aid, const string &nm, const string &em, const string &rl)
    {
        adminID = aid;
        name = nm;
        email = em;
        role = rl;
        actionsCount = 0;
        isActive = true;
    }

    Admin(const Admin &a)
    {
        adminID = a.adminID;
        name = a.name;
        email = a.email;
        role = a.role;
        actionsCount = a.actionsCount;
        isActive = a.isActive;
    }

    int getAdminID() const
    {
        return adminID;
    }
    string getName() const
    {
        return name;
    }
    int getActionsCount() const
    {
        return actionsCount;
    }
    bool getIsActive() const
    {
        return isActive;
    }

    void deactivate()
    {
        isActive = false;
    }

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
        cout << "  [Admin: " << name << "] Rejected listing #" << cl.getListingID() << "\n";
    }

    void featureListing(CarListing &cl)
    {
        cl.setFeatured(true);
        actionsCount++;
        cout << "  [Admin: " << name << "] Featured listing #" << cl.getListingID() << "\n";
    }

    void display() const
    {
        cout << "\n  Admin #" << adminID << " | " << name << " | Role: " << role << " | Actions: " << actionsCount << "\n";
    }
};

//  CLASS 8: SearchFilter
//  PURPOSE: Holds search criteria a buyer sets to find listings.
//           Used with CarListing::matchesFilter().

class SearchFilter
{
private:
    string brand;
    string model;
    string city;
    double minPrice;
    double maxPrice;
    int minYear;
    int maxYear;
    int maxMileage;

public:
    static const double MAX_PRICE_LIMIT;

    SearchFilter()
    {
        brand = "";
        model = "";
        city = "";
        minPrice = 0;
        maxPrice = 1000000000;
        minYear = 1980;
        maxYear = 2025;
        maxMileage = 999999;
    }

    SearchFilter(const string &br, const string &mo, double minP, double maxP, int minY, int maxY, int maxMil, const string &ci = "")
    {
        brand = br;
        model = mo;
        city = ci;
        minPrice = minP;
        maxPrice = maxP;
        minYear = minY;
        maxYear = maxY;
        maxMileage = maxMil;
    }

    void setBrand(const string &b)
    {
        brand = b;
    }
    void setModel(const string &m)
    {
        model = m;
    }
    void setCity(const string &c)
    {
        city = c;
    }
    void setMinPrice(double p)
    {
        minPrice = p;
    }
    void setMaxPrice(double p)
    {
        maxPrice = p;
    }
    void setMinYear(int y)
    {
        minYear = y;
    }
    void setMaxYear(int y)
    {
        maxYear = y;
    }
    void setMaxMileage(int m)
    {
        maxMileage = m;
    }

    string getBrand() const
    {
        return brand;
    }
    string getModel() const
    {
        return model;
    }
    string getCity() const
    {
        return city;
    }
    double getMinPrice() const
    {
        return minPrice;
    }
    double getMaxPrice() const
    {
        return maxPrice;
    }
    int getMinYear() const
    {
        return minYear;
    }
    int getMaxYear() const
    {
        return maxYear;
    }
    int getMaxMileage() const
    {
        return maxMileage;
    }

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
        brand = "";
        model = "";
        city = "";
        minPrice = 0;
        maxPrice = 1000000000;
        minYear = 1980;
        maxYear = 2025;
        maxMileage = 999999;
    }

    bool isActive() const
    {
        return (!brand.empty() || !model.empty() || !city.empty() || minPrice > 0 || maxPrice < 1000000000 || minYear > 1980 || maxYear < 2025 || maxMileage < 999999);
    }

    bool applyTo(const CarListing &cl) const
    {
        return cl.matchesFilter(brand, model, minPrice, maxPrice, minYear, maxYear, maxMileage);
    }
};

const double SearchFilter::MAX_PRICE_LIMIT = 1000000000.0;

//  CLASS 9: Review
//  PURPOSE: Buyer leaves a review for a Seller after a transaction.
//           Stored inside ReviewBoard (array of Reviews).

class Review
{
private:
    int reviewID;
    int sellerID;
    int buyerID;
    int stars;
    string comment;
    string date;

public:
    static const int MAX_STARS = 5;

    Review()
    {
        reviewID = 0;
        sellerID = 0;
        buyerID = 0;
        stars = 0;
        comment = "";
        date = "N/A";
    }

    Review(int rid, int sid, int bid, int s, const string &cmt, const string &dt)
    {
        reviewID = rid;
        sellerID = sid;
        buyerID = bid;
        stars = (s >= 1 && s <= MAX_STARS) ? s : 1;
        comment = cmt;
        date = dt;
    }

    Review(const Review &r)
    {
        reviewID = r.reviewID;
        sellerID = r.sellerID;
        buyerID = r.buyerID;
        stars = r.stars;
        comment = r.comment;
        date = r.date;
    }

    int getReviewID() const
    {
        return reviewID;
    }
    int getSellerID() const
    {
        return sellerID;
    }
    int getBuyerID() const
    {
        return buyerID;
    }
    int getStars() const
    {
        return stars;
    }
    string getComment() const
    {
        return comment;
    }

    void display() const
    {
        cout << "  Review #" << reviewID << " | Stars: " << stars << "/" << MAX_STARS << "\n";
        cout << "  \"" << comment << "\"  (" << date << ")\n";
    }

    bool isPositive() const
    {
        return stars >= 4;
    }

    void updateComment(const string &cmt)
    {
        comment = cmt;
    }

    bool isForSeller(int sid) const
    {
        return sellerID == sid;
    }
};

//  CLASS 10: Marketplace
//  PURPOSE: The central platform that manages all listings, sellers, buyers,
//           messages, and reviews. Holds arrays of objects for all entities.
//
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
    {
        listingCount = 0;
        sellerCount = 0;
        buyerCount = 0;
        msgCount = 0;
        reviewCount = 0;
        platformName = "CarMarket PK";
    }

    Marketplace(const string &name)
    {
        platformName = name;
        listingCount = 0;
        sellerCount = 0;
        buyerCount = 0;
        msgCount = 0;
        reviewCount = 0;
    }

    static int getTotalTransactions()
    {
        return totalTransactions;
    }

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
        {
            if (listings[i].getListingID() == lid)
            {
                for (int j = i; j < listingCount - 1; j++)
                {
                    listings[j] = listings[j + 1];
                }
                listingCount--;
                cout << "  [Marketplace] Listing #" << lid << " deleted.\n";
                return true;
            }
        }
        cout << "  [Marketplace] Listing #" << lid << " not found.\n";
        return false;
    }

    bool updateListingPrice(int lid, double newPrice)
    {
        for (int i = 0; i < listingCount; i++)
        {
            if (listings[i].getListingID() == lid)
            {
                listings[i].updatePrice(newPrice);
                return true;
            }
        }
        return false;
    }

    void searchListings(const SearchFilter &sf) const
    {
        cout << "\n  === Search Results ===\n";
        int found = 0;
        for (int i = 0; i < listingCount; i++)
        {
            if (sf.applyTo(listings[i]))
            {
                listings[i].display();
                found++;
            }
        }
        if (found == 0)
        {
            cout << "  No listings matched your search.\n";
        }
        else
        {
            cout << "  Total found: " << found << "\n";
        }
    }

    void logMessage(const Message &msg)
    {
        if (msgCount < 500)
        {
            msgLog[msgCount++] = msg;
        }
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
        {
            listings[i].display();
        }
        cout << "  Total: " << listingCount << "\n";
    }

    void approveListing(int lid)
    {
        for (int i = 0; i < listingCount; i++)
        {
            if (listings[i].getListingID() == lid)
            {
                listings[i].setStatus("Approved");
                cout << "  [Marketplace] Listing #" << lid << " approved.\n";
                return;
            }
        }
    }

    static void recordTransaction()
    {
        totalTransactions++;
        cout << "  [Marketplace] Transaction recorded. Total: " << totalTransactions << "\n";
    }
};


int Marketplace::totalTransactions = 0;

int main()
{
    cout << "======================================================\n";
    cout << "       CAR MARKETPLACE SYSTEM PakWheels Style       \n";
    cout << "======================================================\n";

    Marketplace market("PakWheels Clone");

    Seller s1(1, "Ali Motors", "ali@motors.pk", "0300-1111111", "Ali Motors Lahore");
    Seller s2(2, "Karachi Cars", "kc@cars.pk", "0321-2222222", "Karachi Cars Hub");

    Vehicle v1("Toyota", "Corolla", 2020, "White", "Petrol", 45000);
    Vehicle v2("Honda", "Civic", 2018, "Black", "Petrol", 80000);
    Vehicle v3("Suzuki", "Swift", 2022, "Red", "Petrol", 15000);
    Vehicle v4("Honda", "City", 2019, "Silver", "Hybrid", 60000);

    Address a1("Main Blvd", "Lahore", "Punjab", "54000");
    Address a2("Tariq Road", "Karachi", "Sindh", "75400");
    Address a3("Blue Area", "Islamabad", "ICT", "44000");
    Address a4("Saddar Bazar", "Karachi", "Sindh", "74200");

    CarListing cl1(101, 1, v1, a1, 3800000, "Excellent condition, one owner");
    CarListing cl2(102, 1, v2, a2, 4500000, "Well maintained, fresh import");
    CarListing cl3(103, 2, v3, a3, 2200000, "Brand new look, low mileage");
    CarListing cl4(104, 2, v4, a4, 3100000, "Fuel efficient hybrid, clean");

    s1.addListingID(101);
    s1.addListingID(102);
    s2.addListingID(103);
    s2.addListingID(104);

    market.addListing(cl1);
    market.addListing(cl2);
    market.addListing(cl3);
    market.addListing(cl4);

    Admin admin1(1, "Usman Admin", "usman@pw.pk", "Super Admin");
    market.approveListing(101);
    market.approveListing(102);
    market.approveListing(103);
    market.approveListing(104);

    cout << "\n--- Display All Listings ---\n";
    market.displayAllListings();

    Buyer b1(1, "Sara Khan", "sara@mail.com", "0333-5555555", 4000000);
    Buyer b2(2, "Umar Farooq", "umar@mail.com", "0312-6666666", 5000000);

    cout << "\n--- Search: Honda cars under PKR 5,000,000 ---\n";
    SearchFilter sf1("Honda", "", 0, 5000000, 2015, 2025, 100000);
    sf1.display();
    market.searchListings(sf1);

    cout << "\n--- Search: Any car between PKR 2M - 3.5M ---\n";
    SearchFilter sf2;
    sf2.setMinPrice(2000000);
    sf2.setMaxPrice(3500000);
    sf2.display();
    market.searchListings(sf2);

    b1.saveFavourite(101);
    b1.saveFavourite(103);

    Message msg1(1, b1.getBuyerID(), s1.getSellerID(), "Is the Corolla still available? Can we negotiate?", "2025-06-01 10:30");

    market.logMessage(msg1);
    b1.receiveMessage(msg1);

    cout << "\n--- Buyer 1 Inbox ---\n";
    b1.displayInbox();

    cout << "\n--- Update Listing #102 Price ---\n";
    market.updateListingPrice(102, 4200000);

    cout << "\n--- Mark Listing #101 as Sold ---\n";
    cl1.markAsSold();

    cout << "\n--- Admin Rejects Listing #103 ---\n";
    admin1.rejectListing(cl3);

    cout << "\n--- Delete Listing #103 ---\n";
    market.deleteListing(103);

    Review rv1(1, s1.getSellerID(), b1.getBuyerID(),
               5, "Great seller, smooth transaction!", "2025-06-02");
    market.addReview(rv1);
    rv1.display();

    cout << "\n--- Platform Stats ---\n";
    cout << "  Total Listings Created : " << CarListing::getTotalListings() << "\n";
    cout << "  Total Sellers          : " << Seller::getTotalSellers() << "\n";
    cout << "  Total Buyers           : " << Buyer::getTotalBuyers() << "\n";
    cout << "  Listing Fee            : PKR " << CarListing::LISTING_FEE << "\n";
    cout << "  Vehicle Max Mileage    : " << Vehicle::MAX_MILEAGE << " km\n";

    Marketplace::recordTransaction();

    cout << "\n--- Seller Profiles ---\n";
    s1.display();
    s2.display();
    cout << "\n--- Buyer Profiles ---\n";
    b1.display();
    b2.display();

    return 0;
}
