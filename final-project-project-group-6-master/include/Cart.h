#pragma once
#include "products.h"
#include <unordered_map>
#include <stdexcept>
#include <string>
#include "Inventory.h"
#include <vector>

class Cart {
private:
    std::unordered_map<int, int> cartItems;
    Inventory& inv;
public:
    Cart(Inventory& inv) : inv(inv) {};
    ~Cart();
    void addProduct(const int, const int);
    void removeProduct (const int);
    void checkout();
    int getQuantity(const int) const;
    int size() const;
    std::vector<int> getProductIDs() const;
    std::string prodTypeFreq();
    void cartRecc();
    double cost() const;
    bool containsProduct(const int) const;
};