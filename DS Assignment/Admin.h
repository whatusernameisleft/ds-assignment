#pragma once

//Admin list
bool loginAdminStatus = false;//hold admin login status.

//admin data structure
struct Admin {
    std::string adminID;
    std::string password;
    Admin *next;
};

//Admin Functions
void LoginAdmin(Admin *adminList) {
    std::string inputAdminID, inputPassword;
    std::cout << "Enter Admin ID: ";
    std::cin >> inputAdminID;
    std::cout << "Enter Password: ";
    std::cin >> inputPassword;

    Admin *current = adminList;
    while (current != nullptr) {
        if (current->adminID == inputAdminID && current->password == inputPassword) {
            std::cout << "Logged in as " << current->adminID << " successfully." << std::endl;
            loginAdminStatus = true; // Login successful
            break;
        } else {
            std::cout << "Failed to log in. Wrong ID or Password." << std::endl;
        }
        current = current->next;
    }
}

void LogoutAdmin() {
    loginAdminStatus = false;
    std::cout << "Logged out successfully." << std::endl;
}

void addAdmin(Admin **head, std::string adminID, std::string password) {
    Admin *newadmin = new Admin;
    newadmin->adminID = adminID;
    newadmin->password = password;
    newadmin->next = nullptr;

    if (*head == nullptr) {
        *head = newadmin;
    } else {
        Admin *current = *head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newadmin;
    }
}

void updateManagerStatus(Manager *head) {
    std::string managerID;
    std::cout << "Enter manager ID to update status: ";
    std::cin >> managerID;

    bool newStatus;
    std::string statusInput;
    std::cout << "Enter new manager status (active/inactive) for manager " << managerID << ": ";
    std::cin >> statusInput;

    // Convert the status input to lowercase for case-insensitive comparison
    std::transform(statusInput.begin(), statusInput.end(), statusInput.begin(), ::tolower);

    if (statusInput == "active") {
        newStatus = true;
    } else if (statusInput == "inactive") {
        newStatus = false;
    } else {
        std::cout << "Invalid status input. Use 'active' or 'inactive'." << std::endl;
        return;
    }

    Manager *current = head;
    bool managerFound = false;

    while (current != nullptr) {
        if (current->managerID == managerID) {
            current->managerStatus = newStatus;
            managerFound = true;
            std::cout << "Manager status updated successfully." << std::endl;
            break;
        }
        current = current->next;
    }

    if (!managerFound) {
        std::cout << "Manager not found." << std::endl;
    }

}

