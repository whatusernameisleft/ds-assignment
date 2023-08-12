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
    std::cout << "Logged out Admin." << std::endl;
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
    std::cout << "Enter managerID to update status: ";
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
    std::cout << "Rent Requests:" << std::endl;
    Manager *current = head;
    while (current != nullptr) {
        std::cout << "Manager ID: " << current->managerID
            << ", Password: " << current->password
            << "Manager status" << current->managerStatus << std::endl;
        current = current->next;
    }
}

void manageManager() {
    int option;
    do {
        std::cout << "Admin's Manager Management Menu Options:\n"
            << "1. Add Manager User\n"
            << "2. Update Manager Status\n"
            << "0. Return to Admin Menu\n"
            << "Enter option: ";
        std::cin >> option;
        cls();

        switch (option) {
        case 1:
            displayManager(managerList);
            addNewManagerList(&managerList);
            break;
        case 2:
            if (loginAdminStatus) {
                displayManager(managerList);
                updateManagerStatus(managerList);
            } else {
                std::cout << "You must be logged in as admin to update manager status." << std::endl;
            }
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

//creating the list
Admin *adminList = nullptr;