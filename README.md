# Dog Day Care Management System 🐕
A console-based C++ application for managing dog daycare bookings, built with file-based persistent storage

<img width="173" height="30" alt="image" src="https://github.com/user-attachments/assets/25dba480-e97c-4036-af44-77ae7f7dded1" />
<img width="173" height="30" alt="image" src="https://github.com/user-attachments/assets/bed52522-3c57-4e4d-988e-754e8360760f" />


## 📋 Table of Contents
- [What is this Project?](#-what-is-this-project)
- [Key Features](#-key-features)
- [How it Works — End-to-End Flow](#-how-it-works--end-to-end-flow)
- [Architecture Overview](#-architecture-overview)
- [Data Model](#-data-model)
- [Input Validation](#-input-validation)
- [Pricing Logic](#-pricing-logic)
- [Installation & Running](#-installation--running)
- [Tech Stack](#-tech-stack)
- [User Roles](#-user-roles)
- [Limitations](#-limitations)
- [Future Scope](#-future-scope)

## 🎯 What is this Project?

The Dog Day Care Management System is a menu-driven console application that lets a daycare center manage bookings for customers and their dogs. It supports two access levels — **Admin** and **User** — and persists all booking data to a text file, so records survive between program runs.

Built entirely in C++ using the standard library, with no external database — all data is stored and retrieved from plain text files (`records.txt`, `nextId.txt`).

## ✨ Key Features

| Feature | Details |
|---|---|
| 🔐 Role-based Access | Separate menus for Admin (hardcoded credentials) and User |
| 🎟️ Add Booking | Captures customer + dog details and calculates cost automatically |
| 🔎 Search Booking | Look up a booking by its unique ID |
| ❌ Cancel Booking | Deletes a record by ID and rewrites the data file |
| ✏️ Update Booking | Edit an existing booking's details by ID (User menu) |
| 📜 Display All Bookings | Admin can view every booking on file |
| ✅ Input Validation | Name, age, and phone number are validated before being accepted |
| 🆔 Persistent ID Counter | Booking IDs auto-increment and persist across program runs via `nextId.txt` |

## 🔄 How it Works — End-to-End Flow

```
┌─────────────────────────────────────────────────────────────────┐
│                         PROGRAM START                            │
└─────────────────────────────────────────────────────────────────┘

1. LOAD LAST BOOKING ID
   └── Reads nextId.txt to resume ID numbering from the last run

2. CHOOSE USER TYPE
   ├── 1: Admin — must enter username/password ("admin" / "123")
   └── 2: User  — goes straight to the User Menu

┌─────────────────────────────────────────────────────────────────┐
│                          ADMIN MENU                              │
└─────────────────────────────────────────────────────────────────┘
   1. Add booking          → addRecord()
   2. Search Booking       → searchRecord()
   3. Cancel a Booking     → deleteRecord()
   4. Display All Bookings → displayAllRecords()
   5. Exit

┌─────────────────────────────────────────────────────────────────┐
│                           USER MENU                              │
└─────────────────────────────────────────────────────────────────┘
   1. Booking          → addRecord()
   2. Cancel booking   → deleteRecord()
   3. Update details   → updateRecord()
   4. Exit

3. ON EXIT
   └── Writes the current ID counter back to nextId.txt for next run
```

## 🏗️ Architecture Overview

The system is a **single-file, procedural-OOP console app** — two classes (`DogRecord` and `DogDaycare`) handle everything, with no networking or database layer. All persistence goes through simple flat-file text I/O.

```
┌────────────────────────────────────────────────────────┐
│                     main() — Entry Point                 │
│         Prompts user type → Admin or User menu           │
└───────────────────────────┬──────────────────────────────┘
                            │
                            ▼
┌────────────────────────────────────────────────────────┐
│                    DogDaycare class                      │
│  adminMenu() / userMenu()                                │
│  ├── addRecord()        — validated input + cost calc     │
│  ├── searchRecord()     — linear search by ID             │
│  ├── deleteRecord()     — rewrite file excluding ID       │
│  ├── updateRecord()     — rewrite file with new values    │
│  └── displayAllRecords()— print every record              │
└───────────────────────────┬──────────────────────────────┘
                            │ ifstream / ofstream
                            ▼
┌────────────────────────────────────────────────────────┐
│                     Flat File Storage                    │
│         records.txt   (all booking data)                 │
│         nextId.txt    (persistent ID counter)             │
└────────────────────────────────────────────────────────┘
```

## 🗄️ Data Model

The `DogRecord` class holds one booking:

| Field | Type | Description |
|---|---|---|
| `id` | `int` | Auto-incrementing, unique booking ID |
| `name` | `string` | Customer's name |
| `age` | `string` | Customer's age (validated as digits) |
| `phoneNumber` | `string` | Customer's 10-digit phone number |
| `dogName` | `string` | The dog's name |
| `dogBreed` | `string` | The dog's breed |
| `dogMedication` | `string` | Any medication the dog needs |
| `cost` | `int` | Total cost, calculated from stay duration |

Records are stored as space-separated values, one booking per line, in `records.txt`.

## ✅ Input Validation

The app validates key fields before accepting them:

- **Name** — must contain only alphabetic characters and spaces (`isAllAlphabetic`)
- **Age** — must contain only digits (`isAllDigits`)
- **Phone Number** — must be exactly 10 digits (`isValidPhoneNumber`)

Invalid input re-prompts the user until a valid value is entered.

## 💰 Pricing Logic

When booking, the customer chooses how long the dog stays:

| Duration Type | Rate |
|---|---|
| Hourly (`h`) | ₹200 per hour |
| Daily (`d`) | ₹2000 per day |
| Invalid choice | Cost set to ₹0 |

## 🚀 Installation & Running

**Prerequisites:** A C++ compiler (g++, MinGW, or any standard C++ compiler)

```bash
# 1. Clone the repository
git clone https://github.com/kamakshi-13/Day-care-system.git
cd Day-care-system

# 2. Compile the program
g++ -o daycare main.cpp

# 3. Run it
./daycare        # on Windows: daycare.exe
```

On first run, `records.txt` and `nextId.txt` will be created automatically in the same directory as the executable.

## 🛠️ Tech Stack

| Layer | Technology | Purpose |
|---|---|---|
| Language | C++ | Core application logic |
| Standard Library | `<iostream>`, `<fstream>`, `<limits>` | Console I/O and file handling |
| Storage | Flat text files | Persisting bookings and ID counter (no external database) |

## 👥 User Roles

**Admin** (login: `admin` / `123`)
- Add, search, cancel, and view all bookings
- Full visibility across all customer records

**User**
- Book a new appointment for their dog
- Cancel their own booking
- Update their booking details

## ⚠️ Limitations

- Admin credentials are hardcoded in the source (not secure for real-world use)
- No way for a user to search only *their own* booking — search is Admin-only
- Data is stored in plain text with no encryption
- No concurrent access handling — not safe for multiple users running the program simultaneously
- No unique customer accounts — anyone can update/cancel any booking ID if they know it

## 🔮 Future Scope

- Replace hardcoded admin credentials with a proper authentication system
- Migrate from flat-file storage to a real database (SQLite/MySQL)
- Add a graphical interface (desktop or web) instead of console I/O
- Restrict users to only viewing/editing their own bookings
- Add booking date/time scheduling instead of just duration
- Generate printable/exportable invoices

---

**Author:** Kamakshi Arora ·
