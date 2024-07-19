#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <unordered_map>
#include <queue>
#include <climits>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Place {
    int id;
    string name;
    string type;
};

struct Edge {
    int start;
    int end;
    string type;
    int distance;
    bool car;
};

vector<Place> records;
vector<vector<Edge>> edges;
unordered_map<string, bool> UniqueType;

void setUpData() {
    records = {
        {0, "CopyCorner-Depot", "Xerox"},
        {1, "AidPlus_Pharmacy", "Pharmacies"},
        {2, "Airport_Public_Parking_Lot", "Parking_Lot"},
        {3, "Alok_Opticals", "Opticals"},
        {4, "Alok_Opticals", "Opticals"},
        {5, "Annapurna_Bakery", "Bakery"},
        {6, "Annapurna_Bakery", "Bakery"},
        {7, "Apex_Hospital", "Hospital"},
        {8, "Arogya_Hospital", "Hospital"},
        {9, "Baba_Vegetable_Shop", "Vegetable_Shop"},
        {10, "Baba_Vegetable_Shop", "Vegetable_Shop"},
        {11, "Bakehouse_Bakery", "Bakery_shop"},
        {12, "Bank_of_Maharastra", "Banks_and_ATMs"},
        {13, "Beauty_Bazaar", "Parler"},
        {14, "Beauty_Bazaar", "Parler"},
        {15, "Bharat_Library", "Library"},
        {16, "Bhel_Center", "Chat"},
        {17, "Bliss_Hospital", "Hospital"},
        {18, "Blossom_Hospital", "Hospital"}
    };

    edges.resize(records.size());

    // Seed the random number generator
    srand(time(0));

    // Create random edges between nodes
    int numEdges = 300; // Define the number of edges to create
    vector<string> roadTypes = {"Highways", "Secondary_roads", "Main_roads"};
    for (int i = 0; i < numEdges; ++i) {
        int start = rand() % records.size();
        int end = rand() % records.size();
        while (end == start) {
            end = rand() % records.size(); // Ensure start != end
        }
        string type = roadTypes[rand() % roadTypes.size()];
        int distance = (rand() % 5000) + 500; // Random distance between 500 and 5500
        bool car = rand() % 2; // Randomly allow or disallow cars

        edges[start].push_back({start, end, type, distance, car});
    }

    for (const auto &record : records) {
        UniqueType[record.type] = true;
    }
}

