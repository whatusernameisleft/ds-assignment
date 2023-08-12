#pragma once

bool loginManagerStatus = false;//to hold manager login status. set to false so that the start state is nobody is logged in.


//All list that manager uses
struct Manager {
    std::string managerID;
    std::string password;
    bool managerStatus;
    Manager *next;
};

struct TenantPayment {
    std::string tenantID;
    std::string paymentID;
    std::string payStatus;
    TenantPayment *next;
};


//Manager Functions
void LoginManager(Manager *managerList) {
    std::string inputManagerID, inputPassword;
    std::cout << "Enter Manager ID: ";
    std::cin >> inputManagerID;
    std::cout << "Enter Password: ";
    std::cin >> inputPassword;

    Manager *current = managerList;
    bool loggedIn = false;

    while (current != nullptr) {
        if (current->managerID == inputManagerID && current->password == inputPassword) {
            if (current->managerStatus) {
                std::cout << "Logged in as " << current->managerID << " successfully." << std::endl;
                loginManagerStatus = true; // Login successful
                loggedIn = true;
                break;
            } else {
                std::cout << "Failed to log in. Account inactive." << std::endl;
                loggedIn = true;
                break;
            }
        }
        current = current->next;
    }

    if (!loggedIn) {
        std::cout << "Failed to log in. Wrong ID/Password." << std::endl;
        loginManagerStatus = false; // Login failed
    }
}

void LogoutManager() {
    loginManagerStatus = false;
    std::cout << "Logged out successfully." << std::endl;
}

void addManager(Manager **head, std::string managerID, std::string password, bool managerStatus) {
    Manager *newmanager = new Manager;
    newmanager->managerID = managerID;
    newmanager->password = password;
    newmanager->managerStatus = managerStatus;
    newmanager->next = nullptr;

    if (*head == nullptr) {
        *head = newmanager;
    } else {
        Manager *current = *head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newmanager;
    }
}

void displayTenantList(Tenant *head) {
    Tenant *current = head;
    std::cout << "List of registered tenants: " << std::endl;
    while (current != nullptr) {
        std::cout << "Tenant ID: " << current->tenantID << "\tPassword: " << current->password << std::endl;
        current = current->next;
    }
}

void displayInactiveTenants(Tenant *head) {
    Tenant *current = head;
    std::cout << "List of inactive tenants: " << std::endl;
    while (current != nullptr) {
        if (current->status == "inactive") {
            std::cout << "Tenant ID: " << current->tenantID << "\tPassword: " << current->password << std::endl;
        }
        current = current->next;
    }
}

bool searchTenantList(Tenant *head) {
    std::string tenantID;
    std::cout << "Search tenant ID: ";
    std::cin >> tenantID;

    Tenant *current = head;
    while (current != nullptr) {
        if (current->tenantID == tenantID) {
            std::cout << "Tenant exists." << std::endl;
            return true;
        }
        current = current->next;
    }
    std::cout << "Tenant does not exist." << std::endl;
    return false;
}

//only allowed to delete inactive tenants
void deleteTenant(Tenant **head) {
    displayInactiveTenants(*head);
    std::string tenantID;
    std::cout << "Enter tenant ID: ";
    std::cin >> tenantID;

    Tenant *current = *head;
    Tenant *prev = nullptr;
    while (current != nullptr && current->tenantID != tenantID) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        std::cout << "Tenant not found." << std::endl;
        return;
    }

    if (current->status == "inactive") {
        if (prev == nullptr) {
            *head = current->next;
        } else {
            prev->next = current->next;
        }
        delete current;
        std::cout << "Tenant deleted successfully." << std::endl;
    } else {
        std::cout << "Only inactive tenants can be deleted." << std::endl;
    }
}

//Favourite Property Functions

