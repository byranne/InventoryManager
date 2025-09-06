#include "FileManager.h"
#include <vector>
#include <string>
#include "products.h"
#include "ProductFactory.h"
#include <iomanip>
#include <fstream>

using std::vector;

// (1) Keep loadJson definition here if it was in the header:
json loadJson(const string& filename) {
    std::ifstream inFS(filename);
    json data = json::parse(inFS);
    inFS.close();
    return data;
}

// (2) Put exactly this definition here—do not change variable names or types:
vector<product*> FileManager::loadProducts(const string& fileName) const {
    vector<product*> products;
    json data = loadJson(fileName);
    ProductFactory f;
    for (const json& productData : data) {
        const string productType = productData["productType"];
        product* newProduct = f.createProduct(productType, productData);
        products.push_back(newProduct);
    }
    return products;
}

// (3) Similarly, move saveToFile(...) into this same .cpp:
void FileManager::saveToFile(const string& fileName, const vector<product*>& products) const {
    json data = json::array();
    for (const product* p : products) {
        data.push_back(p->toJson());
    }
    std::ofstream outFS(fileName);
    outFS << std::setw(4) << data << "\n";
    outFS.close();
}
