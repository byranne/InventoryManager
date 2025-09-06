#include "../include/products.h"
#include <string>
#include <iostream>

using std::string;
using std::cout;

const string product::productTypes[] = {
    "GENERAL",
    "FOOD",
    "CLOTHES",
    "BOOK",
    "GAME"
};

// Constructor
product::product(const string &name, double price, int stock, int id)
: productName(name), productPrice(price), productStock(stock), productID(id), productType("GENERAL") {
}

// Print Product Info
void product::printProductInfo() const {
    std::cout << std::fixed << std::setprecision(2) << "Product Name: " << productName << "\n"
              << "Product Price: $" << productPrice << "\n"
              << "Product Stock: " << productStock << "\n"
              << "Product ID: " << productID << "\n";
}

json product::toJson() const{
    json productData = {};
    productData["productID"] = getProductID();
    productData["productName"] = getProductName();
    productData["price"] = getProductPrice();
    productData["stock"] = getProductStock();
    productData["productType"] = getProductType();
    return productData;
}

// Food Constructor
food::food(const string& name, double price, int quantity, int id, const string& expDate)
: product(name, price, quantity, id), expirationDate(expDate), expired(false) {
    this->productType = "FOOD";
}

// Food printProductInfo override
void food::printProductInfo() const {
    product::printProductInfo();
    std::cout << "Expiration Date: " << expirationDate << "\n"
              << "Expired: " << expired << "\n";
}

json food::toJson() const {
    json productData = product::toJson();
    productData["expirationDate"] = getExpirationDate();
    return productData;
}

clothes::clothes(const string& name, double price, int quantity, int id, const string& gender, const string& size, const string& color, const string& clothingType)
: product(name, price, quantity, id), clothingGender(gender), clothingSize(size), clothingColor(color), clothingType(clothingType) {
    this->productType = "CLOTHES";
}


void clothes::printProductInfo() const {
    product::printProductInfo();
    std::cout << "Gender: " << clothingGender << std::endl;
    std::cout << "Size: " << clothingSize << std::endl;
    std::cout << "Color: " << clothingColor << std::endl;
    std::cout << "Type: " << clothingType << std::endl;
}

json clothes::toJson() const {
    json productData = product::toJson();
    productData["gender"] = getGender();
    productData["size"] = getSize();
    productData["color"] = getColor();
    productData["clothingType"] = getType();
    return productData;
}


Book::Book(const string& name, double price, int quantity, int id, const string& bookAuthor, const string& bookGenre)
: product(name, price, quantity, id), author(bookAuthor), genre(bookGenre) {
    this->productType = "BOOK";
}

void Book::printProductInfo() const {
    product::printProductInfo();
    std::cout << "Author: " << author << std::endl;
    std::cout << "Genre: " << genre << std::endl;
}

json Book::toJson() const {
    json productData = product::toJson();
    productData["author"] = getAuthor();
    productData["genre"] = getGenre();
    return productData;
}

Game::Game(const string& name, double price, int quantity, int id, const string& gamePlatform, const string& gameGenre) 
: product(name, price, quantity, id), platform(gamePlatform), genre(gameGenre) {
    this->productType = "GAME"; 
}

void Game::printProductInfo() const {
    product::printProductInfo();
    std::cout << "Platform: " << platform << std::endl;
    std::cout << "Genre: " << genre << std::endl;
}

json Game::toJson() const {
    json productData = product::toJson();
    productData["platform"] = getPlatform();
    productData["genre"] = getGenre();
    return productData;
}
