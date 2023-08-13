#pragma once

//clear screen for all
void cls() {
    system("cls");
}

//tenant's data structures
struct Tenant {
    std::string tenantID;
    std::string password;
    std::string status;
    Tenant *next;
};
struct FavProperty {
    std::string tenantID;
    std::string propertyID;
    FavProperty *next;
};
struct RentRequest {
    std::string tenantID;
    std::string propertyID;
    std::string rentStatus; //pending/approved/rejected
    RentRequest *next;
};

struct RentHistory {
    std::string tenantID;
    std::string propertyID;
    int rentPeriod;
    RentHistory *next;
};

bool loginTenantStatus = false;//to hold logged in tenant status to prevent double logins
std::string LoggedInTenant;//to hold the tenant id that is logged in

//tenant login
void LoginTenant(Tenant *tenantList) {
    std::string inputTenantID, inputPassword;
    std::cout << "Enter Tenant ID: ";
    std::cin >> inputTenantID;
    std::cout << "Enter Password: ";
    std::cin >> inputPassword;

    bool loginSuccessful = false; // Flag to track login status

    Tenant *current = tenantList;
    while (current != nullptr) {
        if (current->tenantID == inputTenantID && current->password == inputPassword) {
            std::cout << "Logged in as " << current->tenantID << " successfully." << std::endl;
            loginTenantStatus = true; // Login successful
            LoggedInTenant = inputTenantID;
            loginSuccessful = true;
            break;
        }
        current = current->next;
    }

    if (!loginSuccessful) {
        std::cout << "Failed to log in. Wrong ID or Password." << std::endl;
    }
}

//logging tenant out
void logOutTenant() {
    std::cout << "Successfully logged out." << std::endl;
    loginTenantStatus = false;
}

//hardcode to add tenants
void addTenant(Tenant **head, std::string tenantID, std::string password, std::string status) {
    Tenant *newTenant = new Tenant;
    newTenant->tenantID = tenantID;
    newTenant->password = password;
    newTenant->status = status;
    newTenant->next = nullptr;

    if (*head == nullptr) {
        *head = newTenant;
    } else {
        Tenant *current = *head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newTenant;
    }
}

void sortProperties(Entry *entries) {
    std::cout << "Property Sort Options:\n"
        << "    1. Monthly Rent\n"
        << "    2. Location\n"
        << "    3. Size (Square feet)\n"
        << "    0. Go back\n\n"
        << "Choose an option: ";
    int option;
    std::cin >> option;
    cls();

    if (option == 0)
        return;
    else if (option < 0 || option > 3) {
        std::cout << "Invalid input." << std::endl;
        return;
    }

    int sortOp;
    std::cout << "Sorting Algorithm Options:\n    1. Radix Sort\n    2. Quick Sort\n    0. Go back\n\nChoose an option: ";
    std::cin >> sortOp;
    cls();

    if (sortOp == 0)
        return;
    else if (sortOp < 0 || sortOp > 2) {
        std::cout << "Invalid input." << std::endl;
        return;
    }

    int comboOp = ((option - 1) * 2) + (sortOp - 1);
    std::string sortBy;

    std::chrono::steady_clock::time_point begin, end;
    switch (comboOp) {
    case 0:
        begin = std::chrono::steady_clock::now();
        RadixSortRent(entries, MAX_DATA_SIZE);
        end = std::chrono::steady_clock::now();
        sortBy = "Monthly Rent (RM)";
        break;
    case 1:
        begin = std::chrono::steady_clock::now();
        QuickSort(entries, MAX_DATA_SIZE, 0);
        end = std::chrono::steady_clock::now();
        sortBy = "Monthly Rent (RM)";
        break;
    case 2:
        std::cout << "Can't use Radix Sort for location" << std::endl;
        return;
    case 3:
        begin = std::chrono::steady_clock::now();
        QuickSort(entries, MAX_DATA_SIZE, 1);
        end = std::chrono::steady_clock::now();
        sortBy = "Location\t\tRegion";
        break;
    case 4:
        begin = std::chrono::steady_clock::now();
        RadixSortSize(entries, MAX_DATA_SIZE);
        end = std::chrono::steady_clock::now();
        sortBy = "Size (Square Feet)";
        break;
    case 5:
        begin = std::chrono::steady_clock::now();
        QuickSort(entries, MAX_DATA_SIZE, 2);
        end = std::chrono::steady_clock::now();
        sortBy = "Size (Square Feet)";
        break;
    }

    std::cout << "Sorting took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << std::endl << std::endl;
    std::cout << "First 10 properties:\nProperty ID\t\t" << sortBy << std::endl;

    switch (option) {
    case 1:
        for (int i = MAX_DATA_SIZE - 1; i > MAX_DATA_SIZE - 11; i--)
            std::cout << entries[i].id << "\t\t" << entries[i].getRent() << std::endl;
        break;
    case 2:
        for (int i = MAX_DATA_SIZE - 1; i > MAX_DATA_SIZE - 11; i--)
            std::cout << entries[i].id << "\t\t" << entries[i].location << "\t\t" << entries[i].region << std::endl;
        break;
    case 3:
        for (int i = MAX_DATA_SIZE - 1; i > MAX_DATA_SIZE - 11; i--)
            std::cout << entries[i].id << "\t\t" << entries[i].size << std::endl;
        break;
    }
    
    std::cout << std::endl;
}

