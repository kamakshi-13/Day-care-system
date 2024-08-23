#include <iostream>
#include <fstream>

using namespace std;

class DogRecord {
public:
    int id, age;
    string name, dogName, phoneNumber, dogBreed, dogMedication;
    int cost;

    void display() {
        cout << "ID: " << id << "\nName: " << name << "\nAge: " << age << "\nPhone Number: " << phoneNumber << "\nDog Name: " << dogName << "\nDog Breed: " << dogBreed << "\nDog Medication: " << dogMedication <<"\nTotal cost: "<<cost<< "\n\n";
    }
};

class DogDaycare {
public:
    void adminMenu() {
        int choice;
        do {
            cout << "                                                 **********WELCOME ADMIN**********\n";
            cout << "                                                         1. Add Record\n";
            cout << "                                                         2. Search Record\n";
            cout << "                                                         3. Delete Record\n";
            cout << "                                                         4. Display All Records\n";
            cout << "                                                         5. Exit\n";
            cout << "                                                  WHICH OPTION WOULD YOU LIKE TO CHOOSE: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addRecord();
                    break;
                case 2:
                    searchRecord();
                    break;
                case 3:
                    deleteRecord();
                    break;
                case 4:
                    displayAllRecords();
                    break;
                case 5:
                    cout << "Exiting Admin Menu...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 5);
    }

    void userMenu() {
        int choice;
        do {
            cout << "                                                 **********WELCOME USER**********\n";
            cout << "                                                        1. Add Record\n";
            cout << "                                                        2. Delete Record\n";
            cout << "                                                        3. Update Record\n";
            cout << "                                                        4. Exit\n";
            cout << "                                                WHICH OPTION WOULD YOU LIKE TO CHOOSE: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addRecord();
                    break;
                case 2:
                    deleteRecord();
                    break;
                case 3:
                    updateRecord();
                    break;
                case 4:
                    cout << "Exiting User Menu...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 4);
    }

private:
    void addRecord() {
    DogRecord record;

    
    static int nextId = 1;
    record.id = nextId++;

    cout << "Enter Name: ";
    cin >> record.name;
    cout << "Enter Age: ";
    cin >> record.age;
    cout << "Enter Phone Number: ";
    cin >> record.phoneNumber;
    cout << "Enter Dog Name: ";
    cin >> record.dogName;
    cout << "Enter Dog Breed: ";
    cin >> record.dogBreed;
    cout << "Enter Dog Medication: ";
    cin >> record.dogMedication;
    
    char durationChoice;
    cout << "Do you want to keep your dog for hours (h) or days (d)? ";
    cin >> durationChoice;

    if (durationChoice == 'h') {
        int hours;
        cout << "Enter the number of hours: ";
        cin >> hours;
        record.cost = hours * 200; 
    } else if (durationChoice == 'd') {
        int days;
        cout << "Enter the number of days: ";
        cin >> days;
        record.cost = days * 2000; 
    } else {
        cout << "Invalid choice. Setting cost to 0.\n";
        record.cost = 0;
    }

    ofstream file("records.txt", ios::app);
    file << record.id << " " << record.name << " " << record.age << " " << record.phoneNumber << " " << record.dogName << " " << record.dogBreed << " " << record.dogMedication << " " << record.cost << "\n";
    file.close();

    cout << "Record added successfully!\n\n";
}

    

    void searchRecord() {
        int searchId;
        cout << "                    Enter ID to search:\n\n ";
        cin >> searchId;

        ifstream file("records.txt");
        DogRecord record;
        bool found = false;

        while (file >> record.id >> record.name >> record.age >> record.phoneNumber >> record.dogName >> record.dogBreed >> record.dogMedication>>record.cost) {
            if (record.id == searchId) {
                found = true;
                record.display();
                break;
            }
        }

        if (!found) {
            cout << "                 Record not found.\n";
        }

        file.close();
    }

    void deleteRecord() {
        int deleteId;
        cout << "                      Enter ID to delete:\n\n ";
        cin >> deleteId;

        ifstream inFile("records.txt");
        ofstream outFile("temp.txt");

        DogRecord record;

        bool found = false;

        while (inFile >> record.id >> record.name >> record.age >> record.phoneNumber >> record.dogName >> record.dogBreed >> record.dogMedication>> record.cost) {
            if (record.id == deleteId) {
                found = true;
            } else {
                outFile << record.id << " " << record.name << " " << record.age << " " << record.phoneNumber << " " << record.dogName << " " << record.dogBreed << " " << record.dogMedication <<" "<<record.cost<< "\n";
            }
        }

        inFile.close();
        outFile.close();

        remove("records.txt");
        rename("temp.txt", "records.txt");

        if (found) {
            cout << "                   Record with ID " << deleteId << " deleted successfully!\n\n";
        } else {
            cout << "                    Record not found.\n";
        }
    }

    void displayAllRecords() {
        ifstream file("records.txt");
        DogRecord record;

        while (file >> record.id >> record.name >> record.age >> record.phoneNumber >> record.dogName >> record.dogBreed >> record.dogMedication>> record.cost) {
            record.display();
        }

        file.close();
    }

    void updateRecord() {
        int updateId;
        cout << "                           Enter ID to update: \n\n";
        cin >> updateId;

        ifstream inFile("records.txt");
        ofstream outFile("temp.txt");

        DogRecord record;

        bool found = false;

        while (inFile >> record.id >> record.name >> record.age >> record.phoneNumber >> record.dogName >> record.dogBreed >> record.dogMedication>> record.cost) {
            if (record.id == updateId) {
                found = true;
                cout << "                Enter updated details:\n";
                cout << "                Enter Name: ";
                cin >> record.name;
                cout << "                Enter Age: ";
                cin >> record.age;
                cout << "                Enter Phone Number: ";
                cin >> record.phoneNumber;
                cout << "                Enter Dog Name: ";
                cin >> record.dogName;
                cout << "                Enter Dog Breed: ";
                cin >> record.dogBreed;
                cout << "                Enter Dog Medication: ";
                cin >> record.dogMedication;
                char durationChoice;
        cout << "                         Do you want to keep your dog for hours (h) or days (d)? ";
        cin >> durationChoice;

        if (durationChoice == 'h') {
            int hours;
            cout << "                     Enter the number of hours: ";
            cin >> hours;
            record.cost = hours * 200; 
        } else if (durationChoice == 'd') {
            int days;
            cout << "                      Enter the number of days: ";
            cin >> days;
            record.cost = days * 2000; 
        } else {
            cout << "                     Invalid choice. Setting cost to 0.\n";
            record.cost = 0;
        }
            }
            outFile << record.id << " " << record.name << " " << record.age << " " << record.phoneNumber << " " << record.dogName << " " << record.dogBreed << " " << record.dogMedication <<" "<<record.cost<< "\n";
        }

        inFile.close();
        outFile.close();

        remove("records.txt");
        rename("temp.txt", "records.txt");

        if (found) {
            cout << "Record with ID " << updateId << " updated successfully!\n\n";
        } else {
            cout << "Record not found.\n";
        }
    }
};

int main() {
    DogDaycare daycare;
    int userType;

    cout << "                         ******************************WELCOME TO DOG DAYCARE CENTER*******************************\n\n\n";

    cout << "                                                             1. Admin"<<endl;
    cout << "                                                             2. User"<<endl;
    cout<<"                                                           Enter user type:";
    cin >> userType;

    switch (userType) {
        case 1:
            {
                string adminUsername, adminPassword;
                cout << "   \n\n                                        Enter Admin Username: ";
                cin >> adminUsername;
                cout << "    \n\n                                       Enter Admin Password: ";
                cin >> adminPassword;

                if (adminUsername == "admin" && adminPassword == "123") {
                    daycare.adminMenu();
                } else {
                    cout << "                                    Invalid Admin Credentials. Exiting...\n";
                }
            }
            break;

        case 2:
            daycare.userMenu();
            break;

        default:
            cout << "                                               Invalid User Type. Exiting...\n";
    }

    return 0;
}
