#include "gtest/gtest.h"
#include "../include/Inventory.h"
#include "../include/products.h"
#include "../include/json.hpp"
#include "../include/Cart.h"
#include "../include/Login.h"
#include <stdexcept>
#include <vector>

using json = nlohmann::json;
using std::vector;

template<typename T>
bool contains(const T& find, const vector<T>& values);

TEST(ProductTests, AccessorFunctionsTests){
    string name = "Basic";
    double price = 1.00;
    int stock = 3, id = 0;
    product product1(name, price, stock, id);
    EXPECT_EQ(name, product1.getProductName());
    EXPECT_EQ(price, product1.getProductPrice());
    EXPECT_EQ(stock, product1.getProductStock());
    EXPECT_EQ(id, product1.getProductID());
}

TEST(InventoryTests, addProduct_Good) {
    // Normal test
    int id = 1000;
    Inventory inv;
    product* newProduct1 = new product("Basic", 1.00, 3, id);
    inv.addProduct(newProduct1);
    EXPECT_EQ(inv.getProduct(id), newProduct1);
}

TEST(InventoryTests, addProduct_nullptr) {
    // Testing the addition of nullptr
    int id = 1000;
    Inventory inv;
    product* newProduct1 = nullptr;
    EXPECT_THROW({
        inv.addProduct(newProduct1);
    }, std::runtime_error);
}

TEST(InventoryTests, addProduct_same_productID) {
    int id = 1000;
    Inventory inv;
    // Created two products with the same id
    product* newProduct1 = new product("Basic", 1.00, 3, id);
    product* newProduct2 = new product("Basic2", 1.00, 3, id);
    inv.addProduct(newProduct1);
    // Cannot add two products with the same id to inventory
    EXPECT_THROW({
        inv.addProduct(newProduct2);
    }, std::runtime_error);
    delete newProduct2;
}

TEST(InventoryTests, getProduct_emptyInv) {
    // Calling getProduct on invalid productID
    Inventory inv;
    EXPECT_THROW({
        // There are no products inside inventory, so getProduct should fail
        inv.getProduct(1000);
    }, std::runtime_error);
}

TEST(InventoryTests, removeProduct_Good) {
    Inventory inv;
    int id = 1000;
    product* newProduct1 = new product("Basic", 1.00, 3, id);
    inv.addProduct(newProduct1);
    inv.removeProduct(id);
    // product should no longer exist, so this should error.
    EXPECT_THROW({
        inv.getProduct(id);
    }, std::runtime_error);
}

TEST(InventoryTests, removeProduct_2) {
    EXPECT_THROW({
        Inventory inv;
        // There are no products in inventory, so this fails.
        inv.removeProduct(1000);
    }, std::runtime_error);
}

TEST(InventoryTests, searchByName) {
    Inventory inv;
    product* newProduct1 = new product("Basic", 1.00, 3, 1000);
    product* newProduct2 = new product("Hello", 1.00, 3, 1001);
    product* newProduct3 = new product("Hello2", 1.00, 3, 1002);
    inv.addProduct(newProduct1);
    inv.addProduct(newProduct2);
    inv.addProduct(newProduct3);
    vector<int> found = inv.searchByName("llo", 999);
    // product1 and 2 contain "llo" in their anmes.
    EXPECT_EQ(found.size(), 2);
    EXPECT_EQ(found[0], newProduct2->getProductID());
    EXPECT_EQ(found[1], newProduct3->getProductID());
}

TEST(InventoryTests, clearProducts) {
    Inventory inv;
    product* newProduct1 = new product("Basic", 1.00, 3, 1000);
    product* newProduct2 = new product("Hello", 1.00, 3, 1001);
    product* newProduct3 = new product("Hello2", 1.00, 3, 1002);
    inv.addProduct(newProduct1);
    inv.addProduct(newProduct2);
    inv.addProduct(newProduct3);
    inv.clearProducts(); // Delete all products
    // There should be no items in inventory.
    EXPECT_EQ(inv.searchByName("", 999).size(), 0);
}

TEST(InventoryTests, filterByType) {
    Inventory inv;
    product* newProduct1 = new product("Basic", 1.00, 3, 1000);
    product* newProduct2 = new clothes("Blue Jeans", 1.00, 3, 1001, "Male", "Large", "Red", "Pants");
    product* newProduct3 = new product("Hello2", 1.00, 3, 1002);
    inv.addProduct(newProduct1);
    inv.addProduct(newProduct2);
    inv.addProduct(newProduct3);
    vector<int> productIDs = inv.filterByType("GENERAL");
    // There are only two products with the type "GENERAL"
    EXPECT_EQ(productIDs[0], 1000);
    EXPECT_EQ(productIDs[1], 1002);
}

TEST(InventoryTests, containsID_True) {
    int id = 1000;
    Inventory inv;
    product* newProduct1 = new product("Basic", 1.00, 3, id);
    inv.addProduct(newProduct1);
    EXPECT_TRUE(inv.containsId(id));
}

TEST(InventoryTests, containsID_False) {
    int id = 1000;
    int falseID = -999; // non-existent ID
    Inventory inv;
    product* newProduct1 = new product("Basic", 1.00, 3, id);
    inv.addProduct(newProduct1);
    EXPECT_FALSE(inv.containsId(falseID));
}

TEST(CartTests, Cart_addProduct_Good) {
    Inventory inv;
    int stock = 100;
    int id = 1000;
    product* newProduct1 = new product("Basic", 1.00, stock, id);
    inv.addProduct(newProduct1);

    int quantity = 11;
    Cart cart(inv);
    cart.addProduct(id, quantity); // Inventory stock should decrease
    int newStock = stock-quantity; 
    EXPECT_EQ(inv.getProduct(id)->getProductStock(), newStock); // Confirm decrease
}

