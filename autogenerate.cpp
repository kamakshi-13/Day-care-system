#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

class DogRecord {
public:
    int id;
    string name, dogName, phoneNumber, dogBreed, dogMedication,age;
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
            cout << "                                                         1. Add booking\n";
            cout << "                                                         2. Search Booking\n";
            cout << "                                                         3. Cancel a Booking\n";
            cout << "                                                         4. Display All Bookings\n";
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
            cout << "                                                        1. Booking\n";
            cout << "                                                        2. cancel booking\n";
            cout << "                                                        3. Update details\n";
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
static int nextId;
private:
	
	bool isAllDigits(const string& str) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}
	bool isAllAlphabetic(const string& str) {
    for (size_t i = 0; i < str.length(); ++i) {
        char ch = str[i];
        if (!isalpha(ch) && !isspace(ch)) {
            return false; 
        }
    }
    return true;
}
	 bool isValidPhoneNumber(const string& phoneNumber) {
        if (phoneNumber.length() != 10) {
            return false;
        }

        for (size_t i = 0; i < phoneNumber.length(); ++i) {
            if (!isdigit(phoneNumber[i])) {
                return false;
            }
        }

        return true;
    }
    void addRecord() {
    DogRecord record;

    
    
    record.id = nextId++;
    
    cout << "Enter Customer Name: ";
     cin.ignore(); 
        getline(cin, record.name);
        while (!isAllAlphabetic(record.name)) {
            cout << "Invalid name. Please enter a valid name using only characters: ";
            getline(cin, record.name);
        }
    cout << "Enter customer Age: ";
    cin >> record.age;
    while (!isAllDigits(record.age)) {
    cout << "Invalid age. Please enter a valid age using only digits: ";
    cin >> record.age;
}
    cout << "Enter customer Phone Number: ";
    cin >> record.phoneNumber;
    while (!isValidPhoneNumber(record.phoneNumber)) {
            cout << "Invalid phone number. Please enter a valid 10-digit Phone Number: ";
            cin >> record.phoneNumber;
        }

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

    cout << "Appointment booked successfully!\n\n";
    cout<< "Your booking id is :"<<record.id<<endl;
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
            cout << "                   Booking with ID " << deleteId << " canelled successfully!\n\n";
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
                cout << "                Enter updated customer  Name: ";
                cin >> record.name;
                cout << "                Enter updated customer Age: ";
                cin >> record.age;
                cout << "                Enter customer Phone Number: ";
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
int DogDaycare::nextId = 1;

int main() {
    DogDaycare daycare;
    ifstream idFile("nextId.txt");
    if (idFile.is_open()) {
        idFile >> DogDaycare::nextId;
        idFile.close();
    }
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
    ofstream idOutFile("nextId.txt");
    if (idOutFile.is_open()) {
        idOutFile << DogDaycare::nextId;
        idOutFile.close();
    }

    return 0;
}
