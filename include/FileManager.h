#pragma once
#include <vector>
#include <string>
#include "products.h"
#include "ProductFactory.h"
#include <iomanip>

class product;
class FileManager {
public:
    void saveToFile(const std::string& filename, const std::vector<product*>&) const;
    std::vector<product*> loadProducts(const std::string& filename) const;
};

nlohmann::json loadJson(const std::string& filename);
