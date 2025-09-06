#include <fstream>
#include <iostream>
#include <string>
#include <functional>
#include <cctype>
#include <sstream>
#include <thread>
#include "../include/json.hpp"
#include "../include/Inventory.h"
#include "../include/Login.h"
#include "../include/UIManager.h"
#include "../include/Cart.h"

using json = nlohmann::json;

using std::endl;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::string;
using std::setw;
using std::cin;


enum Screen {
    // Main flow
    MODE_MENU,
    CUSTOMER_MODE,
    ADMIN_MODE,

    // Customer flow
    INVENTORY_OPTIONS_CUSTOMER,
    CATAGORIES_CUSTOMER,
    CATALOG_CUSTOMER,
    VIEW_CART,
    CHECKOUT_SUCCESS,
    RECOMMENDATIONS,
    SEARCH_PAGE,
    REMOVE_PRODUCT_CART,

    // Admin flow
    INVENTORY_OPTIONS_ADMIN,
    ADMIN_CHECK_CATEGORIES,
    ADMIN_ADD_INVENTORY,
    ADMIN_CATALOG,
    ADMIN_LOW_STOCK,

    // Exit
    EXIT
};

void display_for_seconds(const std::string& text, int seconds) {
    cout << text << std::flush;
    this_thread::sleep_for(std::chrono::seconds(seconds));
    system("clear");
}