void searchProperties(Entry *entries) {
    cls();
    unsigned int id;
    std::cout << "Enter property ID to search: ";
    std::cin >> id;

    int option;
    std::cout << "\nSearch Algorithm Options:\n    1. Sort & Binary Search\n    2. Sentinel Linear Search\n    0. Go back\n\nChoose an options: ";
    std::cin >> option;

    if (option == 0)
        return;
    else if (option < 0 || option > 2) {
        std::cout << "Invalid input." << std::endl;
        return;
    }

    cls();
    int index;
    std::chrono::steady_clock::time_point begin, end;
    switch (option) {
    case 1: {
        begin = std::chrono::steady_clock::now();
        RadixSortId(entries, MAX_DATA_SIZE);
        std::chrono::steady_clock::time_point binaryBegin = std::chrono::steady_clock::now();
        index = binarySearch(entries, MAX_DATA_SIZE, id);
        std::chrono::steady_clock::time_point binaryEnd = std::chrono::steady_clock::now();
        end = std::chrono::steady_clock::now();
        std::cout << "Binary search time: " << std::chrono::duration_cast<std::chrono::microseconds>(binaryEnd - binaryBegin).count() << " microseconds" << std::endl;
        break;
    }
    case 2:
        begin = std::chrono::steady_clock::now();
        index = sentinelLinearSearch(entries, MAX_DATA_SIZE, id);
        end = std::chrono::steady_clock::now();
        break;
    }

    std::cout << "Total search time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << std::endl << std::endl;
    if (index == -1) {
        std::cout << "Invalid property ID." << std::endl << std::endl;
        return;
    }

    entries[index].print();
}

//hardcode to add data to rent history list
void addHistoryRecord(RentHistory **head, std::string tenantID, std::string propertyID, int rentPeriod) {
    RentHistory *newRentHistory = new RentHistory;
    newRentHistory->tenantID = tenantID;
    newRentHistory->propertyID = propertyID;
    newRentHistory->rentPeriod = rentPeriod;
    newRentHistory->next = nullptr;

    if (*head == nullptr) {
        *head = newRentHistory;
    } else {
        RentHistory *current = *head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newRentHistory;
    }
}

//registering tenant and logging them in.
void registerTenant(Tenant **head) {
    Tenant *newTenant = new Tenant;
    std::cout << "Enter tenant ID: ";
    std::cin >> newTenant->tenantID;
    std::cout << "Enter password: ";
    std::cin >> newTenant->password;
    newTenant->status = "active";
    newTenant->next = nullptr;

    if (*head == nullptr) {
        *head = newTenant;
    } else {
        Tenant *current = *head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newTenant;
    }

    loginTenantStatus = true;
    LoggedInTenant = newTenant->tenantID;
}

//tenant to add data to favourited property list.
void addToFavPropList(FavProperty **head) {
    FavProperty *newFavProperty = new FavProperty;
    newFavProperty->tenantID = LoggedInTenant;
    std::cout << "Enter property ID to add to your favourite list: ";
    std::cin >> newFavProperty->propertyID;
    newFavProperty->next = nullptr;

    if (*head == nullptr) {
        *head = newFavProperty;
    } else {
        FavProperty *current = *head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newFavProperty;
    }
}

//hardcode to add rentreuqest to the list.
void addRentrequest(RentRequest **head, std::string tenantID, std::string propertyID, std::string rentStatus) {
    RentRequest *newRentRequest = new RentRequest;
    newRentRequest->tenantID = tenantID;
    newRentRequest->propertyID = propertyID;
    newRentRequest->rentStatus = rentStatus;
    newRentRequest->next = nullptr;

    if (*head == nullptr) {
        *head = newRentRequest;
    } else {
        RentRequest *current = *head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newRentRequest;
    }
}

//making rent request according to the tenant thats logged in.
void makeRentrequest(RentRequest **head) {
    RentRequest *newRentRequest = new RentRequest;
    newRentRequest->tenantID = LoggedInTenant;
    std::cout << "Enter property id to send request to manager: ";
    std::cin >> newRentRequest->propertyID;
    newRentRequest->rentStatus = "pending";
    newRentRequest->next = nullptr;

    if (*head == nullptr) {
        *head = newRentRequest;
    } else {
        RentRequest *current = *head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newRentRequest;
    }
}

//displays rent history according to tenant ID that is logged in.
void displayTenantRentHistory(RentHistory *head) {
    std::cout << "Rent History for Tenant ID: " << LoggedInTenant << std::endl;

    RentHistory *current = head;
    while (current != nullptr) {
        if (current->tenantID == LoggedInTenant) {
            std::cout << "Property ID: " << current->propertyID
                << ", Rent Period: " << current->rentPeriod << std::endl;
        }
        current = current->next;
    }
}

//declare all tenants lists
Tenant *tenantList = nullptr;
FavProperty *favList = nullptr;
RentRequest *requestList = nullptr;
RentHistory *historyList = nullptr;