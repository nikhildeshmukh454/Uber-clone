# Ride-Sharing System

## Overview

This C++ application models a basic ride-sharing system, including classes for users (drivers and riders), locations, rides, payments, and reviews. The system allows for tracking rides, managing payments, and recording reviews, simulating a simplified version of a ride-sharing service.

## Components

### 1. **User Class**

The `User` class is a base class representing a general user with attributes:
- `id`: Unique identifier for the user.
- `name`: Name of the user.
- `email`: Email address of the user.
- `phone`: Phone number of the user.

**Public Methods:**
- `displayDetails()`: Displays the user's details.

### 2. **Driver Class**

The `Driver` class inherits from `User` and adds driver-specific attributes:
- `vehicleDetails`: Details about the vehicle driven by the driver.
- `rating`: Current rating of the driver.
- `ridesCompleted`: Number of rides completed by the driver.

**Public Methods:**
- `completeRide()`: Increments the count of completed rides.
- `updateRating(double newRating)`: Updates the driver's rating based on a new rating.
- `displayDetails()`: Displays the driver's details along with vehicle information, rating, and rides completed.

### 3. **Rider Class**

The `Rider` class also inherits from `User` and adds attributes specific to riders:
- `accountBalance`: Balance available in the rider's account.

**Public Methods:**
- `addFunds(double amount)`: Adds funds to the rider's account.
- `pay(double amount)`: Deducts the specified amount from the rider's account if sufficient balance is available.
- `displayDetails()`: Displays the rider's details along with account balance.

### 4. **Location Class**

The `Location` class represents a geographic location with:
- `name`: Name of the location.
- `coordinates`: Coordinates of the location (latitude and longitude).

**Public Methods:**
- `getName()`: Returns the name of the location.
- `getCoordinates()`: Returns the coordinates of the location.
- `displayDetails()`: Displays the location's name and coordinates.

### 5. **Ride Class**

The `Ride` class represents a ride between two locations and involves:
- `rideId`: Unique identifier for the ride.
- `driver`: The driver assigned to the ride.
- `rider`: The rider taking the ride.
- `pickup`: Pickup location.
- `dropoff`: Drop-off location.
- `fare`: Fare for the ride.
- `isCompleted`: Status of the ride (completed or in progress).

**Public Methods:**
- `completeRide()`: Completes the ride and processes the payment.
- `calculateFare()`: Calculates the fare based on the distance between pickup and drop-off locations.
- `displayDetails()`: Displays details of the ride including pickup and drop-off locations, fare, and status.

### 6. **Payment Class**

The `Payment` class manages payment transactions:
- `paymentId`: Unique identifier for the payment.
- `rider`: The rider making the payment.
- `amount`: Amount to be paid.

**Public Methods:**
- `processPayment()`: Processes the payment by deducting the amount from the rider's account.
- `displayDetails()`: Displays payment details including the status of the transaction.

### 7. **Review Class**

The `Review` class represents a review for a driver:
- `reviewId`: Unique identifier for the review.
- `driver`: The driver being reviewed.
- `rating`: Rating given in the review.
- `comment`: Review comment.

**Public Methods:**
- `displayDetails()`: Displays review details including rating and comment.

## Example Usage

The main function demonstrates the usage of the classes:
1. Creates instances of `Driver` and `Rider`.
2. Defines pickup and drop-off locations.
3. Adds funds to the rider's account.
4. Creates a `Ride` and completes it.
5. Displays ride details before and after completion.

```cpp
int main() {
    Driver driver1(1, "Rajesh Kumar", "rajesh@example.com", "9876543210", "Maruti Suzuki Swift");
    Rider rider1(1, "Anjali Sharma", "anjali@example.com", "9123456789");

    Location loc1("Connaught Place, Delhi", 28.6328, 77.2197);
    Location loc2("India Gate, Delhi", 28.6129, 77.2295);

    rider1.addFunds(1000.0);

    Ride ride1(1, driver1, rider1, loc1, loc2);
    ride1.displayDetails();
    ride1.completeRide();
    ride1.displayDetails();

    return 0;
}
