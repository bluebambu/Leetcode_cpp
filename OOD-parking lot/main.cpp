#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;


// enum type for Vehicle
enum class VehicleSize {
    Motorcycle,
    Compact,
    Large
};

class Vehicle {
public:
    virtual VehicleSize size() {}
    virtual int spot_num() {}
};

class Bus: public Vehicle {
public:
    VehicleSize size() {
        return VehicleSize::Large;
    }
    int spot_num() {
        return 5;
    }
};

class Car: public Vehicle {
public:
    VehicleSize size() {
        return VehicleSize::Compact;
    }
    int spot_num() {
        return 1;
    }
};

class Motorcycle: public Vehicle {
public:
    VehicleSize size() {
        return VehicleSize::Motorcycle;
    }
    int spot_num() {
        return 1;
    }
};

class Level {
public:
    Level(int num_rows, int spots_per_row) {
        int moto = spots_per_row / 4;
        moto_spots.resize(moto);
        int car = spots_per_row / 4 * 3;
        compact_spots.resize(car - moto);
        large_spots.resize(spots_per_row - car);
    }

    bool park_vehicle(Vehicle* vehicle, VehicleSize size, int num) {
        if (size == VehicleSize::Motorcycle) {
            for (int i = 0; i < moto_spots.size(); ++i) {
                if (moto_spots[i] == NULL) {
                    moto_spots[i] = vehicle;
                    vehicle_to_spot[vehicle][VehicleSize::Motorcycle] = i;
                    return true;
                }
            }
            return false;
        } else if (size == VehicleSize::Compact) {
            for (int i = 0; i < compact_spots.size(); ++i) {
                if (compact_spots[i] == NULL) {
                    compact_spots[i] = vehicle;
                    vehicle_to_spot[vehicle][VehicleSize::Compact] = i;
                    return true;
                }
            }
            for (int i = 0; i < large_spots.size(); ++i) {
                if (large_spots[i] == NULL) {
                    large_spots[i] = vehicle;
                    vehicle_to_spot[vehicle][VehicleSize::Large] = i;
                    return true;
                }
            }
            return false;
        } else if (size == VehicleSize::Large) {
            for (int i = 0; i < large_spots.size(); ++i) {
                if (large_spots[i] == NULL) {
                    bool can_park = true;
                    for (int j = i; j < i + num; ++j) {
                        if (large_spots[j] != NULL) {
                            can_park = false;
                            break;
                        }
                    }
                    if (can_park) {
                        for (int j = i; j < i + num; ++j) {
                            large_spots[j] = vehicle;
                        }
                        vehicle_to_spot[vehicle][VehicleSize::Large] = i;
                        return true;
                    }
                }
            }
            return false;
        }
    }

    void unpark_vehicle(Vehicle *vehicle) {
        map<VehicleSize, int> spot = vehicle_to_spot[vehicle];
        VehicleSize size = vehicle->size();
        if (spot.count(size)) {
            int idx = spot[size];
            if (size == VehicleSize::Motorcycle) {
                moto_spots[idx] = NULL;
            } else if (size == VehicleSize::Compact) {
                compact_spots[idx] = NULL;
            } else {
                for (int i = idx; i < large_spots.size(); ++i) {
                    if (large_spots[i] == vehicle) {
                        large_spots[i] = NULL;
                    } else {
                        break;
                    }
                }
            }
        } else if (size == VehicleSize::Compact && spot.count(VehicleSize::Large)) {
            int idx = spot[VehicleSize::Large];
            large_spots[idx] = NULL;
        }
    }

private:
    vector<Vehicle*> moto_spots;
    vector<Vehicle*> compact_spots;
    vector<Vehicle*> large_spots;
    map<Vehicle*, map<VehicleSize, int>> vehicle_to_spot;
};

class ParkingLot {
public:
    // @param n number of leves
    // @param num_rows  each level has num_rows rows of spots
    // @param spots_per_row each row has spots_per_row spots
    ParkingLot(int n, int num_rows, int spots_per_row) {
        for (int i = 0; i < n; ++i) {
            Level *level = new Level(num_rows, spots_per_row);
            levels.push_back(level);
        }
    }

    // Park the vehicle in a spot (or multiple spots)
    // Return false if failed
    bool parkVehicle(Vehicle &vehicle) {
        for (int i = 0; i < levels.size(); ++i) {
            if (levels[i]->park_vehicle(&vehicle, vehicle.size(), vehicle.spot_num())) {
                vehicle_to_level[&vehicle] = levels[i];
                return true;
            }
        }
        return false;
    }

    // unPark the vehicle
    void unParkVehicle(Vehicle &vehicle) {
        Level *level = vehicle_to_level[&vehicle];
        if (level) {
            level->unpark_vehicle(&vehicle);
        }
    }
private:
    vector<Level*> levels;
    map<Vehicle*, Level*> vehicle_to_level;
};


int main()
{
	Solution a;

//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1),
                                                    new TreeNode(4)),
                                    new TreeNode(8, new TreeNode(7),
                                                    new TreeNode(9)));
    /*      6
        3       8
     1    4   7    9

    */


}
