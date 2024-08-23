#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <iomanip>
#include <fstream>  // For file handling

using namespace std;

class ParkingSlot {
public:
    int id;
    bool isOccupied;
    string vehicleNumber;

    ParkingSlot(int id) : id(id), isOccupied(false), vehicleNumber("") {}

    void occupySlot(string vehicleNo) {
        isOccupied = true;
        vehicleNumber = vehicleNo;
    }

    void freeSlot() {
        isOccupied = false;
        vehicleNumber = "";
    }
};

class ParkingLot {
public:
    vector<ParkingSlot> slots;
    map<int, time_t> entryTimes;  // Maps slotId to entry time

    ParkingLot(int totalSlots) {
        for (int i = 1; i <= totalSlots; i++) {
            ParkingSlot slot(i);
            slots.push_back(slot);
        }
    }

    int findFreeSlot() {
        for (size_t i = 0; i < slots.size(); ++i) {
            if (!slots[i].isOccupied) {
                return slots[i].id;
            }
        }
        return -1;
    }

    void occupySlot(int slotId, string vehicleNo) {
        slots[slotId - 1].occupySlot(vehicleNo);
        entryTimes[slotId] = time(0);
    }

    void freeSlot(int slotId) {
        slots[slotId - 1].freeSlot();
        entryTimes.erase(slotId);
    }

    void showAvailableSlots() {
        cout << "Available Slots: ";
        for (size_t i = 0; i < slots.size(); ++i) {
            if (!slots[i].isOccupied) {
                cout << slots[i].id << " ";
            }
        }
        cout << endl;
    }

    string getVehicleNumber(int slotId) {
        return slots[slotId - 1].vehicleNumber;
    }

    time_t getEntryTime(int slotId) {
        return entryTimes[slotId];
    }
};

class BillingSystem {
public:
    double calculateFee(time_t entryTime, time_t exitTime) {
        double duration = difftime(exitTime, entryTime) / 60.0;  // Duration in minutes
        return duration * 3.0;  // Charge ?3 per minute
    }

    double calculateTotalAmount(double fee, double additionalCharges) {
        return fee + additionalCharges;
    }

    void generateBill(int slotId, ParkingLot& lot) {
        if (lot.entryTimes.find(slotId) == lot.entryTimes.end()) {
            cout << "No entry record found for slot " << slotId << ".\n";
            return;
        }

        time_t exitTime = time(0);
        double fee = calculateFee(lot.getEntryTime(slotId), exitTime);
        double additionalCharges = 10.0;  // Example fixed additional charges (could be dynamic)
        double totalAmount = calculateTotalAmount(fee, additionalCharges);

        // Convert time to readable format
        char entryTimeStr[20];
        strftime(entryTimeStr, sizeof(entryTimeStr), "%Y-%m-%d %H:%M:%S", localtime(&lot.entryTimes[slotId]));
        char exitTimeStr[20];
        strftime(exitTimeStr, sizeof(exitTimeStr), "%Y-%m-%d %H:%M:%S", localtime(&exitTime));

        // Print the bill to the console in rupees
        cout << fixed << setprecision(2);
        cout << "Vehicle Number: " << lot.getVehicleNumber(slotId) << endl;
        cout << "Entry Time: " << entryTimeStr << " | Exit Time: " << exitTimeStr << endl;
        cout << "Parking Slot: " << slotId << " | Fee: ?" << fee << " | Additional Charges: ?" << additionalCharges << " | Total Amount: ?" << totalAmount << endl;

        // Write the bill to the file "records.txt"
        ofstream outFile("records.txt", ios::app);  // Open the file in append mode
        if (outFile.is_open()) {
            outFile << "Vehicle Number: " << lot.getVehicleNumber(slotId) << endl;
            outFile << "Entry Time: " << entryTimeStr << " | Exit Time: " << exitTimeStr << endl;
            outFile << "Parking Slot: " << slotId << " | Fee: ?" << fee << " | Additional Charges: ?" << additionalCharges << " | Total Amount: ?" << totalAmount << endl;
            outFile << "-----------------------------------------" << endl;
            outFile.close();
        } else {
            cout << "Error opening file.\n";
        }
    }
};

class AdminPanel {
public:
    void viewStatistics(ParkingLot& lot) {
        int occupiedSlots = 0;
        for (size_t i = 0; i < lot.slots.size(); ++i) {
            if (lot.slots[i].isOccupied) {
                occupiedSlots++;
            }
        }
        cout << "Total Slots: " << lot.slots.size() << " | Occupied: " << occupiedSlots << " | Available: " << (lot.slots.size() - occupiedSlots) << endl;
    }
};

class ParkingSystem {
public:
    ParkingLot lot;
    BillingSystem billing;
    AdminPanel admin;

    ParkingSystem(int totalSlots) : lot(totalSlots) {}

    void userInterface() {
        int choice;
        do {
            cout << "\n1. View Available Slots\n2. Reserve a Slot\n3. Free a Slot\n4. Generate Bill\n5. Admin Panel\n6. Exit\nEnter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    lot.showAvailableSlots();
                    break;
                case 2: {
                    int slotId = lot.findFreeSlot();
                    if (slotId != -1) {
                        string vehicleNo;
                        cout << "Enter Vehicle Number: ";
                        cin >> vehicleNo;
                        lot.occupySlot(slotId, vehicleNo);
                        cout << "Slot " << slotId << " reserved for vehicle " << vehicleNo << ".\n";
                    } else {
                        cout << "No available slots.\n";
                    }
                    break;
                }
                case 3: {
                    int slotId;
                    cout << "Enter Slot ID to free: ";
                    cin >> slotId;
                    if (lot.slots[slotId - 1].isOccupied) {
                        billing.generateBill(slotId, lot);
                        lot.freeSlot(slotId);
                        cout << "Slot " << slotId << " is now free.\n";
                    } else {
                        cout << "Slot " << slotId << " is already free.\n";
                    }
                    break;
                }
                case 4: {
                    int slotId;
                    cout << "Enter Slot ID to generate bill for: ";
                    cin >> slotId;
                    if (lot.slots[slotId - 1].isOccupied) {
                        billing.generateBill(slotId, lot);
                    } else {
                        cout << "Slot " << slotId << " is free and has no active bill.\n";
                    }
                    break;
                }
                case 5:
                    admin.viewStatistics(lot);
                    break;
                case 6:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice, try again.\n";
            }
        } while (choice != 6);
    }
};

int main() {
    int totalSlots;
    cout << "Enter the total number of parking slots: ";
    cin >> totalSlots;

    ParkingSystem system(totalSlots);
    system.userInterface();

    return 0;
}

