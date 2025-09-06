#include "../include/Cart.h"
#include <algorithm>
#include <iostream>

int Cart::size() const {
    return cartItems.size();
}

void Cart::addProduct(const int productID, const int quantity) {
    if (quantity <= 0) {
        throw std::runtime_error("Cannot have negative or zero quantity when adding product to cart.");
    }

    product* product = inv.getProduct(productID);
    const int stock = product->getProductStock();

    if (stock < quantity) {
        throw std::runtime_error("Attempted to add an amount of products exceeding stock in inventory.");
    }

    // remove product from current inventory
    product->setProductStock(stock - quantity);

    // Add product to cart
    auto cartIt = cartItems.find(productID);
    if (cartIt == cartItems.end()) {
        // product is not already in cart
        cartItems[productID] = quantity;
    } else {
        // product is already in cart
        cartItems[productID] += quantity;
    }

}

void Cart::removeProduct(const int productID) {
    auto cartIt = cartItems.find(productID);
    if (cartIt == cartItems.end()) {
        throw std::runtime_error("Tried to remove product with non-existent ID(" + std::to_string(productID) + ")");
    }
    // add product back to inventory
    product* product = inv.getProduct(productID);
    const int quantity = cartItems[productID];
    product->setProductStock(product->getProductStock() + quantity);
    cartItems.erase(productID);
}

void Cart::checkout() {
    // products in CartItems are already removed from inventory
    cartItems.clear();
}

Cart::~Cart() {
    vector<int> productIDs;
    for (auto it = cartItems.begin(); it != cartItems.end(); ++it) {
        productIDs.push_back(it->first);
    }
    for (int productID : productIDs) {
        removeProduct(productID);
    }
}

int Cart::getQuantity(const int productID) const {
    auto cartIt = cartItems.find(productID);
    if (cartIt == cartItems.end()) {
        throw std::runtime_error("Called getQuantity() on non-existent productID (" + std::to_string(productID) + ")");
    }
    return cartIt->second;
}

std::vector<int> Cart::getProductIDs() const {
    std::vector<int> productIDs;
    for (const auto& it : cartItems) {
        productIDs.push_back(it.first);
    }
    return productIDs;
}

std::string Cart::prodTypeFreq() {
    int genCount = 0;
    int foodCount = 0;
    int clothesCount = 0;

    for (auto it = cartItems.begin(); it != cartItems.end(); ++it) {
        std::string productType = inv.getProduct(it->first)->getProductType();
        if (productType == "GENERAL") genCount++;
        else if (productType == "FOOD") foodCount++;
        else if (productType == "CLOTHES") clothesCount++;
    }

    int maxCount = std::max({genCount, foodCount, clothesCount}); // Requires C++11

    if (maxCount == foodCount) return "food";
    else if (maxCount == genCount) return "general";
    else if (maxCount == clothesCount) return "clothes";
    return "general";
}

void Cart::cartRecc(){
    if(prodTypeFreq() == "food"){
        vector<int> reccItems = inv.filterByType("FOOD");
        for(int i = 0; i < 5; i++){
            int id = reccItems.at(i);
            string productName = inv.getProduct(id)->getProductName();
            std::cout << i << ": " << productName << std::endl;
        }
    }
    else if(prodTypeFreq() == "general"){
        vector<int> reccItems = inv.filterByType("GENERAL");
        for(int i = 0; i < 5; i++){
            int id = reccItems.at(i);
            string productName = inv.getProduct(id)->getProductName();
            std::cout << i << ": " << productName << std::endl;
        }
    }
    else if(prodTypeFreq() == "clothes"){
        vector<int> reccItems = inv.filterByType("CLOTHES");
        for(int i = 0; i < 5; i++){
            int id = reccItems.at(i);
            string productName = inv.getProduct(id)->getProductName();
            std::cout << i << ": " << productName << std::endl;
        }
    }
}

double Cart::cost() const {
    double total = 0;
    for (auto it = cartItems.begin(); it != cartItems.end(); ++it) {
        int productID = it->first;
        int quantity = it->second;
        double price = inv.getProduct(productID)->getProductPrice();
        total += quantity * price;
    }
    return total;
}

bool Cart::containsProduct(const int productID) const {
    for (const auto& it : cartItems) {
        if (it.first == productID) {
            return true;
        }
    }
    return false;
}