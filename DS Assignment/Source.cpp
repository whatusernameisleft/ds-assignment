#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "Entry.h"
#include "CSV.h"
#include "Vector.h"
#include "Sorts.h"
#include "Tenant.h"
#include "Manager.h"
#include "Admin.h"
#include "Menus.h"

extern const int MAX_DATA_SIZE = 19991;
extern const int COLUMN_COUNT = 14;

Entry* init() {
    std::ifstream reader("data.csv");
    if (!reader.is_open()) {
        reader.close();
        std::cout << "Can't read data file. Exiting program." << std::endl;
        return nullptr;
    }
    std::string header;
    getline(reader, header);
    auto entries = readCSV(reader);
    reader.close();

    //adding all data to all the lists for demonstration purpose
    //add tenants data
    addTenant(&tenantList, "t1", "1", "active");
    addTenant(&tenantList, "t2", "2", "active");
    addTenant(&tenantList, "t3", "3", "active");
    addTenant(&tenantList, "t4", "4", "inactive");
    addTenant(&tenantList, "t5", "5", "inactive");
    addTenant(&tenantList, "t6", "6", "active");

    //adding favourite properties
    addfavProperty(&favList, "t1", "1");
    addfavProperty(&favList, "t2", "1");
    addfavProperty(&favList, "t3", "1");
    addfavProperty(&favList, "t4", "2");
    addfavProperty(&favList, "t5", "2");
    addfavProperty(&favList, "t6", "3");

    //adding rent requests
    addRentrequest(&requestList, "t1", "1", "pending");
    addRentrequest(&requestList, "t6", "10", "pending");
    addRentrequest(&requestList, "t5", "999", "pending");
    addRentrequest(&requestList, "t2", "666", "pending");
    addRentrequest(&requestList, "t4", "555", "rejected");
    addRentrequest(&requestList, "t3", "111", "approved");

    //adding manager data
    addManager(&managerList, "m1", "1", true);
    addManager(&managerList, "m2", "2", false);
    addManager(&managerList, "m3", "3", true);

    //adding tenantpayment data
    addTenantPayment(&tenantPaymentList, "t1", "p1", "Paid");
    addTenantPayment(&tenantPaymentList, "t6", "p89", "Paid");
    addTenantPayment(&tenantPaymentList, "t5", "p10", "Paid");
    addTenantPayment(&tenantPaymentList, "t4", "p70", "Unpaid");
    addTenantPayment(&tenantPaymentList, "t3", "p69", "Unpaid");
    addTenantPayment(&tenantPaymentList, "t2", "p11", "Unpaid");

    //adding admin user data
    addAdmin(&adminList, "A1", "1");

    //adding tenant rent history data
    addHistoryRecord(&historyList, "t1", "012930", 18);
    addHistoryRecord(&historyList, "t1", "930", 10);
    addHistoryRecord(&historyList, "t2", "012930", 5);
    addHistoryRecord(&historyList, "t3", "012930", 18);
    addHistoryRecord(&historyList, "t5", "10", 18);
    addHistoryRecord(&historyList, "t4", "930", 18);
    addHistoryRecord(&historyList, "t4", "30", 18);
    addHistoryRecord(&historyList, "t1", "99930", 34);
    addHistoryRecord(&historyList, "t1", "90", 3);

    return entries;
}

int main() {
    Entry *entries = init();
    if (entries == nullptr)
        return -1;

    int option;
    do {
        std::cout << "---------------------------Asia Pacific Home---------------------------" << std::endl;
        std::cout << "                             <<Main Menu>>" << std::endl;
        std::cout << "Pick a user type: " << std::endl;
        std::cout << "    1. Tenant\n    2. Manager\n    3. Admin\n    0. Exit" << std::endl;
        std::cout << "\nChoose an option: ";
        std::cin >> option;
        cls();

        switch (option) {
        case 1:
            cls();
            tenantMenu();
            break;
        case 2:
            cls();
            managerMenu();
            break;

        case 3:
            //open admin page
            cls();
            AdminMenu();
            break;
        case 0:
            std::cout << "Exited program. Thank You.";
            break;
        default:
            std::cout << "Invalid input." << std::endl;
            break;
        }
    } while (option != 0);


	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	RadixSortRent(entries, MAX_DATA_SIZE);
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " milliseconds" << std::endl;

	delete[] entries;
	return 0;
}