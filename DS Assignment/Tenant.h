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