#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <string>
#include "Inventory.h"
#include "Cart.h"
#include <vector>

using std::string;


class UIManager {
public:
    //Do we need a constructor or destructor? Not sure yet, but we can add them later if needed.
    static void printProducts(std::vector<int>, const Inventory& inv, const int limit);
    void showModeMenu(); // which mode Customer or Admin mode
    void showItemCategories(); // Show item categories both for admin and customer (Food, Clothing, Games, Books)* we might chage this
    void showDecisionConformation(); // Show a message to confirm the decision made by the user (e.g., "Are you sure you want to exit?")
    void showLoadedProducts(); // Show the loaded products from the store file + Details

    //Customer UI windows
    void showStoreSelctionCustomer(); // Select Store (decide if you want to pass a file name later)
    void showInventoryOptionsCustomer(); // Inventory Options (check inventory, get reccomendation,  checkout, end program)
    bool showCartSummary(const Cart&, const Inventory&); // Checkout Summary : (show the items in the cart, total price, etc.)
    void showCheckoutSuccess(); // Checkout Success : (show a message that the checkout was successful)
    void showRecommendations(); // Show a recommendations
    void showSearchPage(); // Show a search page for products
    bool showSearchResults(const std::vector<int>& productIDs, const Inventory& inv, const int limit);
    void addToCart(); // Process of adding an item to a cart

    // Admin UI windows
    void showStoreSelectionAdmin(); // Create New Store or Load Existing Store
    void showInventoryOptionsAdmin(); // Inventory Options for Admin (check inventory, add item, delete item, end program)
    void showAddInventoryAdmin(); // Show the add inventory screen
    void showLoadedProductsAdmin(); // Show the loaded products from the store file + Details
    bool showSpecItem(int option);
    void showEditItem();
    
    //UI helper functions
    int getValidInput(int maxRange); // checks the range of the inputs and makes sure that it is valid
    void displayforSeconds(const std::string& message, int seconds); // Display a message for a certain number of seconds
    void clearScreen(); // Clear the console
    string getValidString();
    int getValidInt();
    void waitForUser();
    double getValidDouble(const int);
};

#endif
