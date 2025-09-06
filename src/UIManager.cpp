#include "../include/UIManager.h"
#include "../include/products.h"
#include <iostream>
#include <string>
#include <limits>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <sstream>


using std::string;

void UIManager::showModeMenu() {
    std::cout << "Select Mode:\n";
    std::cout << "1. Customer Mode\n";
    std::cout << "2. Admin Mode\n";
    std::cout << "Enter your choice (1 or 2): ";
}
void UIManager::showItemCategories() {
    std::cout << "Item Categories:\n";
    std::cout << "1. Food\n";
    std::cout << "2. Clothing\n";
    std::cout << "3. Games\n";
    std::cout << "4. Books\n";
    std::cout << "5. Back\n";
    std::cout << "Enter your choice (1 - 5): ";
}
void UIManager::showDecisionConformation() {
    std::cout << "Are you sure you want to do this? \n\n";
    std::cout << "1. Yes\n";
    std::cout << "2. No\n";
    std::cout << "Enter your choice (1 or 2): ";
    // Logic to confirm the user's decision
}
void UIManager::showLoadedProducts() {
    std::cout << "1. Add To Cart\n";
    std::cout << "2. Back\n";
    std::cout << "Enter your choice (1 or 2): ";
}

void UIManager::showStoreSelctionCustomer() {
    std::cout << "Select Store:\n";
    std::cout << "Type the name of the store file to load (e.g., store.json): \n";
    // Logic to import a store file from JSON
    std::cout << " Store file should load here but it is not yet implemented so for now type any number\n";
}
void UIManager::showInventoryOptionsCustomer() {
    std::cout << "Inventory Options:\n";
    std::cout << "1. Check Catalog\n";
    std::cout << "2. Search Item\n";
    std::cout << "3. Checkout\n";
    std::cout << "4. End Program\n";
    std::cout << "Enter your choice (1 - 4): ";
}
bool UIManager::showCartSummary(const Cart& cart, const Inventory& inv) {
    std::cout << "Cart Summary:\n";
    int cartSize = cart.size();

    if (cartSize == 0) {
        std::cout << "There are no items in your cart. Go buy something!\n\n";
        return false;
    }

    std::cout << "\nItems in Cart: " << std::to_string(cartSize) << "\n\n";
    vector<int> productIDs = cart.getProductIDs();
    for (int i =0; i < productIDs.size(); ++i) {
        int productID = productIDs[i];
        product* product = inv.getProduct(productID);
        std::cout << i + 1 << ". " << product->getProductName() << "\n";
        std::cout << "ID: " << productID << "\n";
        std::cout  << std::fixed << std::setprecision(2) << "Price: $" << product->getProductPrice() << "\n";
        std::cout << "Quantity: " << cart.getQuantity(productID) << "\n\n";


    }

    std::cout << std::fixed << std::setprecision(2) << "\nTotal Price: $" << cart.cost() << "\n\n";

    std::cout << "1. Checkout\n";
    std::cout << "2. Remove a product\n";
    std::cout << "3. Go back\n";
    std::cout << "Enter your choice (1 - 3): ";
    return true;
}

bool UIManager::showSpecItem(int option) {
    string userOp;

    if(option == 1) {
        userOp = "FOOD";
    }
    else if( option == 2) {
        userOp = "CLOTHES";
    }
    else if( option == 3) {
        userOp = "GAME";
    } else {
        userOp = "BOOK";
    }
    system("clear");
    std::cout << "======= " << userOp <<  " Items =======\n";

    Inventory inv;
    inv.loadInventory("data/products.json");  // Step 1: Load data

    vector<int> typeID = inv.filterByType(userOp); // Step 2: Filter IDs

    if (typeID.empty()) {
        std::cout << "No " << userOp << " items found.\n";
        return true;
    } else {
        for (int id : typeID) {
                product* p = inv.getProduct(id);    // Step 3: Get each product
                p->printProductInfo();              // Step 4: Print
                std::cout << "-----------------------------\n";
            }
        }
    return false;
}

void UIManager::showEditItem() {
    std::cout << "1. Delete item\n";
    std::cout << "2. Add/Subtract stock\n";
    std::cout << "3. Change price\n";
    std::cout << "4. Go back\n";
    std::cout << "Please type here (1-4): ";
}