TEST(CartTests, Cart_addProduct_TooLarge) {
    Inventory inv;
    int stock = 10;
    int id = 1000;
    product* newProduct1 = new product("Basic", 1.00, stock, id);
    inv.addProduct(newProduct1);

    int quantity = 111;
    ASSERT_TRUE(quantity > stock);
    EXPECT_THROW({
        Cart cart(inv);
        cart.addProduct(id, quantity); // Cannot take more from Inventory than what it alr has
    }, std::runtime_error);
}

TEST(CartTests, Cart_addProduct_Negative) {
    Inventory inv;
    inv.loadInventory("data//productTests.json");
    int quantity = -50;
    ASSERT_TRUE(quantity < 0);
    // Cannot add negative quantity, so error
    EXPECT_THROW({
        Cart cart(inv);
        cart.addProduct(1000, -50);
    }, std::runtime_error);
}

TEST(CartTests, Cart_removeProduct_badID) {
    Inventory inv;
    // There are no ids that are negative.
    int id = -1000;
    // Removing a non-existent ID results in error.
    EXPECT_THROW({
        Cart cart(inv);
        cart.removeProduct(id);
    }, std::runtime_error);
}

TEST(CartTests, Cart_removeProductGood) {
    Inventory inv;
    inv.loadInventory("data//productTests.json");
    // Adds two products with good ID's
    int id1 = 1001, id2 = 1002;
    Cart cart(inv);
    cart.addProduct(id1, 1);
    cart.addProduct(id2, 1);
    // Removes two Products from inventory
    cart.removeProduct(id1);
    cart.removeProduct(id2);
    // Removing both products should result in those items not in the cart
    EXPECT_FALSE(cart.containsProduct(id1));
    EXPECT_FALSE(cart.containsProduct(id2));
}

TEST(CartTests, Cart_checkout) {
    Inventory inv;
    inv.loadInventory("data//productTests.json");
    // Adds two products with good ID's
    int id1 = 1001, id2 = 1002;
    Cart cart(inv);
    cart.addProduct(id1, 1);
    cart.addProduct(id2, 1);
    // Checks for correct size
    ASSERT_EQ(cart.size(), 2);
    cart.checkout(); // Should clear all items in cart
    EXPECT_EQ(cart.size(), 0); // Confirm no items in cart
}

TEST(CartTests, Cart_getQuantity) {
    Inventory inv;
    inv.loadInventory("data//productTests.json");
    // Adds product with good ID and quantity
    int id = 1001, quantity = 10;
    Cart cart(inv);
    // Creats product with id and 10 stock
    cart.addProduct(id, quantity);
    // getQuantity will be 10
    EXPECT_EQ(cart.getQuantity(1001), quantity);
}

TEST(CartTests, Cart_getProductIDs) {
    Inventory inv;
    inv.loadInventory("data//productTests.json");
    int id1 = 1001, id2 = 1002, id3 = 1003;
    Cart cart(inv);
    cart.addProduct(id1, 1);
    cart.addProduct(id2, 1);
    cart.addProduct(id3, 1);
    // Get productIDs of all items in cart
    std::vector<int> productIDs = cart.getProductIDs();
    ASSERT_EQ(productIDs.size(), 3);
    EXPECT_TRUE(contains(id1, productIDs));
    EXPECT_TRUE(contains(id2, productIDs));
    EXPECT_TRUE(contains(id3, productIDs));
}

TEST(CartTests, cost_noItems) {
    Inventory inv;
    Cart cart(inv);
    // If there are no items in cart, then cost should be zero
    EXPECT_EQ(cart.cost(), 0);
}

TEST(CartTests, Cart_costBig) {
    Inventory inv;
    inv.loadInventory("data//productTests.json");
    int id1 = 1001, id2 = 1002, id3 = 1003;
    int quantity1 = 1, quantity2 = 2, quantity3 = 3;
    double price1 = inv.getProduct(id1)->getProductPrice();
    ASSERT_NEAR(price1, 19.99, 0.001);

    double price2 = inv.getProduct(id2)->getProductPrice();
    ASSERT_NEAR(price2, 0.99, 0.001);

    double price3 = inv.getProduct(id3)->getProductPrice();
    ASSERT_NEAR(price3, 15.99, 0.001);

    Cart cart(inv);
    cart.addProduct(id1, quantity1);
    cart.addProduct(id2, quantity2);
    cart.addProduct(id3, quantity3);

    double totalCost = 69.94;
    EXPECT_NEAR(cart.cost(), totalCost, 0.001);
}

TEST(CartTests, Cart_clearProducts) {
    Inventory inv;
    inv.loadInventory("data//productTests.json");
    int id = 1001;
    int origStock = inv.getProduct(id)->getProductStock();
    {
        int quantity = 10;
        Cart cart(inv);
        cart.addProduct(1001, quantity);
        EXPECT_EQ(inv.getProduct(id)->getProductStock(), origStock - quantity);
    }
    // Items in cart are added back to inventory if cart goes out of scope.
    EXPECT_EQ(inv.getProduct(id)->getProductStock(), origStock);
}

template<typename T>
bool contains(const T& find, const vector<T>& values) {
    for (const T& value: values) {
        if (find == value) {
            return true;
        }
    }
    return false;
}

TEST(LoginTest, UsernameIsStoredAndReturned) {
    Login login;
    std::string inputName = "TestUser";

    // Simulate internal behavior
    login.getUserName(inputName);

    // Verify userName() returns what was set
    EXPECT_EQ(login.userName(), inputName);
}