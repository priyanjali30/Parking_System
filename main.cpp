enum VehicleSize { Motorcycle, Compact, Large };

// Declaring a vehicle abstract class for our parking system
class Vehicle {
    vector<ParkingSpot> parkingSpots;
    string licensePlate;
    int spots;
    VehicleSize size;

public:
    int getSpotsNeeded() {
        return spots;
    }
    VehicleSize getSize() {
        return size;
    }
    // Park vehicle in the spot
    void parkInSpot(ParkingSpot spot) {
        parkingSpots.push_back(spot);
    }
    // Remove vehicle from spot
    
    void clearSpots() {
        for (int i = 0; i < parkingSpots.size(); i ++) {
            parkingSpots[i].removeVehicle();
        }
        parkingSpots.clear();
    }
    // Check if the spot is big enough for the vehicle
    virtual bool canFitInSpot(ParkingSpot spot) = 0;
};

class Bus : public Vehicle {
public:
    Bus() {
        spots = 5;
        size = Large;
    }
    // Check if the spot is a Large 
    // Does not check if there are 5 spots.
    bool canFitInSpot(ParkingSpot spot) {
        return spot.getSize() == Large;
    }
};

class Car : public Vehicle {
public:
    Car() {
        spots = 1;
        size = Compact;
    }
    // Check if the spot is a Compact or a Large
    bool canFitInSpot(ParkingSpot spot) {
        return spot.getSize() == Large || spot.getSize() == Compact;
    }
};

class Motorcycle : public Vehicle {
public:
    Motorcycle() {
        spots = 1;
        size = Motorcycle;
    }
    // Check if the spot is a Motorcycle, a Compact, or a Large
    bool canFitInSpot(ParkingSpot spot) {
        return true;
    }
};

class ParkingSpot {
    Vehicle vehicle;
    VehicleSize spotSize;
    int row;
    int spotNumber;
    Level level;

public:
    ParkingSpot(Level lvl, int r, int n, VehicleSize vs) {
        level = lvl;
        row = r;
        spotNumber = n;
        spotSize = vs;
    }

    bool isAvailable() {
        return vehicle == NULL;
    }

    // Check if the spot is big enough and is available
    // This compares the size only, does not check if it has enough spots
    bool canFitVehicle(Vehicle vehicle) {
        return isAvailable() && vehicle.canFitInSpot(this);
    }

    // Park vehicle in this spot
    bool park(Vehicle v) {
        if (!canFitVehicle(v)) {
            return false;
        }
        vehicle = v;
        vehicle.parkInSpot(this);
        return true;
    }

    int getRow() {
        return row;
    }

    int getSpotNumber() {
        return spotNumber;
    }

    VehicleSize getSize() {
        return spotSize;
    }

    // Remove vehicle from spot
    void removeVehicle() {
        vehicle = NULL;
    }
};
