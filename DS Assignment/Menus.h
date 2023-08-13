#pragma once

//tenant user's menu
void tenantMenu(Entry *entries) {
    int Toption;//T: tenant option
    do {
        std::cout << "---------------------------Asia Pacific Home---------------------------" << std::endl;
        std::cout << "                               <<Tenant>>" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "    1. Login\n    2. Sort\n    3. Search\n    4. Register\n    5. Save Fav Property\n    6. Send rent request\n    7. Display rent history\n    0. Logout & Exit" << std::endl;
        std::cout << "\nChoose an option: ";
        std::cin >> Toption;
        cls();

        switch (Toption) {
        case 1:
            if (loginTenantStatus)
                std::cout << "Already logged in as " << LoggedInTenant << std::endl;
            else
                LoginTenant(tenantList);
            break;
        case 2:
            if (loginTenantStatus)
                sortProperties(entries);
            else
                std::cout << "Log in to sort properties." << std::endl;
            break;
        case 3:
            if (loginTenantStatus)
                searchProperties(entries);
            else
                std::cout << "Log in to search for properties." << std::endl;
            break;
        case 4:
            if (!loginTenantStatus)
                registerTenant(&tenantList);
            else 
                std::cout << "Log out to register" << std::endl;
            break;
        case 5:
            if (loginTenantStatus) 
                addToFavPropList(&favList);
            else
                std::cout << "Log in to add property to favourite list. " << std::endl;
            break;
        case 6:
            if (loginTenantStatus) 
                makeRentrequest(&requestList);
            else
                std::cout << "Log in to make rent property request. " << std::endl;
            break;
        case 7:
            if (loginTenantStatus)
                displayTenantRentHistory(historyList);
            else
                std::cout << "Log in to display rent history. " << std::endl;
            break;
        case 0:
            logOutTenant();
            return;
        default:
            std::cout << "Invalid input. Please enter a valid option." << std::endl;
            break;
        }
    } while (Toption != 0);
}

//manager user's Menu
void managerMenu() {
    int  Moption; //M:Manager Options
    do {
        std::cout << "---------------------------Asia Pacific Home---------------------------" << std::endl;
        std::cout << "                              <<Manager>>" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "    1. Login\n    2. Display registered tenants' tetails\n    3. Search tenant details" <<
            "\n    4. Delete inactive tenants\n    5. Summary of favourite properties\n    6. Check rent requests\n    7. Manage tenancy payment\n    0. Logout & Exit" << std::endl;
        std::cout << "\nChoose an option: ";
        std::cin >> Moption;
        cls();

        switch (Moption) {
        case 0:
            LogoutManager();
            return;
        case 1:
            if (!loginManagerStatus)
                LoginManager(managerList);
            else
                std::cout << "Already logged in." << std::endl;
            break;
        case 2:
            if (loginManagerStatus)
                displayTenantList(tenantList);
            else
                std::cout << "Did not login. Please login to use menu functions." << std::endl;
            break;
        case 3:
            if (loginManagerStatus)
                searchTenantList(tenantList);
            else
                std::cout << "Did not login. Please login to use menu functions." << std::endl;
            break;
        case 4:
            if (loginManagerStatus)
                deleteTenant(&tenantList);
            else
                std::cout << "Did not login. Please login to use menu functions." << std::endl;
            break;
        case 5:
            if (loginManagerStatus)
                printSummaryProp(favList);
            else
                std::cout << "Did not login. Please login to use menu functions." << std::endl;
            break;
        case 6:
            if (loginManagerStatus) {
                displayRentRequests(requestList);
                updateRentStatus(requestList);
            } else
                std::cout << "Did not login. Please login to use menu functions." << std::endl;
            break;
        case 7:
            if (loginManagerStatus) {
                displayPayment(tenantPaymentList);
                managePay(tenantPaymentList);
                displayPayment(tenantPaymentList);
            } else 
                std::cout << "Did not login. Please login to use menu functions." << std::endl;
            break;
        default:
            std::cout << "Invalid input. Please enter a valid option." << std::endl;
            break;
        }
    } while (Moption != 0);
}

//Admin user's menu
void AdminMenu(Entry *entries) {
    int Aoption; //A=admin options
    do {
        std::cout << "---------------------------Asia Pacific Home---------------------------" << std::endl;
        std::cout << "                               <<Admin>>" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "    1. Login\n    2. Manage Managers\n    3. List tenant and properties\n    0. Logout & Exit" << std::endl;
        std::cout << "\nChoose an option: ";
        std::cin >> Aoption;
        cls();

        switch (Aoption) {
        case 1:
            if (loginAdminStatus)
                std::cout << "Already Logged in" << std::endl;
            else
                LoginAdmin(adminList);
            break;
        case 2:
            if (loginAdminStatus) 
                manageManager();
            else 
                std::cout << "You must be logged in as admin to update manager status." << std::endl;
            break;
        case 3:
            if (loginAdminStatus)
                displayAllInfo(tenantList, entries);
            else
                std::cout << "You must be logged in as admin to view all tenant and property information." << std::endl;
            break;
        case 0:
            LogoutAdmin();
            return;
        default:
            std::cout << "Invalid input. Please enter a valid option." << std::endl;
            break;
        }
    } while (Aoption != 0);
}