int getShortestDistanceByCar(int start, const string &end) {
    vector<bool> visited(edges.size(), false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    unordered_map<int, int> parent;
    vector<int> dis(edges.size(), INT_MAX);
    dis[start] = 0;

    int result = -1;

    while (!pq.empty()) {
        auto p = pq.top();
        int place = p.second;
        int l = p.first;
        pq.pop();

        if (visited[place])
            continue;

        visited[place] = true;

        if (records[place].type == end) {
            result = place;
            break;
        }

        for (const auto &in : edges[place]) {
            int placeN = in.end;
            int dist = in.distance;
            bool C = in.car;

            if (C && dis[placeN] > dis[place] + dist) {
                dis[placeN] = dis[place] + dist;
                parent[placeN] = place;
                pq.push({dis[placeN], placeN});
            }
        }
    }

    if (result == -1) {
        cout << "NO PATH FOUND FROM " << records[start].name << " TO " << end << " BY CAR" << endl;
        return -1;
    } else {
        vector<string> path;
        int current = result;
        while (current != start) {
            path.push_back(records[current].name);
            current = parent[current];
        }
        path.push_back(records[start].name);

        cout << "Nearest " << end << " from your location by car is " << records[result].name 
             << " at a distance of " << dis[result] << "m. The path is:" << endl;

        for (int i = path.size() - 1; i >= 0; i--) {
            cout << path[i];
            if (i > 0) cout << " -> ";
        }
        cout << endl;

        return dis[result];
    }
}

int NearServiceFromHomeByMode(int HomeId, string place) {
    while (!UniqueType.count(place)) {
        cout << "The place you entered is not recognized. Please try again." << endl;
        cout << "Enter the place you want to visit: ";
        cin >> place;
    }

    return getShortestDistanceByCar(HomeId, place);
}

// Base class User
class User {
protected:
    int id;
    string name;
    string email;
    string phone;

public:
    User(int id, string name, string email, string phone)
        : id(id), name(name), email(email), phone(phone) {}
    
    virtual void displayDetails() const {
        cout << "ID: " << id << ", Name: " << name << ", Email: " << email << ", Phone: " << phone << endl;
    }
    
    string getName() const {
        return name;
    }
};

// Derived class Driver
class Driver : public User {
private:
    string vehicleDetails;
    double rating;
    int ridesCompleted;

public:
    Driver(int id, string name, string email, string phone, string vehicleDetails)
        : User(id, name, email, phone), vehicleDetails(vehicleDetails), rating(0.0), ridesCompleted(0) {}
    void completeRide() { ridesCompleted++; }
    void updateRating(double newRating) { rating = (rating * ridesCompleted + newRating) / (ridesCompleted + 1); }
    void displayDetails()  {
        User::displayDetails();
        cout << "Vehicle: " << vehicleDetails << ", Rating: " << rating << ", Rides Completed: " << ridesCompleted << endl;
    }
};

// Derived class Rider
class Rider : public User {
private:
    double accountBalance;

public:
    Rider(int id, string name, string email, string phone)
        : User(id, name, email, phone), accountBalance(0.0) {}
    void addFunds(double amount) { accountBalance += amount; }
    bool pay(double amount) {
        if (accountBalance >= amount) {
            accountBalance -= amount;
            return true;
        }
        return false;
    }
    void displayDetails() const override {
        User::displayDetails();
        cout << "Account Balance: INR" << accountBalance << endl;
    }
};

// Class Ride
class Ride {
protected:
    int rideId;
    Driver &driver;
    Rider &rider;
    int pickup;
    string dropoff;
    bool isCompleted;
    const double pricePerKm = 50.0; // Price per km in INR
    double fare;

public:
    Ride(int rideId, Driver &driver, Rider &rider, int pickup, string dropoff)
        : rideId(rideId), driver(driver), rider(rider), pickup(pickup), dropoff(dropoff), isCompleted(false) {
        fare = calculateFare();
    }
    void completeRide() {
        if (rider.pay(fare)) {
            isCompleted = true;
            driver.completeRide();
            cout << "Ride completed. Fare: INR " << fare << endl;
        } else {
            cout << "Payment failed. Ride not completed." << endl;
        }
    }
    double calculateFare() const {
        int distance = NearServiceFromHomeByMode(pickup, dropoff);
        double distanceInKm=distance/1000.0;
        return distanceInKm * pricePerKm;
    }
    void displayDetails() const {
        cout << "Ride ID: " << rideId << ", Pickup: " << records[pickup].name << ", Dropoff: " << dropoff
             << ", Fare: INR " << fare << ", Status: " << (isCompleted ? "Completed" : "In Progress") << endl;
    }
};

// Class Payment
class Payment {
private:
    int paymentId;
    Rider &rider;
    double amount;

public:
    Payment(int paymentId, Rider &rider, double amount)
        : paymentId(paymentId), rider(rider), amount(amount) {}
    void processPayment() {
        if (rider.pay(amount)) {
            cout << "Payment of INR " << amount << " processed for " << rider.getName() << endl;
        } else {
            cout << "Payment failed for " << rider.getName() << endl;
        }
    }
};

// Class Review
class Review {
private:
    int reviewId;
    User &reviewer;
    string comments;
    int rating;

public:
    Review(int reviewId, User &reviewer, string comments, int rating)
        : reviewId(reviewId), reviewer(reviewer), comments(comments), rating(rating) {}
    void displayReview() const {
        cout << "Review by " << reviewer.getName() << ": " << comments << " (Rating: " << rating << "/5)" << endl;
    }
};

int main() {
    // Setting up data
    setUpData();

    // Creating driver and rider instances
    Driver driver1(1, "Nikhil", "nikhil.@example.com", "1234567890", "Car - ABC123");
    Rider rider1(2, "Vainavi", "vainavi.@example.com", "0987654321");

    // Adding funds to rider's account
    rider1.addFunds(1000.0);

    // Creating a ride
    Ride ride1(1, driver1, rider1, 0, "Hospital");
   

    // Processing a payment
    Payment payment1(1, rider1, 500.0);
    payment1.processPayment();
     ride1.completeRide();

    // Leaving a review
    Review review1(1, rider1, "Great ride!", 5);
    review1.displayReview();

    return 0;
}