void addNewManagerList(Manager **head) {
    Manager *newmanager = new Manager;
    std::string managerID, password;
    std::cout << "Enter new manager ID: ";
    std::cin >> managerID;
    std::cout << "Enter new password for manager: ";
    std::cin >> password;
    bool managerStatus = true;
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
void displayManager(Manager *head) {
    std::cout << "Existing Managers:" << std::endl;
    Manager *current = head;
    while (current != nullptr) {
        std::cout << "Manager ID: " << current->managerID
            << "\tPassword: " << current->password
            << "\tStatus: " << current->managerStatus << std::endl;
        current = current->next;
    }
}

void manageManager() {
    int option;
    do {
        std::cout << "Admin's Manager Management Menu Options:\n"
            << "    1. Add Manager User\n"
            << "    2. Update Manager Status\n"
            << "    0. Go back\n\n"
            << "Choose an option: ";
        std::cin >> option;
        cls();

        switch (option) {
        case 1:
            displayManager(managerList);
            addNewManagerList(&managerList);
            break;
        case 2:
            displayManager(managerList);
            updateManagerStatus(managerList);
            break;
        case 0:
            return;
        default:
            std::cout << "Invalid input. Please enter a valid option." << std::endl;
            break;
        }
        cls();
    } while (option != 0);
}

void displayAllTenants(Tenant *tenantList) {
    std::cout << "Display All Tenant Information Options:\n"
        << "    1. All\n"
        << "    2. Active\n"
        << "    3. Inactive\n"
        << "    0. Go back\n\n"
        << "Choose an option: ";
    int option;
    std::cin >> option;
    cls();

    switch (option) {
    case 1:
        displayTenantList(tenantList);
        break;
    case 2:
        displayFilteredTenants(tenantList, "active");
        break;
    case 3:
        displayFilteredTenants(tenantList, "inactive");
        break;
    case 0:
        return;
    default:
        std::cout << "Invalid input." << std::endl;
        return;
    }
}

void displayByPropertyType(Entry *entries) {
    std::string propertyTypes[13] = {
        "Apartment",
        "Bungalow House",
        "Condo / Services residence / Penthouse / Townhouse",
        "Condominium",
        "Duplex",
        "Flat",
        "Houses",
        "Others",
        "Residential",
        "Service Residence",
        "Soho",
        "Studio",
        "Townhouse Condo"
    };

    std::cout << "Display By Property Type Options:" << std::endl;
    for (int i = 0; i < 13; i++)
        std::cout << "    " << i + 1 << ". " << propertyTypes[i] << std::endl;
    std::cout << "    0. Go back" << std::endl;
    std::cout << "\nChoose an option: ";
    int option;
    std::cin >> option;
    cls();

    if (option == 0)
        return;
    else if (option < 0 || option > 13) {
        std::cout << "Invalid input." << std::endl;
        return;
    }

    std::string type = propertyTypes[option - 1];
    int count = 0;
    std::cout << "First 10 property IDs for " << type << ": " << std::endl;
    for (int i = 0; i < MAX_DATA_SIZE && count != 10; i++) {
        if (entries[i].type == type) {
            std::cout << entries[i].id << std::endl;
            count++;
        }
    }
    std::cout << std::endl;
}

void displayByFurnishStatus(Entry *entries) {
    std::string furnishStatus[3] = {
        "Fully Furnished",
        "Partially Furnished",
        "Not Furnished"
    };

    std::cout << "Display By Furnish Status Options:" << std::endl;
    for (int i = 0; i < 3; i++)
        std::cout << "    " << i + 1 << ". " << furnishStatus[i] << std::endl;
    std::cout << "    0. Go back" << std::endl;
    std::cout << "\nChoose an option: ";
    int option;
    std::cin >> option;
    cls();

    if (option == 0)
        return;
    else if (option < 0 || option > 3) {
        std::cout << "Invalid input." << std::endl;
        return;
    }

    std::string status = furnishStatus[option - 1];
    int count = 0;
    std::cout << "First 10 property IDs for " << status << ": " << std::endl;
    for (int i = 0; i < MAX_DATA_SIZE && count != 10; i++) {
        if (entries[i].furnished == status) {
            std::cout << entries[i].id << std::endl;
            count++;
        }
    }
    std::cout << std::endl;
}

void displayByRegion(Entry *entries) {
    std::string regions[2] = {
           "Kuala Lumpur",
           "Selangor"
    };

    std::cout << "Display By Region Options:" << std::endl;
    for (int i = 0; i < 2; i++)
        std::cout << "    " << i + 1 << ". " << regions[i] << std::endl;
    std::cout << "    0. Go back" << std::endl;
    std::cout << "\nChoose an option: ";
    int option;
    std::cin >> option;
    cls();

    if (option == 0)
        return;
    else if (option < 0 || option > 2) {
        std::cout << "Invalid input." << std::endl;
        return;
    }

    std::string region = regions[option - 1];
    int count = 0;
    std::cout << "First 10 property IDs for " << region << ": " << std::endl;
    for (int i = 0; i < MAX_DATA_SIZE && count != 10; i++) {
        if (entries[i].region == region) {
            std::cout << entries[i].id << std::endl;
            count++;
        }
    }
    std::cout << std::endl;
}

void displayAllProperties(Entry *entries) {
    std::cout << "Display All Property Information Options:\n"
        << "    1. Property Type\n"
        << "    2. Furnish Status\n"
        << "    3. Region\n"
        << "    0. Go back\n\n"
        << "Choose an option: ";
    int option;
    std::cin >> option;
    cls();

    switch (option) {
    case 1:
        displayByPropertyType(entries);
        break;
    case 2:
        displayByFurnishStatus(entries);
        break;
    case 3:
        displayByRegion(entries);
        break;
    case 0:
        return;
    default:
        std::cout << "Invalid input." << std::endl;
        return;
    }
}

void displayAllInfo(Tenant *tenantList, Entry *entries) {
    std::cout << "Display All Information Options:\n"
        << "    1. Tenant\n"
        << "    2. Property\n"
        << "    0. Go back\n\n"
        << "Choose an option: ";
    int option;
    std::cin >> option;
    cls();

    switch (option) {
    case 1:
        displayAllTenants(tenantList);
        break;
    case 2:
        displayAllProperties(entries);
        break;
    case 0:
        return;
    default:
        std::cout << "Invalid input." << std::endl;
        return;
    }

}

//creating the list
Admin *adminList = nullptr;