void addfavProperty(FavProperty **head, std::string tenantID, std::string propertyID) {
    FavProperty *newFavProperty = new FavProperty;
    newFavProperty->tenantID = tenantID;
    newFavProperty->propertyID = propertyID;
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

//sumamry report of total tenants favourited 1 property
void printSummaryProp(FavProperty *favList) {
    // Count occurrences using an array
    const int maxProperties = 100;  // Assuming a maximum of 100 unique property IDs
    int propertyCount[maxProperties] = { 0 };

    // Traverse the favList and count propertyIDs
    FavProperty *current = favList;
    while (current != nullptr) {
        // Convert propertyID to an index in the propertyCount array
        int index = std::stoi(current->propertyID);

        // Increment the count for that property
        if (index >= 0 && index < maxProperties) {
            propertyCount[index]++;
        }

        current = current->next;
    }

    // Print the summary
    std::cout << "Summary of Favourite Properties:" << std::endl;
    for (int i = 0; i < maxProperties; ++i) {
        if (propertyCount[i] > 0) {
            std::cout << "Property ID: " << i << ", favourited by " << propertyCount[i] << " tenants." << std::endl;
        }
    }
}

//Rent Request Functions
void updateRentStatus(RentRequest *head) {
    std::string tenantID;
    std::cout << "Enter tenant ID to update request status: ";
    std::cin >> tenantID;

    Vector<RentRequest *> requests;

    bool foundTenant = false;
    RentRequest *current = head;
    while (current != nullptr) {
        if (current->tenantID == tenantID) {
            requests.push_back(current);
            foundTenant = true;
        }
        current = current->next;
    }

    if (!foundTenant) {
        std::cout << "Tenant ID does not exist." << std::endl;
        return;
    }

    std::string propertyId;
    std::cout << "Enter property ID to update payment status: ";
    std::cin >> propertyId;

    RentRequest *match = nullptr;
    for (int i = 0; i < requests.size(); i++) {
        if (requests.get(i)->propertyID == propertyId) {
            match = requests.get(i);
            break;
        }
    }

    if (match == nullptr) {
        std::cout << "Invalid property ID." << std::endl;
        return;
    }

    std::cout << "Enter new request status (pending, approved, rejected) for tenant " << tenantID << ": ";
    std::cin >> match->rentStatus;
}

//display all tenants and rent requests for properties
void displayRentRequests(RentRequest *head) {
    std::cout << "Rent Requests:" << std::endl;
    RentRequest *current = head;
    while (current != nullptr) {
        std::cout << "Tenant ID: " << current->tenantID
            << "\tProperty ID: " << current->propertyID
            << "\tRent Status: " << current->rentStatus << std::endl;
        current = current->next;
    }
}


//Payment Functions
void addTenantPayment(TenantPayment **head, std::string tenantID, std::string paymentID, std::string payStatus) {
    TenantPayment *newTenantPayment = new TenantPayment;
    newTenantPayment->tenantID = tenantID;
    newTenantPayment->paymentID = paymentID;
    newTenantPayment->payStatus = payStatus;
    newTenantPayment->next = nullptr;

    if (*head == nullptr) {
        *head = newTenantPayment;
    } else {
        TenantPayment *current = *head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newTenantPayment;
    }
}

void managePay(TenantPayment *head) {
    std::string tenantID;
    std::cout << "Enter tenant ID to update payment status: ";
    std::cin >> tenantID;

    TenantPayment *current = head;
    while (current != nullptr) {
        if (current->tenantID == tenantID) {
            break;
        }
        current = current->next;
    }

    std::cout << "Enter new Payment Status (Paid/Unpaid) for tenant " << current->tenantID << " property " << current->paymentID << ": ";
    std::cin >> current->payStatus;
};

void displayPayment(TenantPayment *head) {
    std::cout << "Rent Requests:" << std::endl;
    TenantPayment *current = head;
    while (current != nullptr) {
        std::cout << "Tenant ID: " << current->tenantID
            << "\tProperty ID: " << current->paymentID
            << "\tPayment Status: " << current->payStatus << std::endl;
        current = current->next;
    }
}

//creating the list
Manager *managerList = nullptr;
TenantPayment *tenantPaymentList = nullptr;