void UIManager::showCheckoutSuccess() {
    std::cout << "Checkout Successful!\n";
    std::cout << "Thank you for your purchase!\n\n";
    std::cout << "\n1. Continue Shopping\n";
    std::cout << "2. Exit Program\n";
    // Logic to display a success message
}
void UIManager::showRecommendations() {
    std::cout << "Recommendations:\n";
    std::cout << "Recommended Item 1\n";
    std::cout << "Recommended Item 2\n";
    std::cout << "Recommended Item 3\n";
    std::cout << "1. Add To Cart\n";
    std::cout << "2. Back\n";
    std::cout << "Enter your choice (1 or 2): ";
    // Logic to display recommendations based on the user's preferences
}
void UIManager::showSearchPage() {
    std::cout << "Search Products:\n";
    std::cout << "Enter product name or keyword: \n\n";

    // Logic to display a search page for products
}
bool UIManager::showSearchResults(const std::vector<int>& productIDs, const Inventory& inv, const int limit) {
    std::cout << "Search Results:\n\n";
    UIManager::printProducts(productIDs, inv, limit);
    // Logic to display search results for products based on user input
    if (!productIDs.size() == 0) {
        std::cout << "1. Add To Cart\n";
        std::cout << "2. Back\n";
        std::cout << "Enter your choice (1 or 2): ";
        return true;
    } else {
        std::cout << "No items with similar name found.\n";
        waitForUser();
        return false;
    }
    
    
}

void UIManager::addToCart() {
    std::cout << "How Many do you want to add?\n";

    std::cout << "1. continue\n";
    std::cout << "2. back\n";
    // Logic to add an item to the cart
}
void UIManager::showStoreSelectionAdmin() {
    std::cout << "Select Inventory Option 1-4" << std::endl << std::endl;
    std::cout << "1. Check/Edit Inventory" << std::endl;
    std::cout << "2. Add new Inventory" << std::endl;
    std::cout << "3. End Program" << std::endl;
    std::cout << std::endl;
    std::cout << "Select Here: ";
}

void UIManager::showInventoryOptionsAdmin() {
    std::cout << "Inventory Options:\n";
    std::cout << "1. Check/Edit Inventory\n";
    std::cout << "2. Add new Inventory\n";
    std::cout << "3. View Low Stock Items\n";
    std::cout << "4. End Program\n";
    std::cout << "Enter your choice (1 - 4): ";
}

void UIManager::showAddInventoryAdmin() {
    std::cout << "1. Add new Book" << std::endl;
    std::cout << "2. Add new Game" << std::endl;
    std::cout << "3. Add new Clothes" << std::endl;
    std::cout << "4. Add new Food" << std::endl;
    std::cout << "5. Go Back" << std::endl;
    std::cout << std::endl;
    std::cout << "Select Here: ";
}

void UIManager::showLoadedProductsAdmin(){
    std::cout << "Loaded Products:\n";
    std::cout << "\n\n ALL PRODUCTS LOADED FROM THE STORE FILE \n\n";
    std::cout << "1. Add To Cart\n";
    std::cout << "2. Back\n";
    std::cout << "Enter your choice (1 or 2): ";
    // Logic to display loaded products from the store file
}

int UIManager::getValidInput(int maxRange) {
    int userInput = 0;
    string input;
    while (true) {
        std::getline(std::cin, input); 
        std::stringstream ss(input); // open string as input
        if ((ss >> userInput) && !(ss >> input) && userInput >= 1 && userInput <= maxRange) {
            // If able to read an int, read again to see if it was a decimal.
            break;
        }
        std::cout << "Please enter a valid number between 1 and " << maxRange << ":\n";
    }
    return userInput;
}

string UIManager::getValidString() {
    string input;
    while (true) {
        getline(std::cin, input);
        if (input.empty()) {
            std::cout << "Input cannot be empty\n\n";
        } else {
            break;
        }
    }
    return input;
}

int UIManager::getValidInt() {
    return getValidDouble(0);
}

double UIManager::getValidDouble(const int precision) {
    if (precision < 0) {
        throw std::runtime_error("Cannot use negative precision");
    }
    double value;
    while (true) {
        string input = getValidString();
        if(sscanf(input.c_str(), "%lf", &value) != 1) {  
            std::cout<< "Invalid input entered. Try again.\n";
        } else {
            double raised = std::pow(10, precision);
            double scaled = value * raised;
            if (std::abs(scaled - std::round(scaled)) > 1e-6) {
                std::cout<< "Expected precision of " << precision << ". Try again.\n";
                continue;
            }
            return value;
        }
    }
}

void UIManager::printProducts(std::vector<int> productIDs, const Inventory& inv, const int limit) {
    for (int i = 0; i < productIDs.size() && i < limit; ++i) {
        product* product = inv.getProduct(productIDs[i]);
        product->printProductInfo();
        std::cout << "\n";
    }
}

void UIManager::waitForUser() {
    std::cout << "Type anything to go back.\n";
    std::string temp;
    std::getline(std::cin, temp);
}