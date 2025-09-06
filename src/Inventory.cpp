#include "../include/Inventory.h"
#include "../include/products.h"
#include "../include/FileManager.h"
#include <vector>
#include <stdexcept>
#include <iostream>

using std::vector;

void Inventory::saveInventory(const string& fileName) const {
        FileManager fm;
        fm.saveToFile(fileName, products);
    }

void Inventory::clearProducts() {
        for (product* product: products) {
            delete product;
        }
        products.clear();
    }

Inventory::~Inventory(){
    clearProducts();
}

void Inventory::loadInventory(const string& fileName) {
    clearProducts();
    FileManager fm;
    products = fm.loadProducts(fileName);
}

void Inventory::removeProduct(const int productID) {
    size_t i;
    for (i = 0; i < products.size(); ++i) {
        if (products[i]->getProductID() == productID) {
            delete products[i];
            products.erase(products.begin()+i);
            return;
        }
    }
    throw std::runtime_error("Attempted to remove product with non-existent ID - " + std::to_string(productID));
}

vector<int> Inventory::filterByType(const string& typeName) const {
    vector<int> filtered;
    for (product* product : products) {
        if (product->getProductType() == typeName) {
            filtered.push_back(product->getProductID());
        }
    }
    return filtered;
}

vector<int> Inventory::searchByName(const string& searchName, const int limit) const {
    vector<int> filtered;
    for (product* product : products) {
        if (product->getProductName().find(searchName)  != std::string::npos && product->getProductStock() > 0) {
            filtered.push_back(product->getProductID());
        }
        if (filtered.size() == limit) {
            break;
        }
    }
    return filtered;
}

product* Inventory::getProduct(const int productID) {
    for (product* product : products) {
        if (product->getProductID() == productID) {
            return product;
        }
    }
    throw std::runtime_error("Called getProduct with non-existent product ID - " + std::to_string(productID));
}

product* Inventory::getProduct(const int productID) const {
    for (product* product : products) {
        if (product->getProductID() == productID) {
            return product;
        }
    }
    throw std::runtime_error("Called getProduct with non-existent product ID - " + std::to_string(productID));
}

void Inventory::addProduct(product* newProduct) {
    if (newProduct == nullptr) {
        throw std::runtime_error("Cannot add nullptr to inv");
    } else if (containsId(newProduct->getProductID())) {
        throw std::runtime_error("Tried to add product to inventory with productID that already exists.");
    }
    products.push_back(newProduct);
}

void Inventory::adminNotif(){
    std::cout << "Low Stock: \n";
    std::cout << " \n---------------------------------\n";
    for(product* product : products) {
        if(product->getProductStock() <= 5){
            product->printProductInfo();
            std::cout << "---------------------------------\n";
        }
    }
}

bool Inventory::containsId(const int productID) {
    size_t i;
    for (i = 0; i < products.size(); ++i) {
        if (products[i]->getProductID() == productID) {
            return true;
        }
    }
    return false;
}