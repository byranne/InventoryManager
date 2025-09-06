#pragma once

#include "products.h"
#include "FileManager.h"
#include <vector>
#include <stdexcept>
#include <iostream>

using std::vector;

class Inventory {
private:
    vector<product*> products;
public:
    void saveInventory(const string& fileName) const;
    void clearProducts();
    ~Inventory();
    void loadInventory(const string& fileName);
    void removeProduct(const int productID);
    vector<int> filterByType(const string& typeName) const;
    vector<int> searchByName(const string& searchName, const int limit) const;
    product* getProduct(const int productID);
    product* getProduct(const int productID) const;
    void addProduct(product* newProduct);
    void adminNotif();
    bool containsId(const int productID);
};
