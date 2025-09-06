#pragma once
#include <stdexcept>
#include "products.h"

class ProductFactory {
public:
    product* createProduct(const string& productType, const json& productData) {
        const string productName = productData["productName"];
        const double price = productData["price"];
        const int productID = productData["productID"];
        const int stock = productData["stock"];

        if (productType == "GENERAL") {
            return new product(productName, price, stock, productID);
        } else if (productType == "CLOTHES") {
            const string gender = productData["gender"];
            const string size = productData["size"];
            const string color = productData["color"];
            const string clothingType = productData["clothingType"];
            return new clothes(productName, price, stock, productID, gender, size, color, clothingType);
        } else if (productType == "FOOD") {
            const string expirationDate = productData["expirationDate"];
            return new food(productName, price, stock, productID, expirationDate);
        } else if (productType == "BOOK") {
            const string author = productData["author"];
            const string genre = productData["genre"];
            return new Book(productName, price, stock, productID, author, genre);
        } else if (productType == "GAME") {
            const string platform = productData["platform"];
            const string genre = productData["genre"];
            return new Game(productName, price, stock, productID, platform, genre);
        } else {
            throw std::runtime_error("Unknown product type: " + productType);
        }
    }
};