void customerUI(UIManager& ui, Screen& currentScreen, int& userChoice, string& objType){
    Inventory inv;
    Cart cart(inv);
    inv.loadInventory("data//products.json");
    while (currentScreen != EXIT) {
        switch (currentScreen) {
            case INVENTORY_OPTIONS_CUSTOMER: {
                system("clear");
                ui.showInventoryOptionsCustomer();
                userChoice = ui.getValidInput(4); // Assuming 1-4 for different options
                if (userChoice == 1) currentScreen = CATAGORIES_CUSTOMER;
                else if (userChoice == 2) currentScreen = SEARCH_PAGE;
                //else if (userChoice == 3) currentScreen = RECOMMENDATIONS;
                else if (userChoice == 3) currentScreen = VIEW_CART;
                else {
                    currentScreen = EXIT;
                }
                userChoice = 0; // Reset user choice for next screen
                break;
            }
            case CATAGORIES_CUSTOMER: {
                system("clear");
                ui.showItemCategories();
                userChoice = ui.getValidInput(5);
                if (userChoice == 1) {
                    currentScreen = CATALOG_CUSTOMER;
                    objType = "FOOD";
                }
                else if (userChoice == 2) {
                    currentScreen = CATALOG_CUSTOMER;
                    objType = "CLOTHES";
                }
                else if (userChoice == 3) {
                    currentScreen = CATALOG_CUSTOMER;
                    objType = "GAMES";
                }
                else if (userChoice == 4) {
                    currentScreen = CATALOG_CUSTOMER;
                    objType = "BOOKS";
                } else {
                    currentScreen = INVENTORY_OPTIONS_CUSTOMER;
                }
                userChoice = 0;
                break;
            }
            case CATALOG_CUSTOMER: {
                system("clear");
                std::cout << "Loaded Products - (" << objType << ") :\n\n";
                vector<int> productIDs = inv.filterByType(objType);
                std::cout << "--------------------------\n";
                if (productIDs.empty()){
                    std::cout << "No items found \n\n";
                    ui.waitForUser();
                    currentScreen = CATAGORIES_CUSTOMER;
                    break;
                } else {
                    for (int id : productIDs) {
                        product* p = inv.getProduct(id);
                        p->printProductInfo();
                        std::cout << "--------------------------\n";
                    }
                }
                ui.showLoadedProducts();
                userChoice = ui.getValidInput(2); // Assuming 1 for Add to Cart, 2 for Back
                if (userChoice == 1) {
                    while (true) {
                            bool found = false;
                            std::cout << "Enter ID of product you want to add.\n";
                            int productID = ui.getValidInt();
                            
                            for (int i = 0; i < productIDs.size(); ++i ) {
                                if (productID == productIDs[i]) {
                                    found = true;
                                    break;
                                }
                            }

                            if (!found) {
                                std::cout << "Entered product ID not found.\n\n";
                                continue;
                            } else {
                                std::cout << "Enter product quantity wanted.\n";
                                int quantity = ui.getValidInt();
                                int stock = inv.getProduct(productID)->getProductStock();
                                if (quantity > stock) {
                                    std:: cout << "Entered quantity exceeds product stock.\n\n";
                                    continue;
                                } else if (quantity < 0) {
                                    std:: cout << "Quantity cannot be negative.\n\n";
                                    continue;
                                } else {
                                    cart.addProduct(productID, quantity);
                                    std::cout << "Product added to cart successfully.\n\n";
                                    ui.waitForUser();
                                    currentScreen = INVENTORY_OPTIONS_CUSTOMER;
                                    break;
                                }
                            }
                        }
                } else {
                    currentScreen = INVENTORY_OPTIONS_CUSTOMER; // Go back to inventory options
                }
                userChoice = 0; // Reset user choice for next screen
                break;
            }

            case SEARCH_PAGE: {
                system("clear");
                ui.showSearchPage();
                //we would have to implement the search logic here
                string search = ui.getValidString(); 
                system("clear");
                int limit = 5;
                vector<int> productIDs = inv.searchByName(search, limit);
                if (ui.showSearchResults(productIDs, inv, limit)) {
                    userChoice = ui.getValidInput(2);
                    if (userChoice == 1) {
                        while (true) {
                            bool found = false;
                            std::cout << "Enter ID of product you want to add.\n";
                            int productID = ui.getValidInt();
                            
                            for (int i = 0; i < productIDs.size(); ++i ) {
                                if (productID == productIDs[i]) {
                                    found = true;
                                    break;
                                }
                            }

                            if (!found) {
                                std::cout << "Entered product ID not found.\n\n";
                                continue;
                            } else {
                                std::cout << "Enter product quantity wanted.\n";
                                int quantity = ui.getValidInt();
                                int stock = inv.getProduct(productID)->getProductStock();
                                if (quantity > stock) {
                                    std:: cout << "Entered quantity exceeds product stock.\n\n";
                                    continue;
                                } else if (quantity < 0) {
                                    std:: cout << "Quantity cannot be negative.\n\n";
                                    continue;
                                } else {
                                    cart.addProduct(productID, quantity);
                                    std::cout << "Product added to cart successfully.\n\n";
                                    inv.saveInventory("data//products.json");
                                    ui.waitForUser();
                                    currentScreen = INVENTORY_OPTIONS_CUSTOMER;
                                    break;
                                }
                            }
                        }

                    }
                }
                currentScreen = INVENTORY_OPTIONS_CUSTOMER;
                break;
            }

            case RECOMMENDATIONS: {
                system("clear");
                ui.showRecommendations();
                userChoice = ui.getValidInput(2); // Assuming 1 for Add to Cart, 2 for Back
                if (userChoice == 1) {
                    // Logic to add recommended item to cart
                    currentScreen = RECOMMENDATIONS; // Stay in recommendations after adding
                } else {
                    currentScreen = INVENTORY_OPTIONS_CUSTOMER; // Go back to inventory options
                }
                userChoice = 0; // Reset user choice for next screen
                break;
            }
            case VIEW_CART: {
                system("clear");
                if (ui.showCartSummary(cart, inv)) {
                    userChoice = ui.getValidInput(3); // Assuming 1 for Confirm Checkout, 2 for Cancel Checkout
                    if (userChoice == 1) {
                        currentScreen = CHECKOUT_SUCCESS; // Go to checkout success
                    } else if (userChoice == 2) {
                        currentScreen = REMOVE_PRODUCT_CART;
                    } else {
                        currentScreen = INVENTORY_OPTIONS_CUSTOMER; // Go back to inventory options
                    }
                } else {
                    ui.waitForUser();
                    currentScreen = INVENTORY_OPTIONS_CUSTOMER;
                } 
                break;
            }
            case REMOVE_PRODUCT_CART: {
                std::cout << "What product do you want to remove?\n\nID: \n";
                int productID;
                while (true) {
                    productID = ui.getValidInt();
                    if (!cart.containsProduct(productID)) {
                        std::cout<< "\nEntered ID was not found in cart.\nID:\n";
                    } else {
                        break;
                    }
                }
                cart.removeProduct(productID);
                cout << "\n\nRemoval successful!\n";
                ui.waitForUser();
                currentScreen = INVENTORY_OPTIONS_CUSTOMER;
                break;
            }
            case CHECKOUT_SUCCESS: {
                system("clear");
                cart.checkout();
                inv.saveInventory("data//products.json");
                ui.showCheckoutSuccess();
                userChoice = ui.getValidInput(2); // Assuming 1 for Continue Shopping, 2 for Exit
                if (userChoice == 1) {
                    currentScreen = INVENTORY_OPTIONS_CUSTOMER; // Go back to inventory options
                } else {
                    currentScreen = EXIT; // Exit the program
                }
                userChoice = 0;
                break;
            }
        }
    }       
}

