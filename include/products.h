#pragma once

#include <string>
#include "json.hpp"
using json = nlohmann::json;
using std::string;

class product {
    protected:
        static const string productTypes[5];
        string productType;
    private:
        string productName;
        double productPrice;
        int productStock;
        int productID;
    public:
        product(const string& name, double price, int quantity, int id);
        // Ensure proper cleanup of derived classes when deleted through parent class pointer
        virtual ~product() { return; }

        string getProductName() const { return productName;}
        double getProductPrice() const { return productPrice;}
        int getProductStock() const { return productStock;}
        int getProductID() const { return productID;}
        string getProductType() const { return productType;}
        
        void setProductName(const string& name) { productName = name;}
        void setProductPrice(double price) { productPrice = price;}
        void setProductStock(int stock) { productStock = stock;}
        void setProductID(const int id) { productID = id;}
        virtual json toJson() const;
        virtual void printProductInfo() const;
};

class food : public product {
    private:
        string expirationDate;
        bool expired;
    public:
        food(const string& name, double price, int quantity, int id, const string& expDate);
        json toJson() const override;
        string getExpirationDate() const { return expirationDate;}
        bool isExpired() const  { return expired;}
        void setExpirationDate(const string& expDate) { expirationDate = expDate;}
        void printProductInfo() const override;
};

class clothes: public product {
    private:
        string clothingGender;
        string clothingSize;
        string clothingColor;
        string clothingType;
    public:
        clothes(const string& name, double price, int quantity, int id, const string& gender, const string& size, const string& color, const string& clothingType);
        json toJson() const override;
        void setSize(const string& size) { this->clothingSize = size; };
        void setGender(const string& gender) { this->clothingGender = gender; }; 
        void setColor(const string& color) { this->clothingColor = color; }; 
        void setClothingType(const string& clothingType) { this->clothingType = clothingType; }; 
        string getSize() const { return clothingSize; };
        string getColor() const { return clothingColor; };
        string getGender() const {return clothingGender; };
        string getType() const {return clothingType; };
        void printProductInfo() const override; 
};

class Book : public product {
private:
    string author;
    string genre;

public:
    Book(const string& name, double price, int quantity, int id,
         const string& bookAuthor, const string& bookGenre);

    json toJson() const override;
    void printProductInfo() const override;

    void setAuthor(const string& author) { this->author = author; }
    void setGenre(const string& genre) { this->genre = genre; }

    string getAuthor() const { return author; }
    string getGenre() const { return genre; }
};

class Game : public product {
private:
    string platform;
    string genre;

public:
    Game(const string& name, double price, int quantity, int id,
         const string& gamePlatform, const string& gameGenre);

    json toJson() const override;
    void printProductInfo() const override;

    void setPlatform(const string& platform) { this->platform = platform; }
    void setGenre(const string& genre) { this->genre = genre; }

    string getPlatform() const { return platform; }
    string getGenre() const { return genre; }
};