void adminUI(UIManager& ui, Screen& currentScreen, int& userChoice){
    Inventory inv;
    inv.loadInventory("data//products.json");
    while (currentScreen != EXIT) {
        switch (currentScreen) {
            case INVENTORY_OPTIONS_ADMIN:
                system("clear");
                ui.showInventoryOptionsAdmin();
                userChoice = ui.getValidInput(4);
                if (userChoice == 1) currentScreen = ADMIN_CHECK_CATEGORIES;
                else if (userChoice == 2) currentScreen = ADMIN_ADD_INVENTORY;
                else if (userChoice == 3) currentScreen = ADMIN_LOW_STOCK;
                else currentScreen = EXIT;
                userChoice = 0;
                break;

            case ADMIN_CHECK_CATEGORIES:
                system("clear");
                ui.showItemCategories(); // Reuses existing method
                userChoice = ui.getValidInput(5);
                bool isEmpty;
                // Just print selected category for now
                if (userChoice == 1) {
                    system("clear");
                    isEmpty = ui.showSpecItem(userChoice);
                }
                else if (userChoice == 2) {
                    system("clear");
                    isEmpty = ui.showSpecItem(userChoice);
                }
                    
                else if (userChoice == 3) {
                    system("clear");
                    isEmpty = ui.showSpecItem(userChoice);
                }
                    
                else if (userChoice == 4) {
                    system("clear");
                    isEmpty = ui.showSpecItem(userChoice);
                }
                else {
                    currentScreen = INVENTORY_OPTIONS_ADMIN;
                    break;
                }
                userChoice = 0;
                std::cout << "1. Edit Items \n";
                std::cout << "2. Back\n";
                std::cout << "Select here (1-2): ";

                userChoice = ui.getValidInput(2);

                if(userChoice == 1) {
                    if(isEmpty) {
                        cout << endl;
                        display_for_seconds("No items to edit going back...", 2);
                        break;
                    }
                    else {
                        cout << endl;
                        ui.showEditItem();
                        userChoice = ui.getValidInput(4);
                        if(userChoice == 1) {    
                            int id = 0;
                            int checkTwice = 0;
                            cout << "Please give ID: ";
                            while (true) {
                                id = ui.getValidInt();
                                if (!inv.containsId(id)) {
                                    cout << "That productID was not found inside inventory. Try again.\n";
                                } else {
                                    break;
                                }
                            }
                            cout << endl;
                            cout << "Are you sure you wanna delete\n";
                            cout << "1. Delete" << endl;
                            cout << "2. keep" << endl;
                            cout << "Enter Here (1-2): ";
                            checkTwice = ui.getValidInput(2);
                            if(checkTwice == 1) {
                                inv.loadInventory("data/products.json"); // searchs through current json
                                inv.removeProduct(id); // finds 
                                inv.saveInventory("data/products.json");
                            }
                        }
                        else if (userChoice == 2){
                            inv.loadInventory("data/products.json");
                            cout << "Please give ID: \n";
                            int id;
                            while (true) {
                                id = ui.getValidInt();
                                if (!inv.containsId(id)) {
                                    cout << "That productID was not found inside inventory. Try again.\n";
                                } else {
                                    break;
                                }
                            }
                            product* p = inv.getProduct(id);
                            cout << "How many do you want to add/remove?: \n";
                            int newQuantity;
                            while (true) {
                                newQuantity = p->getProductStock() + ui.getValidInt();
                                if (newQuantity < 0) {
                                    cout << "Tried to remove more product than inventory currently holds. Try again.\n";
                                } else {
                                    break;
                                }
                            }
                            p->setProductStock(newQuantity);
                            inv.saveInventory("data/products.json");
                    }
                        else if (userChoice == 3){
                            inv.loadInventory("data/products.json");
                            cout << "Please give ID: \n";
                            int id;
                            while (true) {
                                id = ui.getValidInt();
                                if (!inv.containsId(id)) {
                                    cout << "That productID was not found inside inventory. Try again.\n";
                                } else {
                                    break;
                                }
                            }
                            product* p = inv.getProduct(id);
                            cout << "Give a New Price: \n";
                            double newPrice = ui.getValidDouble(2);
                            p->setProductPrice(newPrice);
                            inv.saveInventory("data/products.json");
                        }
                    }
                }
                else {
                    currentScreen = INVENTORY_OPTIONS_ADMIN;
                }
                userChoice = 0;
                break;

            case ADMIN_ADD_INVENTORY:
                system("clear");
                ui.showAddInventoryAdmin();

                userChoice = ui.getValidInput(5); // 1-4 add item, 5 go back
                if (userChoice == 1) {
                    cout << "==========================" << endl;
                    cout << "       Adding Books       " << endl;
                    cout << "==========================" << endl;

                    string name, author, genre;
                    double price;
                    int productID, stock;

                    // Prompt user for input
                    cout << "Enter product name (dupes will overide): ";
                    name = ui.getValidString();

                    cout << "Enter price: ";
                    price = ui.getValidDouble(2);

                    cout << "Enter stock quantity: ";
                    stock = ui.getValidInt();

                    cout << "Enter product ID: ";
                    productID = ui.getValidInt();
                    while (inv.containsId(productID)) {
                        cout << endl;
                        cout << "ID in use. Please type another ID here: ";
                        productID = ui.getValidInt();
                    }

                    cout << "Enter auhtor: ";
                    author = ui.getValidString();

                    cout << "Enter genre (Fantasy, Horror): ";
                    genre = ui.getValidString();

                    // Create JSON object
                    product* bookItem = new Book(name, price, stock, productID, author, genre);
                    //Add to inventory
                    
                    inv.addProduct(bookItem);
                    inv.saveInventory("data/products.json");
                }
                else if (userChoice == 2) {
                    cout << "==========================" << endl;
                    cout << "       Adding Games       " << endl;
                    cout << "==========================" << endl;
                    
                    string name, platform, genre;
                    double price;
                    int productID, stock;

                    // Prompt user for input
                    cout << "Enter product name (dupes will overide): ";
                    name = ui.getValidString();

                    cout << "Enter price: ";
                    price = ui.getValidDouble(2);

                    cout << "Enter stock quantity: ";
                    stock = ui.getValidInt();

                    cout << "Enter product ID: ";
                    productID = ui.getValidInt();
                    while (inv.containsId(productID)) {
                        cout << endl;
                        cout << "ID in use. Please type another ID here: ";
                        productID = ui.getValidInt();
                    }

                    cout << "Enter genre (e.g., FPS, RPG): ";
                    genre = ui.getValidString();

                    cout << "Enter Platform (PC, PS5, XBOX): ";
                    platform = ui.getValidString();

                    // Create JSON object
                    product* gameItem = new Game(name, price, stock, productID, platform, genre);
                    // Add to inventory
                    inv.loadInventory("data/products.json");
                    inv.addProduct(gameItem);
                    inv.saveInventory("data/products.json");
                }
                else if (userChoice == 3) {
                    
                    cout << "==========================" << endl;
                    cout << "      Adding Clothing     " << endl;
                    cout << "==========================" << endl;

                    string name, gender, size, color, clothingType;
                    double price;
                    int productID, stock;
                    inv.loadInventory("data/products.json");

                    // Prompt user for input
                    cout << "Enter product name (dupes will overide): ";
                    name = ui.getValidString();

                    cout << "Enter price: ";
                    price = ui.getValidDouble(2);

                    cout << "Enter stock quantity: ";
                    stock = ui.getValidInt();

                    cout << "Enter product ID: ";
                    productID = ui.getValidInt();
                    while (inv.containsId(productID)) {
                        cout << endl;
                        cout << "ID in use. Please type another ID here: ";
                        productID = ui.getValidInt();
                    }

                    cout << "Enter gender (e.g., Male/Female/Unisex): ";
                    gender = ui.getValidString();

                    cout << "Enter size (e.g., S, M, L, XL): ";
                    size = ui.getValidString();

                    cout << "Enter color: ";
                    color = ui.getValidString();

                    cout << "Enter clothing type (e.g., T-Shirt, Jacket): ";
                    clothingType = ui.getValidString();

                    // Create JSON object
                    product* clothingItem = new clothes(name, price, stock, productID, gender, size, color, clothingType);
                    // Add to inventory
                    inv.addProduct(clothingItem);
                    inv.saveInventory("data/products.json");
                } 
                else if (userChoice == 4) {
                    
                    cout << "==========================" << endl;
                    cout << "      Adding Food     " << endl;
                    cout << "==========================" << endl;

                    string name, expDate;
                    double price;
                    int productID, stock;

                    // Prompt user for input
                    cout << "Enter product name (dupes will overide): ";
                    getline(cin >> std::ws, name);

                    cout << "Enter price: ";
                    price = ui.getValidDouble(2);

                    cout << "Enter stock quantity: ";
                    stock = ui.getValidInt();

                    cout << "Enter product ID: ";
                    productID = ui.getValidInt();
                    while (inv.containsId(productID)) {
                        cout << endl;
                        cout << "ID in use. Please type another ID here: ";
                        productID = ui.getValidInt();
                    }

                    cout << "Enter expiration date: ";
                    expDate = ui.getValidString();

                    // Create JSON object
                    product* foodItem = new food(name, price, stock, productID, expDate);
                    // Add to inventory
                    inv.addProduct(foodItem);
                    inv.saveInventory("data/products.json");
                }
                else currentScreen = INVENTORY_OPTIONS_ADMIN;
                userChoice = 0;
                break;
            
            case ADMIN_CATALOG:
                system("clear");
                ui.showLoadedProductsAdmin();
                userChoice = ui.getValidInput(2); // Assuming 1 for Add to Cart, 2 for Back
                if (userChoice == 1) {
                    // Logic to add item to cart
                    currentScreen = ADMIN_CATALOG; // Stay in catalog after adding
                } else {
                    currentScreen = INVENTORY_OPTIONS_ADMIN; // Go back to inventory options
                }
                userChoice = 0; // Reset user choice for next screen
                break;

            case ADMIN_LOW_STOCK:
                system("clear");
                inv.loadInventory("data/products.json");
                inv.adminNotif();
                cout << "1. Add More Stock\n";
                cout << "2. Back\n";
                userChoice = ui.getValidInput(2);
                if (userChoice == 1) {
                    inv.loadInventory("data/products.json");
                    cout << "Please give ID: \n";
                    int id;
                    while (true) {
                        id = ui.getValidInt();
                        if (!inv.containsId(id)) {
                            cout << "That productID was not found inside inventory. Try again.\n";
                        } else {
                            break;
                        }
                    }
                    product* p = inv.getProduct(id);
                    cout << "How many do you want to add?: \n";
                    int newQuantity = p->getProductStock() + ui.getValidInt();
                    p->setProductStock(newQuantity);
                    inv.saveInventory("data/products.json");
                } else {
                    currentScreen = INVENTORY_OPTIONS_ADMIN;
                }
            userChoice = 0;
            break;
        }
    }       
}

int main() {
    UIManager ui;
    int userChoice = 0;
    string objType;
    system("clear");

    Login loginSystem;

    cout << "==========================" << endl;
    cout << "   Secure Login System    " << endl;
    cout << "==========================" << endl;

    int userType = loginSystem.run();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (userType == 1) {
        Screen currentScreen = INVENTORY_OPTIONS_CUSTOMER;
        customerUI(ui, currentScreen, userChoice, objType);
    } else {
        Screen currentScreen = INVENTORY_OPTIONS_ADMIN;
        adminUI(ui, currentScreen, userChoice);
    }
    return 0;
}
